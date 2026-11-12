#include "Explosion_generator.h"

#include "../../scenes/Physics_scene.h"

#include <cmath>
#include <numbers>

Explosion_generator::Explosion_generator(Physics_scene& scene, Vector3D position, float radius, float explosion_force, float time_constant)
	: Force_generator(scene), position(position), radius(radius), explosion_force(explosion_force), time_constant(time_constant), time_zero(glutGet(GLUT_ELAPSED_TIME)) {}

void Explosion_generator::apply_force(double dt, int index) {
	Vector3D vec = Vector3D(scene.particles_struct->tr.pos.x[index], scene.particles_struct->tr.pos.y[index], scene.particles_struct->tr.pos.z[index]) - position;
	float magnitude = vec.magnitude();
	float current_time = (glutGet(GLUT_ELAPSED_TIME) / 1000.0f) - (time_zero / 1000.0f);

	if (magnitude <= radius) {
		scene.particles_struct->forc.x[index] += (explosion_force * vec.x * std::pow(std::numbers::e, -(current_time / time_constant))) / std::pow(magnitude, 2);
		scene.particles_struct->forc.y[index] += (explosion_force * vec.y * std::pow(std::numbers::e, -(current_time / time_constant))) / std::pow(magnitude, 2);
		scene.particles_struct->forc.z[index] += (explosion_force * vec.z * std::pow(std::numbers::e, -(current_time / time_constant))) / std::pow(magnitude, 2);
	}
}

void Explosion_generator::reset() {
	time_zero = glutGet(GLUT_ELAPSED_TIME);
}