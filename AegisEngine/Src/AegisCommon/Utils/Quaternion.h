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

	Vector3 getEulerAngles() const {
		// if the input quaternion is normalized, this is exactly one. Otherwise, this acts as a correction factor for the quaternion's not-normalizedness
		Vector3 res;
		float rx = 0;
		float ry = 0;
		float rz = 0;

		double sinr_cosp = +2.0 * (w * x + y * z);
		double cosr_cosp = +1.0 - 2.0 * (x * x + y * y);
		rx = atan2(sinr_cosp, cosr_cosp);

		double sinp = +2.0 * (w * y - z * x);
		if (abs(sinp) >= 1) 
			ry = MathUtils::PI / 2 * MathUtils::sign(sinp);
		else
			ry = asin(sinp);

		double siny_cosp = +2.0 * (w * z + x * y);
		double cosy_cosp = +1.0 - 2.0 * (y * y + z * z);
		rz = atan2(siny_cosp, cosy_cosp);

		return Vector3(rx, ry, rz) * MathUtils::Rad2Deg;
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
		result.setX(cosYOver2 * sinXOver2 * cosZOver2 + sinYOver2 * cosXOver2 * sinZOver2);
		result.setY(sinYOver2 * cosXOver2 * cosZOver2 - cosYOver2 * sinXOver2 * sinZOver2);
		result.setZ(cosYOver2 * cosXOver2 * sinZOver2 - sinYOver2 * sinXOver2 * cosZOver2);
		result.setW(cosYOver2 * cosXOver2 * cosZOver2 + sinYOver2 * sinXOver2 * sinZOver2);

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
		const float dot2 = (getX() * vx + getY() * vy + getZ() * vz);
		return Vector3((vx * w2 + (getY() * vz - getZ() * vy) * getW() + getX() * dot2),
			(vy * w2 + (getZ() * vx - getX() * vz) * getW() + getY() * dot2),
			(vz * w2 + (vy - getY() * vx) * getW() + getZ() * dot2));
	}


	inline float getX()const { return x; }
	inline float getY()const { return y; }
	inline float getZ()const { return z; }
	inline float getW()const { return w; }

	inline void setX(float x) { this->x = x; return; }
	inline void setY(float y) { this->y = y; return; }
	inline void setZ(float z) { this->z = z; return; }
	inline void setW(float w) { this->w = w; return; }


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
			addProperty("x", &Quaternion::getX, &Quaternion::setX).
			addProperty("y", &Quaternion::getY, &Quaternion::setY).
			addProperty("z", &Quaternion::getZ, &Quaternion::setZ).
			addProperty("w", &Quaternion::getW, &Quaternion::setW).
			addFunction("ToEuler", &Quaternion::getEulerAngles).
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