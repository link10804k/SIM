#include "Scene2.h"

Scene2::Scene2(std::string name) : Scene(std::move(name)) {}

void Scene2::init() {
	floor = new RenderItem(CreateShape(physx::PxBoxGeometry(1000000, 1, 1000000)), new physx::PxTransform(Vector3D(0.0f, 0.0f, 0.0f)), Vector4(0, 1, 0, 1));
	ps = Particle_system(physx::PxTransform(Vector3D(0, 20, 0)), Vector3D(0, 0, 0), Particle_system::FOG);
}

void Scene2::cleanup() {

}

void Scene2::update(double dt) {
	ps.update(dt);
}

void Scene2::keyPress(unsigned char key, const physx::PxTransform& cameraTransform) {

}