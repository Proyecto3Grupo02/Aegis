@echo off

set OGRE_BAT=.\ogre.bat
set BULLET_BAT=.\bullet.bat
set LUA_BAT=.\lua.bat
set AEGIS_BAT=.\aegis.bat
goto a

cd .\Dependencias\Ogre
if not exist %OGRE_BAT% goto errorOgre
if exist %OGRE_BAT% call %OGRE_BAT%

cd ..\Bullet
if not exist %BULLET_BAT% goto errorBullet
if exist %BULLET_BAT% call %BULLET_BAT%

cd ..\Lua
if not exist %LUA_BAT% goto errorLua
if exist %LUA_BAT% call %LUA_BAT%

cd ..\..\Exes
dir
if not exist %AEGIS_BAT% goto errorAegis
if exist %AEGIS_BAT% call %AEGIS_BAT%

goto end

:errorOgre
echo ERROR: ogre.bat does not exist
goto end

:errorBullet
echo ERROR: bullet.bat does not exist
goto end

:errorLua
echo ERROR: lua.bat does not exist
goto end

:errorAegis
echo ERROR: aegis.bat does not exist
goto end

:a
dir
::Creating build folder with a release version
echo copiandoAssets
mkdir Build
dir
XCOPY /y /d /s .\Exes\AegisEngine\x64\Release .\Build

:end