#pragma once
#ifndef VECTOR3_H 
#define VECTOR3_H
#include "../Interfaces/ILuaObject.h"

class Vector3 : public ILuaObject {
public:
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
	Vector3(float _all) : x(_all), y(_all), z(_all) {};
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {};

	float GetX() const{ return x; }
	float GetY() const{ return y; }
	float GetZ() const{ return z; }

	void SetX(float _x) { x = _x; }
	void SetY(float _y) { x = _y; }
	void SetZ(float _z) { x = _z; }

	Vector3 operator+(Vector3 const& b) { return Vector3(x + b.x, y + b.y, z + b.z); }
	Vector3 operator-(Vector3 const& b) { return Vector3(x - b.x, y - b.y, z - b.z); }
	Vector3 operator*(Vector3 const& b) { return Vector3(x * b.x, y * b.y, z * b.z); }
	Vector3 operator*(float const& f) { return Vector3(x * f, y * f, z * f); }
	bool operator==(Vector3 const& b) { return ((x == b.x) && (y == b.y) && (z == b.z)); }
	bool operator!=(Vector3 const& b) { return !((x == b.x) && (y == b.y) && (z == b.z)); }

	static void ConvertToLua(lua_State* state)
	{
		getGlobalNamespace(state).
			beginNamespace("ECS").
			beginClass<Vector3>("Vector3").
			addConstructor<void(*)(float, float, float)>().
			addProperty("x", &Vector3::GetX, &Vector3::SetX).
			addProperty("y", &Vector3::GetY, &Vector3::SetY).
			addProperty("z", &Vector3::GetZ, &Vector3::SetZ).
			endClass().
			endNamespace();
	}
protected:
	float x;
	float y;
	float z;
};

#endif // VECTOR 3_H