@echo off
setlocal

if "%~1"=="" (
    cmake --build build --target run
) else if /i "%~1"=="generate" (
    cmake -G Ninja -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
) else (
    echo Unknown argument: "%~1"
    echo Usage: %~nx0 [generate]
    exit /b 1
)
