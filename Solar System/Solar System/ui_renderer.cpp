#include "ui_renderer.h"
#include <sstream>
#include <iomanip>

UIRenderer::UIRenderer() 
    : showInfo(true), showHelp(false), fpsCounter(nullptr)
{
}

void UIRenderer::render(SolarSystem* solarSystem, int windowWidth, int windowHeight) {
    // 2D overlay için projection değiştir
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    // Depth test ve lighting'i kapat
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    
    // FPS'i her zaman göster
    drawFPS(windowWidth, windowHeight);
    
    // Bilgi paneli
    if (showInfo) {
        drawSystemInfo(solarSystem, windowHeight);
        
        Planet* selected = solarSystem ? solarSystem->getSelectedPlanet() : nullptr;
        if (selected) {
            drawPlanetInfo(selected, windowHeight);
        }
    }
    
    // Yardım
    if (showHelp) {
        drawHelp(windowWidth, windowHeight);
    }
    
    // Ayarları geri yükle
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void UIRenderer::drawText(int x, int y, const std::string& text) {
    glRasterPos2i(x, y);
    for (size_t i = 0; i < text.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
}

void UIRenderer::drawFPS(int windowWidth, int windowHeight) {
    if (!fpsCounter) return;
    
    // Sağ üst köşe - semi-transparent arka plan
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2i(windowWidth - 100, windowHeight - 30);
    glVertex2i(windowWidth, windowHeight - 30);
    glVertex2i(windowWidth, windowHeight);
    glVertex2i(windowWidth - 100, windowHeight);
    glEnd();
    glDisable(GL_BLEND);
    
    // FPS metni
    glColor3f(0.0f, 1.0f, 0.0f);
    std::ostringstream oss;
    oss << "FPS: " << std::fixed << std::setprecision(1) << fpsCounter->getFPS();
    drawText(windowWidth - 90, windowHeight - 15, oss.str());
}

void UIRenderer::drawPlanetInfo(Planet* planet, int windowHeight) {
    if (!planet) return;
    
    // Sol taraf - gezegen bilgileri
    int x = 10;
    int y = windowHeight - 40;
    
    // Arka plan
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2i(5, windowHeight - 150);
    glVertex2i(250, windowHeight - 150);
    glVertex2i(250, windowHeight - 5);
    glVertex2i(5, windowHeight - 5);
    glEnd();
    glDisable(GL_BLEND);
    
    // Başlık
    glColor3f(1.0f, 1.0f, 0.0f);
    drawText(x, y, "Selected Planet");
    y -= 20;
    
    // Gezegen bilgileri
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(x, y, "Name: " + planet->getName());
    y -= 15;
    
    std::ostringstream oss;
    oss << "Radius: " << std::fixed << std::setprecision(2) << planet->getRadius();
    drawText(x, y, oss.str());
    y -= 15;
    
    oss.str("");
    oss << "Distance: " << std::fixed << std::setprecision(1) << planet->getOrbitDistance() << " AU";
    drawText(x, y, oss.str());
    y -= 15;
    
    oss.str("");
    oss << "Speed: " << std::fixed << std::setprecision(4) << planet->getOrbitSpeed();
    drawText(x, y, oss.str());
    y -= 15;
    
    PlanetVector3D pos = planet->getPosition();
    oss.str("");
    oss << "Position: (" << std::fixed << std::setprecision(1) 
        << pos.x << ", " << pos.y << ", " << pos.z << ")";
    drawText(x, y, oss.str());
}

void UIRenderer::drawSystemInfo(SolarSystem* solarSystem, int windowHeight) {
    if (!solarSystem) return;
    
    // Sol alt köşe - sistem bilgileri
    int x = 10;
    int y = 60;
    
    // Arka plan
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2i(5, 5);
    glVertex2i(200, 5);
    glVertex2i(200, 70);
    glVertex2i(5, 70);
    glEnd();
    glDisable(GL_BLEND);
    
    // Sistem durumu
    glColor3f(0.5f, 1.0f, 0.5f);
    
    std::ostringstream oss;
    oss << "Time Scale: " << std::fixed << std::setprecision(1) << solarSystem->getTimeScale() << "x";
    drawText(x, y, oss.str());
    y -= 15;
    
    drawText(x, y, solarSystem->isShowingOrbits() ? "Orbits: ON" : "Orbits: OFF");
    y -= 15;
    
    drawText(x, y, solarSystem->isShowingTrails() ? "Trails: ON" : "Trails: OFF");
    y -= 15;
    
    glColor3f(0.7f, 0.7f, 0.7f);
    drawText(x, y, "Press 'H' for help");
}

void UIRenderer::drawHelp(int windowWidth, int windowHeight) {
    // Merkez - yardım paneli
    int panelWidth = 400;
    int panelHeight = 380;
    int x = (windowWidth - panelWidth) / 2;
    int y = (windowHeight - panelHeight) / 2;
    
    // Arka plan
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.85f);
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + panelWidth, y);
    glVertex2i(x + panelWidth, y + panelHeight);
    glVertex2i(x, y + panelHeight);
    glEnd();
    
    // Çerçeve
    glColor3f(0.3f, 0.5f, 1.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x, y);
    glVertex2i(x + panelWidth, y);
    glVertex2i(x + panelWidth, y + panelHeight);
    glVertex2i(x, y + panelHeight);
    glEnd();
    glLineWidth(1.0f);
    glDisable(GL_BLEND);
    
    // Başlık
    int textX = x + 20;
    int textY = y + panelHeight - 30;
    glColor3f(1.0f, 1.0f, 0.0f);
    drawText(textX, textY, "=== CONTROLS ===");
    textY -= 25;
    
    // Kontroller
    glColor3f(1.0f, 1.0f, 1.0f);
    const char* controls[] = {
        "Camera Movement:",
        "  Mouse - Look Around",
        "  W/S - Forward/Backward",
        "  A/D - Turn Left/Right",
        "  X/Z - Look Up/Down",
        "  C/V - Strafe Left/Right",
        "  R/F - Move Up/Down",
        "",
        "Features:",
        "  P - Pause/Resume Simulation",
        "  M - Toggle Mouse Control",
        "  T - Toggle Trails",
        "  O - Toggle Orbits",
        "  +/- - Speed Up/Slow Down",
        "  1-8 - Select Planet",
        "  0 - Clear Selection",
        "  I - Toggle Info Panel",
        "  H - Toggle This Help",
        "  L - Toggle Lighting",
        "  Q - Quit",
        "",
        "Press 'H' to close"
    };
    
    int numLines = sizeof(controls) / sizeof(controls[0]);
    for (int i = 0; i < numLines; i++) {
        drawText(textX, textY, controls[i]);
        textY -= 15;
    }
}
