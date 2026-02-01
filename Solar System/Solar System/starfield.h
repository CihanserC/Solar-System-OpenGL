#ifndef STARFIELD_H
#define STARFIELD_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <vector>

/**
 * Star structure - Represents a single star
 */
struct Star {
    float x, y, z;          // 3D position
    float brightness;       // Brightness (0.0 - 1.0)
    float size;             // Size
    
    Star(float x, float y, float z, float brightness, float size)
        : x(x), y(y), z(z), brightness(brightness), size(size) {}
};

/**
 * StarField Class
 * Creates and renders background star field
 * 5000+ randomly distributed stars in 3D space
 */
class StarField {
private:
    std::vector<Star> stars;
    int starCount;
    float radius;           // Star field radius

public:
    /**
     * Constructor
     * @param count Star count
     * @param radius Star field radius
     */
    StarField(int count = 5000, float radius = 1000.0f);
    
    /**
     * Render star field
     */
    void render();

private:
    /**
     * Generate random stars
     */
    void generateStars();
    
    /**
     * Generate random float value (min, max)
     */
    float randomFloat(float min, float max);
};

#endif // STARFIELD_H
