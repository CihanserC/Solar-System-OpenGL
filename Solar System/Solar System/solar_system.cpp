#include "solar_system.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

SolarSystem::SolarSystem() 
    : sun(nullptr), timeScale(1.0f), showOrbits(true), 
      showTrails(false), selectedPlanet(nullptr) 
{
    initializePlanets();
}

SolarSystem::~SolarSystem() {
    // Gezegenleri temizle
    for (size_t i = 0; i < planets.size(); i++) {
        delete planets[i];
    }
    planets.clear();
    
    // Güneş'i temizle
    if (sun) {
        delete sun;
        sun = nullptr;
    }
}

void SolarSystem::initializePlanets() {
    // Güneş - merkezdeki ışık kaynağı (yörünge yok)
    sun = new Planet("Sun", 1.0f, 0.0f, 0.0f, 0.5f, 1.0f, 0.84f, 0.25f);
    
    // Merkür
    Planet* mercury = new Planet("Mercury", 0.38f, 4.0f, 0.01607f, 5.0f,
                                 0.82f, 0.81f, 0.81f);
    planets.push_back(mercury);
    
    // Venüs
    Planet* venus = new Planet("Venus", 0.95f, 7.0f, 0.01176f, 2.5f,
                               0.55f, 0.50f, 0.52f);
    planets.push_back(venus);
    
    // Dünya
    Planet* earth = new Planet("Earth", 1.0f, 10.0f, 0.01f, 10.0f,
                               0.0f, 0.5f, 1.0f);  // Mavi/yeşil Dünya
    
    // Dünya'nın Ay'ı
    Planet* moon = new Planet("Moon", 0.27f, 2.5f, 0.04f, 3.0f,
                              0.7f, 0.7f, 0.7f);
    earth->addMoon(moon);
    planets.push_back(earth);
    
    // Mars
    Planet* mars = new Planet("Mars", 0.53f, 15.0f, 0.008085f, 9.0f,
                              0.95f, 0.31f, 0.09f);
    planets.push_back(mars);
    
    // Jüpiter
    Planet* jupiter = new Planet("Jupiter", 11.0f, 52.0f, 0.004389f, 20.0f,
                                 0.84f, 0.62f, 0.50f);
    
    // Jüpiter'in büyük uyduları
    Planet* io = new Planet("Io", 0.28f, 15.0f, 0.06f, 5.0f,
                            1.0f, 0.9f, 0.0f);
    Planet* europa = new Planet("Europa", 0.25f, 18.0f, 0.05f, 4.0f,
                                0.9f, 0.85f, 0.75f);
    Planet* ganymede = new Planet("Ganymede", 0.41f, 21.0f, 0.04f, 3.5f,
                                  0.6f, 0.5f, 0.4f);
    Planet* callisto = new Planet("Callisto", 0.38f, 24.0f, 0.035f, 3.0f,
                                  0.4f, 0.35f, 0.3f);
    jupiter->addMoon(io);
    jupiter->addMoon(europa);
    jupiter->addMoon(ganymede);
    jupiter->addMoon(callisto);
    planets.push_back(jupiter);
    
    // Satürn (halkalarıyla)
    Planet* saturn = new Planet("Saturn", 9.1f, 96.0f, 0.003234f, 18.0f,
                                0.82f, 0.73f, 0.73f);
    saturn->setHasRings(true);
    
    // Satürn'ün uydusu Titan
    Planet* titan = new Planet("Titan", 0.40f, 16.0f, 0.045f, 4.0f,
                               0.9f, 0.7f, 0.3f);
    saturn->addMoon(titan);
    planets.push_back(saturn);
    
    // Uranüs
    Planet* uranus = new Planet("Uranus", 4.0f, 192.0f, 0.002287f, 15.0f,
                                0.74f, 0.89f, 0.90f);
    planets.push_back(uranus);
    
    // Neptün
    Planet* neptune = new Planet("Neptune", 3.9f, 300.0f, 0.001823f, 14.0f,
                                 0.45f, 0.68f, 0.68f);
    planets.push_back(neptune);
}

void SolarSystem::update(float deltaTime) {
    // Zaman ölçeğini uygula
    float scaledDeltaTime = deltaTime * timeScale;
    
    // Tüm gezegenleri güncelle
    for (size_t i = 0; i < planets.size(); i++) {
        planets[i]->update(scaledDeltaTime);
    }
}

void SolarSystem::render() {
    // Güneş'i render et
    renderSun();
    
    // Gezegenleri render et
    for (size_t i = 0; i < planets.size(); i++) {
        planets[i]->render(showOrbits, showTrails);
        
        // Seçili gezegeni vurgula
        if (planets[i] == selectedPlanet) {
            PlanetVector3D pos = planets[i]->getPosition();
            float rad = planets[i]->getRadius();
            
            glPushMatrix();
            glTranslatef(pos.x, pos.y, pos.z);
            glDisable(GL_LIGHTING);
            glColor3f(1.0f, 1.0f, 0.0f);  // Sarı vurgu
            glutWireSphere(rad * 1.3f, 20, 16);
            glEnable(GL_LIGHTING);
            glPopMatrix();
        }
    }
}

void SolarSystem::renderSun() {
    if (!sun) return;
    
    glPushMatrix();
    
    // Güneş'i merkeze yerleştir
    glTranslatef(0.0f, 0.0f, 0.0f);
    
    // Güneş kendi ışığını yayar - lighting'i geçici olarak kapat
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 0.84f, 0.25f);  // Altın sarısı
    
    // Güneş'i render et
    glutSolidSphere(sun->getRadius(), 30, 30);
    
    // Işık kaynağını güneşe yerleştir
    GLfloat lightPos[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void SolarSystem::selectPlanet(int index) {
    if (index >= 0 && index < (int)planets.size()) {
        selectedPlanet = planets[index];
    }
}

Planet* SolarSystem::getPlanet(int index) const {
    if (index >= 0 && index < (int)planets.size()) {
        return planets[index];
    }
    return nullptr;
}
