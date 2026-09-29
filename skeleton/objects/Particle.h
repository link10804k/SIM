#ifndef PARTICLE_H
#define PARTICLE_H

#include "../RenderUtils.hpp"
#include "../utils/Vector3D.h"

class Particle  {
public:
	Particle(Vector3D pos, Vector3D vel);
	~Particle();

	void integrate(double dt);
private:
	Vector3D vel;
	physx::PxTransform pos;
	RenderItem* render_item;
};

#endif
