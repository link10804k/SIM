#ifndef FORCE_GENERATOR_H
#define FORCE_GENERATOR_H

class Physics_scene;

class Force_generator {
public:
	Force_generator() = default;
	virtual ~Force_generator() = default;
	virtual void apply_force(Physics_scene& scene) = 0;
};

#endif