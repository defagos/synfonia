@echo off

rem ************************************************************
rem Installs all files needed to compile Google Test with CMake
rem ************************************************************

rem Check that the maximum number of parameters has not been exceeded
if not "%2"=="" goto Usage

rem Directory where this batch file resides (absolute path)
set BAT_FILE_DIR=%~dp0

rem Directory where the files must be installed (absolute path)
set OUTPUT_DIR=%~f1

rem Main devtools directory where the generic scripts reside
set MAIN_DEVTOOLS_DIR=%BAT_FILE_DIR%..\..

rem Check that the destination directory seems correct
if not exist "%OUTPUT_DIR%\include\gtest\" goto NotExist

rem Copy the CMakeLists.txt files
xcopy /Y "%BAT_FILE_DIR%CMakeLists.txt" "%OUTPUT_DIR%"
xcopy /Y /E "%BAT_FILE_DIR%src" "%OUTPUT_DIR%\src"

rem Copy the makefile generators
mkdir "%OUTPUT_DIR%\devtools"
xcopy /Y "%MAIN_DEVTOOLS_DIR%\generate*.bat" "%OUTPUT_DIR%\devtools"
xcopy /Y "%MAIN_DEVTOOLS_DIR%\common\*.bat" "%OUTPUT_DIR%\devtools\common\"

goto End

:Usage
echo.
echo.Copies all necessary files to compile Google Test with CMake
echo.
echo.Usage: %0 GOOGLE_TEST_MAIN_DIRECTORY
echo.
goto End

:NotExist
echo.Error: The directory %OUTPUT_DIR% is not a Google Test main directory
goto End

:End
set BAT_FILE_DIR=
set OUTPUT_DIR=
set MAIN_DEVTOOLS_DIR=