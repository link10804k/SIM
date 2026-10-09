#ifndef SCENE2_H
#define SCENE2_H

#include "../Scene.h"

#include "../objects/Particle_system.h"

class Scene2 : public Scene {
public:
    explicit Scene2(std::string name);
    void init() override;
    void cleanup() override;
    void update(double dt) override;
    void keyPress(unsigned char key, const physx::PxTransform& cameraTransform) override;
private:
    RenderItem* floor = nullptr;
    Particle_system ps;
};

#endif