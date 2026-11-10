#ifndef SCENE3_H
#define SCENE3_H

#include "Physics_scene.h"

class Scene3 : public Physics_scene {
public:
	using Physics_scene::Physics_scene;
	virtual ~Scene3() = default;

	void init() override;
	void cleanup() override;
	void scene_update(double dt) override;
	void keyPress(unsigned char key, const physx::PxTransform& cameraTransform) override;
private:
	void generate_particles();
};

#endif