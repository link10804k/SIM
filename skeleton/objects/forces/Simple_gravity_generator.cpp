#include "Simple_gravity_generator.h"

#include "../../scenes/Physics_scene.h"

Simple_gravity_generator::Simple_gravity_generator(float gravity_force) : gravity_force(gravity_force) {}

void Simple_gravity_generator::apply_force(Physics_scene& scene) {
	for (int i = 0; i < scene.num_particles; ++i) {
		if (scene.act[i]) {
			scene.acc.y[i] += gravity_force;
		}
	}
}