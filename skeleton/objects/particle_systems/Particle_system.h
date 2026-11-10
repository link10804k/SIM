#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "../../utils/Vector3D.h"

#include <random>

class Physics_scene;

class Particle_system {
public:
	Particle_system(Physics_scene& scene, Vector3D pos) : scene(scene), pos(pos) {}
	virtual ~Particle_system() = default;
			
	virtual void update() = 0;
protected:
	// TODO: Debería ser static const?
	std::default_random_engine generator;

	Physics_scene& scene;
	Vector3D pos;
};

#endif