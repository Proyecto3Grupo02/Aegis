#pragma once

#include "Scripting.h"
#define LuaMngr LuaManager::getInstance()

struct ILuaObject
{
public:
	static void ConvertToLua(lua_State* state);
};

template <typename T>
inline void exportToLua(T item, const char* name)
{
	auto state = LuaMngr->getState();
	push(state, item);
	lua_setglobal(state, name);
}