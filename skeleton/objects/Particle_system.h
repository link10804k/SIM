#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "../RenderUtils.hpp"
#include "../utils/Vector3D.h"

#include <random>

constexpr int MAX_PARTICLES = 10000;

class Particle_system {
public:
	Particle_system() = default;
	Particle_system(physx::PxTransform pos, Vector3 dir);
	~Particle_system() = default;

	void update(double dt);
private:
	physx::PxTransform pos;
	Vector3 dir;

	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));
	Vector4 color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

	physx::PxTransform trans[MAX_PARTICLES];
	Vector3D vel[MAX_PARTICLES];
	Vector3D acc[MAX_PARTICLES];
	float damp[MAX_PARTICLES];
	float mass[MAX_PARTICLES];
	float lifetime[MAX_PARTICLES];
	bool active[MAX_PARTICLES];

	int n_particles;

	std::default_random_engine generator;
	std::normal_distribution<float> pos_dist;
	std::normal_distribution<float> speed_dist;
	std::normal_distribution<float> dir_dist;
	std::normal_distribution<float> lifetime_dist;

	std::normal_distribution<float> part_gen_dist;

	void create_particle();
};

#endif