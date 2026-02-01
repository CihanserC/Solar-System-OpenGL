#ifndef UI_RENDERER_H
#define UI_RENDERER_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <string>
#include "planet.h"
#include "solar_system.h"
#include "utils.h"

/**
 * UIRenderer Class
 * Ekran üzerinde bilgi gösterimi (HUD)
 * GLUT bitmap fontları kullanır
 */
class UIRenderer {
private:
    bool showInfo;          // Bilgi paneli göster/gizle
    bool showHelp;          // Yardım göster/gizle
    FPSCounter* fpsCounter; // FPS sayacı referansı

public:
    UIRenderer();
    
    /**
     * FPS sayacını ayarla
     */
    void setFPSCounter(FPSCounter* counter) { fpsCounter = counter; }
    
    /**
     * Bilgi panelini aç/kapat
     */
    void toggleInfo() { showInfo = !showInfo; }
    
    /**
     * Yardımı aç/kapat
     */
    void toggleHelp() { showHelp = !showHelp; }
    
    /**
     * UI'ı render et
     * @param solarSystem Güneş sistemi referansı
     * @param windowWidth Pencere genişliği
     * @param windowHeight Pencere yüksekliği
     */
    void render(SolarSystem* solarSystem, int windowWidth, int windowHeight);

private:
    /**
     * Ekrana metin yaz
     * @param x X koordinatı (piksel)
     * @param y Y koordinatı (piksel)
     * @param text Yazılacak metin
     */
    void drawText(int x, int y, const std::string& text);
    
    /**
     * FPS göster
     */
    void drawFPS(int windowWidth, int windowHeight);
    
    /**
     * Gezegen bilgilerini göster
     */
    void drawPlanetInfo(Planet* planet, int windowHeight);
    
    /**
     * Kontrol yardımını göster
     */
    void drawHelp(int windowWidth, int windowHeight);
    
    /**
     * Sistem bilgilerini göster
     */
    void drawSystemInfo(SolarSystem* solarSystem, int windowHeight);
};

#endif // UI_RENDERER_H
