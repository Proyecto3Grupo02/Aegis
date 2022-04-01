@echo off

cd Dependencias
set LUA_BAT=.\Lua.bat
set OGRE_BAT=.\Ogre.bat
set BULLET_BAT=.\Bullet.bat

if not exist %LUA_BAT% goto errorLua
if exist %LUA_BAT% call %LUA_BAT%


if not exist %OGRE_BAT% goto errorOgre
if exist %OGRE_BAT% call %OGRE_BAT%

if not exist %BULLET_BAT% goto errorBullet
if exist %BULLET_BAT% call %BULLET_BAT%



goto end

:errorLua
echo ERROR: Lua.bat does not exist
goto end

:errorBullet
echo ERROR: Bullet.bat does not exist
goto end

:errorOgre
echo ERROR: Ogre.bat does not exist
goto end

:end