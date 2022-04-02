#pragma once
#include "Randomized.h"
#include <math.h>
#include <iostream>

using namespace std;

namespace MathUtils
{
	constexpr float PI = 3.14159265358979323846;
	constexpr float Rad2Deg = PI / 180.0f;
	constexpr float Deg2Rad = 180.0f / PI;

	static float Lerp(float start_value, float end_value, float pct)
	{
		return (start_value + (end_value - start_value) * pct);
	}

	static int loop(int min, int max, int current)
	{
		return  min + (abs(current + abs(max - min)) % max);
	}

	//[min, max)
	static float loopF(float min, float max, float current)
	{
		return  min + fmod(abs(current + abs(max - min)), max);
	}

	static float maxOf(float a, float b, float c) {
		return ((a > b) ? (a > c ? a : c) : (b > c ? b : c));
	}
	static float minOf(float a, float b, float c) {
		return ((a < b) ? (a < c ? a : c) : (b < c ? b : c));
	}

	static float InverseLerp(float start_value, float end_value, float currentValue)
	{
		float start = 0;
		float current = currentValue - start_value;
		float end = end_value - start_value;
		return (min(currentValue, end_value) / end_value);
	}

	static Vector3 Lerp(Vector3 start_value, Vector3 end_value, float t)
	{
		return Vector3(
			start_value.x + (end_value.x - start_value.x) * t,
			start_value.y + (end_value.y - start_value.y) * t,
			start_value.z + (end_value.z - start_value.z) * t
		);
	}

	static Vector4 Lerp(Vector4 start_value, Vector4 end_value, float t)
	{
		return Vector4(
			start_value.x + (end_value.x - start_value.x) * t,
			start_value.y + (end_value.y - start_value.y) * t,
			start_value.z + (end_value.z - start_value.z) * t,
			start_value.w + (end_value.w - start_value.w) * t
		);
	}

	// Returns IN DEGREES angle between 2 vectors
	static float AngleBetweenDEG(Vector3 from, Vector3 to)
	{
		return acos((from.x * to.x + from.y * to.y + from.z * to.z) / (sqrt(from.x * from.x + from.y * from.y + from.z * from.z) * (sqrt(to.x * to.x + to.y * to.y + to.z * to.z))));
	}

	// Returns IN RADIANS angle between 2 
	static float AngleBetweenRAD(Vector3 from, Vector3 to)
	{
		from.normalize();
		to.normalize();
		const float dotProduct = from.dot(to);

		return acos(dotProduct);
	}

	static Vector4 Vector32Vector4(Vector3 color, float alpha = 1)
	{
		return Vector4(color.x, color.y, color.z, alpha);
	}

	static Vector3 Vector4_TO_Vector3(Vector4 color)
	{
		return Vector3(color.x, color.y, color.z);
	}

	static Vector3 UnitToRGB(Vector3 color)
	{
		return color * 255.0f;
	}

	static Vector3 RotatedFromTo(const Vector3 point, const Vector3 rotationAxis, float angle)
	{
		float cos_theta = cos(angle);
		float sin_theta = sin(angle);

		Vector3 rotated = (point * cos_theta) + (rotationAxis.cross(point) * sin_theta) + Vector3((rotationAxis.dot(Vector3(rotationAxis.dot(point)))) * (1 - cos_theta));

		return rotated;
	}

	//Si el numero es negativo devuelve -1, si es positivo devuelve 1
	template <typename T> int sign(T val) {
		return (T(0) < val) - (val < T(0));
	}

	static Vector3 PerpendicularTo(Vector3 to)
	{
		float a = 1;
		float b = 1;
		float c = 1;

		float x = to.x;
		float y = to.y;
		float z = to.z;

		if (x != 0)
			a = -max((y + z) / x, (float)sign(x));
		else if (y != 0)
			b = -max((x + z) / y, (float)sign(y));
		else if (z != 0)
			c = -max((x + y) / z, (float)sign(z));
		else a = b = c = 0;

		if (z == 0 && y == 0) return Vector3(0, -x, 0);
		if (x == 0 && z == 0) return Vector3(0, 0, -y);
		if (x == 0 && y == 0) return Vector3(-z, 0, 0);

		return Vector3(a, b, c);
	}

	static float Distance(Vector3 start, Vector3 end)
	{
		return (start - end).magnitude();
	}

	static float DistanceSquared(Vector3 start, Vector3 end)
	{
		return (start - end).magnitudeSquared();
	}

	//Uso la distancia al cuadrado por eficiencie, si usara la distancia normal por debajo se llama a .magnitude que 
	//tiene que hacer una raiz cuadrada, es un calculo un poco costoso y de esta forma lo evito
	static bool IsInsideSphere(Vector3 point, Vector3 sphereCenter, float sphereRadius)
	{
		return DistanceSquared(point, sphereCenter) < sphereRadius * sphereRadius;
	}

	static bool SphereIntersection(Vector3 pointA, float radiusA, Vector3 pointB, float radiusB)
	{
		float r = radiusA + radiusB;
		float d2 = DistanceSquared(pointA, pointB);
		return d2 < r* r;
	}

	static float SpherePenetration(Vector3 pointA, float radiusA, Vector3 pointB, float radiusB)
	{
		float r = radiusA + radiusB;
		float d2 = Distance(pointA, pointB);
		return abs(d2 - r);
	}

	static bool IsInsideBox(Vector3 point, Vector3 boxCenter, float width, float height, float depth)
	{
		return true;
	}
}