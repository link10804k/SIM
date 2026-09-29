#include "Particle.h"

#include <cmath>

Particle::Particle(Vector3D pos, Vector3D vel, Vector3D acc, float damp) : pos(pos), vel(vel), acc(acc), damp(damp) {
	render_item = new RenderItem(CreateShape(physx::PxSphereGeometry(10.0f)), &this->pos, Vector4(1, 0, 0, 1));
}
Particle::~Particle() {
	if (render_item != nullptr) {
		render_item->release();
		render_item = nullptr;
	}
}

void Particle::integrate(double dt) {
	pos.p = (Vector3D)pos.p + (vel * dt);
	vel = vel + (acc * dt);
	vel = vel * std::pow(damp, dt); // TODO: Revisar
}