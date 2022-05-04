#pragma once

#include "MathUtils.h"

namespace LuaMaths
{
	static void ConvertToLua(lua_State* state)
	{
		getGlobalNamespace(state).
			beginNamespace("Aegis").
			beginNamespace("Maths").
			addFunction("Vector3Lerp", &MathUtils::Vector3Lerp).
			endNamespace().
			endNamespace();
	}
}