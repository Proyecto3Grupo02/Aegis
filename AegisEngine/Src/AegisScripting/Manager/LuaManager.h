#pragma once

#ifndef LUA_MANAGER
#define LUA_MANAGER
#include "../../AegisCommon/Utils/Singleton.h"
#include "../Utils/LuaBasic.h"
#include "../../checkML.h" //BASURA

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

private:
	void RegisterFunctionsToLua();
	lua_State* state;
};


#endif