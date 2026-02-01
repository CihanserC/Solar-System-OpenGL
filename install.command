#!/bin/bash

# Solar System OpenGL - Otomatik Kurulum ve Çalıştırma
# Sadece çift tıklayın!

clear
echo "================================================"
echo "  Solar System OpenGL - Otomatik Kurulum"
echo "================================================"
echo ""

# Script'in bulunduğu dizine git
cd "$(dirname "$0")"

# XCode Command Line Tools kontrolü
echo "[1/4] XCode Command Line Tools kontrol ediliyor..."
if ! xcode-select -p &> /dev/null; then
    echo "⚠️  XCode Command Line Tools bulunamadı!"
    echo "📦 Yükleme penceresi açılacak, lütfen 'Install' düğmesine tıklayın..."
    echo "⏱️  Bu işlem 5-10 dakika sürebilir, lütfen bekleyin..."
    xcode-select --install
    
    # Kullanıcının tools'u yüklemesini bekle
    echo ""
    echo "✋ XCode Command Line Tools yüklendikten sonra bu pencereye geri dönün"
    read -p "Yükleme tamamlandığında ENTER tuşuna basın..." dummy
else
    echo "✅ XCode Command Line Tools zaten yüklü!"
fi

# Homebrew kontrolü
echo ""
echo "[2/4] Homebrew kontrol ediliyor..."
if ! command -v brew &> /dev/null; then
    echo "⚠️  Homebrew bulunamadı!"
    echo "📦 Homebrew yükleniyor (Mac için paket yöneticisi)..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    
    # Homebrew'i PATH'e ekle (M1/M2 Mac için)
    if [[ $(uname -m) == 'arm64' ]]; then
        echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.zprofile
        eval "$(/opt/homebrew/bin/brew shellenv)"
    fi
else
    echo "✅ Homebrew zaten yüklü!"
fi

# CMake kontrolü
echo ""
echo "[3/4] CMake kontrol ediliyor..."
if ! command -v cmake &> /dev/null; then
    echo "⚠️  CMake bulunamadı!"
    echo "📦 CMake yükleniyor..."
    brew install cmake
else
    echo "✅ CMake zaten yüklü! ($(cmake --version | head -n1))"
fi

# Projeyi derle
echo ""
echo "[4/4] Solar System projesi derleniyor..."
if [ -d "build" ]; then
    echo "🧹 Eski build klasörü temizleniyor..."
    rm -rf build
fi

mkdir -p build
cd build

echo "⚙️  CMake yapılandırması..."
if ! cmake ..; then
    echo ""
    echo "❌ HATA: CMake yapılandırması başarısız!"
    read -p "Devam etmek için ENTER tuşuna basın..." dummy
    exit 1
fi

echo "🔨 Derleme işlemi başlıyor..."
if ! make; then
    echo ""
    echo "❌ HATA: Derleme başarısız!"
    read -p "Devam etmek için ENTER tuşuna basın..." dummy
    exit 1
fi

cd ..

echo ""
echo "================================================"
echo "✨ Kurulum tamamlandı!"
echo "================================================"
echo ""
echo "🚀 Solar System başlatılıyor..."
echo ""
sleep 2

# Uygulamayı çalıştır
./build/SolarSystem

echo ""
echo "================================================"
echo "Tekrar çalıştırmak için:"
echo "  - Bu dosyaya tekrar çift tıklayın"
echo "  - Veya Terminalde: ./build/SolarSystem"
echo "================================================"