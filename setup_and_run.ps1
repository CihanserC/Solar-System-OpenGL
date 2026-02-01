# Otomatik Kurulum ve Calistirma
# Bu script FreeGLUT'u indirir, kurar ve projeyi derler

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Solar System OpenGL - Otomatik Kurulum" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Step 1: Check Visual Studio
Write-Host "1/4: Visual Studio kontrol ediliyor..." -ForegroundColor Yellow
$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"

if (!(Test-Path $vswhere)) {
    Write-Host "HATA: Visual Studio bulunamadi!" -ForegroundColor Red
    Write-Host "Lutfen Visual Studio ile C++ Desktop Development yukleyin." -ForegroundColor Red
    Read-Host "Devam etmek icin Enter tusuna basin"
    exit 1
}

Write-Host "Visual Studio bulundu!" -ForegroundColor Green
Write-Host ""

# Step 2: Download FreeGLUT
Write-Host "2/4: FreeGLUT indiriliyor..." -ForegroundColor Yellow

$freeglutUrl = "https://www.transmissionzero.co.uk/files/software/development/GLUT/freeglut-MSVC.zip"
$downloadPath = "$env:TEMP\freeglut.zip"
$extractPath = "$PSScriptRoot\freeglut"

try {
    Write-Host "Indirme basladi (bu 1-2 dakika surebilir)..." -ForegroundColor Gray
    Invoke-WebRequest -Uri $freeglutUrl -OutFile $downloadPath -UseBasicParsing
    Write-Host "FreeGLUT indirildi!" -ForegroundColor Green
} catch {
    Write-Host "UYARI: Otomatik indirme basarisiz." -ForegroundColor Yellow
    Write-Host "Manuel indirme: https://www.transmissionzero.co.uk/software/freeglut-devel/" -ForegroundColor Yellow
    Write-Host "Zip dosyasini $extractPath klasorune cikarin." -ForegroundColor Yellow
    Write-Host ""
    $manual = Read-Host "Manuel olarak indirdiniz mi? (E/H)"
    if ($manual -ne "E") {
        exit 1
    }
}

# Step 3: Extract FreeGLUT
Write-Host ""
Write-Host "3/4: FreeGLUT cikartiliyor..." -ForegroundColor Yellow

if (Test-Path $downloadPath) {
    try {
        Expand-Archive -Path $downloadPath -DestinationPath $extractPath -Force
        Write-Host "FreeGLUT cikartildi!" -ForegroundColor Green
    } catch {
        Write-Host "HATA: Zip dosyasi cikartilirken sorun olustu." -ForegroundColor Red
        Read-Host "Devam etmek icin Enter tusuna basin"
        exit 1
    }
}

# Copy DLL to project root
$dllSource = Get-ChildItem -Path $extractPath -Filter "freeglut.dll" -Recurse | Select-Object -First 1
if ($dllSource) {
    Copy-Item $dllSource.FullName -Destination "$PSScriptRoot\" -Force
    Write-Host "freeglut.dll kopyalandi!" -ForegroundColor Green
} else {
    Write-Host "UYARI: freeglut.dll bulunamadi. Manuel kopyalama gerekebilir." -ForegroundColor Yellow
}

Write-Host ""

# Step 4: Build
Write-Host "4/4: Proje derleniyor..." -ForegroundColor Yellow
Write-Host ""

# Try CMake build first (more reliable)
$cmakeBuild = Join-Path $PSScriptRoot "build_cmake.bat"
$msvcBuild = Join-Path $PSScriptRoot "build_msvc.bat"

if (Test-Path $cmakeBuild) {
    Write-Host "CMake ile derleme yapiliyor..." -ForegroundColor Gray
    & cmd /c $cmakeBuild
    if ($LASTEXITCODE -eq 0) {
        $buildSuccess = $true
    }
}

if (-not $buildSuccess -and (Test-Path $msvcBuild)) {
    Write-Host "MSVC ile derleme deneniyor..." -ForegroundColor Gray
    & cmd /c $msvcBuild
    if ($LASTEXITCODE -eq 0) {
        $buildSuccess = $true
    }
}

if (-not $buildSuccess) {
    Write-Host "HATA: Derleme basarisiz!" -ForegroundColor Red
    Write-Host ""
    Write-Host "Manuel olarak deneyebilirsiniz:" -ForegroundColor Yellow
    Write-Host "1. .\build_cmake.bat" -ForegroundColor White
    Write-Host "2. .\build_msvc.bat" -ForegroundColor White
    Write-Host "3. .\build.bat" -ForegroundColor White
    Read-Host "Devam etmek icin Enter tusuna basin"
    exit 1
}

Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Kurulum Tamamlandi!" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "Proje SolarSystem.exe olarak derlendi." -ForegroundColor White
Write-Host "Calistirmak icin: .\SolarSystem.exe" -ForegroundColor White
Write-Host ""

Read-Host "Kapatmak icin Enter tusuna basin"
