@echo off

:: Batch variables
set LUA_BUILD_SLN=.\Lua\Lua.sln
set LUA_LIB_PATH =.\Lua\build\Lua_Project.lib

:: Make the build directory
if exist %LUA_LIB_PATH% goto done

:: Build Lua
echo Compiling Lua...

msbuild %LUA_BUILD_SLN% /t:Lua_Project /p:platform=x64 /p:configuration=Debug
msbuild %LUA_BUILD_SLN% /t:Lua_Project /p:platform=x64 /p:configuration=Release 

echo Lua compiled

goto end

:done

:: Confirmation message
echo Lua already compiled

:end