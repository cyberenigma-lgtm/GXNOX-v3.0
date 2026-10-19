@echo off
echo ===============================================================================
echo   Compilando GXNOX Storage Container Toolchain (v3.0) en C99 Nativo
echo ===============================================================================

gcc -O3 -std=c99 -Wall -Wextra gxnox_tool.c -o gxnox_tool.exe
if %ERRORLEVEL% EQU 0 (
    echo.
    echo [EXITO] Binario gxnox_tool.exe compilado con optimizacion -O3.
    gxnox_tool.exe
) else (
    echo.
    echo [ERROR] Fallo en la compilacion con GCC.
)
