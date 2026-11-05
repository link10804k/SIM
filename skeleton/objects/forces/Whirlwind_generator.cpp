#include "Whirlwind_generator.h"

#include "../../scenes/Physics_scene.h"

void Whirlwind_generator::apply_force(Physics_scene& scene, double dt) {
	for (int i = 0; i < scene.num_particles; ++i) {
		if (scene.act[i] && scene.subscribed_force_gens[i][force_generator_index] &&
			scene.tr.pos.x[i] >= pos_x && scene.tr.pos.x[i] <= pos_x + action_radius_width &&
			scene.tr.pos.z[i] >= pos_z && scene.tr.pos.z[i] <= pos_z + action_radius_depth) {

			Vector3D whirlwind_velocity;

			whirlwind_velocity.x = -(scene.tr.pos.z[i] - (pos_z + action_radius_depth / 2));
			whirlwind_velocity.y = 1 - (scene.tr.pos.y[i] - (50 + action_radius_depth / 2));
			whirlwind_velocity.z = scene.tr.pos.x[i] - (pos_x + action_radius_width / 2);
			

			float relative_vel_mag = (whirlwind_velocity - Vector3D(scene.vel.x[i], scene.vel.y[i], scene.vel.z[i])).magnitude();

			scene.forc.x[i] += k1 * (whirlwind_velocity.x - scene.vel.x[i]) + k2 * relative_vel_mag * (whirlwind_velocity.x - scene.vel.x[i]);
			scene.forc.y[i] += k1 * (whirlwind_velocity.y - scene.vel.y[i]) + k2 * relative_vel_mag * (whirlwind_velocity.y - scene.vel.y[i]);
			scene.forc.z[i] += k1 * (whirlwind_velocity.z - scene.vel.z[i]) + k2 * relative_vel_mag * (whirlwind_velocity.z - scene.vel.z[i]);
		}
	}
}