#ifndef Scene0_h
#define Scene0_h

#include "../Scene.h"

#include <vector>

class RenderItem;

class Scene0 : public Scene {
public:
    explicit Scene0(std::string name);
    void init() override;
    void cleanup() override;
    void update(double dt) override;
private:
    std::vector<RenderItem*> render_item_vector;
};

#endif