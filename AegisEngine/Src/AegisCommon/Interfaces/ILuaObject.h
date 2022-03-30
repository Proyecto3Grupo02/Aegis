#pragma once

#include "../Utils/Scripting.h"

class ILuaObject
{
public:
	static void ConvertToLua(lua_State* state);
};