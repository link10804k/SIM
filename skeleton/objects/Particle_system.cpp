#include "Particle_system.h"

#include <cmath>

Particle_system::Particle_system(physx::PxTransform pos, Vector3 dir) : pos(pos), dir(dir), n_particles(0) {
	pos_dist = std::normal_distribution<float>(0.0f, 0.5f);
	speed_dist = std::normal_distribution<float>(10.0f, 5.0f);
	dir_dist = std::normal_distribution<float>(0.0f, 0.1f);
	lifetime_dist = std::normal_distribution<float>(3.0f, 0.5f);

	part_gen_dist = std::normal_distribution<float>(5, 3);
}

void Particle_system::create_particle() {
	if (n_particles != MAX_PARTICLES) {
		trans[n_particles] = physx::PxTransform(Vector3(pos.p.x + pos_dist(generator), pos.p.y + pos_dist(generator), pos.p.z + pos_dist(generator)));
		vel[n_particles] = Vector3(dir.x + dir_dist(generator), dir.y + dir_dist(generator), dir.z + dir_dist(generator)) * speed_dist(generator);
		acc[n_particles] = Vector3(0.0f, -9.8f, 0.0f);
		damp[n_particles] = 0.98f;
		mass[n_particles] = 1;
		lifetime[n_particles] = lifetime_dist(generator);
		active[n_particles] = true;

		++n_particles;
	}
}

void Particle_system::update(double dt) {
	for (int i = 0; i < n_particles; ++i) {
		// Integrador Euler Semi-implícito
		vel[i] = vel[i] + (acc[i] * dt);
		trans[i].p = (Vector3D)trans[i].p + (vel[i] * dt);

		// Damping
		vel[i] = vel[i] * std::pow(damp[i], dt);
	}

	int part_to_gen = (int)part_gen_dist(generator);
	for (int i = 0; i < part_to_gen; ++i) {
		create_particle();
	}

	startRender(GetCamera()->getEye(), GetCamera()->getDir());
	for (int i = 0; i < n_particles; ++i) {
		if (active[i]) {
			renderShape(*shape, trans[i], color);
		}
	}
	finishRender();
}