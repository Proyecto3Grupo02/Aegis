#pragma once

#include "../Utils/Scripting.h"

struct ILuaObject
{
public:
	static void ConvertToLua(lua_State* state);
};

template <typename T>
inline void ExportToLua(T item, const char* name)
{
	auto state = LuaMngr()->GetState();
	push(state, item);
	lua_setglobal(state, name);
}