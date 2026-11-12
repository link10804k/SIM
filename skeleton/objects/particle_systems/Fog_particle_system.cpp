#include "Fog_particle_system.h"

#include "../../scenes/Physics_scene.h"
#include <cmath>
#include <stdfloat>

Fog_particle_system::Fog_particle_system(Physics_scene& scene, Vector3D pos) 
	: Particle_system(scene, pos) {
	pos_dist = std::normal_distribution<float>(0.0f, 4.0f);
	speed_dist = std::normal_distribution<float>(1.0f, 0.5f);
	dir_dist = std::uniform_real_distribution<float>(-1.0f, 1.0f);
	life_dist = std::normal_distribution<float>(10.0f, 1.0f);
	part_gen_dist = std::normal_distribution<float>(500, 1);
}

void Fog_particle_system::update() {
	int particles_to_gen = std::roundf(std::clamp(part_gen_dist(generator), 0.0f, FLT_MAX));
	for (int i = 0; i < particles_to_gen; ++i) {
		scene.add_particle(pos + Vector3(pos_dist(generator), pos_dist(generator), pos_dist(generator)), 
		std::clamp(speed_dist(generator), 0.0f, FLT_MAX) * Vector3D(dir_dist(generator), dir_dist(generator), dir_dist(generator)).normalize(), 0.98f,
		std::clamp(mass_dist(generator), 0.0f, FLT_MAX), std::clamp(life_dist(generator), 0.0f, FLT_MAX), Vector4(1, 0, 0, 1), { true, true, true, true });
	}
}