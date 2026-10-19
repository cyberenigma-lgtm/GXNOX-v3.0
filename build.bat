@echo off
setlocal enabledelayedexpansion

echo ===============================================================================
echo   GXNOX v3.0 COMPILATION TOOLCHAIN - 100%% ANSI C99
echo ===============================================================================

if not exist bin mkdir bin

echo [*] Compiling GXNOX Core and Dual-Bank modules...
gcc -O3 -Wall -Wextra -std=c99 -Isrc src\gxnox_core.c src\dual_parity.c src\neurocobol_rules.c src\main.c -o bin\gxnox_tool.exe -lpsapi

if %ERRORLEVEL% EQU 0 (
    echo [OK] Compilation successful: bin\gxnox_tool.exe
) else (
    echo [ERROR] Compilation failed with code %ERRORLEVEL%
    exit /b %ERRORLEVEL%
)

echo.
bin\gxnox_tool.exe
