#include "Physics_scene.h"

#include <cmath>

void Physics_scene::update(double dt) {
    for (int i = 0; i < num_particles; ++i) {
        lif[i] -= dt;
        if (lif[i] <= 0) act[i] = false;
    }

    for (int i = 0; i < num_force_generators; ++i) {
        force_generators[i].apply_force(*this);
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


void Physics_scene::add_particle(Vector3 p, Vector3 v, float d, float m, float l, Vector4 c) {
    if (num_particles != MAX_PARTICLES) {
        tr.pos.x[num_particles] = p.x;
        tr.pos.y[num_particles] = p.y;
        tr.pos.z[num_particles] = p.z;

        vel.x[num_particles] = v.x;
        vel.y[num_particles] = v.y;
        vel.z[num_particles] = v.z;

        acc.x[num_particles] = 0.0f;
        acc.y[num_particles] = 0.0f;
        acc.z[num_particles] = 0.0f;

        dam[num_particles] = d;

        mas[num_particles] = m;

        lif[num_particles] = l;

        act[num_particles] = true;

        col.x[num_particles] = c.x;
        col.y[num_particles] = c.y;
        col.z[num_particles] = c.z;
        col.w[num_particles] = c.w;

        ++num_particles;
    }
}

void Physics_scene::integrate(double dt) {
    // TODO: usar simd
    for (int i = 0; i < num_particles; ++i) {
        // Integrador Euler Semi-implícito
        if (act[i]) {
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
        }
    }
}