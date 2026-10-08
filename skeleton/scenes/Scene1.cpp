#include "Scene1.h"

#include "../utils/Vector3D.h"
#include "../objects/Particle.h"

#include "../utils/maths.h"

#include <algorithm>
#include <cmath>

Scene1::Scene1(std::string name) : Scene(std::move(name)) {}

void Scene1::init() {
    floor = new RenderItem(CreateShape(physx::PxBoxGeometry(1000000, 1, 1000000)), new physx::PxTransform(Vector3(0.0f, 40.0f, 0.0f)), Vector4(0, 1, 0, 1));
}
void Scene1::cleanup() {
    for (Particle* p : particle_vector) {
        delete p;
    }
    particle_vector.clear();

    if (floor != nullptr) {
        floor->release();
        floor = nullptr;
    }
}
void Scene1::update(double dt) {
    for (Particle* p : particle_vector) {
        p->integrate(dt);
    }
}

void Scene1::keyPress(unsigned char key, const physx::PxTransform& cameraTransform) {
    switch (key) {
    case 'f': // Flecha tradicional
    {
        float speed = 55; // 55 m/s^2
        float mass = 0.030; // 30 g
        float gravity = -9.8; // -9.8 m/s^2
        float damp = 0.98;
        Vector3 camera_pos = GetCamera()->getEye();
        Vector3 camera_dir = GetCamera()->getDir();
        shoot(camera_pos, camera_dir, speed, gravity, damp, mass);
        break;
    }
    case 'b': // Bala 9mm
    {
        float speed = 111; // ~450 km/h
        float mass = 0.008; // 8 g
        float gravity = -9.8; // -9.8 m/s^2
        float damp = 0.98;
        Vector3 camera_pos = GetCamera()->getEye();
        Vector3 camera_dir = GetCamera()->getDir();
        shoot(camera_pos, camera_dir, speed, gravity, damp, mass);
        break;
    }
    }
    
}

void Scene1::shoot(Vector3D pos, Vector3D direction, float speed, float gravity, float damp, float mass) {
    float adjusted_speed = maths::remap(std::clamp(speed, 0.0f, 150.0f), 0.0f, 150.0f, 0.0f, 500.0f);
    Vector3D adjusted_velocity = adjusted_speed * direction.normalize();
    float adjusted_mass = mass * std::pow(speed / adjusted_speed, 2);
    float adjusted_gravity = gravity * std::pow(adjusted_speed / speed, 2);
    Vector3D adjusted_acceleration = Vector3D(0.0f, adjusted_gravity, 0.0f);

    particle_vector.push_back(new Particle(pos, adjusted_velocity, adjusted_acceleration, 0.98f, adjusted_mass));
}