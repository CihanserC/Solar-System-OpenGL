@echo off
REM Solar System OpenGL - CMake + Visual Studio Build
chcp 65001 >nul 2>&1
echo ====================================
echo Solar System OpenGL - CMake Build
echo ====================================
echo.

REM Check for CMake
where cmake >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: CMake not found!
    echo Please install CMake from: https://cmake.org/download/
    pause
    exit /b 1
)

REM Create build directory
if not exist build mkdir build
cd build

echo Configuring with CMake for Visual Studio...
echo.

REM Try to configure with Visual Studio
cmake .. -G "Visual Studio 18 2026" -A x64
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Visual Studio 2026 generator failed, trying other options...
    echo.
    
    REM Try generic Visual Studio
    cmake .. -G "Visual Studio 17 2022" -A x64
    if %ERRORLEVEL% NEQ 0 (
        echo.
        echo All Visual Studio generators failed. Trying NMake...
        echo.
        
        REM Setup MSVC environment for NMake
        set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
        if exist "%VSWHERE%" (
            for /f "usebackq delims=" %%i in (`"%VSWHERE%" -latest -property installationPath`) do (
                if exist "%%i\Common7\Tools\VsDevCmd.bat" (
                    call "%%i\Common7\Tools\VsDevCmd.bat" -arch=amd64 >nul 2>&1
                )
            )
        )
        
        cmake .. -G "NMake Makefiles"
        if %ERRORLEVEL% NEQ 0 (
            echo.
            echo ERROR: CMake configuration failed with all generators!
            echo.
            cd ..
            pause
            exit /b 1
        )
    )
)

echo.
echo Building project...
echo.

cmake --build . --config Release
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: Build failed!
    cd ..
    pause
    exit /b 1
)

cd ..

echo.
echo ====================================
echo BUILD SUCCESSFUL!
echo ====================================
echo.

REM Find the executable
if exist "build\Release\SolarSystem.exe" (
    echo Copying executable...
    copy "build\Release\SolarSystem.exe" "SolarSystem.exe" >nul
    echo Executable: SolarSystem.exe
) else if exist "build\SolarSystem.exe" (
    copy "build\SolarSystem.exe" "SolarSystem.exe" >nul
    echo Executable: SolarSystem.exe
) else (
    echo Executable location: build\SolarSystem.exe or build\Release\SolarSystem.exe
)

echo.
set /p run="Run the program now? (Y/N): "
if /i "%run%"=="Y" (
    echo.
    echo Starting Solar System...
    echo.
    if exist "SolarSystem.exe" (
        SolarSystem.exe
    ) else if exist "build\Release\SolarSystem.exe" (
        build\Release\SolarSystem.exe
    ) else if exist "build\SolarSystem.exe" (
        build\SolarSystem.exe
    )
)

echo.
echo Done!
pause
