#ifndef PLANET_H
#define PLANET_H

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
#include <vector>
#include <deque>

// 3D Vector yapısı (planet için)
struct PlanetVector3D {
    float x, y, z;
    PlanetVector3D() : x(0), y(0), z(0) {}
    PlanetVector3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

/**
 * Planet Class
 * Güneş sistemindeki bir gezegeni temsil eder
 * Yörünge hareketi, rotasyon, ay/uydu sistemi ve görselleştirmeyi yönetir
 */
class Planet {
private:
    std::string name;                    // Gezegen adı
    float radius;                        // Yarıçap (Earth = 1.0 referans)
    float orbitDistance;                 // Güneş'ten uzaklık (AU)
    float orbitSpeed;                    // Yörünge hızı (Earth = 1.0 referans)
    float rotationSpeed;                 // Kendi ekseni etrafında dönüş hızı
    
    float orbitAngle;                    // Mevcut yörünge açısı (radyan)
    float rotationAngle;                 // Mevcut rotasyon açısı (derece)
    
    PlanetVector3D position;                   // 3D uzaydaki pozisyon
    float color[3];                      // RGB renk değerleri
    
    std::vector<Planet*> moons;          // Ay/uydu listesi
    std::deque<PlanetVector3D> trail;          // Yörünge izi için pozisyon geçmişi
    
    GLuint textureID;                    // OpenGL texture ID
    GLuint ringTextureID;                // OpenGL ring texture ID
    GLuint nightTextureID;               // Night texture ID (for Earth)
    bool hasTexture;                     // Has texture?
    bool hasDualTexture;                 // Has day/night textures (Earth)
    bool hasRings;                       // Has rings (Saturn)
    
    static const int MAX_TRAIL_LENGTH = 100;  // Maksimum iz uzunluğu

public:
    /**
     * Constructor
     * @param name Gezegen adı
     * @param radius Yarıçap
     * @param orbitDistance Güneş'ten uzaklık
     * @param orbitSpeed Yörünge hızı
     * @param rotationSpeed Rotasyon hızı
     * @param r Red renk bileşeni
     * @param g Green renk bileşeni
     * @param b Blue renk bileşeni
     */
    Planet(const std::string& name, float radius, float orbitDistance, 
           float orbitSpeed, float rotationSpeed,
           float r, float g, float b);
    
    ~Planet();
    
    // Getter metodları
    std::string getName() const { return name; }
    float getRadius() const { return radius; }
    float getOrbitDistance() const { return orbitDistance; }
    float getOrbitSpeed() const { return orbitSpeed; }
    PlanetVector3D getPosition() const { return position; }
    float getOrbitAngle() const { return orbitAngle; }
    
    /**
     * Gezegeni güncelle (pozisyon, açı)
     * @param deltaTime Frame arası geçen süre
     */
    void update(float deltaTime);
    
    /**
     * Gezegeni render et
     * @param drawOrbitPath Yörünge yolunu çiz mi?
     * @param drawTrail İzi çiz mi?
     */
    void render(bool drawOrbitPath = true, bool drawTrail = false);
    
    /**
     * Yörünge yolunu çiz
     */
    void drawOrbit();
    
    /**
     * Gezegen izini çiz (geçmiş pozisyonlar)
     */
    void drawTrail();
    
    /**
     * Satürn halkalarını çiz (sadece Satürn için)
     */
    void drawRings();
    
    /**
     * Ay/uydu ekle
     * @param moon Eklenecek ay/uydu
     */
    void addMoon(Planet* moon);
    
    /**
     * Set texture
     * @param texID OpenGL texture ID
     */
    void setTexture(GLuint texID);
    
    /**
     * Set night texture (for Earth day/night cycle)
     * @param texID OpenGL texture ID
     */
    void setNightTexture(GLuint texID);
    
    /**
     * Set ring texture (for Saturn)
     * @param texID OpenGL texture ID
     */
    void setRingTexture(GLuint texID);
    
    /**
     * Enable rings feature (for Saturn)
     * @param enabled Has rings?
     */
    void setHasRings(bool enabled) { hasRings = enabled; }
    
    /**
     * Yörünge pozisyonunu hesapla ve güncelle
     */
    void updateOrbitPosition();
    
    /**
     * Rotasyonu güncelle
     * @param deltaTime Frame arası geçen süre
     */
    void updateRotation(float deltaTime);
    
    /**
     * Add trail point to history
     */
    void addTrailPoint();

private:
    /**
     * Render Earth with day/night cycle
     */
    void renderWithDayNight();
};

#endif // PLANET_H
