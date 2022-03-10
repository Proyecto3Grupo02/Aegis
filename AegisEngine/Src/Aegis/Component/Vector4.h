#pragma once
#include "Vector3.h"

class Vector4 : public Vector3 {
public:
	Vector4(float _x, float _y, float _z, float _w) : Vector3(_x, _y, _z), w(_w) {};
	Vector4(float _all) : Vector3(_all), w(_all) {};
	Vector4() : Vector3(), w(1.0f) {};

	float GetW() { return w; }
	void SetW(float _w) { w = _w; }

	Vector4 operator+(Vector4 const& b) { return Vector4(x + b.x, y + b.y, z + b.z, w + b.w); }
	Vector4 operator-(Vector4 const& b) { return Vector4(x - b.x, y - b.y, z - b.z, w - b.w); }
	Vector4 operator*(Vector4 const& b) { return Vector4(x * b.x, y * b.y, z * b.z, w * b.w); }
	Vector4 operator*(float const& f) { return Vector4(x * f, y * f, z * f, w * f); }
	bool operator==(Vector4 const& b) { return ((x == b.x) && (y == b.y) && (z == b.z) && (w == b.w)); }
	bool operator!=(Vector4 const& b) { return !(x == b.x) && (y == b.y) && (z == b.z) && (w == b.w); }

protected:
	float w;
};