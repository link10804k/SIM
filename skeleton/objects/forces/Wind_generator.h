#ifndef WIND_GENERATOR_H
#define WIND_GENERATOR_H

#include "Force_generator.h"

#include <vector>
#include "../../utils/Vector3D.h"

class Wind_generator : public Force_generator {
public:
	Wind_generator(Physics_scene& scene, float k1, float k2, Vector3D pos, float radius, Vector3D wind_velocity);
	virtual ~Wind_generator() = default;

	virtual void apply_force(double dt, int index) override;
protected:
	float k1;
	float k2;

	Vector3D pos;
	float radius;
	Vector3D wind_velocity;
};

#endif