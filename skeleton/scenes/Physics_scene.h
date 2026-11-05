#ifndef PHYSICS_SCENE_H
#define PHYSICS_SCENE_H

#include "../Scene.h"
#include "../RenderUtils.hpp"

#include "../objects/forces/Force_generator.h"
#include "../objects/forces/Simple_gravity_generator.h"
#include "../objects/forces/Wind_generator.h"
#include "../objects/forces/Whirlwind_generator.h"
#include "../objects/forces/Explosion_generator.h"

#include <memory>
#include <array>

class Physics_scene : public Scene {
    friend class Simple_gravity_generator;
    friend class Wind_generator;
    friend class Whirlwind_generator;
    friend class Explosion_generator;
public:
    // Constantes
    static constexpr int MAX_PARTICLES = 2048;
    static constexpr int MAX_FORCE_GENERATORS = 10;
public:
    Physics_scene(std::string name);
    virtual ~Physics_scene() = default;

    virtual void update(double dt) override;

    void add_particle(Vector3 p, Vector3 v, float d, float m, float l, Vector4 c, std::array<bool, MAX_FORCE_GENERATORS> force_gens_to_subscribe);
    void kill_all_particles();

    template<typename T, typename ...Ts>
        requires std::is_base_of_v<Force_generator, T>
    inline void add_force_generator(Ts... args) {
        if (num_force_generators < MAX_FORCE_GENERATORS) {
            force_generators[num_force_generators] = std::make_unique<T>(T(num_force_generators, std::forward<Ts>(args)...));
            ++num_force_generators;
        }
    }

    void set_active_force_generator(int index, bool active);
    void toggle_active_force_generator(int index);
    void reset_force_generator(int index);
private:
    // Partículas
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
    Vector3_array forc;
    Vector3_array acc;
    float dam[MAX_PARTICLES];
    float mas[MAX_PARTICLES];
    float wmas[MAX_PARTICLES];
    float lif[MAX_PARTICLES];
    bool act[MAX_PARTICLES];
    Vector4_array col;
    bool subscribed_force_gens[MAX_PARTICLES][MAX_FORCE_GENERATORS];

    physx::PxShape* particle_shape = CreateShape(physx::PxSphereGeometry(2.0f));

    void integrate(double dt);

    // Generadores de fuerzas
    int num_force_generators = 0;
    std::unique_ptr<Force_generator> force_generators[MAX_FORCE_GENERATORS];
    bool act_force_gens[MAX_FORCE_GENERATORS];

    // Render
    void render();
};

#endif