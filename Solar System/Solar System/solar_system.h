#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include "planet.h"
#include <vector>

/**
 * SolarSystem Class
 * Güneş sisteminin tüm gezegenlerini ve Güneş'i yönetir
 * Güncelleme ve render işlemlerini koordine eder
 */
class SolarSystem {
private:
    std::vector<Planet*> planets;        // Tüm gezegenler
    Planet* sun;                         // Güneş (özel render)
    
    float timeScale;                     // Zaman hızlandırma faktörü
    bool showOrbits;                     // Yörüngeleri göster
    bool showTrails;                     // İzleri göster
    
    Planet* selectedPlanet;              // Seçili gezegen (takip için)

public:
    /**
     * Constructor - Güneş sistemini oluşturur
     */
    SolarSystem();
    
    /**
     * Destructor - Belleği temizler
     */
    ~SolarSystem();
    
    /**
     * Tüm gezegenleri güncelle
     * @param deltaTime Frame arası geçen süre
     */
    void update(float deltaTime);
    
    /**
     * Güneş sistemini render et
     */
    void render();
    
    /**
     * Yörünge gösterimini aç/kapat
     */
    void toggleOrbits() { showOrbits = !showOrbits; }
    
    /**
     * İz gösterimini aç/kapat
     */
    void toggleTrails() { showTrails = !showTrails; }
    
    /**
     * Zaman hızını ayarla
     * @param scale Yeni zaman ölçeği (1.0 = normal)
     */
    void setTimeScale(float scale) { timeScale = scale; }
    
    /**
     * Zaman hızını artır
     */
    void increaseTimeScale() { timeScale *= 1.5f; }
    
    /**
     * Zaman hızını azalt
     */
    void decreaseTimeScale() { 
        timeScale /= 1.5f; 
        if (timeScale < 0.1f) timeScale = 0.1f;
    }
    
    /**
     * Gezegeni index ile seç
     * @param index Gezegen indexi (0-7)
     */
    void selectPlanet(int index);
    
    /**
     * Seçimi temizle
     */
    void clearSelection() { selectedPlanet = nullptr; }
    
    /**
     * Seçili gezegeni al
     */
    Planet* getSelectedPlanet() const { return selectedPlanet; }
    
    /**
     * Gezegen sayısını döndür
     */
    int getPlanetCount() const { return planets.size(); }
    
    /**
     * Index ile gezegen al
     */
    Planet* getPlanet(int index) const;
    
    /**
     * Zaman ölçeğini al
     */
    float getTimeScale() const { return timeScale; }
    
    /**
     * Yörünge gösterimi aktif mi?
     */
    bool isShowingOrbits() const { return showOrbits; }
    
    /**
     * İz gösterimi aktif mi?
     */
    bool isShowingTrails() const { return showTrails; }

private:
    /**
     * Güneş sistemini başlat (gezegenleri oluştur)
     */
    void initializePlanets();
    
    /**
     * Güneş'i render et (özel - ışık kaynağı)
     */
    void renderSun();
};

#endif // SOLAR_SYSTEM_H
