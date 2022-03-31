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
	setLuaPath(state, "../Assets/LuaScripts");
}

LuaManager::~LuaManager()
{
	lua_close(state);
}

void LuaManager::Execute(const char* filename)
{
	// ESTO ES TEMPORAL
	std::string name = ".\\..\\Assets\\LuaScripts\\";
	name.append(filename);

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

int LuaManager::setLuaPath(lua_State* L, const char* path)
{
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "path"); // get field "path" from table at top of stack (-1)
	std::string cur_path = lua_tostring(L, -1); // grab path string from top of stack
	cur_path.append(";"); // do your path magic here
	cur_path.append(path);
	cur_path.append("/?.lua");
	lua_pop(L, 1); // get rid of the string on the stack we just pushed on line 5
	lua_pushstring(L, cur_path.c_str()); // push the new one
	lua_setfield(L, -2, "path"); // set the field "path" in table at -2 with value at top of stack
	lua_pop(L, 1); // get rid of package table from top of stack
	return 0; // all done!
}

luabridge::LuaRef LuaManager::GetEmptyLuaRef()
{
	return luabridge::LuaRef(state);
}
