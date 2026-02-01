@echo off
REM Simple CMake Build with Auto-detection

echo ====================================
echo Solar System OpenGL - CMake Build
echo ====================================
echo.

REM Add CMake to PATH if needed
if exist "C:\Program Files\CMake\bin\cmake.exe" (
    set "PATH=%PATH%;C:\Program Files\CMake\bin"
)

REM Check CMake
where cmake >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: CMake not found in PATH!
    echo.
    echo Please add CMake to your PATH or install it from:
    echo https://cmake.org/download/
    pause
    exit /b 1
)

echo CMake found!
cmake --version
echo.

REM Clean build directory
if exist build rmdir /s /q build
mkdir build
cd build

echo Configuring project with CMake...
echo.

REM Try NMake with MSVC
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if exist "%VSWHERE%" (
    for /f "usebackq delims=" %%i in (`"%VSWHERE%" -latest -property installationPath`) do (
        set "VSINSTALLDIR=%%i"
    )
    
    if defined VSINSTALLDIR (
        echo Found Visual Studio at: %VSINSTALLDIR%
        echo Setting up MSVC environment...
        
        if exist "%VSINSTALLDIR%\Common7\Tools\VsDevCmd.bat" (
            call "%VSINSTALLDIR%\Common7\Tools\VsDevCmd.bat" -arch=amd64 -host_arch=amd64 >nul 2>&1
        )
        
        REM Try NMake
        cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release
        if %ERRORLEVEL% EQU 0 (
            echo.
            echo Building with NMake...
            nmake
            if %ERRORLEVEL% EQU 0 goto build_success
        )
    )
)

echo.
echo ERROR: No suitable build environment found!
echo.
echo You need one of the following:
echo 1. Visual Studio 2019/2022 with C++ Desktop Development
echo 2. MinGW-w64 (GCC compiler)
echo.
echo Recommended: Install MinGW via MSYS2
echo https://www.msys2.org/
echo Then run: pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-freeglut
echo.
cd ..
pause
exit /b 1

:build_success
cd ..

echo.
echo ====================================
echo BUILD SUCCESSFUL!
echo ====================================
echo.

REM Find and copy executable
if exist "build\SolarSystem.exe" (
    copy "build\SolarSystem.exe" "SolarSystem.exe" >nul
    echo Executable created: SolarSystem.exe
) else if exist "build\Release\SolarSystem.exe" (
    copy "build\Release\SolarSystem.exe" "SolarSystem.exe" >nul
    echo Executable created: SolarSystem.exe
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
pause
