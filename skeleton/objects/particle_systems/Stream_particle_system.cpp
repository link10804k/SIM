#include "Stream_particle_system.h"

#include "../../scenes/Physics_scene.h"
#include <array>
#include <cmath>
#include <stdfloat>

Stream_particle_system::Stream_particle_system(Physics_scene& scene, Vector3D pos, Vector3D dir) 
	: Particle_system(scene, pos), dir(dir) {
	speed_dist = std::normal_distribution<float>(50.0f, 1.0f);
	dir_dist = std::normal_distribution<float>(0.0f, 0.05f);
	mass_dist = std::normal_distribution<float>(1.0f, 0.1f);
	life_dist = std::normal_distribution<float>(15.0f, 1.0f);
	part_gen_dist = std::normal_distribution<float>(5, 1);
}

void Stream_particle_system::update() {
	int particles_to_gen = std::roundf(std::clamp(part_gen_dist(generator), 0.0f, FLT_MAX));
	for (int i = 0; i < particles_to_gen; ++i) {
		scene.add_particle(pos, std::clamp(speed_dist(generator), 0.0f, FLT_MAX) * (/*dir + */Vector3D(dir_dist(generator),
			dir_dist(generator), dir_dist(generator))), 0.98f, std::clamp(mass_dist(generator), 0.0f, FLT_MAX),
			std::clamp(life_dist(generator), 0.0f, FLT_MAX), Vector4(0, 0, 1, 1), {true, true, true, true});
	}
}