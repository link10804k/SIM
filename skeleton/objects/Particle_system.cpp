#include "Particle_system.h"

#include <cmath>

Particle_system::Particle_system(physx::PxTransform pos, Vector3 dir, Particle_system_type type) : pos(pos), dir(dir), type(type), n_particles(0) {
	switch (type) {
	case STREAM:
	{
		speed_dist = std::normal_distribution<float>(10.0f, 1.0f);
		dir_normal_dist = std::normal_distribution<float>(0.0f, 0.05f);
		lifetime_dist = std::normal_distribution<float>(7.0f, 1.0f);

		part_gen_dist = std::normal_distribution<float>(5, 1);

		gravity = -9.8f;
		break;
	}
	case FOG:
	{
		pos_normal_dist = std::normal_distribution<float>(0.0f, 8.0f);
		speed_dist = std::normal_distribution<float>(1.0f, 1.0f);
		dir_uniform_dist = std::uniform_real_distribution<float>(-1.0f, 1.0f);
		lifetime_dist = std::normal_distribution<float>(7.0f, 1.0f);

		part_gen_dist = std::normal_distribution<float>(5, 1);

		gravity = 0.0f;
		break;
	}
	case BOX:
	{
		pos_uniform_dist = std::uniform_real_distribution<float>(-10.0f, 10.0f);
		dir_uniform_dist = std::uniform_real_distribution<float>(-1.0f, 1.0f);
		lifetime_dist = std::normal_distribution<float>(7.0f, 1.0f);

		part_gen_dist = std::normal_distribution<float>(5, 1);

		gravity = 0.0f;
		break;
	}
	}
}

void Particle_system::create_particle() {
	// Provisional
	if (n_particles == MAX_PARTICLES) return;
	int index;
	if (n_particles == MAX_PARTICLES) {
		index = 0;
	}
	else {
		index = n_particles;
		++n_particles;
	}
	if (type == STREAM) trans[index] = physx::PxTransform(Vector3D(pos.p.x, pos.p.y, pos.p.z));
	else if (type == FOG) trans[index] = physx::PxTransform(Vector3D(pos.p.x + pos_normal_dist(generator), pos.p.y + pos_normal_dist(generator), pos.p.z + pos_normal_dist(generator)));
	else trans[index] = physx::PxTransform(Vector3D(pos.p.x + pos_uniform_dist(generator), pos.p.y + pos_uniform_dist(generator), pos.p.z + pos_uniform_dist(generator)));
	
	if (type == STREAM) vel[index] = Vector3D(dir.x + dir_normal_dist(generator), dir.y + dir_normal_dist(generator), dir.z + dir_normal_dist(generator)).normalize() * speed_dist(generator);
	else if (type == FOG) {
		vel[index] = std::move(Vector3D(dir_uniform_dist(generator), dir_uniform_dist(generator), dir_uniform_dist(generator)).normalize() * speed_dist(generator));
	}
	else vel[index] = Vector3D(0.0f, 0.0f, 0.0f);

	acc[index] = Vector3D(0.0f, gravity, 0.0f);
	damp[index] = 0.98f;
	mass[index] = 1;
	lifetime[index] = lifetime_dist(generator);
	active[index] = true;
}

void Particle_system::update(double dt) {
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
		if (active[i]) {
			vel[i] = vel[i] + (acc[i] * dt);
			trans[i].p = (Vector3D)trans[i].p + (vel[i] * dt);
		}

		// Damping
		vel[i] = vel[i] * std::pow(damp[i], dt);
	}

	int part_to_gen = (int)std::roundf(part_gen_dist(generator));
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