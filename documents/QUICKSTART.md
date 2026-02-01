# Quick Start Guide - Solar System OpenGL

## 🚀 Quick Start

### Step 1: Download the Project
```bash
git clone [repository-url]
cd Solar-System-OpenGL
```

### Step 2: Build

#### Windows + MinGW (Recommended)
```bash
cd "Solar System\Solar System"
g++ -o SolarSystem.exe Main.cpp camera.cpp planet.cpp solar_system.cpp texture_manager.cpp starfield.cpp ui_renderer.cpp -lopengl32 -lglu32 -lfreeglut -lwinmm -std=c++11
```

#### With CMake
```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

### Step 3: Run
```bash
# If you're in "Solar System\Solar System" folder:
SolarSystem.exe

# If you're in build folder:
SolarSystem.exe
```

## 📋 Requirements Check

### Is MinGW/GCC Installed?
```bash
g++ --version
```
If not found: https://sourceforge.net/projects/mingw/

### Is FreeGLUT Installed?
```bash
# FreeGLUT library required
# Download: https://www.transmissionzero.co.uk/software/freeglut-devel/
```

## ⚠️ Common Issues

### "freeglut library not found"
- Download and install FreeGLUT
- Alternative: use `-lglut` instead of `-lfreeglut`

### "stb_image.h not found"
- stb_image.h file should be in "Solar System\Solar System" folder
- Comes with the project, no additional download needed

### Textures not loading
- Normal! Textures are optional
- Works perfectly without textures (with solid colors)
- To add textures: see `textures\README.md` file

## 🎮 First Use

1. When the program opens, you'll see the solar system from a top-down view
2. Use **W/A/S/D** keys to move
3. Press **H** to see all controls
4. Use **1-8** keys to select planets
5. Press **T** to enable planet trails
6. Use **+/-** to change simulation speed

## 📊 Performance Tips

- If FPS is low, you can reduce star count (in starfield.cpp)
- Disabling trails improves performance (**T** key)
- Reducing window size increases FPS

## 🎨 Adding Textures (Optional)

1. Create a `textures` folder in the project root directory
2. Add these files:
   - sun.jpg, mercury.jpg, venus.jpg, earth.jpg
   - mars.jpg, jupiter.jpg, saturn.jpg
   - uranus.jpg, neptune.jpg, moon.jpg

3. Recommended source: https://www.solarsystemscope.com/textures/

## 💡 Tips

- **Lost camera position?** Restart the program
- **Want to see a planet up close?** Select with 1-8 keys and approach with W
- **Want to see the entire solar system?** Move away with S key

## 📞 Help

If you encounter problems:
1. Make sure all files are in the correct location
2. Verify requirements are installed
3. Read error messages and check relevant files

Good luck! Enjoy exploring the solar system! 🌟
