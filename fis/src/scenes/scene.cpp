#include "scene.h"

void Scene::update(double dt) {
    for (int i = 0; i < num_particles; ++i) {
        lif[i] -= dt;
        if (lif[i] <= 0) act[i] = false;
    }

    integrate(dt);
}

void Scene::render() {
    physx::PxShape sh = *shape;

    startRender(GetCamera()->getEye(), GetCamera()->getDir());
    for (int i = 0; i < n_particles; ++i) {
    	if (active[i]) {
    		renderShape(sh, {{tr.qua.x[i], tr.qua.y[i], tr.qua.z[i], tr.qua.w[i]}, 
                {tr.pos.x[i], tr.pos.y[i], tr.pos.z[i]}}, {col.x[i], col.y[i], col.z[i], col.w[i]});
    	}
    }
    finishRender();
}


void Scene::add_particle(Vector3 p, Vector3 v, float d, float m, float l, Vector4 c) {
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

void Scene::integrate(double dt) {
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
            vel.x[i] = vel.x[i] * std::pow(damp[i], dt);
            vel.y[i] = vel.y[i] * std::pow(damp[i], dt);
            vel.z[i] = vel.z[i] * std::pow(damp[i], dt);
        }
    }
}