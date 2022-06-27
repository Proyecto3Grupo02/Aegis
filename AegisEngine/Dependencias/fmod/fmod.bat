@echo off

set DEBUG_DLLS_DIR=..\..\Exes\AegisEngine\x64\Debug
set RELEASE_DLLS_DIR=..\..\Exes\AegisEngine\x64\Release


echo Copying fmod .dll files

::Copiamos los dlls 
XCOPY /y /d .\lib\x64\fmod.dll %DEBUG_DLLS_DIR%
XCOPY /y /d .\lib\x64\fmod.dll %RELEASE_DLLS_DIR%
  