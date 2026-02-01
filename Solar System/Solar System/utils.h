#ifndef UTILS_H
#define UTILS_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

// Matematiksel sabitler
#ifndef PI
#define PI 3.14159265358979323846
#endif

#ifndef PIdiv180
#define PIdiv180 (PI/180.0)
#endif

/**
 * FPS Counter
 * Frame rate hesaplamak için yardımcı sınıf
 */
class FPSCounter {
private:
    int frameCount;
    float fps;
    float lastTime;

public:
    FPSCounter() : frameCount(0), fps(0.0f), lastTime(0.0f) {}
    
    void update() {
        frameCount++;
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        
        if (currentTime - lastTime >= 1.0f) {
            fps = frameCount / (currentTime - lastTime);
            frameCount = 0;
            lastTime = currentTime;
        }
    }
    
    float getFPS() const { return fps; }
};

/**
 * Delta Time Calculator
 * Frame arası geçen süreyi hesaplar
 */
class DeltaTime {
private:
    float lastTime;
    float deltaTime;

public:
    DeltaTime() : lastTime(0.0f), deltaTime(0.0f) {}
    
    void update() {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
    }
    
    float getDelta() const { return deltaTime; }
};

#endif // UTILS_H
