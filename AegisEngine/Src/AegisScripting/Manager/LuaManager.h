#pragma once

#ifndef LUA_MANAGER
#define LUA_MANAGER
#include "../../AegisCommon/Utils/Singleton.h"

#ifdef __cplusplus
#include <lua.hpp>
#else
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#endif

namespace Lua {
	class LuaScript;
}
class LuaManager : public Singleton<LuaManager> {
public:
	LuaManager();
	virtual ~LuaManager();
	void Execute(const char* filename);
	void PrintError(lua_State* state);
private:
};


#endif