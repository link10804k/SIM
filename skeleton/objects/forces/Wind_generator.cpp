#include "Wind_generator.h"

#include "../../scenes/Physics_scene.h"

Wind_generator::Wind_generator(Physics_scene& scene, float k1, float k2, Vector3D pos, float radius, Vector3D wind_velocity)
	: Force_generator(scene), k1(k1), k2(k2), pos(pos), radius(radius), wind_velocity(wind_velocity) {}

void Wind_generator::apply_force(double dt, int index) {
	if ((pos - Vector3D(scene.particles_struct->tr.pos.x[index], scene.particles_struct->tr.pos.y[index], scene.particles_struct->tr.pos.z[index])).magnitude() <= radius) {
		float relative_vel_mag = (wind_velocity - Vector3D(scene.particles_struct->vel.x[index], scene.particles_struct->vel.y[index], scene.particles_struct->vel.z[index])).magnitude();

		scene.particles_struct->forc.x[index] += k1 * (wind_velocity.x - scene.particles_struct->vel.x[index]) + k2 * relative_vel_mag * (wind_velocity.x - scene.particles_struct->vel.x[index]);
		scene.particles_struct->forc.y[index] += k1 * (wind_velocity.y - scene.particles_struct->vel.y[index]) + k2 * relative_vel_mag * (wind_velocity.y - scene.particles_struct->vel.y[index]);
		scene.particles_struct->forc.z[index] += k1 * (wind_velocity.z - scene.particles_struct->vel.z[index]) + k2 * relative_vel_mag * (wind_velocity.z - scene.particles_struct->vel.z[index]);
	}
}