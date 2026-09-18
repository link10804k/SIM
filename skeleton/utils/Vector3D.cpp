#include "Vector3D.h"

#include "PxPhysicsAPI.h"

#include <cmath>

// Constructores
Vector3D::Vector3D(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
Vector3D::Vector3D(const physx::PxVec3& other) : x(other.x), y(other.y), z(other.z) {}

// Operaciones
float Vector3D::magnitude() const {
	return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
}
Vector3D Vector3D::normalize() const {
	return *this / magnitude();
}

float Vector3D::dot(const Vector3D& other) const {
	return this->x * other.x + this->y * other.y + this->z * other.z;
}
Vector3D Vector3D::cross(const Vector3D& other) const {
	return { this->y * other.z - this->z * other.y,
			this->z * other.x - this->x * other.z,
			this->x * other.y - this->y * other.x };
}
