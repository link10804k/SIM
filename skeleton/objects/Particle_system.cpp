#include "Particle_system.h"

#include <cmath>

Particle_system::Particle_system(physx::PxTransform pos, Vector3 dir) : pos(pos), dir(dir), n_particles(0) {
	pos_dist = std::normal_distribution<float>(0.0f, 0.1f);
	speed_dist = std::normal_distribution<float>(10.0f, 1.0f);
	dir_dist = std::normal_distribution<float>(0.0f, 0.05f);
	lifetime_dist = std::normal_distribution<float>(7.0f, 1.0f);

	part_gen_dist = std::normal_distribution<float>(5, 1);
}

void Particle_system::create_particle() {
	int index;
	if (n_particles == MAX_PARTICLES) {
		index = 0;
	}
	else {
		index = n_particles;
		++n_particles;
	}
	trans[index] = physx::PxTransform(Vector3(pos.p.x + pos_dist(generator), pos.p.y + pos_dist(generator), pos.p.z + pos_dist(generator)));
	vel[index] = Vector3(dir.x + dir_dist(generator), dir.y + dir_dist(generator), dir.z + dir_dist(generator)) * speed_dist(generator);
	acc[index] = Vector3(0.0f, -9.8f, 0.0f);
	damp[index] = 0.98f;
	mass[index] = 1;
	lifetime[index] = lifetime_dist(generator);
	active[index] = true;
}

#include <iostream>
void Particle_system::update(double dt) {
	std::cout << n_particles << "\n";
	for (int i = 0; i < n_particles; ++i) {
		// Lifetime
		lifetime[i] -= dt;
		if (lifetime[i] <= 0) {
			--n_particles;

			trans[i] = trans[n_particles];
			vel[i] = vel[n_particles];
			acc[i] = acc[n_particles];
			damp[i] = damp[n_particles];
			mass[i] = mass[n_particles];
			lifetime[i] = lifetime[n_particles];
			active[i] = active[n_particles];

			active[n_particles] = false;
			
		}

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