#include "LuaManager.h"
#include <iostream>


//typedef int (*lua_CFunction) (lua_State* L);

extern "C" int howdy(lua_State * state)
{
	// The number of function arguments will be on top of the stack.
	int args = lua_gettop(state);

	printf("howdy() was called with %d arguments:\n", args);

	for (int n = 1; n <= args; ++n) {
		printf("  argument %d: '%s'\n", n, lua_tostring(state, n));
	}

	lua_pushnumber(state, 123);

	// Let Lua know how many return values we've passed
	return 1;
}

LuaManager::LuaManager()
{
	state = luaL_newstate();
	luaL_openlibs(state);
	RegisterFunctionsToLua();
}

LuaManager::~LuaManager()
{
	lua_close(state);
}

void LuaManager::Execute(const char* filename)
{
	// ESTO ES TEMPORAL
	std::string name = "../Assets/LuaScripts/";
	name += filename;

	// Load the program; this supports both source code and bytecode files.
	int result = luaL_loadfile(state, name.c_str());

	if (result != LUA_OK) {
		PrintError(state);
		return;
	}

	// Finally, execute the program by calling into it.
	// Change the arguments if you're not running vanilla Lua code.
	result = lua_pcall(state, 0, LUA_MULTRET, 0);

	if (result != LUA_OK) {
		PrintError(state);
		return;
	}
}

void LuaManager::PrintError(lua_State* state)
{
	// The error message is on top of the stack.
	// Fetch it, print it and then pop it off the stack.
	const char* message = lua_tostring(state, -1);
	puts(message);
	lua_pop(state, 1);
}

void LuaManager::RegisterFunction(lua_CFunction function, const char* functionName)
{
	lua_register(state, functionName, function);
}

lua_State* LuaManager::GetState()
{
	return this->state;
}

void LuaManager::RegisterFunctionsToLua()
{
	RegisterFunction(howdy, "howdy");
}
