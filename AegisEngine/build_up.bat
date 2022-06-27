@echo off

set OGRE_BAT=.\Dependencias\Ogre\ogre.bat
set BULLET_BAT=.\Dependencias\Bullet\bullet.bat
set FMOD_BAT=.\Dependencias\fmod\fmod.bat
set LUA_BAT=.\Dependencias\Lua\lua.bat
set AEGIS_BAT=.\Exes\aegis.bat

if not exist %OGRE_BAT% goto errorOgre
if exist %OGRE_BAT% call %OGRE_BAT%

if not exist %BULLET_BAT% goto errorBullet
if exist %BULLET_BAT% call %BULLET_BAT%

if not exist %FMOD_BAT% goto errorFmod
if exist %FMOD_BAT% call %FMOD_BAT%

if not exist %LUA_BAT% goto errorLua
if exist %LUA_BAT% call %LUA_BAT%

if not exist %AEGIS_BAT% goto errorAegis
if exist %AEGIS_BAT% call %AEGIS_BAT%

goto end

:errorOgre
echo ERROR: ogre.bat does not exist
goto end

:errorBullet
echo ERROR: bullet.bat does not exist
goto end

:errorFmod
echo ERROR: fmod.bat does not exist
goto end

:errorLua
echo ERROR: lua.bat does not exist
goto end

:errorAegis
echo ERROR: aegis.bat does not exist
goto end

:end