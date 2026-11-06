#ifndef WIND_GENERATOR_H
#define WIND_GENERATOR_H

#include "Force_generator.h"

#include <vector>
#include "../../utils/Vector3D.h"

class Wind_generator : public Force_generator {
public:
	Wind_generator(Physics_scene& scene, int force_generator_index, float k1, float k2, float pos_x, float pos_z, float action_radius_width, float action_radius_depth, Vector3D wind_velocity);
	virtual ~Wind_generator() = default;

	virtual void apply_force(double dt) override;
protected:
	float k1;
	float k2;

	float pos_x;
	float pos_z;
	float action_radius_width;
	float action_radius_depth;
	Vector3D wind_velocity;
};

#endif