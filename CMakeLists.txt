cmake_minimum_required(VERSION 3.10)
project(SolarSystem)

# C++ standardını ayarla
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Kaynak dosyaları
set(SOURCES
    "Solar System/Solar System/Main.cpp"
    "Solar System/Solar System/camera.cpp"
    "Solar System/Solar System/planet.cpp"
    "Solar System/Solar System/solar_system.cpp"
    "Solar System/Solar System/texture_manager.cpp"
    "Solar System/Solar System/starfield.cpp"
    "Solar System/Solar System/ui_renderer.cpp"
)

set(HEADERS
    "Solar System/Solar System/camera.h"
    "Solar System/Solar System/planet.h"
    "Solar System/Solar System/solar_system.h"
    "Solar System/Solar System/texture_manager.h"
    "Solar System/Solar System/starfield.h"
    "Solar System/Solar System/ui_renderer.h"
    "Solar System/Solar System/utils.h"
    "Solar System/Solar System/stb_image.h"
)

# Executable oluştur
add_executable(SolarSystem ${SOURCES} ${HEADERS})

# ============================================================
# OpenGL'i bul (tüm platformlar için gerekli)
# ============================================================
find_package(OpenGL REQUIRED)

# ============================================================
# Platform-specific GLUT configuration
# ============================================================

if(APPLE)
    # ========================================
    # macOS Configuration
    # ========================================
    message(STATUS "Configuring for macOS...")
    
    # macOS'ta GLUT framework olarak gelir
    find_library(GLUT_LIBRARY GLUT)
    find_library(COCOA_LIBRARY Cocoa)
    
    if(NOT GLUT_LIBRARY)
        message(FATAL_ERROR "GLUT framework not found! Please install XCode Command Line Tools.")
    endif()
    
    message(STATUS "Found GLUT Framework: ${GLUT_LIBRARY}")
    
    # Include directories (frameworks için gerekli değil ama belirtelim)
    include_directories(/System/Library/Frameworks)
    
    # Link libraries
    target_link_libraries(SolarSystem 
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARY}
        ${COCOA_LIBRARY}
    )
    
    # macOS-specific compiler flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")
    
elseif(WIN32)
    # ========================================
    # Windows Configuration
    # ========================================
    message(STATUS "Configuring for Windows...")
    
    # Önce proje dizinindeki freeglut'u kontrol et
    set(LOCAL_FREEGLUT "${CMAKE_SOURCE_DIR}/freeglut")
    
    if(EXISTS "${LOCAL_FREEGLUT}")
        # freeglut klasörü içinde freeglut alt klasörü var mı kontrol et
        if(EXISTS "${LOCAL_FREEGLUT}/freeglut")
            set(LOCAL_FREEGLUT "${LOCAL_FREEGLUT}/freeglut")
        endif()
        
        # Include dizinini bul
        file(GLOB FREEGLUT_INCLUDE_SEARCH "${LOCAL_FREEGLUT}/include*")
        if(FREEGLUT_INCLUDE_SEARCH)
            list(GET FREEGLUT_INCLUDE_SEARCH 0 GLUT_INCLUDE_DIR)
            message(STATUS "Found local FreeGLUT include: ${GLUT_INCLUDE_DIR}")
        endif()
        
        # Library'yi bul (x64 öncelikli)
        file(GLOB_RECURSE FREEGLUT_LIB_SEARCH "${LOCAL_FREEGLUT}/lib/*/freeglut.lib")
        if(NOT FREEGLUT_LIB_SEARCH)
            file(GLOB_RECURSE FREEGLUT_LIB_SEARCH "${LOCAL_FREEGLUT}/lib/freeglut.lib")
        endif()
        if(FREEGLUT_LIB_SEARCH)
            list(GET FREEGLUT_LIB_SEARCH 0 GLUT_LIBRARY)
            message(STATUS "Found local FreeGLUT library: ${GLUT_LIBRARY}")
        endif()
    endif()
    
    # Eğer local'de bulunamadıysa sistem path'lerinde ara
    if(NOT GLUT_INCLUDE_DIR OR NOT GLUT_LIBRARY)
        find_path(GLUT_INCLUDE_DIR GL/glut.h
            PATHS
            "C:/Program Files/Common Files/freeglut/include"
            "C:/Program Files/freeglut/include"
            "C:/freeglut/include"
            "$ENV{PROGRAMFILES}/freeglut/include"
        )
        
        find_library(GLUT_LIBRARY
            NAMES freeglut freeglut_static glut32 glut
            PATHS
            "C:/Program Files/Common Files/freeglut/lib"
            "C:/Program Files/Common Files/freeglut/lib/x64"
            "C:/Program Files/freeglut/lib"
            "C:/Program Files/freeglut/lib/x64"
            "C:/freeglut/lib"
            "$ENV{PROGRAMFILES}/freeglut/lib"
        )
    endif()
    
    # Include directories
    if(GLUT_INCLUDE_DIR)
        include_directories(${GLUT_INCLUDE_DIR})
    endif()
    
    include_directories(${OPENGL_INCLUDE_DIR})
    
    # Link libraries
    target_link_libraries(SolarSystem 
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARY}
        winmm
    )
    
else()
    # ========================================
    # Linux Configuration
    # ========================================
    message(STATUS "Configuring for Linux...")
    
    # Linux'ta GLUT genellikle freeglut paketi ile gelir
    find_package(GLUT REQUIRED)
    
    if(NOT GLUT_FOUND)
        message(FATAL_ERROR "GLUT not found! Install with: sudo apt-get install freeglut3-dev")
    endif()
    
    include_directories(${GLUT_INCLUDE_DIR})
    include_directories(${OPENGL_INCLUDE_DIR})
    
    target_link_libraries(SolarSystem 
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES}
    )
    
endif()

# ============================================================
# Debug bilgisi
# ============================================================
message(STATUS "========================================")
message(STATUS "Build Configuration Summary:")
message(STATUS "  Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  OpenGL Library: ${OPENGL_LIBRARIES}")
message(STATUS "  GLUT Include Dir: ${GLUT_INCLUDE_DIR}")
message(STATUS "  GLUT Library: ${GLUT_LIBRARY}")
message(STATUS "========================================")

