# Texture Loading Guide

This project can apply realistic textures to planets. Texture files are optional - if not available, solid colors will be used.

## Texture Files

Place the following files in this directory:

- `sun.jpg` - Sun texture
- `mercury.jpg` - Mercury texture
- `venus.jpg` - Venus texture
- `earth.jpg` - Earth texture
- `mars.jpg` - Mars texture
- `jupiter.jpg` - Jupiter texture
- `saturn.jpg` - Saturn texture
- `uranus.jpg` - Uranus texture
- `neptune.jpg` - Neptune texture
- `moon.jpg` - Moon texture

## Recommended Texture Sources

### 1. Solar System Scope
- Website: https://www.solarsystemscope.com/textures/
- Free, high-quality planet textures
- 2K and 4K resolutions available

### 2. NASA 3D Resources
- Website: https://nasa3d.arc.nasa.gov/
- Public domain planet and moon textures
- Scientifically accurate

### 3. Planet Pixel Emporium
- Website: http://planetpixelemporium.com/
- Planet maps and textures
- Free to use

## Texture Download

PowerShell script for easy downloading:

```powershell
# Run in textures folder
# Example: Download from Solar System Scope
$urls = @{
    "sun.jpg" = "URL_HERE"
    "earth.jpg" = "URL_HERE"
    # ... other planets
}

foreach ($file in $urls.Keys) {
    Invoke-WebRequest -Uri $urls[$file] -OutFile $file
    Write-Host "Downloaded: $file"
}
```

## Texture Format

- Format: JPG or PNG
- Recommended size: 2048x1024 (2K) or 1024x512 (1K)
- Mapping: Equirectangular (cylindrical projection)

## Note

If the program cannot find textures, it will automatically fall back to solid colors. All features work without textures.
