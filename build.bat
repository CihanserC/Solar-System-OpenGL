@echo off
chcp 65001 >nul 2>&1
echo ====================================
echo Solar System OpenGL - Build Script
echo ====================================
echo.

REM Ask for build method
echo Which method would you like to use?
echo 1. CMake (Recommended)
echo 2. Direct g++ (Fast)
echo.
set /p choice="Your choice (1 or 2): "

if "%choice%"=="1" goto cmake_build
if "%choice%"=="2" goto gcc_build

:cmake_build
echo.
echo Building with CMake...
if not exist build mkdir build
cd build
cmake .. -G "MinGW Makefiles"
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: CMake configuration failed!
    pause
    exit /b 1
)
cmake --build .
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Build failed!
    pause
    exit /b 1
)
cd ..
echo.
echo Build successful! build/SolarSystem.exe created.
echo.
set /p run="Would you like to run the program? (Y/N): "
if /i "%run%"=="Y" (
    echo Starting program...
    build\SolarSystem.exe
)
goto end

:gcc_build
echo.
echo Building with g++...
g++ -o SolarSystem.exe "Solar System/Solar System/Main.cpp" "Solar System/Solar System/camera.cpp" -lopengl32 -lglu32 -lfreeglut -lwinmm
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Build failed!
    echo.
    echo Possible reasons:
    echo - g++ not installed (MinGW required)
    echo - FreeGLUT library not found
    pause
    exit /b 1
)
echo.
echo Build successful! SolarSystem.exe created.
echo.
set /p run="Would you like to run the program? (Y/N): "
if /i "%run%"=="Y" (
    echo Starting program...
    SolarSystem.exe
)

:end
echo.
echo Done!
pause
