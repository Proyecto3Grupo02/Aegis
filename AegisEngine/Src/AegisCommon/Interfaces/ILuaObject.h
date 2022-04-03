#pragma once

#include "../Utils/Scripting.h"

struct ILuaObject
{
public:
	static void ConvertToLua(lua_State* state);
};