#pragma once
#ifndef VECTOR3_H 
#define VECTOR3_H
#include "ILuaObject.h"

enum Vector3Mode { RGB, XYZ };

struct Vector3 : public ILuaObject {
public:
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
	Vector3(float _all) : x(_all), y(_all), z(_all) {};
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {};

	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }

	void setX(float _x) { x = _x; }
	void setY(float _y) { y = _y; }
	void setZ(float _z) { z = _z; }

	Vector3 divide(Vector3 const& b) const { return Vector3(x / b.x, y / b.y, z / b.z); }
	Vector3 scalarMult(Vector3 const& b) const { return Vector3(x * b.x, y * b.y, z * b.z); }
	float magnitudeSquared() const { return x * x + y * y + z * z; }
	float magnitude() const { return sqrt(magnitudeSquared()); }
	float dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }
	Vector3 cross(const Vector3& v) const { return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
	Vector3 getNormalized() const
	{
		// return copy of self normalized
		float m = magnitude();
		if (m == 0.0f)
			return Vector3();
		return Vector3(x / m, y / m, z / m);
	}
	Vector3 normalize()
	{
		*this = getNormalized();
		return *this;
	}
	Vector3 inverse() { return Vector3(-x, -y, -z); }

	friend Vector3 operator*(float s, Vector3 v) { return v*= s; }
	Vector3 operator+(Vector3 const& b) { return Vector3(x + b.x, y + b.y, z + b.z); }
	Vector3 operator-(Vector3 const& b) { return Vector3(x - b.x, y - b.y, z - b.z); }
	//Vector3 operator*(Vector3 const& b) { return Vector3(x * b.x, y * b.y, z * b.z); }
	Vector3 operator*(float const& f) const { return Vector3(x * f, y * f, z * f); }
	Vector3 operator%(float const& f) const { return Vector3(fmod(x,f), fmod(y, f), fmod(z, f)); }
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

	static Vector3 ParseVector3(LuaRef vector3Ref, Vector3Mode mode = Vector3Mode::XYZ)
	{
		std::string keys = (mode == Vector3Mode::XYZ ? "xyz" : "rgb");
		return Vector3(LuaMngr()->parseFloat(vector3Ref[keys[0]]), LuaMngr()->parseFloat(vector3Ref[keys[1]]), LuaMngr()->parseFloat(vector3Ref[keys[2]]));
	}

	static void ConvertToLua(lua_State* state)
	{
		getGlobalNamespace(state).
			beginNamespace("Aegis").
			beginNamespace("Maths").
			beginClass<Vector3>("Vector3").
			addConstructor<void(*)(float, float, float)>().
			addProperty("x", &Vector3::getX, &Vector3::setX).
			addProperty("y", &Vector3::getY, &Vector3::setY).
			addProperty("z", &Vector3::getZ, &Vector3::setZ).
			addFunction("Normalize", &Vector3::normalize).
			addFunction("GetNormalized", &Vector3::getNormalized).
			addFunction("__add", &Vector3::operator+).
			addFunction("__sub", &Vector3::operator-).
			addFunction("__mul", &Vector3::operator*).
			addFunction("__div", &Vector3::operator/).
			endClass().
			endNamespace().
			endNamespace();
	}

	float x;
	float y;
	float z;
};

#endif // VECTOR 3_H