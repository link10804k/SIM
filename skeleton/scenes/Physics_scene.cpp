#include "Physics_scene.h"

#include <cmath>
#include <immintrin.h>
#include <cassert>

#define RENDER(count, positions, colors) startRender(GetCamera()->getEye(), GetCamera()->getDir());\
                                        glEnable(GL_BLEND);\
                                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);\
                                        glDisable(GL_LIGHTING);\
                                        glPointSize(1.0f);\
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

//#include <iostream>
Physics_scene::Physics_scene(std::string name) : Scene(name) {
    memset(act, false, sizeof(act));
    memset(act_force_gens, false, sizeof(act_force_gens));
}

void Physics_scene::update(double dt) {
    scene_update(dt);

    int particles_removed = 0;

    float positions[MAX_PARTICLES * 3];
    float colors[MAX_PARTICLES * 4];
    int count = 0;

    // Sistemas de partículas
    for (int i = 0; i < num_particle_systems; ++i) {
        particle_systems[i]->update();
    }

    for (int i = 0; i < MAX_PARTICLES; ++i) {
        if (act[i]) {
            // Eliminar partículas expiradas
            lif[i] -= dt;
            if (lif[i] <= 0) {
                act[i] = false;
                ++particles_removed;
                free_particle_index_stack.push(i);
                continue;
            }

            // Limpiar acumulador de fuerzas
            forc.x[i] = 0;
            forc.y[i] = 0;
            forc.z[i] = 0;

            // Aplicar fuerzas
            for (int j = 0; j < num_force_generators; ++j) {
                if (act_force_gens[j] && subscribed_force_gens[i][j])
                    force_generators[j]->apply_force(dt, i);
            }

            // Integrar
            integrate(dt, i);

            // Insertar en array para el renderizado
            positions[count * 3] = tr.pos.x[i];
            positions[count * 3 + 1] = tr.pos.y[i];
            positions[count * 3 + 2] = tr.pos.z[i];

            colors[count * 4] = col.x[i];
            colors[count * 4 + 1] = col.y[i];
            colors[count * 4 + 2] = col.z[i];
            colors[count * 4 + 3] = col.w[i];

            ++count;
        }
    }
    num_particles -= particles_removed;

    // Renderizado
    RENDER(count, positions, colors)

    //std::cout << "Particles: " << num_particles+particles_removed << "\nParticles removed: " << particles_removed << "\nParticles now: " << num_particles << "\n";
}

void Physics_scene::add_particle(Vector3 p, Vector3 v, float d, float m, float l, Vector4 c, std::array<bool, MAX_FORCE_GENERATORS> force_gens_to_subscribe) {
    if (num_particles >= MAX_PARTICLES) return;

    int index;
    if (free_particle_index_stack.size() > 0) {
        index = free_particle_index_stack.top();
        free_particle_index_stack.pop();
    }
    else index = num_particles;

    tr.pos.x[index] = p.x;
    tr.pos.y[index] = p.y;
    tr.pos.z[index] = p.z;

    tr.qua.x[index] = 0;
    tr.qua.y[index] = 0;
    tr.qua.z[index] = 0;
    tr.qua.w[index] = 1;

    vel.x[index] = v.x;
    vel.y[index] = v.y;
    vel.z[index] = v.z;

    forc.x[index] = 0.0f;
    forc.y[index] = 0.0f;
    forc.z[index] = 0.0f;

    acc.x[index] = 0.0f;
    acc.y[index] = 0.0f;
    acc.z[index] = 0.0f;

    dam[index] = d;

    mas[index] = m;
    wmas[index] = 1.0f / m;

    lif[index] = l;

    act[index] = true;

    col.x[index] = c.x;
    col.y[index] = c.y;
    col.z[index] = c.z;
    col.w[index] = c.w;

    for (int i = 0; i < MAX_FORCE_GENERATORS; ++i)
        subscribed_force_gens[index][i] = force_gens_to_subscribe[i];

    ++num_particles;
}

void Physics_scene::kill_all_particles() {
    memset(act, false, sizeof(act));
    num_particles = 0;
}

void Physics_scene::integrate(double dt, int index) {
    // TODO: usar simd (con la representación actual complicado, quizás hacer if (index % 8 == 0))
    // Integrador Euler Semi-implícito
    // Aplicación de la fuerza acumulada
    acc.x[index] = forc.x[index] * wmas[index];
    acc.y[index] = forc.y[index] * wmas[index];
    acc.z[index] = forc.z[index] * wmas[index];

    vel.x[index] = vel.x[index] + (acc.x[index] * dt);
    vel.y[index] = vel.y[index] + (acc.y[index] * dt);
    vel.z[index] = vel.z[index] + (acc.z[index] * dt);
    
    tr.pos.x[index] = tr.pos.x[index] + (vel.x[index] * dt);
    tr.pos.y[index] = tr.pos.y[index] + (vel.y[index] * dt);
    tr.pos.z[index] = tr.pos.z[index] + (vel.z[index] * dt);
    
    // Damping
    vel.x[index] = vel.x[index] * std::pow(dam[index], dt);
    vel.y[index] = vel.y[index] * std::pow(dam[index], dt);
    vel.z[index] = vel.z[index] * std::pow(dam[index], dt);

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