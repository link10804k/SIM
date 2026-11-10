#ifndef EXPLOSION_GENERATOR_H
#define EXPLOSION_GENERATOR_H

#include "Force_generator.h"

#include "../../utils/Vector3D.h"

class Explosion_generator : public Force_generator {
public:
	Explosion_generator(Physics_scene& scene, Vector3D position, float radius, float explosion_force, float time_constant);
	virtual ~Explosion_generator() = default;

	void apply_force(double dt, int index) override;
	void reset() override;
protected:
	Vector3D position;
	float radius;
	float explosion_force;
	float time_constant;
	float time_zero;
};

#endif