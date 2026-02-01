#include "planet.h"
#include <cmath>

#ifndef PI
#define PI 3.14159265358979323846
#endif

Planet::Planet(const std::string& name, float radius, float orbitDistance,
               float orbitSpeed, float rotationSpeed,
               float r, float g, float b)
    : name(name), radius(radius), orbitDistance(orbitDistance),
      orbitSpeed(orbitSpeed), rotationSpeed(rotationSpeed),
      orbitAngle(0.0f), rotationAngle(0.0f),
      textureID(0), ringTextureID(0), nightTextureID(0), 
      hasTexture(false), hasDualTexture(false), hasRings(false)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
    
    // Başlangıç pozisyonu
    position.x = orbitDistance;
    position.y = 0.0f;
    position.z = 0.0f;
}

Planet::~Planet() {
    // Ayları temizle
    for (size_t i = 0; i < moons.size(); i++) {
        delete moons[i];
    }
    moons.clear();
}

void Planet::update(float deltaTime) {
    // Yörünge pozisyonunu güncelle
    updateOrbitPosition();
    
    // Rotasyonu güncelle
    updateRotation(deltaTime);
    
    // İz ekle
    addTrailPoint();
    
    // Ayları güncelle
    for (size_t i = 0; i < moons.size(); i++) {
        moons[i]->update(deltaTime);
    }
}

void Planet::updateOrbitPosition() {
    // Yörünge açısını artır
    orbitAngle += orbitSpeed;
    
    // 2π'den büyükse sıfırla (overflow önleme)
    if (orbitAngle >= 2.0f * PI) {
        orbitAngle -= 2.0f * PI;
    }
    
    // Pozisyonu hesapla (dairesel yörünge)
    position.x = orbitDistance * sin(orbitAngle);
    position.y = 0.0f;
    position.z = orbitDistance * cos(orbitAngle);
}

void Planet::updateRotation(float deltaTime) {
    // Kendi ekseni etrafında dönüş
    rotationAngle += rotationSpeed * deltaTime;
    
    // 360 dereceden büyükse sıfırla
    if (rotationAngle >= 360.0f) {
        rotationAngle -= 360.0f;
    }
}

void Planet::addTrailPoint() {
    // Yeni pozisyon ekle
    trail.push_back(position);
    
    // Maksimum uzunluğu aş dönüyorsa en eskiyi sil
    if (trail.size() > MAX_TRAIL_LENGTH) {
        trail.pop_front();
    }
}

void Planet::render(bool drawOrbitPath, bool drawTrail) {
    // Yörünge yolunu çiz
    if (drawOrbitPath) {
        drawOrbit();
    }
    
    // İzi çiz
    if (drawTrail) {
        this->drawTrail();
    }
    
    glPushMatrix();
    
    // Gezegeni yörünge pozisyonuna taşı
    glTranslatef(position.x, position.y, position.z);
    
    // Kendi ekseni etrafında döndür
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
    
    // Rengi ayarla
    glColor3f(color[0], color[1], color[2]);
    
    // Use texture (if available)
    if (hasTexture && textureID > 0) {
        glEnable(GL_TEXTURE_2D);
        
        // Special handling for Earth with day/night cycle
        if (hasDualTexture && nightTextureID > 0) {
            // Use multi-texturing for day/night blend
            renderWithDayNight();
        } else {
            // Normal single texture rendering
            glBindTexture(GL_TEXTURE_2D, textureID);
            
            GLUquadricObj* quadric = gluNewQuadric();
            gluQuadricTexture(quadric, GL_TRUE);
            gluQuadricNormals(quadric, GLU_SMOOTH);
            gluSphere(quadric, radius, 32, 32);
            gluDeleteQuadric(quadric);
        }
        
        glDisable(GL_TEXTURE_2D);
    } else {
        // No texture - simple sphere
        glutSolidSphere(radius, 20, 16);
    }
    
    // Satürn halkalarını çiz (varsa)
    if (hasRings) {
        drawRings();
    }
    
    glPopMatrix();
    
    // Ayları render et
    for (size_t i = 0; i < moons.size(); i++) {
        glPushMatrix();
        // Gezegenin pozisyonuna göre ay pozisyonunu ayarla
        glTranslatef(position.x, position.y, position.z);
        moons[i]->render(true, false);  // Ayların yörüngesini çiz ama izini çizme
        glPopMatrix();
    }
}

void Planet::drawOrbit() {
    glPushMatrix();
    glDisable(GL_LIGHTING);  // Yörünge çizgisi için ışıklandırmayı kapat
    
    glBegin(GL_LINE_LOOP);
    glColor3f(0.3f, 0.3f, 0.3f);  // Koyu gri yörünge çizgisi
    
    // Dairesel yörünge çiz
    const int segments = 360;
    for (int i = 0; i < segments; i++) {
        float angle = (float)i * PI / 180.0f;
        float x = orbitDistance * sin(angle);
        float z = orbitDistance * cos(angle);
        glVertex3f(x, 0.0f, z);
    }
    
    glEnd();
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void Planet::drawTrail() {
    if (trail.size() < 2) return;
    
    glPushMatrix();
    glDisable(GL_LIGHTING);
    
    glBegin(GL_LINE_STRIP);
    
    // İz çizgisini çiz (alpha blending ile sönükleşen)
    for (size_t i = 0; i < trail.size(); i++) {
        float alpha = (float)i / (float)trail.size();  // 0 -> 1 fade
        glColor4f(color[0], color[1], color[2], alpha);
        glVertex3f(trail[i].x, trail[i].y, trail[i].z);
    }
    
    glEnd();
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void Planet::drawRings() {
    // Saturn rings
    glPushMatrix();
    
    // Rotate ring to horizontal plane
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    
    // Semi-transparent ring
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Inner radius: 1.2x planet radius
    // Outer radius: 2.3x planet radius
    float innerRadius = radius * 1.2f;
    float outerRadius = radius * 2.3f;
    
    // Use ring texture if available
    if (ringTextureID > 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ringTextureID);
        glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
        
        GLUquadricObj* quadric = gluNewQuadric();
        gluQuadricTexture(quadric, GL_TRUE);
        gluQuadricNormals(quadric, GLU_SMOOTH);
        gluDisk(quadric, innerRadius, outerRadius, 50, 10);
        gluDeleteQuadric(quadric);
        
        glDisable(GL_TEXTURE_2D);
    } else {
        // Fallback to solid color
        glColor4f(0.82f, 0.73f, 0.73f, 0.6f);
        
        GLUquadricObj* quadric = gluNewQuadric();
        gluQuadricDrawStyle(quadric, GLU_FILL);
        gluDisk(quadric, innerRadius, outerRadius, 50, 10);
        gluDeleteQuadric(quadric);
    }
    
    glDisable(GL_BLEND);
    glPopMatrix();
}

void Planet::addMoon(Planet* moon) {
    if (moon) {
        moons.push_back(moon);
    }
}

void Planet::setTexture(GLuint texID) {
    textureID = texID;
    hasTexture = (texID > 0);
}

void Planet::setNightTexture(GLuint texID) {
    nightTextureID = texID;
    hasDualTexture = (texID > 0 && textureID > 0);
}

void Planet::setRingTexture(GLuint texID) {
    ringTextureID = texID;
}

void Planet::renderWithDayNight() {
    // Enable blending for day/night transition
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // First pass: Render day texture with lighting
    glEnable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluSphere(quadric, radius, 64, 64);
    
    // Second pass: Render night texture (inverted lighting)
    // Night lights appear on the dark side
    glBlendFunc(GL_ONE, GL_ONE);  // Additive blending
    
    // Invert lighting effect for night side
    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, nightTextureID);
    
    // Calculate which side is facing away from sun (position 0,0,0)
    // We'll use a subtle emission effect
    glColor4f(0.3f, 0.3f, 0.4f, 1.0f);  // Slight blue tint for night
    
    gluSphere(quadric, radius * 1.001f, 64, 64);  // Slightly larger to avoid z-fighting
    
    gluDeleteQuadric(quadric);
    
    glEnable(GL_LIGHTING);
    glDisable(GL_BLEND);
    glColor3f(1.0f, 1.0f, 1.0f);  // Reset color
}
