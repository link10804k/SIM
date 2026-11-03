#ifndef PHYSICS_SCENE_H
#define PHYSICS_SCENE_H

#include "../Scene.h"
#include "../RenderUtils.hpp"

#include "../objects/forces/Force_generator.h"
#include "../objects/forces/Simple_gravity_generator.h"

class Physics_scene : public Scene {
    friend class Simple_gravity_generator;
public:
    using Scene::Scene;
    virtual ~Physics_scene() = default;

    virtual void update(double dt) override;

    void add_particle(Vector3 p, Vector3 v, float d, float m, float l, Vector4 c);
    void add_force_generator();
private:
    // Partículas
    static constexpr int MAX_PARTICLES = 2000;
    int num_particles = 0;

    struct Quaternion_array {
        float x[MAX_PARTICLES], y[MAX_PARTICLES], z[MAX_PARTICLES], w[MAX_PARTICLES];
    };

    struct Vector3_array {
        float x[MAX_PARTICLES], y[MAX_PARTICLES], z[MAX_PARTICLES];
    };

    struct Vector4_array {
        float x[MAX_PARTICLES], y[MAX_PARTICLES], z[MAX_PARTICLES], w[MAX_PARTICLES];
    };

    struct Transform_array {
        Quaternion_array qua;
        Vector3_array pos;
    };

    Transform_array tr;
    Vector3_array vel;
    Vector3_array acc;
    float dam[MAX_PARTICLES];
    float mas[MAX_PARTICLES];
    float lif[MAX_PARTICLES];
    bool act[MAX_PARTICLES];
    Vector4_array col;

    physx::PxShape* particle_shape = CreateShape(physx::PxSphereGeometry(0.2f));

    void integrate(double dt);

    // Generadores de fuerzas
    static constexpr int MAX_FORCE_GENERATORS = 10;
    int num_force_generators = 0;
    Force_generator force_generators[MAX_FORCE_GENERATORS];

    // Render
    void render();
};

#endif