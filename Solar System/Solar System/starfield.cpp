#include "starfield.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

StarField::StarField(int count, float radius)
    : starCount(count), radius(radius) 
{
    // Random seed
    static bool seeded = false;
    if (!seeded) {
        srand((unsigned int)time(nullptr));
        seeded = true;
    }
    
    generateStars();
}

void StarField::generateStars() {
    stars.reserve(starCount);
    
    for (int i = 0; i < starCount; i++) {
        // Küresel koordinatlar kullanarak rastgele pozisyon
        float theta = randomFloat(0.0f, 2.0f * 3.14159265f);  // Yatay açı
        float phi = randomFloat(0.0f, 3.14159265f);           // Dikey açı
        float r = randomFloat(radius * 0.5f, radius);         // Mesafe
        
        // Kartezyen koordinatlara çevir
        float x = r * sin(phi) * cos(theta);
        float y = r * sin(phi) * sin(theta);
        float z = r * cos(phi);
        
        // Rastgele parlaklık ve boyut
        float brightness = randomFloat(0.3f, 1.0f);
        float size = randomFloat(1.0f, 3.0f);
        
        stars.push_back(Star(x, y, z, brightness, size));
    }
}

void StarField::render() {
    // Işıklandırmayı kapat (yıldızlar kendi kendine parlıyor)
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);  // Yıldızlar her zaman arka planda
    
    glPointSize(1.0f);
    glBegin(GL_POINTS);
    
    for (size_t i = 0; i < stars.size(); i++) {
        const Star& star = stars[i];
        
        // Parlaklığa göre renk (beyaz - hafif sarımsı)
        float r = star.brightness;
        float g = star.brightness;
        float b = star.brightness * 0.95f;  // Hafif sarı ton
        
        glColor3f(r, g, b);
        glVertex3f(star.x, star.y, star.z);
    }
    
    glEnd();
    
    // Bazı büyük yıldızlar çiz (daha parlak)
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    
    for (size_t i = 0; i < stars.size(); i += 20) {  // Her 20'de bir büyük yıldız
        const Star& star = stars[i];
        
        if (star.brightness > 0.7f) {  // Sadece parlak olanlar
            glColor3f(1.0f, 1.0f, 0.95f);
            glVertex3f(star.x, star.y, star.z);
        }
    }
    
    glEnd();
    
    // Ayarları geri yükle
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

float StarField::randomFloat(float min, float max) {
    float random = ((float)rand()) / (float)RAND_MAX;
    return min + random * (max - min);
}
