#include "Explosion_generator.h"

#include "../../scenes/Physics_scene.h"

#include <cmath>
#include <numbers>

Explosion_generator::Explosion_generator(int force_generator_index, Vector3D position, float radius, float explosion_force, float time_constant)
	: Force_generator(force_generator_index), position(position), radius(radius), explosion_force(explosion_force), time_constant(time_constant) {}

void Explosion_generator::apply_force(Physics_scene& scene, double dt) {
	for (int i = 0; i < scene.num_particles; ++i) {
		if (scene.act[i] && scene.subscribed_force_gens[i][force_generator_index]) {
			Vector3D vec = Vector3D(scene.tr.pos.x[i], scene.tr.pos.y[i], scene.tr.pos.z[i]) - position;
			float magnitude = vec.magnitude();

			if (magnitude <= radius) {
				scene.forc.x[i] += (explosion_force * vec.x * std::pow(std::numbers::e, -(current_time / time_constant))) / std::pow(magnitude, 2);
				scene.forc.y[i] += (explosion_force * vec.y * std::pow(std::numbers::e, -(current_time / time_constant))) / std::pow(magnitude, 2);
				scene.forc.z[i] += (explosion_force * vec.z * std::pow(std::numbers::e, -(current_time / time_constant))) / std::pow(magnitude, 2);
			}
		}
	}
	current_time += dt;
}

void Explosion_generator::reset() {
	current_time = 0;
}