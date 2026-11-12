#include "Physics_scene.h"

#include <cmath>
#include <immintrin.h>
#include <cassert>
#include "../utils/memory_allocator.h"

#define RENDER(count, positions, colors) startRender(GetCamera()->getEye(), GetCamera()->getDir());\
                                        glEnable(GL_BLEND);\
                                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);\
                                        glDisable(GL_LIGHTING);\
                                        glPointSize(2.0f);\
                                        glEnableClientState(GL_VERTEX_ARRAY);\
                                        glVertexPointer(3, GL_FLOAT, 0, positions);\
                                        glEnableClientState(GL_COLOR_ARRAY);\
                                        glColorPointer(4, GL_FLOAT, 0, colors);\
                                        glDrawArrays(GL_POINTS, 0, count);\
                                        glDisableClientState(GL_COLOR_ARRAY);\
                                        glDisableClientState(GL_VERTEX_ARRAY);\
                                        glEnable(GL_LIGHTING);\
                                        glDisable(GL_BLEND);\
                                        finishRender();

Physics_scene::Physics_scene(std::string name) : Scene(name) {
    particles_struct = static_cast<Particles_struct*>(mem_alloc::heap_alloc(sizeof(Particles_struct)));
    assert(particles_struct != nullptr);

    //memset(particles_struct->act, false, sizeof(particles_struct->act));
    memset(act_force_gens, false, sizeof(act_force_gens));
    memset(act_particle_sys, false, sizeof(act_particle_sys));
}

//#include <iostream>
void Physics_scene::update(double dt) {
    scene_update(dt);

    int particles_removed = 0;

    float* positions = (float*)mem_alloc::heap_alloc(sizeof(float) * 3 * MAX_PARTICLES); // [MAX_PARTICLES * 3];
    float* colors = (float*)mem_alloc::heap_alloc(sizeof(float) * 4 * MAX_PARTICLES); // [MAX_PARTICLES * 4];
    int count = 0;

    // Sistemas de partículas
    for (int i = 0; i < num_particle_systems; ++i) {
        particle_systems[i]->update();
    }

    for (int i = 0; i < MAX_PARTICLES; ++i) {
        if (particles_struct->act[i]) {
            // Eliminar partículas expiradas
            particles_struct->lif[i] -= dt;
            if (particles_struct->lif[i] <= 0) {
                particles_struct->act[i] = false;
                ++particles_removed;
                particles_struct->free_particle_index_stack.push(i);
                continue;
            }

            // Limpiar acumulador de fuerzas
            particles_struct->forc.x[i] = 0;
            particles_struct->forc.y[i] = 0;
            particles_struct->forc.z[i] = 0;

            // Aplicar fuerzas
            for (int j = 0; j < num_force_generators; ++j) {
                if (act_force_gens[j] && particles_struct->subscribed_force_gens[i][j])
                    force_generators[j]->apply_force(dt, i);
            }

            // Integrar
            integrate(dt, i);

            // Insertar en array para el renderizado
            positions[count * 3] = particles_struct->tr.pos.x[i];
            positions[count * 3 + 1] = particles_struct->tr.pos.y[i];
            positions[count * 3 + 2] = particles_struct->tr.pos.z[i];

            colors[count * 4] = particles_struct->col.x[i];
            colors[count * 4 + 1] = particles_struct->col.y[i];
            colors[count * 4 + 2] = particles_struct->col.z[i];
            colors[count * 4 + 3] = particles_struct->col.w[i];

            ++count;
        }
    }
    num_particles -= particles_removed;

    // Renderizado
    RENDER(count, positions, colors)

    //std::cout << "Num Particles: " << num_particles << "\n";
    //std::cout << "Particles: " << num_particles+particles_removed << "\nParticles removed: " << particles_removed << "\nParticles now: " << num_particles << "\n";
}

void Physics_scene::add_particle(Vector3 p, Vector3 v, float d, float m, float l, Vector4 c, std::array<bool, MAX_FORCE_GENERATORS> force_gens_to_subscribe) {
    if (num_particles >= MAX_PARTICLES) return;

    int index;
    if (particles_struct->free_particle_index_stack.size() > 0) {
        index = particles_struct->free_particle_index_stack.top();
        particles_struct->free_particle_index_stack.pop();
    }
    else index = num_particles;

    particles_struct->tr.pos.x[index] = p.x;
    particles_struct->tr.pos.y[index] = p.y;
    particles_struct->tr.pos.z[index] = p.z;

    particles_struct->tr.qua.x[index] = 0;
    particles_struct->tr.qua.y[index] = 0;
    particles_struct->tr.qua.z[index] = 0;
    particles_struct->tr.qua.w[index] = 1;

    particles_struct->vel.x[index] = v.x;
    particles_struct->vel.y[index] = v.y;
    particles_struct->vel.z[index] = v.z;

    particles_struct->forc.x[index] = 0.0f;
    particles_struct->forc.y[index] = 0.0f;
    particles_struct->forc.z[index] = 0.0f;

    particles_struct->acc.x[index] = 0.0f;
    particles_struct->acc.y[index] = 0.0f;
    particles_struct->acc.z[index] = 0.0f;

    particles_struct->dam[index] = d;

    particles_struct->mas[index] = m;
    particles_struct->wmas[index] = 1.0f / m;

    particles_struct->lif[index] = l;

    particles_struct->act[index] = true;

    particles_struct->col.x[index] = c.x;
    particles_struct->col.y[index] = c.y;
    particles_struct->col.z[index] = c.z;
    particles_struct->col.w[index] = c.w;

    for (int i = 0; i < MAX_FORCE_GENERATORS; ++i)
        particles_struct->subscribed_force_gens[index][i] = force_gens_to_subscribe[i];

    ++num_particles;
}

void Physics_scene::kill_all_particles() {
    memset(particles_struct->act, false, sizeof(particles_struct->act));
    num_particles = 0;
}

void Physics_scene::integrate(double dt, int index) {
    // TODO: usar simd (con la representación actual complicado, quizás hacer if (index % 8 == 0))
    // Integrador Euler Semi-implícito
    // Aplicación de la fuerza acumulada
    particles_struct->acc.x[index] = particles_struct->forc.x[index] * particles_struct->wmas[index];
    particles_struct->acc.y[index] = particles_struct->forc.y[index] * particles_struct->wmas[index];
    particles_struct->acc.z[index] = particles_struct->forc.z[index] * particles_struct->wmas[index];

    particles_struct->vel.x[index] = particles_struct->vel.x[index] + (particles_struct->acc.x[index] * dt);
    particles_struct->vel.y[index] = particles_struct->vel.y[index] + (particles_struct->acc.y[index] * dt);
    particles_struct->vel.z[index] = particles_struct->vel.z[index] + (particles_struct->acc.z[index] * dt);
    
    particles_struct->tr.pos.x[index] = particles_struct->tr.pos.x[index] + (particles_struct->vel.x[index] * dt);
    particles_struct->tr.pos.y[index] = particles_struct->tr.pos.y[index] + (particles_struct->vel.y[index] * dt);
    particles_struct->tr.pos.z[index] = particles_struct->tr.pos.z[index] + (particles_struct->vel.z[index] * dt);
    
    // Damping
    particles_struct->vel.x[index] = particles_struct->vel.x[index] * std::pow(particles_struct->dam[index], dt);
    particles_struct->vel.y[index] = particles_struct->vel.y[index] * std::pow(particles_struct->dam[index], dt);
    particles_struct->vel.z[index] = particles_struct->vel.z[index] * std::pow(particles_struct->dam[index], dt);

    // Cargar 8 valores de velocidad
    //__m256 avx_vel_x = _mm256_loadu_ps(&vel.x[i]);
    //__m256 avx_vel_y = _mm256_loadu_ps(&vel.y[i]);
    //__m256 avx_vel_z = _mm256_loadu_ps(&vel.z[i]);
    //
    // Cargar 8 valores de aceleración
    //__m256 avx_acc_x = _mm256_loadu_ps(&acc.x[i]);
    //__m256 avx_acc_y = _mm256_loadu_ps(&acc.y[i]);
    //__m256 avx_acc_z = _mm256_loadu_ps(&acc.z[i]);
}

void Physics_scene::set_active_force_generator(int index, bool active) {
    assert(index >= 0 && index < MAX_FORCE_GENERATORS);
    act_force_gens[index] = active;
}

void Physics_scene::toggle_active_force_generator(int index) {
    assert(index >= 0 && index < MAX_FORCE_GENERATORS);
    act_force_gens[index] = !act_force_gens[index];
}

void Physics_scene::reset_force_generator(int index) {
    assert(index >= 0 && index < MAX_FORCE_GENERATORS);
    force_generators[index]->reset();
}