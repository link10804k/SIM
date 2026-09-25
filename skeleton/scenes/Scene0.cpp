#include "Scene0.h"

#include "../RenderUtils.hpp"
#include "../utils/Vector3D.h"

#include <iostream>

Scene0::Scene0(std::string name) : Scene(std::move(name)) {}

void Scene0::init() {    
    Vector3D A(-8.0f, 1.0f, -8.0f);
    Vector3D B(8.0f, 8.0f, 8.0f);

    float ti = 5;
    float tf = -30;
    int n = 200;

    for (int i = 0; i < n; ++i) {
        float t = ((tf / (n - 1)) * i) + ti;
        Vector3 v = (A + t*(B - A));

        RenderItem* r = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0f)), new physx::PxTransform(v), Vector4(1, 1, 1, 1));
        render_item_vector.push_back(r);
    }
}
void Scene0::cleanup() {
    for (RenderItem* ri : render_item_vector) {
        if (ri != nullptr)
            ri->release();
    }
    render_item_vector.clear();
}
void Scene0::update(double dt) {

}