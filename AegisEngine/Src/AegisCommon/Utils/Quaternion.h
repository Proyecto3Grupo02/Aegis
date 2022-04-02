#pragma once

#ifndef QUATERNION_H
#define QUATERNION_H
#include <tgmath.h>
#include <math.h>
#include "Vector4.h"
#include "MathUtils.h"

struct Quaternion {
public:
	Quaternion() :x(0), y(0), z(0), w(1)
	{
	};

	Quaternion(float x, float y, float z, float w) :x(x), y(y), z(z), w(w)
	{
	};
	~Quaternion() {};

	Vector3 GetEulerAngles() const {
		Vector3 euler;

		// if the input quaternion is normalized, this is exactly one. Otherwise, this acts as a correction factor for the quaternion's not-normalizedness
		float unit = (x * x) + (y * y) + (z * z) + (w * w);

		// this will have a magnitude of 0.5 or greater if and only if this is a singularity case
		float test = x * w - y * z;

		if (test > 0.4995f * unit) // singularity at north pole
		{
			euler.SetX(MathUtils::PI / 2);
			euler.SetY(2.0f * atan2(y, x));
			euler.SetZ(0);
		}
		else if (test < -0.4995f * unit) // singularity at south pole
		{
			euler.SetX(-MathUtils::PI / 2);
			euler.SetY(-2.0f * atan2(y, x));
			euler.SetZ(0);
		}
		else // no singularity - this is the majority of cases
		{
			euler.SetX(asin(2.0f * (w * x - y * z)));
			euler.SetY(atan2(2.0f * w * y + 2.0f * z * x, 1 - 2.0f * (x * x + y * y)));
			euler.SetZ(atan2(2.0f * w * z + 2.0f * x * y, 1 - 2.0f * (z * z + x * x)));
		}
		// all the math so far has been done in radians. Before returning, we convert to degrees...
		euler *= MathUtils::Rad2Deg;

		return euler;
	}

	static Quaternion eulerToQuaternion(const Vector3& euler){
		float	factor = MathUtils::PI / 360;

		float xOver2 = euler.x * factor;
		float yOver2 = euler.y * factor;
		float zOver2 = euler.z * factor;

		float sinXOver2 = sin(xOver2);
		float cosXOver2 = cos(xOver2);
		float sinYOver2 = sin(yOver2);
		float cosYOver2 = cos(yOver2);
		float sinZOver2 = sin(zOver2);
		float cosZOver2 = cos(zOver2);

		Quaternion result;
		result.SetX(cosYOver2 * sinXOver2 * cosZOver2 + sinYOver2 * cosXOver2 * sinZOver2);
		result.SetY(sinYOver2 * cosXOver2 * cosZOver2 - cosYOver2 * sinXOver2 * sinZOver2);
		result.SetZ(cosYOver2 * cosXOver2 * sinZOver2 - sinYOver2 * sinXOver2 * cosZOver2);
		result.SetW(cosYOver2 * cosXOver2 * cosZOver2 + sinYOver2 * sinXOver2 * sinZOver2);

		return result;
	}

	bool isIdentity() const {
		return x == 0.0f && y == 0.0f && z == 0.0f && w == 1.0f;
	}
	float getAngle() const {
		return acos(w) * 2.0f;
	}

	float magnitudeSquared() {
		return x * x + y * y + z * z + w * w;
	}

	float dot(const Quaternion& v) const {
		return x * v.x + y * v.y + z * v.z + w * v.w;
	}

	Vector3 rotate(const Vector3& v) const
	{
		const float vx = 2.0f * v.x;
		const float vy = 2.0f * v.y;
		const float vz = 2.0f * v.z;
		const float w2 = w * w - 0.5f;
		const float dot2 = (GetX() * vx + GetY() * vy + GetZ() * vz);
		return Vector3((vx * w2 + (GetY() * vz - GetZ() * vy) * GetW() + GetX() * dot2),
			(vy * w2 + (GetZ() * vx - GetX() * vz) * GetW() + GetY() * dot2),
			(vz * w2 + (vy - GetY() * vx) * GetW() + GetZ() * dot2));
	}


	inline float GetX()const { return x; }
	inline float GetY()const { return y; }
	inline float GetZ()const { return z; }
	inline float GetW()const { return w; }

	inline void SetX(float x) { this->x = x; return; }
	inline void SetY(float y) { this->y = y; return; }
	inline void SetZ(float z) { this->z = z; return; }
	inline void SetW(float w) { this->w = w; return; }


	Quaternion operator+(Quaternion const& b) { return Quaternion(x + b.x, y + b.y, z + b.z, w + b.w); }
	Quaternion operator-(Quaternion const& b) { return Quaternion(x - b.x, y - b.y, z - b.z, w - b.w); }
	Quaternion operator*(Quaternion const& b) { return Quaternion(x * b.x, y * b.y, z * b.z, w * b.w); }
	Quaternion operator*(float const& f) { return Quaternion(x * f, y * f, z * f, w * f); }

	bool operator==(Quaternion const& b) { return ((x == b.x) && (y == b.y) && (z == b.z) && (w == b.w)); }
	bool operator!=(Quaternion const& b) { return !(x == b.x) && (y == b.y) && (z == b.z) && (w == b.w); }


	//define
	static void ConvertToLua(lua_State* state) {
		getGlobalNamespace(state).
			beginNamespace("ECS").
			beginNamespace("Maths").
			beginClass<Quaternion>("Quaternion").
			addConstructor<void(*)(float, float, float, float)>().
			addProperty("x", &Quaternion::GetX, &Quaternion::SetX).
			addProperty("y", &Quaternion::GetY, &Quaternion::SetY).
			addProperty("z", &Quaternion::GetZ, &Quaternion::SetZ).
			addProperty("w", &Quaternion::GetW, &Quaternion::SetW).
			addFunction("ToEuler", &Quaternion::GetEulerAngles).
			addFunction("GetAngle", &Quaternion::getAngle).
			addFunction("Rotate", &Quaternion::rotate).
			addStaticFunction("EulerToQuaternion", &Quaternion::eulerToQuaternion).
			endClass().
			endNamespace().
			endNamespace();
	}

protected:
	float x;
	float y;
	float z;
	float w;
};


#endif