# Solar System OpenGL Simulation

[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20macOS%20%7C%20Linux-blue)]()
[![OpenGL](https://img.shields.io/badge/OpenGL-2.1%2B-green)]()
[![C++](https://img.shields.io/badge/C%2B%2B-11-orange)]()

A realistic 3D solar system simulation built with OpenGL and C++. Features accurate planetary motion, textures, lighting, and an interactive camera system.

## 🌟 Features

- **8 Planets** with realistic orbital distances and velocities
- **Moon and Satellite Systems** (Earth's Moon, Jupiter's moons, Saturn's Titan)
- **High-Quality Textures** for all celestial bodies
- **Saturn's Rings** with semi-transparency
- **Earth Day/Night Cycle** with separate textures
- **5000+ Background Stars** for immersive space environment
- **Orbital Trails** to visualize planetary paths
- **Free Camera Movement** with mouse and keyboard controls
- **Time Control** - speed up or slow down the simulation
- **Interactive UI** with real-time information panels
- **Planet Selection** to focus on specific celestial bodies

## 🖥️ Platform Support

This project is fully cross-platform and has been tested on:

- ✅ **Windows 10/11** (Visual Studio, MinGW, CMake)
- ✅ **macOS** (Catalina and newer)
- ✅ **Linux** (Ubuntu, Debian, Fedora)

## 📋 Requirements

### All Platforms
- CMake 3.10 or higher
- C++11 compatible compiler
- OpenGL 2.1 or higher

### Windows
- Visual Studio 2017+ OR MinGW-w64
- FreeGLUT library (included in project)

### macOS
- XCode Command Line Tools
- Homebrew (for CMake)

### Linux
- GCC/Clang compiler
- OpenGL development libraries
- FreeGLUT development package

## 🚀 Quick Start

### macOS

```bash
# Install requirements
xcode-select --install
brew install cmake

# Build and run
mkdir -p build && cd build
cmake ..
make
cd ..
./build/SolarSystem
```

**For detailed macOS instructions, see [README_MACOS.md](README_MACOS.md)**

### Windows

```batch
# Using CMake (recommended)
mkdir build
cd build
cmake ..
cmake --build .
cd ..
build\Debug\SolarSystem.exe

# Or use the provided batch file
build.bat
```

### Linux

```bash
# Install dependencies (Ubuntu/Debian)
sudo apt-get update
sudo apt-get install build-essential cmake libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev

# Build and run
mkdir -p build && cd build
cmake ..
make
cd ..
./build/SolarSystem
```

## 🎮 Controls

### Camera Movement
- **Mouse**: Look around (drag or move)
- **W/S**: Move Forward/Backward
- **A/D**: Turn Left/Right
- **X/Z**: Look Up/Down
- **C/V**: Strafe Left/Right
- **R/F**: Move Up/Down

### Features
- **P**: Pause/Resume Simulation
- **M**: Toggle Mouse Control
- **T**: Toggle Orbital Trails
- **O**: Toggle Orbit Paths
- **+/-**: Speed Up/Slow Down Time
- **1-8**: Select Planet (Mercury through Neptune)
- **0**: Clear Selection
- **I**: Toggle Info Panel
- **H**: Toggle Help Menu
- **L**: Toggle Lighting
- **Q**: Quit

## 📁 Project Structure

```
Solar-System-OpenGL/
├── Solar System/Solar System/    # Source code
│   ├── Main.cpp                   # Main application entry point
│   ├── camera.h/cpp               # Camera system
│   ├── planet.h/cpp               # Planet class
│   ├── solar_system.h/cpp         # Solar system manager
│   ├── starfield.h/cpp            # Background stars
│   ├── texture_manager.h/cpp      # Texture loading
│   ├── ui_renderer.h/cpp          # UI/HUD rendering
│   ├── utils.h                    # Utility functions
│   └── stb_image.h                # Image loading library
├── textures/                      # Planet textures
│   ├── sun.jpg
│   ├── mercury.jpg
│   ├── earth_daymap.jpg
│   ├── saturn_ring.png
│   └── ... (more textures)
├── freeglut/                      # FreeGLUT library (Windows)
├── CMakeLists.txt                 # Cross-platform build config
├── README.md                      # This file
└── README_MACOS.md                # Detailed macOS guide

```

## 🌍 Planetary Data

All planetary data is based on real astronomical measurements:

### Radii (relative to Earth)
- Sun: 109.2x | Jupiter: 11.0x | Saturn: 9.1x | Neptune: 3.9x
- Uranus: 4.0x | Earth: 1.0x | Venus: 0.95x | Mars: 0.53x | Mercury: 0.38x

### Orbital Distances (AU - scaled)
- Mercury: 4 AU | Venus: 7 AU | Earth: 10 AU | Mars: 15 AU
- Jupiter: 52 AU | Saturn: 96 AU | Uranus: 192 AU | Neptune: 300 AU

### Orbital Velocities (relative to Earth)
- Mercury: 1.607x | Venus: 1.176x | Earth: 1.0x | Mars: 0.809x
- Jupiter: 0.439x | Saturn: 0.323x | Uranus: 0.229x | Neptune: 0.182x

## 🖼️ Textures

The project includes high-quality textures for:
- All 8 planets
- The Sun
- Earth's Moon
- Saturn's rings
- Day/Night maps for Earth
- Background starfield

Textures are loaded from the `textures/` directory. If textures are missing, the simulation will use solid colors as fallback.

## 🛠️ Technical Details

### Cross-Platform Header Management

The project uses platform-specific preprocessor directives:

```cpp
#ifdef __APPLE__
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
#else
    #include <GL/freeglut.h>
    #include <GL/gl.h>
#endif
```

### CMake Configuration

The CMakeLists.txt automatically detects your platform and configures accordingly:
- **Windows**: Uses FreeGLUT from local folder or system paths
- **macOS**: Uses GLUT framework from XCode
- **Linux**: Uses system FreeGLUT package

## 🐛 Troubleshooting

### macOS: "GLUT framework not found"
```bash
xcode-select --install
```

### Windows: "freeglut.dll not found"
Copy `freeglut.dll` from `freeglut/freeglut/bin/` to the executable directory.

### Linux: "cannot find -lglut"
```bash
sudo apt-get install freeglut3-dev
```

### Black Screen / No Textures
1. Ensure `textures/` folder is in the correct location
2. Run from project root directory: `./build/SolarSystem`
3. Check console output for texture loading errors

## 📚 Documentation

- [README_MACOS.md](README_MACOS.md) - Detailed macOS build guide
- [documents/](documents/) - Additional documentation
  - BUILD.md - Build instructions for all platforms
  - FEATURES.md - Detailed feature list
  - QUICKSTART.md - Quick start guide

## 👨‍💻 Development

### Debug Build
```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

### Release Build (Optimized)
```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

### Clean Build
```bash
rm -rf build
mkdir build
cd build
cmake ..
make
```

## 📝 License

This project is created for educational purposes.

## 🙏 Credits

- **Student**: CIHANSER CALISKAN (ID: 16070001020)
- **Textures**: Various public domain sources
- **Libraries**: FreeGLUT, OpenGL, stb_image

## 🌌 Future Enhancements

- [ ] Add Pluto and dwarf planets
- [ ] Implement asteroid belt
- [ ] Add comet trajectories
- [ ] VR support
- [ ] More realistic physics
- [ ] Skybox for better background
- [ ] Sound effects

---

**Enjoy exploring the solar system! 🚀🌍🪐**
