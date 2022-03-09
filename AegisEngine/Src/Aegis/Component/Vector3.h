#pragma once


class Vector3 {
public:
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
	Vector3() : x(), y(), z() {};

	float GetX() { return x; }
	float GetY() { return y; }
	float GetZ() { return z; }

	void SetX(float _x) { x = _x; }
	void SetY(float _y) { x = _y; }
	void SetZ(float _z) { x = _z; }

	Vector3 operator+(Vector3 const& b) { return Vector3(x + b.x, y + b.y, z + b.z); }
	Vector3 operator-(Vector3 const& b) { return Vector3(x - b.x, y - b.y, z - b.z); }
	Vector3 operator*(Vector3 const& b) { return Vector3(x * b.x, y * b.y, z * b.z); }
	Vector3 operator*(float const& f) { return Vector3(x * f, y * f, z * f); }
	bool operator==(Vector3 const& b) { return ((x == b.x) && (y == b.y) && (z == b.z)); }
	bool operator!=(Vector3 const& b) { return !((x == b.x) && (y == b.y) && (z == b.z)); }
protected:
	float x;
	float y;
	float z;
};