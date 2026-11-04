#include "Scene3.h"

void Scene3::init() {
	// Create force generators
	add_force_generator<Simple_gravity_generator>(-100.0f);

	// Create particles
	add_particle(Vector3(0, 0, 0), Vector3(0, 100, 0), 0.98f, 10, 10, Vector4(1, 0, 0, 1));
	add_particle(Vector3(20, 0, 0), Vector3(0, 150, 0), 0.98f, 10, 10, Vector4(0, 1, 0, 1));
	add_particle(Vector3(-20, 0, 0), Vector3(0, 50, 0), 0.98f, 10, 10, Vector4(0, 0, 1, 1));
}

void Scene3::cleanup() {

}

void Scene3::update(double dt) {
	Physics_scene::update(dt);
}

void Scene3::keyPress(unsigned char key, const physx::PxTransform& cameraTransform) {

}