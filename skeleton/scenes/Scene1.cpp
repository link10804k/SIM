#include "Scene1.h"

#include "../utils/Vector3D.h"
#include "../objects/Particle.h"

#include "../utils/maths.h"

#include <algorithm>
#include <cmath>

Scene1::Scene1(std::string name) : Scene(std::move(name)) {}

void Scene1::init() {
    particle_vector.push_back(new Particle({ 0, 0, 0 }, { 0, 0, 0 }, { 0, -9.8f, 0 }, 0.98f, 1.0f));
}
void Scene1::cleanup() {
    for (Particle* p : particle_vector) {
        delete p;
    }
    particle_vector.clear();
}
void Scene1::update(double dt) {
    for (Particle* p : particle_vector) {
        p->integrate(dt);
    }
}

void Scene1::keyPress(unsigned char key, const physx::PxTransform& cameraTransform) {
    switch (key) {
    case 'i':
        shooting_speed += 50.0f;
        break;
    case 'k':
        shooting_speed -= 50.0f;
        break;
    case 'j':
        shooting_mass += 0.1f;
        break;
    case 'l':
        shooting_mass -= 0.1f;
        break;
    case 'p':
        //shoot(c);
        break;
    }
    
}

void Scene1::shoot(Vector3D pos, Vector3D direction, float speed, float gravity, float damp, float mass) {
    float adjusted_speed = maths::remap(std::clamp(speed, 0.0f, 500.0f), 0.0f, 500.0f, 0.0f, 25.0f);
    Vector3D adjusted_velocity = adjusted_speed * direction.normalize();
    float adjusted_mass = mass * std::pow(speed / adjusted_speed, 2);
    float adjusted_gravity = gravity * std::pow(adjusted_speed / speed, 2);
    Vector3D adjusted_acceleration = Vector3D(0.0f, adjusted_gravity, 0.0f);

    particle_vector.push_back(new Particle(pos, adjusted_velocity, adjusted_acceleration, 0.98f, adjusted_mass));
}