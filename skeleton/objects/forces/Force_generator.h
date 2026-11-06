#ifndef FORCE_GENERATOR_H
#define FORCE_GENERATOR_H

class Physics_scene;

class Force_generator {
public:
	Force_generator(Physics_scene& scene, int force_generator_index) : scene(scene), force_generator_index(force_generator_index) {}
	virtual ~Force_generator() = default;
	virtual void apply_force(double dt) = 0;

	virtual void reset() {}
protected:
	Physics_scene& scene;
	int force_generator_index;
};

#endif