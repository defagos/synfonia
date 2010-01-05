@echo off

rem *************************************************************************
rem Visual Studio 2008 32-bit (out-of-source) solution generator for Synfonia
rem *************************************************************************

rem Set directories
set SYNFONIA_DEV_DIR=%cd%
set SYNFONIA_ROOT_DIR=%SYNFONIA_DEV_DIR%\..

rem Generate the Microsoft Visual Studio 2008 solution
echo.
echo.Generating Visual Studio 2008 solution (32 bits)
echo.------------------------------------------------
mkdir %SYNFONIA_DEV_DIR%\MSVC9x86
cd %SYNFONIA_DEV_DIR%\MSVC9x86
cmake -G "Visual Studio 9 2008" %SYNFONIA_ROOT_DIR%

rem Back to dev directory
cd %SYNFONIA_DEV_DIR%