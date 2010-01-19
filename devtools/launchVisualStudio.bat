@echo off

rem ****************************
rem Launch the Visual Studio IDE
rem ****************************

set SCRIPT_DIR=%~dp0

rem Check that the maximum number of parameters has not been exceeded
if not "%2"=="" goto Usage

rem Sanitize input
if "%1"=="" goto Usage

rem Environment directory and main solution file
set ENV_DIR=%SCRIPT_DIR%%1
set SOLUTION_FILE=%ENV_DIR%\synfonia.sln

rem Check that the environment has been generated
if not exist "%SOLUTION_FILE%" goto NotExist

rem Main Synfonia directory
set ROOT_DIR=%SCRIPT_DIR%..

rem ------------------------------------------------------------------
rem Some useful shortcuts for use in the IDE. Should end with a
rem backslash to be more helpful

rem Include directories
set i=%ROOT_DIR%\include\
set ic=%i%core\
set is=%i%synfonia\
set iu=%i%utils\

rem Source directories
set s=%ROOT_DIR%\src\
set sc=%s%core\
set ss=%s%synfonia\
set su=%s%utils\

rem Test directories
set t=%ROOT_DIR%\test\
set tc=%t%core\
set ts=%t%synfonia\
set tu=%t%utils\
rem ------------------------------------------------------------------

rem Launch the IDE
"%SOLUTION_FILE%"

goto End

:Usage
echo Usage: %0 CONFIGURATION_NAME
goto End

:NotExist
echo The environment for configuration %1 has not been generated. Generate it first
echo using generate%1.bat
goto End

:End
set SCRIPT_DIR=
set ENV_DIR=
set SOLUTION_FILE=
set ROOT_DIR=
set i=
set ic=
set is=
set iu=
set s=
set sc=
set ss=
set su=
set t=
set tc=
set ts=
set tu=