@echo off

set LUA_SOL= .\Dependencias\Lua\Lua.sln 
set LUA_LIB_PATH= .\Dependencias\Lua\Lua.lib

if exist %LUA_LIB_PATH% goto done

echo Compiling Lua...

msbuild %LUA_SOL% /t:LuaProject /p:platform=x64 /p:configuration=Debug
msbuild %LUA_SOL% /t:LuaProject /p:platform=x64 /p:configuration=Release

echo Lua compiled

goto end

:done
echo Lua already compiled

:end