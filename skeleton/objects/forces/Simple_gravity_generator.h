#ifndef SIMPLE_GRAVITY_GENERATOR_H
#define SIMPLE_GRAVITY_GENERATOR_H

#include "Force_generator.h"

class Simple_gravity_generator : public Force_generator {
public:
	Simple_gravity_generator(float gravity_force = -9.8f);
	~Simple_gravity_generator() = default;

	void apply_force(Physics_scene& scene) override;
private:
	float gravity_force;
};

#endif