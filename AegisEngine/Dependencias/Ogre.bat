:: Batch variables
set SRC_DIR=.\Dependencias\Ogre\src\
set BUILD_DIR=.\Dependencias\Ogre\build\

set OGRE_BUILD_SOL=.\build\OGRE.sln
set SDL2_BUILD_SOL=.\Dependencias\build\SDL-build\SDL2.sln

set CMAKE_EXE=.\Dependencias\Cmake\bin\cmake.exe

if not exist %BUILD_DIR% mkdir %BUILD_DIR%
if exist %OGRE_BUILD_SOL% goto done

:: Configurations of cmake

%CMAKE_EXE% -D CMAKE_CONFIGURATION_TYPES:STRING 
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
            -S %SRC_DIR% -B %BUILD_DIR%

echo OGRE and SDL2 build generated

echo compiling OGRE...
msbuild %OGRE_BUILD_SOL%  /t:ALL_BUILD /p:platform=x64 /p:configuration=Debug
msbuild %OGRE_BUILD_SOL%  /t:ALL_BUILD /p:platform=x64 /p:configuration=Release
echo OGRE compiled correctly

echo compiling SDL2...
msbuild %OGRE_BUILD_SOL%  /t:ALL_BUILD /p:platform=x64 /p:configuration=Debug
msbuild %OGRE_BUILD_SOL%  /t:ALL_BUILD /p:platform=x64 /p:configuration=Release
echo SDL2 compiled correctly

goto end

:done
echo OGRE and SDL2 already built and compiled 

:end