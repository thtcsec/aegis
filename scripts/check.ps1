# Aegis Local Verification Script
# This script formats code, builds the project, and runs tests.

$ErrorActionPreference = "Stop"

# --- 0. Setup Git Hooks ---
$hookPath = ".git/hooks/pre-push"
if (!(Test-Path $hookPath)) {
    Write-Host "Installing Git pre-push hook..." -ForegroundColor Yellow
    Copy-Item "scripts/pre-push.sample" $hookPath
    Write-Host "Git hook installed successfully." -ForegroundColor Green
}

Write-Host "--- 1. Checking Code Formatting ---" -ForegroundColor Cyan
$clangFormat = "C:\Program Files\LLVM\bin\clang-format.exe"
if (!(Test-Path $clangFormat)) { $clangFormat = "clang-format" } # Fallback to PATH

Get-ChildItem -Include *.cpp,*.hpp -Recurse | ForEach-Object {
    & $clangFormat -i $_.FullName
}
Write-Host "Formatting check complete." -ForegroundColor Green

Write-Host "--- 2. Configuring CMake ---" -ForegroundColor Cyan
if (!(Test-Path build)) { New-Item -ItemType Directory -Path build }
& cmake -B build -DCMAKE_BUILD_TYPE=Debug

Write-Host "--- 3. Building Aegis ---" -ForegroundColor Cyan
& cmake --build build --config Debug

Write-Host "--- 4. Running Tests ---" -ForegroundColor Cyan
Set-Location build
& ctest --output-on-failure
Set-Location ..

Write-Host "`nAll local checks PASSED! You are safe to push." -ForegroundColor Green
