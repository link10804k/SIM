#ifndef PARTICLE_H
#define PARTICLE_H

#include "../RenderUtils.hpp"
#include "../utils/Vector3D.h"

class Particle  {
public:
	Particle(Vector3D pos, Vector3D vel, Vector3D acc, float damp);
	~Particle();

	void integrate(double dt);
private:
	float damp;
	Vector3D acc;
	Vector3D vel;
	physx::PxTransform pos;
	bool using_verlet = false; // Verlet
	Vector3D pos_ant; // Verlet
	RenderItem* render_item;
};

#endif
