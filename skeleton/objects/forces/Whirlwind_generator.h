#ifndef WHIRLWIND_GENERATOR_H
#define WHIRLWIND_GENERATOR_H

#include "Wind_generator.h"

class Whirlwind_generator : public Wind_generator {
public:
	Whirlwind_generator(Physics_scene& scene, int force_generator_index, float k1, float k2, float pos_x, float pos_z, float action_radius_width, float action_radius_depth);
	virtual ~Whirlwind_generator() = default;

	void apply_force(double dt) override;
};

#endif