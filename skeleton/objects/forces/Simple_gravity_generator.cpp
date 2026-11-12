#include "Simple_gravity_generator.h"

#include "../../scenes/Physics_scene.h"

Simple_gravity_generator::Simple_gravity_generator(Physics_scene& scene, float gravity_force) 
	: Force_generator(scene), gravity_force(gravity_force) {}

void Simple_gravity_generator::apply_force(double dt, int index) {
	scene.particles_struct->forc.y[index] += gravity_force * scene.particles_struct->mas[index];
}