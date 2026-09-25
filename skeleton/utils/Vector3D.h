#ifndef Vector3D_h
#define Vector3D_h

#include <cassert>

namespace physx {
	class PxVec3;
}


struct Vector3D {
	float x, y, z;

	// Constructores
	Vector3D(float x = 0, float y = 0, float z = 0);
	Vector3D(const physx::PxVec3& other);

	// Operaciones
	float magnitude() const;
	Vector3D normalize() const;

	float dot(const Vector3D& other) const;
	Vector3D cross(const Vector3D& other) const;

	// Sobrecarga de operadores
	inline Vector3D& operator+=(const Vector3D& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	inline friend Vector3D operator+(Vector3D lv, const Vector3D& rv) {
		lv += rv;
		return lv;
	}
	inline Vector3D& operator-=(const Vector3D& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	inline friend Vector3D operator-(Vector3D lv, const Vector3D& rv) {
		lv -= rv;
		return lv;
	}
	inline Vector3D& operator*=(float s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	inline friend Vector3D operator*(Vector3D lv, const float& rv) {
		lv *= rv;
		return lv;
	}
	inline friend Vector3D operator*(const float& lv, Vector3D rv) {
		rv *= lv;
		return rv;
	}
	inline Vector3D& operator/=(float s) {
		assert(s != 0, "Intento de división de un Vector3D entre 0");
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}
	inline friend Vector3D operator/(Vector3D lv, const float& rv) {
		lv /= rv;
		return lv;
	}
	operator physx::PxVec3() const;
};

#endif