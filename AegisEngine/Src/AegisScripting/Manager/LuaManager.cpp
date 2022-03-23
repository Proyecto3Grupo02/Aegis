#include "LuaManager.h"
#include <iostream>

extern "C" int howdy(lua_State * state)
{
	// The number of function arguments will be on top of the stack.
	int args = lua_gettop(state);

	printf("howdy() was called with %d arguments:\n", args);

	for (int n = 1; n <= args; ++n) {
		printf("  argument %d: '%s'\n", n, lua_tostring(state, n));
	}

	// Push the return value on top of the stack. NOTE: We haven't popped the
	// input arguments to our function. To be honest, I haven't checked if we
	// must, but at least in stack machines like the JVM, the stack will be
	// cleaned between each function call.

	lua_pushnumber(state, 123);

	// Let Lua know how many return values we've passed
	return 1;
}

LuaManager::LuaManager()
{
	lua_State* state = luaL_newstate();
	lua_close(state);
}

LuaManager::~LuaManager()
{
}

void LuaManager::Execute(const char* filename)
{
	lua_State* state = luaL_newstate();
	
	lua_register(state, "howdy", howdy);

	// Make standard libraries available in the Lua object
	luaL_openlibs(state);

	int result;

	// Load the program; this supports both source code and bytecode files.
	result = luaL_loadfile(state, filename);

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
