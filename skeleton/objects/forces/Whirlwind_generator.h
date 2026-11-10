#ifndef WHIRLWIND_GENERATOR_H
#define WHIRLWIND_GENERATOR_H

#include "Wind_generator.h"

class Whirlwind_generator : public Wind_generator {
public:
	Whirlwind_generator(Physics_scene& scene, float k1, float k2, Vector3D pos, float radius);
	virtual ~Whirlwind_generator() = default;

	void apply_force(double dt, int index) override;
};

#endif