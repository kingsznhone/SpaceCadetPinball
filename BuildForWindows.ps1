# Run from a Developer PowerShell for Visual Studio 2022/2026.
# Modern baseline: Windows 11 x64 only. XP/x86 builds are no longer supported.
param(
    [string]$Preset = "windows-x64"
)

$ErrorActionPreference = "Stop"

if (-not $env:VCPKG_ROOT) {
    throw "VCPKG_ROOT is not set. Point it at your vcpkg checkout first."
}

cmake --preset $Preset
cmake --build --preset "$Preset-release"

Compress-Archive -Path ".\bin\Release\*" -DestinationPath ".\bin\SpaceCadetPinball-x64-win.zip" -Force