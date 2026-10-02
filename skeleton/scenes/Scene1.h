#ifndef Scene1_h
#define Scene1_h

#include "../Scene.h"

#include <vector>

class Particle;
class Vector3D;

class Scene1 : public Scene {
public:
    explicit Scene1(std::string name);
    void init() override;
    void cleanup() override;
    void update(double dt) override;
    void keyPress(unsigned char key, const physx::PxTransform& cameraTransform) override;
private:
    std::vector<Particle*> particle_vector;
    void shoot(Vector3D pos, Vector3D direction, float speed, float gravity, float damp, float mass);
    float shooting_speed = 0;
    float shooting_mass = 0;
};

#endif