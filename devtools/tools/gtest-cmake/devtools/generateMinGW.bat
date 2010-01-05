@echo off

rem ********************************************************
rem MinGW (out-of-source) makefile generator for Google Test
rem ********************************************************

rem Set directories
set GOOGLE_TEST_DEV_DIR=%cd%
set GOOGLE_TEST_ROOT_DIR=%GOOGLE_TEST_DEV_DIR%\..

rem Generate the MinGW makefile (32 bits) for all configurations
echo.
echo.Generating MinGW makefile (32 bits)
echo.-----------------------------------

echo.
echo.Generating Debug makefile
mkdir %GOOGLE_TEST_DEV_DIR%\MinGW\Debug
cd %GOOGLE_TEST_DEV_DIR%\MinGW\Debug
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug %GOOGLE_TEST_ROOT_DIR%

echo.
echo.Generating Release makefile
mkdir %GOOGLE_TEST_DEV_DIR%\MinGW\Release
cd %GOOGLE_TEST_DEV_DIR%\MinGW\Release
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release %GOOGLE_TEST_ROOT_DIR%

echo.
echo.Generating RelWithDebInfo makefile
mkdir %GOOGLE_TEST_DEV_DIR%\MinGW\RelWithDebInfo
cd %GOOGLE_TEST_DEV_DIR%\MinGW\RelWithDebInfo
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo %GOOGLE_TEST_ROOT_DIR%

echo.
echo.Generating MinSizeRel makefile
mkdir %GOOGLE_TEST_DEV_DIR%\MinGW\MinSizeRel
cd %GOOGLE_TEST_DEV_DIR%\MinGW\MinSizeRel
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel %GOOGLE_TEST_ROOT_DIR%

rem Back to dev directory
cd %GOOGLE_TEST_DEV_DIR%