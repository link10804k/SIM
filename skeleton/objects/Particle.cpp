#include "Particle.h"

Particle::Particle(Vector3D pos, Vector3D vel) : pos(pos), vel(vel) {
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
}