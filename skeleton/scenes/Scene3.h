#ifndef SCENE3_H
#define SCENE3_H

#include "Physics_scene.h"

class Scene3 : public Physics_scene {
public:
	using Physics_scene::Physics_scene;
	using Physics_scene::~Physics_scene;

	void init() override;
	void cleanup() override;
	void update(double dt) override;
	void keyPress(unsigned char key, const physx::PxTransform& cameraTransform) override;
};

#endif