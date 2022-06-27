@echo off

set BUILD_DIR=.\build
set SOURCE_DIR=.\src
set CMAKE_DIR=..\cmake\bin\cmake.exe
set SDL2_BUILD_SOL=.\build\SDL2-build\SDL2.sln
set OGRE_BUILD_SOL=.\build\OGRE.sln

if exist %BUILD_DIR% goto buildsol
mkdir %BUILD_DIR%

:: Building Ogre project
%CMAKE_DIR% -S %SOURCE_DIR% -B %BUILD_DIR% 
        -D CMAKE_CONFIGURATION_TYPES:STRING 
        -D CMAKE_CONFIGURATION_TYPES:STRING=Debug;Release 
        -D OGRE_BUILD_COMPONENT_BITES:BOOL=0 
        -D OGRE_BUILD_PLUGIN_DOT_SCENE:BOOL=0 
        -D OGRE_BUILD_RENDERSYSTEM_D3D11:BOOL=0 
        -D OGRE_BUILD_RENDERSYSTEM_D3D9:BOOL=0 
        -D OGRE_BUILD_RENDERSYSTEM_GLES2:BOOL=0 
        -D OGRE_BUILD_RENDERSYSTEM_TINY:BOOL=0 
        -D OGRE_BUILD_RENDERSYSTEM_VULKAN:BOOL=0 
        -D OGRE_BUILD_RTSHADERSYSTEM_SHADERS:BOOL=1 
        -D OGRE_BUILD_SAMPLES:BOOL=0 
        -D OGRE_INSTALL_SAMPLES:BOOL=0 

echo Ogre and SDL build generated

:buildsol
::Compiling Ogre and SDL projects
echo Compiling SDL2
msbuild %SDL2_BUILD_SOL%   /p:platform=x64 /p:configuration=Debug
msbuild %SDL2_BUILD_SOL%   /p:platform=x64 /p:configuration=Release

echo Compiling Ogre
msbuild %OGRE_BUILD_SOL%   /p:platform=x64 /p:configuration=Debug
msbuild %OGRE_BUILD_SOL%  /p:platform=x64 /p:configuration=Release

echo Ogre and Lua compilation finsished.