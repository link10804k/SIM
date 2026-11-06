#ifndef SIMPLE_GRAVITY_GENERATOR_H
#define SIMPLE_GRAVITY_GENERATOR_H

#include "Force_generator.h"

class Simple_gravity_generator : public Force_generator {
public:
	Simple_gravity_generator(Physics_scene& scene, int force_generator_index, float gravity_force = -9.8f);
	~Simple_gravity_generator() = default;

	void apply_force(double dt) override;
private:
	float gravity_force;
};

#endif