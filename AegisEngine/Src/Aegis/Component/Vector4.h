#pragma once
#include <Vector3.h>

template<typename T>
class Vector4 : public Vector3<T> {
public:
	Vector4(T _x, T _y, T _z, T _w) : Vector3<T>(_x, _y, _z), w(_w) {};
	Vector4() : Vector3<T>(), w() {};

	T GetW() { return w; }
	void SetW(T _w) { w = _w; }

	Vector4 operator+(Vector4 const& b) { return Vector4(x + b.x, y + b.y, z + b.z, w + b.w); }
	Vector4 operator-(Vector4 const& b) { return Vector4(x - b.x, y - b.y, z - b.z, w - b.w); }
	Vector4 operator*(Vector4 const& b) { return Vector4(x * b.x, y * b.y, z * b.z, w * b.w); }
	Vector4 operator*(float const& f) { return Vector4(x * f, y * f, z * f, w * f); }
	bool operator==(Vector4 const& b) { return ((x == b.x) && (y == b.y) && (z == b.z) && (w == b.w)); }
	bool operator!=(Vector4 const& b) { return !(this == b); }

protected:
	T w;
};