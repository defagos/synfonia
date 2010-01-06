@echo off

rem *****************************************************
rem MinGW (out-of-source) makefile generator for Synfonia
rem *****************************************************

rem Set directories
set SYNFONIA_DEV_DIR=%cd%
set SYNFONIA_ROOT_DIR=%SYNFONIA_DEV_DIR%\..

rem Generate the MinGW makefile (32 bits) for all configurations
echo.
echo.Generating MinGW makefile (32 bits)
echo.-----------------------------------

echo.
echo.Generating Debug makefile
mkdir "%SYNFONIA_DEV_DIR%\MinGW\Debug"
cd "%SYNFONIA_DEV_DIR%\MinGW\Debug"
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug "%SYNFONIA_ROOT_DIR%"

echo.
echo.Generating Release makefile
mkdir "%SYNFONIA_DEV_DIR%\MinGW\Release"
cd "%SYNFONIA_DEV_DIR%\MinGW\Release"
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release "%SYNFONIA_ROOT_DIR%"

echo.
echo.Generating RelWithDebInfo makefile
mkdir "%SYNFONIA_DEV_DIR%\MinGW\RelWithDebInfo"
cd "%SYNFONIA_DEV_DIR%\MinGW\RelWithDebInfo"
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo "%SYNFONIA_ROOT_DIR%"

echo.
echo.Generating MinSizeRel makefile
mkdir "%SYNFONIA_DEV_DIR%\MinGW\MinSizeRel"
cd "%SYNFONIA_DEV_DIR%\MinGW\MinSizeRel"
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel "%SYNFONIA_ROOT_DIR%"

rem Back to dev directory
cd "%SYNFONIA_DEV_DIR%"