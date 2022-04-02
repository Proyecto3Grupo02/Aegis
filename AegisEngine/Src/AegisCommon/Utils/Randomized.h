#pragma once
#include <cstdlib>
#include "Vector3.h"
#include "Vector4.h"

/// <summary>
/// Pequeña libreria para obtener datos pseudoAleatorios
/// No uso plantillas (<template T>) porque prefiero dar legibilidad en los nombres
/// </summary>

namespace Randomized
{
	//Returns a number in the range of [min, max]
	static float GetRandomFloat(float&& min, float&& max) noexcept
	{
		return (max - min) * ((((float)rand()) / (float)RAND_MAX)) + min;
	}

	//Returns a number in the range of [min, max]
	static float GetRandomFloat(const float& min, const float& max) noexcept
	{
		return (max - min) * ((((float)rand()) / (float)RAND_MAX)) + min;
	}
	
	//Returns a number in the range of [min, max]
	static int GetRandomInt(int&& min, int&& max) noexcept
	{
		return rand() % (max - min) + min + 1;
	}

	//Returns a number in the range of [min, max]
	static int GetRandomInt(const int& min, const int& max) noexcept
	{
		return rand() % (max - min) + min + 1;
	}

	//Returns a Vector3 in the range of [min, max]
	//static Vector3 GetRandomVector3(Vector3 min, Vector3 max)
	//{
	//	return (min + (GetRandomFloat(0, 1) * (max - min)));
	//}

	static Vector3 ShiftVector3(Vector3 min, Vector3 max)
	{
		return Vector3(GetRandomFloat(min.x, max.x), GetRandomFloat(min.y, max.y), GetRandomFloat(min.z, max.z));
	}

	//Returns a Vector3 in the range of [min, max]
	//static Vector4 GetRandomVector4(Vector4 min, Vector4 max)
	//{
	//	return (min + (GetRandomFloat(0, 1) * (max - min)));
	//}

	static Vector4 ShiftVector4(Vector4 min, Vector4 max)
	{
		return Vector4(GetRandomFloat(min.x, max.x), GetRandomFloat(min.y, max.y), GetRandomFloat(min.z, max.z), GetRandomFloat(min.w, max.w));
	}

	//Returns a random point inside a cone of vec height and direction and radius base (perpendicular to vec direction)
	static Vector3 GetRandomPointInsideCone(Vector3 vec, float radius)
	{
		while (true) {
			float x = GetRandomFloat(-radius, radius);
			float y = GetRandomFloat(-radius, radius);
			float z = GetRandomFloat(-radius, radius);

			if (x * x + y * y + z * z <= radius * radius)
				return Vector3(x + vec.x, y + vec.y, z + vec.z);
		}
	}

	//Get random uniform point inside unitary sphere
	static Vector3 GetRandomPointInsideUnitSphere()
	{
		float x, y, z;
		x = y = z = 0;
		while (true) {
			x = GetRandomFloat(-1, 1);
			y = GetRandomFloat(-1, 1);
			z = GetRandomFloat(-1, 1);
			if (sqrt((x * x) + (y * y) + (z * z)) < 1) break;
		}
		return Vector3(x, y, z);
	}
}
