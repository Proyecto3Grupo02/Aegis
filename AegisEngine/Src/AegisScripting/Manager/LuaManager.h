#pragma once

#ifndef LUA_MANAGER
#define LUA_MANAGER
#include "../../AegisCommon/Utils/Singleton.h"

#include "LuaBasic.h"

namespace Lua {
	class LuaScript;
}
class LuaManager : public Singleton<LuaManager> {
public:
	LuaManager();
	virtual ~LuaManager();
	void Execute(const char* filename);
	void PrintError(lua_State* state);
	void RegisterFunction(lua_CFunction function, const char* functionName);
private:
	void RegisterFunctionsToLua();
	lua_State* state;
};


#endif