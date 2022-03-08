#pragma once

template<typename T>
class Vector3 {
public:
	Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {};
	Vector3() : x(), y(), z() {};

	T GetX() { return x; }
	T GetY() { return y; }
	T GetZ() { return z; }

	void SetX(T _x) { x = _x; }
	void SetY(T _y) { x = _y; }
	void SetZ(T _z) { x = _z; }

	Vector3 operator+(Vector3 const& b) { return Vector3(x + b.x, y + b.y, z + b.z); }
	Vector3 operator-(Vector3 const& b) { return Vector3(x - b.x, y - b.y, z - b.z); }
	Vector3 operator*(Vector3 const& b) { return Vector3(x * b.x, y * b.y, z * b.z); }
	Vector3 operator*(float const& f) { return Vector3(x * f, y * f, z * f); }
	bool operator==(Vector3 const& b) { return ((x == b.x) && (y == b.y) && (z == b.z)); }
	bool operator!=(Vector3 const& b) { return !(this == b); }
protected:
	T x;
	T y;
	T z;
};