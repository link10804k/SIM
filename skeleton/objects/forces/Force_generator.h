#ifndef FORCE_GENERATOR_H
#define FORCE_GENERATOR_H

class Physics_scene;

class Force_generator {
public:
	virtual ~Force_generator() = default;
	virtual void apply_force(Physics_scene& scene) {}
protected:
	Force_generator() = default;
};

#endif