#include "Simple_gravity_generator.h"

#include "../../scenes/Physics_scene.h"

Simple_gravity_generator::Simple_gravity_generator(int force_generator_index, float gravity_force) : Force_generator(force_generator_index), gravity_force(gravity_force) {}

void Simple_gravity_generator::apply_force(Physics_scene& scene, double dt) {
	for (int i = 0; i < scene.num_particles; ++i) {
		if (scene.act[i] && scene.subscribed_force_gens[i][force_generator_index]) {
			scene.forc.y[i] += gravity_force * scene.mas[i];
		}
	}
}