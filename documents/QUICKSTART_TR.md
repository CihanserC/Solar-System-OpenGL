# 🚀 Hızlı Başlangıç - Projeyi 5 Dakikada Çalıştırın

## 🎯 En Kolay Yöntem: FreeGLUT + Visual Studio

Visual Studio zaten yüklüyse, sadece FreeGLUT eklemeniz yeterli!

### Adım 1: FreeGLUT İndir (2 dakika)

1. **İndir:** https://www.transmissionzero.co.uk/software/freeglut-devel/
   - `freeglut-MSVC-3.0.0-2.mp.zip` dosyasını indirin

2. **Klasöre Çıkar:**
   ```
   C:\freeglut\
   ├── bin\
   │   └── x64\
   │       └── freeglut.dll
   ├── include\
   │   └── GL\
   │       └── freeglut.h
   └── lib\
       └── x64\
           └── freeglut.lib
   ```

### Adım 2: DLL'i Kopyala (30 saniye)

Sadece bu komutu çalıştırın (PowerShell'de):

```powershell
Copy-Item "C:\freeglut\bin\x64\freeglut.dll" "C:\Users\cihan\Documents\GitHub\Automatic1111\Solar-System-OpenGL\"
```

Ya da manuel olarak:
- `C:\freeglut\bin\x64\freeglut.dll` dosyasını
- Proje klasörüne yapıştırın (SolarSystem.exe ile aynı yere)

### Adım 3: Derle ve Çalıştır! (1 dakika)

**Yöntem A: Otomatik (Tek Tıkla)**
1. `build_msvc.bat` dosyasına çift tıklayın
2. Bekleyin (30 saniye)
3. "Run the program now? (Y/N):" sorusuna `Y` yazın
4. Bitirdiniz! 🎉

**Yöntem B: Manuel**
```powershell
cd "C:\Users\cihan\Documents\GitHub\Automatic1111\Solar-System-OpenGL"
.\build_msvc.bat
```

---

## 🔧 Alternatif: MinGW Kurulumu

Eğer Visual Studio yerine MinGW kullanmak isterseniz:

### Adım 1: MinGW İndir

1. **MSYS2 İndir:** https://www.msys2.org/
2. Kur (varsayılan ayarlar)
3. MSYS2 terminalini aç ve şunu çalıştır:
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   pacman -S mingw-w64-x86_64-freeglut
   ```

### Adım 2: PATH'e Ekle

Windows'ta:
1. "Ortam Değişkenleri"ni aç
2. PATH'e ekle: `C:\msys64\mingw64\bin`

### Adım 3: Derle

```powershell
cd "Solar System\Solar System"
g++ -o SolarSystem.exe Main.cpp camera.cpp planet.cpp solar_system.cpp texture_manager.cpp starfield.cpp ui_renderer.cpp -lopengl32 -lglu32 -lfreeglut -lwinmm -std=c++11 -O2
```

---

## ⚡ Hangisini Seçmeliyim?

| Yöntem | Süre | Avantajlar | Dezavantajlar |
|--------|------|-----------|---------------|
| **MSVC + FreeGLUT** | 5 dk | ✅ VS zaten var<br>✅ Daha hızlı exe<br>✅ Microsoft desteği | ❌ FreeGLUT manuel kurulum |
| **MinGW** | 10 dk | ✅ Açık kaynak<br>✅ Çapraz platform | ❌ Ek kurulum<br>❌ PATH ayarı |

**🏆 Öneri:** Visual Studio zaten varsa → **MSVC + FreeGLUT** (daha hızlı!)

---

## 🎮 Çalıştırma

Program açıldığında:

### Temel Kontroller:
- **W/S/A/D:** Kamera hareket
- **Mouse:** Kamera dönüş
- **+/-:** Zaman hızı
- **Space:** Durdur/Başlat
- **ESC:** Çıkış

### Gelişmiş:
- **1-8:** Gezegen seç
- **0:** Seçimi kaldır
- **T:** Yörünge izleri
- **O:** Yörünge çizgileri
- **I:** Bilgi paneli
- **H:** Yardım

### Özellikler:
- 🌍 Dünya gün/gece döngüsü (otomatik)
- 🪐 Satürn halkaları
- 🌙 Aylar ve uydular
- ⭐ 5000 yıldızlı arka plan
- 📊 FPS sayacı
- 🎯 Gezegen bilgileri

---

## 🚨 Sorun Giderme

### "freeglut.dll not found"
**Çözüm:** DLL'i exe ile aynı klasöre kopyalayın

### "MSVCR140.dll eksik"
**Çözüm:** Visual C++ Redistributable kurun:
https://aka.ms/vs/17/release/vc_redist.x64.exe

### Pencere açılmıyor
**Çözüm:** 
1. Windows Defender'ı kontrol edin
2. Antivirüs'ü geçici olarak kapatın
3. Administrator olarak çalıştırın

### Tekstürler görünmüyor
**Çözüm:** Normal! Tekstür dosyaları opsiyonel.
- Tekstürler `textures/` klasöründe
- Yoksa düz renkli gezegenler görünür

---

## 📊 Performans

**Minimum:**
- Windows 7+
- OpenGL 2.1
- 2 GB RAM

**Önerilen:**
- Windows 10+
- OpenGL 3.0+
- 4 GB RAM
- Dedicated GPU

**FPS:**
- İyi GPU: 60+ FPS
- Orta GPU: 30-60 FPS
- Düşük GPU: 15-30 FPS

---

## 🎉 Başarılı!

Program çalışıyor mu? Harika! Şimdi:
1. Dünya'yı seçin (`3` tuşu)
2. Yaklaşın (W tuşu)
3. Gün/gece döngüsünü izleyin 🌍🌙
4. Satürn'e gidin (`6` tuşu) - halkaları görün! 🪐

**Keyifli keşifler!** ✨

---

## 📞 Yardım

Sorun mu var? 
1. `documents/BUILD.md` - Detaylı derleme talimatları
2. `documents/FEATURES.md` - Tüm özellikler
3. GitHub Issues - Hata bildirin
