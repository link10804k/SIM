#ifndef FORCE_GENERATOR_H
#define FORCE_GENERATOR_H

class Physics_scene;

class Force_generator {
public:
	Force_generator(int force_generator_index) : force_generator_index(force_generator_index) {}
	virtual ~Force_generator() = default;
	virtual void apply_force(Physics_scene& scene, double dt) = 0;

	virtual void reset() {}
protected:
	int force_generator_index;
};

#endif