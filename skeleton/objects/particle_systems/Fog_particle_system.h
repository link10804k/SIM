#ifndef FOG_PARTICLE_SYSTEM_H
#define FOG_PARTICLE_SYSTEM_H

#include "Particle_system.h"

class Fog_particle_system : public Particle_system {
public:
	Fog_particle_system(Physics_scene& scene, Vector3D pos);
	virtual ~Fog_particle_system() = default;

	void update() override;
private:
	std::normal_distribution<float> pos_dist;
	std::normal_distribution<float> speed_dist;
	std::uniform_real_distribution<float> dir_dist;
	std::normal_distribution<float> mass_dist;
	std::normal_distribution<float> life_dist;
	std::normal_distribution<float> part_gen_dist;
};

#endif