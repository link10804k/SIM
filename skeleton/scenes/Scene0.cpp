#include "Scene0.h"
#include "../RenderUtils.hpp"

Scene0::Scene0(std::string name) : Scene(std::move(name)) {}

void Scene0::init() {
    physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
    physx::PxTransform m_transform = physx::PxTransform(physx::PxVec3(0.0f, 10.0f, 0.0f));

    // Se registra el RenderItem exactamente como en la plantilla original
    render_item_vector.push_back(new RenderItem(shape, &m_transform, Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
    RegisterRenderItem(render_item_vector.back());
}
void Scene0::cleanup() {
    for (RenderItem* ri : render_item_vector) {
        ri->release();
    }
    render_item_vector.clear();
}
void Scene0::update(double dt) {

}