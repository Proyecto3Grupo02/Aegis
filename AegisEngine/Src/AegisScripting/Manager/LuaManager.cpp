#include "LuaManager.h"
#include "LuaManager.h"

LuaManager::LuaManager()
{
	state = luaL_newstate();
	empty = luabridge::LuaRef(state);
	luaL_openlibs(state);
}

LuaManager::~LuaManager() {
	lua_close(state);
}

/// <summary>
/// Carga un script y lo ejecuta. Devuelve true si se carga y ejecuta correctametne
/// </summary>
/// <param name="filename"></param>
/// <returns></returns>
bool LuaManager::execute(const char* filename) {

	// Load the program; this supports both source code and bytecode files.
	int result = luaL_loadfile(state, filename);

	if (result != LUA_OK) {
		printError(state);
		return false;
	}

	// Finally, execute the program by calling into it.
	// Change the arguments if you're not running vanilla Lua code.
	result = lua_pcall(state, 0, LUA_MULTRET, 0);

	if (result != LUA_OK) {
		printError(state);
		return false;
	}

	return true;
}

void LuaManager::printError(lua_State* state) {
	// The error message is on top of the stack.
	// Fetch it, print it and then pop it off the stack.
	const char* message = lua_tostring(state, -1);
	puts(message);
	lua_pop(state, 1);
}

float LuaManager::parseFloat(luabridge::LuaRef ref, float defaultValue)
{
	return ref.isNil() ? defaultValue : ref.cast<float>();
}

std::string LuaManager::parseString(luabridge::LuaRef ref, std::string defaultString)
{
	return ref.isNil() ? defaultString : ref.cast<std::string>();
}

bool LuaManager::parseBool(luabridge::LuaRef ref, bool defaultBool)
{
	return ref.isNil() ? defaultBool : ref.cast<bool>();
}

void LuaManager::clearGarbage()
{
	luabridge::LuaRef luaUtils = luabridge::getGlobal(state, "utils");
	luaUtils["CollectGarbage"](MAX_GARBAGE_ALLOWED_MB);
}

void LuaManager::registerFunction(lua_CFunction function, const char* functionName) {
	lua_register(state, functionName, function);
}

lua_State* LuaManager::getState()
{
	return this->state;
}

int LuaManager::addPath(const char* path)
{
	lua_State* L = state;
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

luabridge::LuaRef LuaManager::getSharedEmptyLuaRef()
{
	return empty;
}

luabridge::LuaRef LuaManager::getNewEmptyTable()
{
	return luabridge::newTable(state);
}

