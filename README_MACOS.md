# Solar System OpenGL - macOS Derleme Kılavuzu

Bu belge, Solar System OpenGL projesini macOS üzerinde derleme ve çalıştırma talimatlarını içerir.

## Gereksinimler

### 1. XCode Command Line Tools

macOS'ta OpenGL ve GLUT framework'leri XCode Command Line Tools ile birlikte gelir.

```bash
# Command Line Tools yüklü mü kontrol et
xcode-select -p

# Eğer yüklü değilse, şu komutla yükle:
xcode-select --install
```

### 2. CMake

CMake build sistemini yönetmek için gereklidir.

```bash
# Homebrew ile CMake yükle
brew install cmake

# CMake versiyonunu kontrol et (3.10 veya üzeri olmalı)
cmake --version
```

## Derleme Adımları

### Yöntem 1: CMake ile Derleme (Önerilen)

1. **Proje dizinine gidin:**
```bash
cd /path/to/Solar-System-OpenGL
```

2. **Build dizini oluşturun:**
```bash
mkdir build
cd build
```

3. **CMake ile projeyi yapılandırın:**
```bash
cmake ..
```

Bu komut otomatik olarak:
- OpenGL framework'ünü bulacak
- GLUT framework'ünü bulacak
- Gerekli tüm bağımlılıkları yapılandıracak

4. **Projeyi derleyin:**
```bash
make
```

5. **Uygulamayı çalıştırın:**
```bash
./SolarSystem
```

### Yöntem 2: Tek Satır Derleme

Build klasöründen çıkarak doğrudan çalıştırmak için:

```bash
# Build ve çalıştır (proje kök dizininden)
mkdir -p build && cd build && cmake .. && make && ./SolarSystem
```

## Tekstür Dosyaları

Uygulama çalışır durumda ancak gezegen tekstürlerini görmek için:

1. `textures/` klasörünün proje kök dizininde olduğundan emin olun
2. Şu dosyalar mevcut olmalı:
   - `sun.jpg`
   - `mercury.jpg`
   - `venus.jpg`
   - `earth.jpg` (veya `earth_daymap.jpg`)
   - `earth_nightmap.jpg`
   - `mars.jpg`
   - `jupiter.jpg`
   - `saturn.jpg`
   - `saturn_ring.png`
   - `uranus.jpg`
   - `neptune.jpg`
   - `moon.jpg`

Not: Tekstürler yoksa uygulama düz renkli gezegenlerle çalışacaktır.

## Çalıştırma Dizini

Eğer build klasöründen çalıştırıyorsanız ve tekstürleri göremiyorsanız:

```bash
# Build dizininden bir üst dizine dön ve çalıştır
cd ..
./build/SolarSystem
```

Ya da:

```bash
# Sembolik link oluştur (build içinden)
cd build
ln -s ../textures textures
./SolarSystem
```

## Klavye Kontrolleri

### Kamera Hareketi
- **Mouse**: Etrafına bakın (sürükle veya hareket ettir)
- **W/S**: İleri/Geri
- **A/D**: Sola/Sağa Dön
- **X/Z**: Yukarı/Aşağı Bak
- **C/V**: Sola/Sağa Kayma
- **R/F**: Yukarı/Aşağı Hareket

### Özellikler
- **P**: Simülasyonu Duraklat/Devam Ettir
- **M**: Fare Kontrolünü Aç/Kapat
- **T**: İzleri Aç/Kapat
- **O**: Yörüngeleri Aç/Kapat
- **+/-**: Hızlandır/Yavaşlat
- **1-8**: Gezegen Seç
- **0**: Seçimi Temizle
- **I**: Bilgi Panelini Aç/Kapat
- **H**: Yardımı Göster/Gizle
- **L**: Işıklandırmayı Aç/Kapat
- **Q**: Çıkış

## Sorun Giderme

### "GLUT framework not found" Hatası

```bash
# XCode Command Line Tools'u yeniden yükle
sudo rm -rf /Library/Developer/CommandLineTools
xcode-select --install
```

### "CMake not found" Hatası

```bash
# Homebrew yüklü değilse önce onu yükle
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Sonra CMake yükle
brew install cmake
```

### Derleme Hatası: "OpenGL/gl.h not found"

XCode Command Line Tools eksik olabilir:

```bash
xcode-select --install
```

### Uygulama Açılıyor Ama Ekran Siyah

1. `textures/` klasörünün doğru konumda olduğundan emin olun
2. Terminal'den uygulamayı çalıştırarak hata mesajlarını kontrol edin
3. Işıklandırma kapalı olabilir - **L** tuşuna basın

### Performance Sorunları

macOS'ta Retina ekranlarda yavaşlık yaşıyorsanız:

```bash
# Düşük çözünürlük modunda açın
# (Henüz uygulamaya eklenmedi, isteğe bağlı geliştirme)
```

## Ek Bilgiler

### Platform Farkları

- **Windows**: FreeGLUT kullanır (`#include <GL/freeglut.h>`)
- **macOS**: GLUT Framework kullanır (`#include <GLUT/glut.h>`)
- **Linux**: FreeGLUT paketi kullanır

Kod, bu platformlar arasında otomatik olarak geçiş yapar (`#ifdef __APPLE__` direktifleri ile).

### Sistem Gereksinimleri

- macOS 10.12 (Sierra) veya üzeri
- OpenGL 2.1 veya üzeri (çoğu Mac'te varsayılan)
- En az 4GB RAM
- 100MB boş disk alanı

### Clean Build (Temiz Derleme)

Sorun yaşıyorsanız build klasörünü temizleyin:

```bash
# Proje kök dizininde
rm -rf build
mkdir build
cd build
cmake ..
make
```

## Geliştirici Notları

### Debug Modu

```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

### Release Modu (Optimize)

```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

### Verbose Build (Detaylı Çıktı)

```bash
make VERBOSE=1
```

## İletişim ve Destek

Sorun yaşıyorsanız veya öneriniz varsa:

- GitHub Issues sayfasını kullanın
- Hata raporlarında sistem bilgilerinizi (macOS versiyonu, CMake versiyonu) ekleyin

---

**Not**: Bu proje hem Windows, macOS hem de Linux üzerinde derlenebilir şekilde yapılandırılmıştır. Platform-specific kodlar otomatik olarak derleme zamanında seçilir.

## Hızlı Başlangıç (TL;DR)

```bash
# 1. Gereksinimleri yükle
xcode-select --install
brew install cmake

# 2. Derle ve çalıştır
cd /path/to/Solar-System-OpenGL
mkdir -p build && cd build
cmake ..
make
cd ..
./build/SolarSystem

# 3. Eğlence başlasın! 🚀
```
