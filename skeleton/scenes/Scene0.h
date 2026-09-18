#ifndef Scene0_h
#define Scene0_h

#include "../Scene.h"

class Scene0 : public Scene {
    void init() override;
    void cleanup() override;
    void update(double dt) override;
};

#endif