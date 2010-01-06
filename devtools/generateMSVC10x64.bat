@echo off

rem *************************************************************************
rem Visual Studio 2010 64-bit (out-of-source) solution generator for Synfonia
rem *************************************************************************

rem Set directories
set SYNFONIA_DEV_DIR=%cd%
set SYNFONIA_ROOT_DIR=%SYNFONIA_DEV_DIR%\..

rem Generate the Microsoft Visual Studio 2010 solution
echo.
echo.Generating Visual Studio 2010 solution (64 bits)
echo.------------------------------------------------
mkdir "%SYNFONIA_DEV_DIR%\MSVC10x64"
cd "%SYNFONIA_DEV_DIR%\MSVC10x64"
cmake -G "Visual Studio 10 Win64" "%SYNFONIA_ROOT_DIR%"

rem Back to dev directory
cd "%SYNFONIA_DEV_DIR%"