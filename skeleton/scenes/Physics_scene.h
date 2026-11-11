#ifndef PHYSICS_SCENE_H
#define PHYSICS_SCENE_H

#include "../Scene.h"
#include "../RenderUtils.hpp"

#include "../objects/particle_systems/Particle_system.h"
#include "../objects/particle_systems/Stream_particle_system.h"
#include "../objects/particle_systems/Fog_particle_system.h"

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

    friend class Stream_particle_generator;
    friend class Fog_particle_generator;
public:
    // Constantes
    static constexpr int MAX_PARTICLES = 32768;
    static constexpr int MAX_PARTICLE_SYSTEMS = 10;
    static constexpr int MAX_FORCE_GENERATORS = 10;
public:
    Physics_scene(std::string name);
    virtual ~Physics_scene() = default;

    void update(double dt) final override;

    void add_particle(Vector3 p, Vector3 v, float d, float m, float l, Vector4 c, std::array<bool, MAX_FORCE_GENERATORS> force_gens_to_subscribe);
    void kill_all_particles();

    template<typename T, typename ...Ts>
        requires std::is_base_of_v<Particle_system, T>
    inline void add_particle_system(Ts... args) {
        if (num_particle_systems < MAX_PARTICLE_SYSTEMS) {
            particle_systems[num_particle_systems] = std::make_unique<T>(T(*this, std::forward<Ts>(args)...));
            ++num_particle_systems;
        }
    }

    template<typename T, typename ...Ts>
        requires std::is_base_of_v<Force_generator, T>
    inline void add_force_generator(Ts... args) {
        if (num_force_generators < MAX_FORCE_GENERATORS) {
            force_generators[num_force_generators] = std::make_unique<T>(T(*this, std::forward<Ts>(args)...));
            ++num_force_generators;
        }
    }

    void set_active_force_generator(int index, bool active);
    void toggle_active_force_generator(int index);
    void reset_force_generator(int index);
protected:
    virtual void scene_update(double dt) = 0;
private:
    // Partículas
    int num_particles = 0;

    class Index_stack {
    private:
        int circular_stack[MAX_PARTICLES];
        int ini = 0;
        int fin = 0;
    public:
        void push(int index) {
            circular_stack[fin] = index;
            fin = (fin + 1) % MAX_PARTICLES;
        }
        int top() const {
            assert(size() > 0);
            return circular_stack[ini];
        }
        void pop() {
            assert(size() > 0);
            ini = (ini + 1) % MAX_PARTICLES;
        }
        int size() const { // TODO: Refactorizar Index_stack::size()
            if (fin < ini) {
                return fin + MAX_PARTICLES - ini;
            }
            return fin - ini;
        }
    } free_particle_index_stack;

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

    physx::PxShape* particle_shape = CreateShape(physx::PxSphereGeometry(0.2f));

    void integrate(double dt, int index);

    // Sistemas de partículas
    int num_particle_systems = 0;
    std::unique_ptr<Particle_system> particle_systems[MAX_PARTICLE_SYSTEMS];
    bool act_particle_sys[MAX_PARTICLE_SYSTEMS];

    // Generadores de fuerzas
    int num_force_generators = 0;
    std::unique_ptr<Force_generator> force_generators[MAX_FORCE_GENERATORS];
    bool act_force_gens[MAX_FORCE_GENERATORS];
};

#endif