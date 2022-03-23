@echo off

cd .\Dependencias

set LUA_BAT=.\Lua.bat
set OGRE_BAT=.\Ogre.bat
set BULLET_BAT=.\Bullet.bat

if not exist %LUA_BAT% echo ERROR: Lua.bat does not exist
if exist %LUA_BAT% .\Lua.bat

if not exist %OGRE_BAT% echo ERROR: Ogre.bat does not exist
if exist %OGRE_BAT% .\Ogre.bat

if not exist %BULLET_BAT% echo ERROR: Bullet.bat does not exist
if exist %BULLET_BAT% .\Bullet.bat