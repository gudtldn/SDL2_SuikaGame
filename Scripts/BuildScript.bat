@echo off
setlocal enabledelayedexpansion

rem ## SDL Game Project build script

rem ## Change these variables to match your project
set ProjectName=SDL2_SuikaGame
set SolutionFile=%ProjectName%.sln
set Configuration=Debug
set Platform=x64

rem ## Set the path to MSBuild (Visual Studio 2022)
set MSBuildPath="C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"

rem ## Check if MSBuild exists
if not exist %MSBuildPath% (
    echo ERROR: MSBuild not found at %MSBuildPath%
    echo Please update the MSBuildPath variable in this script.
    exit /b 1
)

rem ## Parse command line arguments
:parse
if "%~1"=="" goto :main
if /i "%~1"=="-config" set Configuration=%~2& shift & shift & goto :parse
if /i "%~1"=="-platform" set Platform=%~2& shift & shift & goto :parse
shift
goto :parse

:main
echo Building %ProjectName% (%Configuration% %Platform%)

rem ## Build the project
echo Running MSBuild...
%MSBuildPath% %SolutionFile% /t:Build /p:Configuration=%Configuration% /p:Platform=%Platform%

if errorlevel 1 (
    echo ERROR: Build failed.
    exit /b 1
) else (
    echo Build succeeded.
)

@REM rem ## Copy SDL2.dll to the output directory
@REM echo Copying SDL2.dll to output directory...
@REM copy "ThirdParty\SDL2\lib\x64\SDL2.dll" "Binaries\%Platform%\%Configuration%\" >nul

echo Build process completed.
exit /b 0
