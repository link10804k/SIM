#ifndef STREAM_PARTICLE_SYSTEM_H
#define STREAM_PARTICLE_SYSTEM_H

#include "Particle_system.h"

#include <random>

class Stream_particle_system : public Particle_system {
public:
	Stream_particle_system(Physics_scene& scene, Vector3D pos, Vector3D dir);
	virtual ~Stream_particle_system() = default;
	
	void update() override;
private:
	Vector3D dir;

	std::normal_distribution<float> speed_dist;
	std::normal_distribution<float> dir_dist;
	std::normal_distribution<float> mass_dist;
	std::normal_distribution<float> life_dist;
	std::normal_distribution<float> part_gen_dist;
};

#endif