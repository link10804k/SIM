#include "Particle.h"

#include <cmath>

Particle::Particle(Vector3D pos, Vector3D vel, Vector3D acc, float damp) : pos(pos), vel(vel), acc(acc), damp(damp) {
	render_item = new RenderItem(CreateShape(physx::PxSphereGeometry(10.0f)), &this->pos, Vector4(1, 0, 0, 1));
	pos_ant = (Vector3D)this->pos.p - (vel * (1.0 / 60.0));
}
Particle::~Particle() {
	if (render_item != nullptr) {
		render_item->release();
		render_item = nullptr;
	}
}

void Particle::integrate(double dt) {
	// Euler
	//pos.p = (Vector3D)pos.p + (vel * dt);
	//vel = vel + (acc * dt);
	
	// Euler Semi-implícito
	//vel = vel + (acc * dt);
	//pos.p = (Vector3D)pos.p + (vel * dt);

	// Verlet
	Vector3D new_pos = (2 * (Vector3D)pos.p) - pos_ant + (acc * std::pow(dt, 2));
	pos_ant = pos.p;
	pos.p = new_pos;

	// Damping
	vel = vel * std::pow(damp, dt); // TODO: Revisar
}