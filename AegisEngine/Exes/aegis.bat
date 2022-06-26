@echo off
:: Batch variables
set AEGIS_BUILD_SLN=..\AegisEngine.sln

:: Build Aegis
echo Compiling Aegis...

msbuild %AEGIS_BUILD_SLN% /p:platform=x64 /p:configuration=Debug
msbuild %AEGIS_BUILD_SLN% /p:platform=x64 /p:configuration=Release 

echo Aegis compiled