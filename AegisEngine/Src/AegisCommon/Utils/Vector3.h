#pragma once
#ifndef VECTOR3_H 
#define VECTOR3_H
#include "../Interfaces/ILuaObject.h"

struct Vector3 : public ILuaObject {
public:
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
	Vector3(float _all) : x(_all), y(_all), z(_all) {};
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {};

	float GetX() const { return x; }
	float GetY() const { return y; }
	float GetZ() const { return z; }

	void SetX(float _x) { x = _x; }
	void SetY(float _y) { x = _y; }
	void SetZ(float _z) { x = _z; }

	float magnitudeSquared() const { return x * x + y * y + z * z; }
	float magnitude() const { return sqrt(magnitudeSquared()); }
	float dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }
	Vector3 cross(const Vector3& v) const { return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
	Vector3 getNormalized() const
	{
		const float m = magnitudeSquared();
		return m > 0.0f ? *this * sqrt(m) : Vector3(0, 0, 0);
	}
	float normalize()
	{
		const float m = magnitude();
		if (m > 0.0f)
			*this = *this/m;
		return m;
	}

	Vector3 operator+(Vector3 const& b) { return Vector3(x + b.x, y + b.y, z + b.z); }
	Vector3 operator-(Vector3 const& b) { return Vector3(x - b.x, y - b.y, z - b.z); }
	//Vector3 operator*(Vector3 const& b) { return Vector3(x * b.x, y * b.y, z * b.z); }
	Vector3 operator*(float const& f) const { return Vector3(x * f, y * f, z * f); }
	Vector3 operator/(float f) const
	{
		f = 1.0f / f;
		return Vector3(x * f, y * f, z * f);
	}
	Vector3& operator*=(float f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	bool operator==(Vector3 const& b) { return ((x == b.x) && (y == b.y) && (z == b.z)); }
	bool operator!=(Vector3 const& b) { return !((x == b.x) && (y == b.y) && (z == b.z)); }

	static void ConvertToLua(lua_State* state)
	{
		getGlobalNamespace(state).
			beginNamespace("Aegis").
			beginNamespace("Maths").
			beginClass<Vector3>("Vector3").
			addConstructor<void(*)(float, float, float)>().
			addProperty("x", &Vector3::GetX, &Vector3::SetX).
			addProperty("y", &Vector3::GetY, &Vector3::SetY).
			addProperty("z", &Vector3::GetZ, &Vector3::SetZ).
			endClass().
			endNamespace().
			endNamespace();
	}

	float x;
	float y;
	float z;
};

#endif // VECTOR 3_H