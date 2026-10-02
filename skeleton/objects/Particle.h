#ifndef PARTICLE_H
#define PARTICLE_H

#include "../RenderUtils.hpp"
#include "../utils/Vector3D.h"

class Particle  {
public:
	Particle(Vector3D pos, Vector3D vel, Vector3D acc, float damp, float mass);
	~Particle();

	void integrate(double dt);
private:
	physx::PxTransform pos;
	Vector3D vel;
	Vector3D acc;
	float damp;
	float mass;

	Vector3D pos_ant; // Verlet
	bool using_verlet = false; // Verlet

	RenderItem* render_item;
};

#endif
