#pragma once
#ifndef VECTOR4_H 
#define VECTOR4_H

#include "Vector3.h"
#include "ILuaObject.h"

struct Vector4 : public Vector3, public ILuaObject {
public:
	Vector4(float _x, float _y, float _z, float _w) : Vector3(_x, _y, _z), w(_w) {};
	Vector4(float _all) : Vector3(_all), w(_all) {};
	Vector4() : Vector3(), w(1.0f) {};

	float GetW() const { return w; }
	void SetW(float _w) { w = _w; }
	Vector3 GetForwardVector(Vector4 quaternion) {
		return(Vector3(0, 0, quaternion.z));
	}

	Vector4 operator+(Vector4 const& b) { return Vector4(x + b.x, y + b.y, z + b.z, w + b.w); }
	Vector4 operator-(Vector4 const& b) { return Vector4(x - b.x, y - b.y, z - b.z, w - b.w); }
	Vector4 operator*(Vector4 const& b) { return Vector4(x * b.x, y * b.y, z * b.z, w * b.w); }
	Vector4 operator*(float  f) { return Vector4(x * f, y * f, z * f, w * f); }
	bool operator==(Vector4 const& b) { return ((x == b.x) && (y == b.y) && (z == b.z) && (w == b.w)); }
	bool operator!=(Vector4 const& b) { return !(x == b.x) && (y == b.y) && (z == b.z) && (w == b.w); }


	static void ConvertToLua(lua_State* state)
	{
		getGlobalNamespace(state).
			beginNamespace("Aegis").
			beginNamespace("Maths").
			deriveClass<Vector4, Vector3>("Vector4").
			addConstructor<void(*)(float, float, float,float)>().
			addProperty("w", &Vector4::GetW, &Vector4::SetW).
			endClass().
			endNamespace().
			endNamespace();
	}
	float w;
};

#endif //