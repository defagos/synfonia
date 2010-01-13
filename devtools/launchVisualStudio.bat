@echo off

rem ****************************
rem Launch the Visual Studio IDE
rem ****************************

rem Check that the maximum number of parameters has not been exceeded
if not "%2"=="" goto Usage
¨
rem Sanitize input
if "%1"=="" goto Usage

rem Check that the environment has been generated
if not exist %1 goto NotExist

set ROOT_DIR=%cd%\..\

rem ------------------------------------------------------------------
rem Some useful shortcuts for use in the IDE

rem Include directories
set i=%ROOT_DIR%include\
set ic=%i%core\
set is=%i%synfonia\
set iu=%i%utils\

rem Source directories
set s=%ROOT_DIR%src\
set sc=%s%core\
set ss=%s%synfonia\
set su=%s%utils\

rem Test directories
set t=%ROOT_DIR%test\
set tc=%t%core\
set ts=%t%synfonia\
set tu=%t%utils\
rem ------------------------------------------------------------------

rem Launch the IDE
start %1\synfonia.sln

goto End

:Usage
echo Usage: %0 CONFIGURATION_NAME
goto End

:NotExist
echo The environment for configuration %1 has not been generated. Generate it first
echo using generate%1.bat
goto End

:End