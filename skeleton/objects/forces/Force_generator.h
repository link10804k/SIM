#ifndef FORCE_GENERATOR_H
#define FORCE_GENERATOR_H

class Physics_scene;

class Force_generator {
public:
	Force_generator(Physics_scene& scene) : scene(scene) {}
	virtual ~Force_generator() = default;
	virtual void apply_force(double dt, int index) = 0;

	virtual void reset() {}
protected:
	Physics_scene& scene;
};

#endif