# Solar System OpenGL - Hızlı Başlangıç

## 🎯 En Kolay Yöntem (Önerilen)

### Windows için Basit Kurulum:

1. **MinGW-w64 İndirin ve Kurun:**
   - İndir: https://github.com/niXman/mingw-builds-binaries/releases
   - `x86_64-13.2.0-release-posix-seh-ucrt-rt_v11-rev0.7z` dosyasını indirin
   - `C:\` dizinine çıkarın (sonuç: `C:\mingw64`)
   - PATH'e ekleyin:
     ```powershell
     [Environment]::SetEnvironmentVariable("Path", $env:Path + ";C:\mingw64\bin", "User")
     ```

2. **FreeGLUT'u Yükleyin:**
   
   **Seçenek A - MSYS2 ile (En Kolay):**
   ```bash
   # MSYS2'yi indirin: https://www.msys2.org/
   # MSYS2 terminalinde:
   pacman -S mingw-w64-x86_64-freeglut
   
   # Sonra PATH'e ekleyin:
   C:\msys64\mingw64\bin
   ```

   **Seçenek B - Manuel:**
   - İndir: https://www.transmissionzero.co.uk/software/freeglut-devel/
   - `freeglut-MSVC.zip` dosyasını indirin
   - Dosyaları şu şekilde kopyalayın:
     - `freeglut.dll` → `C:\mingw64\bin\`
     - `lib` klasöründen `.a` dosyalarını → `C:\mingw64\lib\`
     - `include\GL` klasörünü → `C:\mingw64\include\`

3. **Projeyi Derleyin:**
   ```powershell
   .\build.bat
   ```
   Menüden seçim yapın ve program otomatik derlenecek!

## 🚀 Alternatif: Visual Studio ile Derleme

Eğer Visual Studio 2022/2026 yüklüyse ve C++ Desktop Development workload'u yüklüyse:

```powershell
.\setup_and_run.ps1
```

Bu script:
- FreeGLUT'u otomatik indirir
- Visual Studio ile derlemeyi dener
- Eğer Visual Studio uygun değilse, MinGW gerektiğini söyler

## 📊 Durum Kontrolü

Sisteminizdeki araçları kontrol edin:

```powershell
g++ --version           # MinGW kurulu mu?
cmake --version         # CMake kurulu mu? (opsiyonel)
where freeglut.dll      # FreeGLUT PATH'te mi?
```

## 🎮 Çalıştırma

Derleme başarılı olduktan sonra:

```powershell
.\SolarSystem.exe
```

### Kontroller:

#### 🖱️ Mouse Kontrolleri (YENİ!)
- **Mouse Hareketi**: Kamerayı döndür (varsayılan olarak aktif)
- **M Tuşu**: Mouse kontrolünü aç/kapa

#### ⌨️ Klavye Kontrolleri
- **W/S/A/D**: Kamera hareketi
- **X/Z**: Yukarı/Aşağı bak
- **R/F**: Yukarı/Aşağı hareket
- **C/V**: Sağa/Sola kayma
- **P**: Simülasyonu duraklat/devam ettir (YENİ!)
- **L**: Işıklandırma aç/kapa
- **T**: Gezegen izlerini aç/kapa
- **O**: Yörüngeleri aç/kapa
- **I**: Bilgi panelini aç/kapa
- **H**: Yardım menüsünü aç/kapa
- **+/-**: Simülasyon hızını değiştir
- **1-8**: Gezegen seç
- **0**: Seçimi temizle
- **Q**: Çıkış

## ❓ Sorun Giderme

### "g++ is not recognized" Hatası
```powershell
# MinGW PATH'e ekli değil, şunu çalıştırın:
$env:PATH += ";C:\mingw64\bin"
```

### "cannot find -lfreeglut" Hatası
- FreeGLUT düzgün kurulmamış
- MSYS2 yöntemini deneyin veya dosyaları manuel olarak doğru yerlere kopyalayın

### Visual Studio Derleme Hatası
- Visual Studio 2022/2026'da "C++ ile Masaüstü Geliştirme" workload'u yüklü olmalı
- Alternatif olarak MinGW yöntemini kullanın (daha kolay)

## 📚 Detaylı Dökümanlar

- `documents/INSTALL.md` - Detaylı kurulum kılavuzu
- `documents/QUICKSTART.md` - Hızlı başlangıç (İngilizce)
- `documents/QUICKSTART_TR.md` - Hızlı başlangıç (Türkçe)
- `documents/FEATURES.md` - Özellikler listesi

## 💡 Öneri

**En kolay kurulum:** MSYS2 kullanarak FreeGLUT yükleyin ve `build.bat` ile derleyin!

```powershell
# 1. MSYS2'yi kurun (https://www.msys2.org/)
# 2. MSYS2 terminalinde:
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-freeglut

# 3. PATH'e ekleyin:
# C:\msys64\mingw64\bin

# 4. PowerShell'de:
.\build.bat
```

İyi eğlenceler! 🌍🪐✨
