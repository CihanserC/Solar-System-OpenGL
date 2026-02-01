# Installation Guide - Solar System OpenGL

## 📋 Prerequisites

### 1. MinGW (GCC Compiler)
C++ compiler for Windows

**Installation:**
- Download from https://sourceforge.net/projects/mingw-w64/
- Install and add `C:\mingw64\bin` to your PATH
- Test in terminal: `g++ --version`

### 2. CMake (Optional but recommended)
Build system

**Installation:**
- Download from https://cmake.org/download/
- Check "Add CMake to PATH" during installation
- Test in terminal: `cmake --version`

### 3. FreeGLUT
OpenGL library

**Installation Method 1: Using MSYS2 (Easiest)**
```bash
# Download and install MSYS2 from https://www.msys2.org/
# Open MSYS2 terminal and run:
pacman -S mingw-w64-x86_64-freeglut
```

**Installation Method 2: Manual Installation**
1. Download FreeGLUT from https://www.transmissionzero.co.uk/software/freeglut-devel/
2. Extract the archive
3. Place files as follows:
   ```
   Copy to MinGW directory:
   - freeglut.dll → C:\mingw64\bin\
   - libfreeglut.a → C:\mingw64\lib\
   - GL folder → C:\mingw64\include\
   ```

## 🚀 Running in Cursor IDE

### Method 1: Using Terminal (Quick)

1. **Open Terminal in Cursor** (Ctrl + `)

2. **Run the build script:**
   ```powershell
   .\build.bat
   ```

3. Select from the menu and the program will automatically compile and run!

### Method 2: Using Tasks (Professional)

1. **Build Task:** Press `Ctrl + Shift + B`
   - Select "Compile Solar System"

2. **Run Task:** Press `Ctrl + Shift + P` → "Tasks: Run Task"
   - Select "Build and Run"

3. **Debug Mode:** Press `F5`

### Method 3: Manual Compilation

In terminal:
```bash
# Using CMake
cmake -B build -G "MinGW Makefiles"
cmake --build build
.\build\SolarSystem.exe

# Or directly with g++
g++ -o SolarSystem.exe "Solar System/Solar System/Main.cpp" "Solar System/Solar System/camera.cpp" -lopengl32 -lglu32 -lfreeglut -lwinmm
.\SolarSystem.exe
```

## 🔧 Troubleshooting

### Error: "g++ is not recognized"
**Solution:** Ensure MinGW is added to PATH
```powershell
# Check PATH
$env:PATH

# Add temporarily
$env:PATH += ";C:\mingw64\bin"
```

### Error: "cannot find -lfreeglut"
**Solution:** FreeGLUT not installed correctly
- Use MSYS2 method or ensure files are in the correct location for manual installation

### Error: "GL/glut.h: No such file or directory"
**Solution:** Include directory not found
```bash
# FreeGLUT headers should be at:
C:\mingw64\include\GL\glut.h
```

### Program doesn't open or closes immediately
**Solution:** 
1. Run from terminal to see error messages
2. `freeglut.dll` must be in PATH or in the same folder as the executable

## ✅ Installation Test

Run these commands in terminal:
```bash
g++ --version        # Is GCC installed?
cmake --version      # Is CMake installed?
where freeglut.dll   # Is FreeGLUT in PATH?
```

If all succeed, you can run the project! 🎉

## 🎮 Controls

When the program is running:
- **W/S/A/D**: Camera movement
- **X/Z**: Look up/down
- **R/F**: Move up/down
- **L**: Toggle lighting on/off
- **Q**: Quit

Happy coding! 🚀
