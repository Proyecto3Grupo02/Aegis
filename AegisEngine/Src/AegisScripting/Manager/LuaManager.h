#pragma once

#ifndef LUA_MANAGER
#define LUA_MANAGER
#include "../../AegisCommon/Utils/Singleton.h"
#include "../Utils/LuaBasic.h"

//EXPLICACION LUA (29 de marzo): 
//* EN \Exes\AegisEngine\x64\Assets\LuaScripts teneis archivos LUA. 
//* ESOS ARCHIVOS DE MOMENTO HACEN PRINTF O LLAMAN A FUNCIONES DE LUAMANAGER (howdy).
//* LA MECANICA ES QUE AegisMain HAGA luaManager->Execute("ARCHIVO.lua"), EL CUAL LLMARA A LA FUNCION C++ DESEADA.

//namespace Lua {
//	class LuaScript;
//}

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
	
	float ParseFloat(luabridge::LuaRef ref, float defaultValue = 0);
	std::string ParseString(luabridge::LuaRef ref, std::string defaultString = "");

	//if nil, it returns false
	bool ParseBool(luabridge::LuaRef ref, bool defaultBool = false);

private:
	lua_State* state;
	luabridge::LuaRef empty = luabridge::LuaRef(state);
};

inline LuaManager* LuaMngr()
{
	return LuaManager::getInstance();
}
#endif
