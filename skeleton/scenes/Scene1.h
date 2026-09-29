#ifndef Scene1_h
#define Scene1_h

#include "../Scene.h"

#include <vector>

class Particle;

class Scene1 : public Scene {
public:
    explicit Scene1(std::string name);
    void init() override;
    void cleanup() override;
    void update(double dt) override;
private:
    std::vector<Particle> particle_vector;
};

#endif