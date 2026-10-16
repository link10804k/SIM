#include "Scene2.h"

Scene2::Scene2(std::string name) : Scene(std::move(name)) {}

void Scene2::init() {
	floor = new RenderItem(CreateShape(physx::PxBoxGeometry(1000000, 1, 1000000)), new physx::PxTransform(Vector3D(0.0f, 0.0f, 0.0f)), Vector4(0, 1, 0, 1));
	ps_stream = Particle_system(physx::PxTransform(Vector3D(0, 20, 0)), Vector3D(1, 1, 0), Particle_system::STREAM);
	ps_fog = Particle_system(physx::PxTransform(Vector3D(0, 20, 0)), Vector3D(0, 0, 0), Particle_system::FOG);
	ps_box = Particle_system(physx::PxTransform(Vector3D(0, 20, 0)), Vector3D(0, 0, 0), Particle_system::BOX);
	current_system = &ps_stream;
}

void Scene2::cleanup() {

}

void Scene2::update(double dt) {
	current_system->update(dt);
}

void Scene2::keyPress(unsigned char key, const physx::PxTransform& cameraTransform) {
	switch (key) {
	case 't':
		current_system = &ps_stream;
		break;
	case 'f':
		current_system = &ps_fog;
		break;
	case 'b':
		current_system = &ps_box;
		break;
	}
}