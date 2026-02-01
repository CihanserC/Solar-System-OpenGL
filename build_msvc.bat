@echo off
REM Solar System OpenGL - MSVC Build Script
REM ========================================

echo Solar System OpenGL - Building with MSVC...
echo.

REM Find Visual Studio installation
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"

if not exist "%VSWHERE%" (
    echo ERROR: Visual Studio not found!
    echo Please install Visual Studio with C++ Desktop Development workload.
    pause
    exit /b 1
)

REM Get VS installation path
for /f "usebackq delims=" %%i in (`"%VSWHERE%" -latest -property installationPath`) do (
    set "VSINSTALLDIR=%%i"
)

if not defined VSINSTALLDIR (
    echo ERROR: Could not find Visual Studio installation!
    pause
    exit /b 1
)

echo Found Visual Studio at: %VSINSTALLDIR%
echo.

REM Setup MSVC environment
if exist "%VSINSTALLDIR%\VC\Auxiliary\Build\vcvars64.bat" (
    call "%VSINSTALLDIR%\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1
) else if exist "%VSINSTALLDIR%\Common7\Tools\VsDevCmd.bat" (
    call "%VSINSTALLDIR%\Common7\Tools\VsDevCmd.bat" -arch=amd64 -host_arch=amd64 >nul 2>&1
) else (
    echo ERROR: Cannot find Visual Studio environment setup script!
    pause
    exit /b 1
)

if %ERRORLEVEL% NEQ 0 (
    echo WARNING: VS environment setup returned error, but continuing...
    echo Checking if cl.exe is available...
    where cl.exe >nul 2>&1
    if %ERRORLEVEL% NEQ 0 (
        echo ERROR: cl.exe not found! MSVC environment setup failed.
        pause
        exit /b 1
    )
    echo cl.exe found, proceeding with compilation...
)

echo.
echo Compiling with MSVC...
echo.

REM Set FreeGLUT paths
set "FREEGLUT_DIR=%~dp0freeglut"
if exist "%FREEGLUT_DIR%\freeglut" (
    set "FREEGLUT_DIR=%FREEGLUT_DIR%\freeglut"
)

REM Find include and lib directories
for /d %%i in ("%FREEGLUT_DIR%\include*") do set "FREEGLUT_INC=%%i"
for /d %%i in ("%FREEGLUT_DIR%\lib\x64") do set "FREEGLUT_LIB=%%i"
if not defined FREEGLUT_LIB (
    for /d %%i in ("%FREEGLUT_DIR%\lib") do set "FREEGLUT_LIB=%%i"
)

if not exist "%FREEGLUT_INC%\GL\freeglut.h" (
    echo ERROR: FreeGLUT include files not found!
    echo Expected at: %FREEGLUT_INC%\GL\freeglut.h
    pause
    exit /b 1
)

echo FreeGLUT Include: %FREEGLUT_INC%
echo FreeGLUT Lib: %FREEGLUT_LIB%
echo.

cd "Solar System\Solar System"

REM Compile with MSVC
cl.exe /EHsc /std:c++14 /O2 ^
    /Fe:..\..\SolarSystem.exe ^
    Main.cpp ^
    camera.cpp ^
    planet.cpp ^
    solar_system.cpp ^
    texture_manager.cpp ^
    starfield.cpp ^
    ui_renderer.cpp ^
    opengl32.lib ^
    glu32.lib ^
    "%FREEGLUT_LIB%\freeglut.lib" ^
    winmm.lib ^
    /I. ^
    /I"%FREEGLUT_INC%" ^
    /D_CRT_SECURE_NO_WARNINGS

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ====================================
    echo ERROR: Compilation failed!
    echo ====================================
    echo.
    echo Possible issues:
    echo 1. FreeGLUT not installed
    echo    Download from: https://www.transmissionzero.co.uk/software/freeglut-devel/
    echo    Extract and add lib path to MSVC
    echo.
    echo 2. Missing OpenGL development files
    echo    Usually included with Windows SDK
    echo.
    cd ..\..
    pause
    exit /b 1
)

cd ..\..

echo.
echo ====================================
echo BUILD SUCCESSFUL!
echo ====================================
echo.
echo Executable: SolarSystem.exe
echo.

REM Check if textures folder exists
if exist "textures\" (
    echo Textures folder found!
) else (
    echo WARNING: No textures folder found. Program will use solid colors.
    echo You can add textures to 'textures\' folder later.
)

echo.
set /p run="Run the program now? (Y/N): "
if /i "%run%"=="Y" (
    echo.
    echo Starting Solar System...
    echo.
    SolarSystem.exe
)

echo.
echo Done!
pause
