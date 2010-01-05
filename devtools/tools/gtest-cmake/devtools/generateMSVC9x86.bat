@echo off

rem ****************************************************************************
rem Visual Studio 2008 32-bit (out-of-source) solution generator for Google Test
rem ****************************************************************************

rem Set directories
set GOOGLE_TEST_DEV_DIR=%cd%
set GOOGLE_TEST_ROOT_DIR=%GOOGLE_TEST_DEV_DIR%\..

rem Generate the Microsoft Visual Studio 2008 solution for all configurations
echo.
echo.Generating Visual Studio 2008 solution (32 bits)
echo.------------------------------------------------
mkdir %GOOGLE_TEST_DEV_DIR%\MSVC9x86
cd %GOOGLE_TEST_DEV_DIR%\MSVC9x86
cmake -G "Visual Studio 9 2008" %GOOGLE_TEST_ROOT_DIR%

rem Back to dev directory
cd %GOOGLE_TEST_DEV_DIR%