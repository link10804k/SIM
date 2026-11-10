#include "Whirlwind_generator.h"

#include "../../scenes/Physics_scene.h"

Whirlwind_generator::Whirlwind_generator(Physics_scene& scene, float k1, float k2, Vector3D pos, float radius)
	: Wind_generator(scene, k1, k2, pos, radius, Vector3D(0, 0, 0)) { }

void Whirlwind_generator::apply_force(double dt, int index) {
	if (((pos + Vector3D(radius, radius, radius)) - Vector3D(scene.tr.pos.x[index], scene.tr.pos.y[index], scene.tr.pos.z[index])).magnitude() <= radius) {
		Vector3D whirlwind_velocity;

		whirlwind_velocity.x = -(scene.tr.pos.z[index] - (pos.z + radius / 2));
		whirlwind_velocity.y = radius - (scene.tr.pos.y[index] - (pos.y));
		//whirlwind_velocity.y = 0;
		whirlwind_velocity.z = scene.tr.pos.x[index] - (pos.x + radius / 2);
		
		float relative_vel_mag = (whirlwind_velocity - Vector3D(scene.vel.x[index], scene.vel.y[index], scene.vel.z[index])).magnitude();

		scene.forc.x[index] += k1 * (whirlwind_velocity.x - scene.vel.x[index]) + k2 * relative_vel_mag * (whirlwind_velocity.x - scene.vel.x[index]);
		scene.forc.y[index] += k1 * (whirlwind_velocity.y - scene.vel.y[index]) + k2 * relative_vel_mag * (whirlwind_velocity.y - scene.vel.y[index]);
		scene.forc.z[index] += k1 * (whirlwind_velocity.z - scene.vel.z[index]) + k2 * relative_vel_mag * (whirlwind_velocity.z - scene.vel.z[index]);
	}
}