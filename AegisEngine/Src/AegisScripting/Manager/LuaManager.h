#pragma once

#ifndef LUA_MANAGER
#define LUA_MANAGER
#include "../../AegisCommon/Utils/Singleton.h"

#include "../Utils/LuaBasic.h"

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
	lua_State* GetState();
	int setLuaPath(lua_State* L, const char* path);
	luabridge::LuaRef GetSharedEmptyLuaRef();
	luabridge::LuaRef GetNewEmptyTable();
private:
	lua_State* state;
	luabridge::LuaRef empty = luabridge::LuaRef(state);
};

inline LuaManager* LuaMngr()
{
	return LuaManager::getInstance();
}


#endif