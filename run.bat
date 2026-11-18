@echo off
setlocal
if not defined VSCMD_VER call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"

if "%~1"=="" (
    cmake --build build --target run
) else if /i "%~1"=="generate" (
    if exist "build\CMakeCache.txt" del /f /q "build\CMakeCache.txt"
    cmake -G Ninja -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
) else (
    echo Unknown argument: "%~1"
    echo Usage: %~nx0 [generate]
    exit /b 1
)
