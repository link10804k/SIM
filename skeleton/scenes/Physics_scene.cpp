#include "Physics_scene.h"

#include <cmath>
#include <immintrin.h>
#include <cassert>

Physics_scene::Physics_scene(std::string name) : Scene(name) {
    memset(act, false, sizeof(act));
    memset(act_force_gens, false, sizeof(act_force_gens));
}

void Physics_scene::update(double dt) {
    for (int i = 0; i < num_particles; ++i) {
        // Kill expired particles
        lif[i] -= dt;
        if (lif[i] <= 0) act[i] = false;

        // Clean acc accumulator
        forc.x[i] = 0;
        forc.y[i] = 0;
        forc.z[i] = 0;
    }
    
    for (int i = 0; i < num_force_generators; ++i) {
        if (act_force_gens[i])
            force_generators[i]->apply_force(*this, dt);
    }

    integrate(dt);

    render();
}

void Physics_scene::render() {
    startRender(GetCamera()->getEye(), GetCamera()->getDir());
    for (int i = 0; i < num_particles; ++i) {
        if (act[i]) {
            renderShape(*particle_shape, { {tr.pos.x[i], tr.pos.y[i], tr.pos.z[i]}, 
                {tr.qua.x[i], tr.qua.y[i], tr.qua.z[i], tr.qua.w[i]} }, { col.x[i], col.y[i], col.z[i], col.w[i] });
        }
    }
    finishRender();
}

void Physics_scene::add_particle(Vector3 p, Vector3 v, float d, float m, float l, Vector4 c, std::array<bool, MAX_FORCE_GENERATORS> force_gens_to_subscribe) {
    if (num_particles != MAX_PARTICLES) {
        tr.pos.x[num_particles] = p.x;
        tr.pos.y[num_particles] = p.y;
        tr.pos.z[num_particles] = p.z;

        tr.qua.x[num_particles] = 0;
        tr.qua.y[num_particles] = 0;
        tr.qua.z[num_particles] = 0;
        tr.qua.w[num_particles] = 1;

        vel.x[num_particles] = v.x;
        vel.y[num_particles] = v.y;
        vel.z[num_particles] = v.z;

        forc.x[num_particles] = 0.0f;
        forc.y[num_particles] = 0.0f;
        forc.z[num_particles] = 0.0f;

        acc.x[num_particles] = 0.0f;
        acc.y[num_particles] = 0.0f;
        acc.z[num_particles] = 0.0f;

        dam[num_particles] = d;

        mas[num_particles] = m;
        wmas[num_particles] = 1.0f / m;

        lif[num_particles] = l;

        act[num_particles] = true;

        col.x[num_particles] = c.x;
        col.y[num_particles] = c.y;
        col.z[num_particles] = c.z;
        col.w[num_particles] = c.w;

        for (int i = 0; i < MAX_FORCE_GENERATORS; ++i)
            subscribed_force_gens[num_particles][i] = force_gens_to_subscribe[i];

        ++num_particles;
    }
}

void Physics_scene::kill_all_particles() {
    memset(act, false, sizeof(act));
    num_particles = 0;
}

void Physics_scene::integrate(double dt) {
    // TODO: usar simd
    for (int i = 0; i < num_particles; ++i) { // TODO: Cambiar a i += 8 para el simd 
        // Integrador Euler Semi-implícito
        if (act[i]) {
            // Aplicación de la fuerza acumulada
            acc.x[i] = forc.x[i] * wmas[i];
            acc.y[i] = forc.y[i] * wmas[i];
            acc.z[i] = forc.z[i] * wmas[i];

            vel.x[i] = vel.x[i] + (acc.x[i] * dt);
            vel.y[i] = vel.y[i] + (acc.y[i] * dt);
            vel.z[i] = vel.z[i] + (acc.z[i] * dt);
            
            tr.pos.x[i] = tr.pos.x[i] + (vel.x[i] * dt);
            tr.pos.y[i] = tr.pos.y[i] + (vel.y[i] * dt);
            tr.pos.z[i] = tr.pos.z[i] + (vel.z[i] * dt);
            
            // Damping
            vel.x[i] = vel.x[i] * std::pow(dam[i], dt);
            vel.y[i] = vel.y[i] * std::pow(dam[i], dt);
            vel.z[i] = vel.z[i] * std::pow(dam[i], dt);

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
    }
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