#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

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
#include <map>

/**
 * TextureManager Class
 * Tekstür yükleme ve yönetimini handle eder
 * stb_image kütüphanesi kullanır (header-only)
 */
class TextureManager {
private:
    std::map<std::string, GLuint> textures;  // Yüklenmiş tekstürler (isim -> ID)

public:
    TextureManager();
    ~TextureManager();
    
    /**
     * Tekstür yükle
     * @param name Tekstür ismi (anahtar olarak kullanılır)
     * @param filename Dosya yolu
     * @return OpenGL texture ID (0 = başarısız)
     */
    GLuint loadTexture(const std::string& name, const std::string& filename);
    
    /**
     * Tekstür ID'sini al
     * @param name Tekstür ismi
     * @return OpenGL texture ID (0 = bulunamadı)
     */
    GLuint getTexture(const std::string& name) const;
    
    /**
     * Tüm tekstürleri temizle
     */
    void clear();
    
    /**
     * Gezegen tekstürlerini yükle
     * @return Başarılı yüklenen sayısı
     */
    int loadPlanetTextures();

private:
    /**
     * Raw image verilerinden OpenGL tekstür oluştur
     * @param data Image verisi
     * @param width Genişlik
     * @param height Yükseklik
     * @param channels Kanal sayısı (3=RGB, 4=RGBA)
     * @return OpenGL texture ID
     */
    GLuint createTextureFromData(unsigned char* data, int width, int height, int channels);
};

#endif // TEXTURE_MANAGER_H
