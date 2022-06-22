#pragma once

#ifndef LUA_MANAGER
#define LUA_MANAGER
#include "Singleton.h"
#include "LuaBasic.h"

//EXPLICACION LUA (29 de marzo): 
//* EN \Exes\AegisEngine\x64\Assets\LuaScripts teneis archivos LUA. 
//* ESOS ARCHIVOS DE MOMENTO HACEN PRINTF O LLAMAN A FUNCIONES DE LUAMANAGER (howdy).
//* LA MECANICA ES QUE AegisMain HAGA luaManager->Execute("ARCHIVO.lua"), EL CUAL LLMARA A LA FUNCION C++ DESEADA.

//namespace Lua {
//	class LuaScript;
//}

template <typename T>
extern void exportToLua(T item, const char* name);

class LuaManager : public Singleton<LuaManager> {
public:
	LuaManager();
	virtual ~LuaManager();
	bool execute(const char* filename);
	void printError(lua_State* state);
	void registerFunction(lua_CFunction function, const char* functionName);
	lua_State* getState();
	int addPath(const char* path);
	luabridge::LuaRef getSharedEmptyLuaRef();
	luabridge::LuaRef getNewEmptyTable();
	
	float parseFloat(luabridge::LuaRef ref, float defaultValue = 0);
	std::string parseString(luabridge::LuaRef ref, std::string defaultString = "");

	//if nil, it returns false
	bool parseBool(luabridge::LuaRef ref, bool defaultBool = false);
private:
	lua_State* state = nullptr;
	luabridge::LuaRef empty = luabridge::LuaRef(state);
};

inline LuaManager* LuaMngr()
{
	return LuaManager::getInstance();
}
#endif
