#ifndef SCENE_H
#define SCENE_H

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    virtual void update(double dt);
    void render();
    virtual void input(unsigned char key, const physx::PxTransform& camera) {}

    void add_particle(Vector3 p, Vector3 v, float d, float m, float l, Vector4 c);
    void integrate(double dt);
private:
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

    physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(0.2f));
};

#endif