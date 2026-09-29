#include "Scene1.h"

#include "../utils/Vector3D.h"
#include "../objects/Particle.h"

Scene1::Scene1(std::string name) : Scene(std::move(name)) {}

void Scene1::init() {
    particle_vector.push_back(new Particle({ 0, 0, 0 }, { 5, 0, 0 }, {0, 1, 0}, 0.98f));
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