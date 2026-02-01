# Build Instructions - Derleme Talimatları

## 📦 Proje Dosya Yapısı

Derlemeye başlamadan önce, tüm dosyaların yerinde olduğundan emin olun:

```
Solar-System-OpenGL/
├── CMakeLists.txt
├── build.bat
├── README.md
├── QUICKSTART.md
├── Solar System/
│   └── Solar System/
│       ├── Main.cpp
│       ├── camera.h / camera.cpp
│       ├── planet.h / planet.cpp
│       ├── solar_system.h / solar_system.cpp
│       ├── texture_manager.h / texture_manager.cpp
│       ├── starfield.h / starfield.cpp
│       ├── ui_renderer.h / ui_renderer.cpp
│       ├── utils.h
│       └── stb_image.h
└── textures/ (opsiyonel)
    └── [gezegen tekstürleri]
```

## 🔧 Gereksinimler

### Windows
- **MinGW** veya **MSVC** (Visual Studio)
- **OpenGL** (genelde sistem ile gelir)
- **FreeGLUT** kütüphanesi
- **CMake** (opsiyonel, build.bat kullanımı için)

### FreeGLUT Kurulumu

#### Yöntem 1: Önceden Derlenmiş (En Kolay)
1. https://www.transmissionzero.co.uk/software/freeglut-devel/ adresinden indirin
2. MinGW için x64 versiyonunu seçin
3. `freeglut.dll` dosyasını sistem PATH'ine veya exe ile aynı klasöre koyun
4. Include ve lib klasörlerini not edin

#### Yöntem 2: Package Manager
```bash
# MSYS2 kullanıyorsanız
pacman -S mingw-w64-x86_64-freeglut
```

## 🏗️ Derleme Yöntemleri

### Yöntem 1: Doğrudan g++ (En Hızlı)

```bash
cd "Solar System\Solar System"

g++ -o SolarSystem.exe ^
    Main.cpp ^
    camera.cpp ^
    planet.cpp ^
    solar_system.cpp ^
    texture_manager.cpp ^
    starfield.cpp ^
    ui_renderer.cpp ^
    -lopengl32 ^
    -lglu32 ^
    -lfreeglut ^
    -lwinmm ^
    -std=c++11 ^
    -O2
```

**Notlar:**
- `-O2`: Optimizasyon (daha hızlı çalışır)
- `-std=c++11`: C++11 standardı gerekli
- Eğer `freeglut` bulunamazsa, `-lglut` veya `-lglut32` deneyin

### Yöntem 2: CMake ile

```bash
# Build klasörü oluştur
mkdir build
cd build

# MinGW için
cmake .. -G "MinGW Makefiles"
cmake --build . --config Release

# Veya Visual Studio için
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
```

### Yöntem 3: build.bat Scripti

```bash
# Proje kök dizininde
build.bat

# Ekranda seçenekler çıkacak:
# 1 - CMake (önerilen)
# 2 - Doğrudan g++
```

## 🐛 Hata Çözümleri

### Hata: "GL/glut.h: No such file or directory"

**Çözüm 1:** FreeGLUT include yolunu belirtin
```bash
g++ ... -I"C:/path/to/freeglut/include" ...
```

**Çözüm 2:** CMakeLists.txt'de yolu düzeltin
```cmake
set(GLUT_INCLUDE_DIR "C:/path/to/freeglut/include")
```

### Hata: "undefined reference to `gluSphere`"

**Çözüm:** GLU kütüphanesini ekleyin
```bash
g++ ... -lglu32 -lopengl32 ...
```

### Hata: "freeglut library not found"

**Çözüm 1:** Library yolunu belirtin
```bash
g++ ... -L"C:/path/to/freeglut/lib" -lfreeglut ...
```

**Çözüm 2:** Farklı isim deneyin
```bash
# Bunlardan birini deneyin:
-lfreeglut
-lglut
-lglut32
```

### Hata: "undefined reference to `__imp_PostQuitMessage`"

**Çözüm:** Windows kütüphanesini ekleyin
```bash
g++ ... -lwinmm ...
```

### Hata: "stb_image.h: No such file or directory"

**Çözüm:** stb_image.h dosyasını indirin
```bash
# PowerShell'de proje dizininde:
cd "Solar System\Solar System"
Invoke-WebRequest -Uri "https://raw.githubusercontent.com/nothings/stb/master/stb_image.h" -OutFile "stb_image.h"
```

## ✅ Derleme Doğrulama

Başarılı derleme sonrası şunları kontrol edin:

```bash
# EXE dosyası oluştu mu?
dir SolarSystem.exe

# Çalıştırma testi
.\SolarSystem.exe
```

Eğer program açılıyor ve güneş sistemini görüyorsanız, başarılı! 🎉

## 🚀 Optimizasyon Seçenekleri

Daha hızlı derleme için:

```bash
g++ ... -O3 -march=native -mtune=native
```

Debug için (hata ayıklama):

```bash
g++ ... -g -O0 -DDEBUG
```

## 📊 Derleme Süresi

Yaklaşık süreler (ortalama PC):
- Doğrudan g++: ~5-10 saniye
- CMake ilk derleme: ~15-20 saniye
- CMake incremental: ~2-5 saniye

## 🎯 İleri Seviye

### Statik Linking (tek exe dosyası)

```bash
g++ ... -static -static-libgcc -static-libstdc++
```

### Boyut Optimizasyonu

```bash
g++ ... -Os -s
strip SolarSystem.exe
```

### Parallel Compilation (CMake)

```bash
cmake --build . -j8  # 8 paralel işlem
```

## 📝 Notlar

1. **Windows Defender:** İlk çalıştırmada uyarı verebilir (normal)
2. **Administrator:** Gerekmiyor, normal kullanıcı yeterli
3. **Tekstürler:** Opsiyoneldir, tekstürsüz de çalışır
4. **DLL Dosyaları:** freeglut.dll exe ile aynı dizinde olmalı

## 🔄 Temiz Derleme

Sorun yaşarsanız temiz derleme yapın:

```bash
# Eski dosyaları sil
del *.o *.exe

# Build klasörünü sil
rmdir /s /q build

# Yeniden derle
# [Yukarıdaki yöntemlerden birini kullanın]
```

## 💡 İpuçları

- İlk derleme her zaman daha uzun sürer
- Sadece bir dosya değiştiyse, CMake incremental derleme yapar
- `-O2` optimizasyon önerilen dengedir (hız vs derleme süresi)
- Debug yaparken `-g -O0` kullanın

Başarılı derlemeler! 🛠️
