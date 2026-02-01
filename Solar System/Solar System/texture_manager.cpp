#include "texture_manager.h"
#include <iostream>

// stb_image.h - header-only image loading library
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureManager::TextureManager() {
}

TextureManager::~TextureManager() {
    clear();
}

GLuint TextureManager::loadTexture(const std::string& name, const std::string& filename) {
    // Check if already loaded
    auto it = textures.find(name);
    if (it != textures.end()) {
        return it->second;
    }
    
    // Load image data
    int width, height, channels;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
    
    if (!data) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        std::cerr << "Reason: " << stbi_failure_reason() << std::endl;
        return 0;
    }
    
    // Create OpenGL texture
    GLuint textureID = createTextureFromData(data, width, height, channels);
    
    // Free memory
    stbi_image_free(data);
    
    // Add to cache
    if (textureID > 0) {
        textures[name] = textureID;
        std::cout << "Loaded texture: " << name << " (" << width << "x" << height << ")" << std::endl;
    }
    
    return textureID;
}

GLuint TextureManager::getTexture(const std::string& name) const {
    auto it = textures.find(name);
    if (it != textures.end()) {
        return it->second;
    }
    return 0;
}

void TextureManager::clear() {
    // Delete all textures
    for (auto& pair : textures) {
        glDeleteTextures(1, &pair.second);
    }
    textures.clear();
}

int TextureManager::loadPlanetTextures() {
    int loadedCount = 0;
    
    // Texture file paths (must be in textures folder)
    // Note: If these files don't exist, program still works (with solid colors)
    const char* textureFiles[][2] = {
        {"sun", "textures/sun.jpg"},
        {"mercury", "textures/mercury.jpg"},
        {"venus", "textures/venus.jpg"},
        {"earth", "textures/earth.jpg"},
        {"earth_day", "textures/earth_daymap.jpg"},
        {"earth_night", "textures/earth_nightmap.jpg"},
        {"mars", "textures/mars.jpg"},
        {"jupiter", "textures/jupiter.jpg"},
        {"saturn", "textures/saturn.jpg"},
        {"saturn_ring", "textures/saturn_ring.png"},
        {"uranus", "textures/uranus.jpg"},
        {"neptune", "textures/neptune.jpg"},
        {"moon", "textures/moon.jpg"},
        {"stars", "textures/stars.jpg"},
        {"stars_milky_way", "textures/stars_milky_way.jpg"}
    };
    
    int count = sizeof(textureFiles) / sizeof(textureFiles[0]);
    
    for (int i = 0; i < count; i++) {
        if (loadTexture(textureFiles[i][0], textureFiles[i][1]) > 0) {
            loadedCount++;
        }
    }
    
    std::cout << "Loaded " << loadedCount << " / " << count << " planet textures" << std::endl;
    
    return loadedCount;
}

GLuint TextureManager::createTextureFromData(unsigned char* data, int width, int height, int channels) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Determine format
    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
    
    // Load texture data
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    
    // Generate mipmap (for performance)
    gluBuild2DMipmaps(GL_TEXTURE_2D, format, width, height, format, GL_UNSIGNED_BYTE, data);
    
    return textureID;
}
