#ifndef WHIRLWIND_GENERATOR_H
#define WHIRLWIND_GENERATOR_H

#include "Wind_generator.h"

class Whirlwind_generator : public Wind_generator {
public:
	using Wind_generator::Wind_generator;
	virtual ~Whirlwind_generator() = default;

	void apply_force(Physics_scene& scene, double dt) override;
};

#endif