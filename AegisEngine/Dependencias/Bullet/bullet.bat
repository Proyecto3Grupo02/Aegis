@echo off

set SRC_DIR=.\src
set BUILD_DIR=.\build
set CMAKE_DIR=..\cmake\bin\cmake.exe
set BULLET_BUILD_SOL=.\build\BULLET_PHYSICS.sln

:: Make the build directory
if exist %BULLET_BUILD_SOL% goto buildsol
mkdir %BUILD_DIR%

:: Generate the build
echo Generating Bullet build...

%CMAKE_DIR% -S %SRC_DIR% -B %BUILD_DIR%
            -D CMAKE_CONFIGURATION_TYPES:STRING=Debug;Release
            -D BUILD_BULLET2_DEMOS:BOOL=0
            -D BUILD_CPU_DEMOS:BOOL=0
            -D BUILD_OPENGL3_DEMOS:BOOL=0
            -D USE_MSVC_RUNTIME_LIBRARY_DLL:BOOL=1
	        -DINSTALL_LIBS=ON
             

echo Bullet build succesfully generated

:buildsol
:: Build OGRE library
echo Compiling Bullet library...

msbuild %BULLET_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Debug
msbuild %BULLET_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Release 

echo Bullet library compiled

:: Confirmation message
echo Bullet already built and compiled
