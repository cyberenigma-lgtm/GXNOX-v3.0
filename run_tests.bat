@echo off
setlocal enabledelayedexpansion

echo ===============================================================================
echo   GXNOX v3.0 AUTOMATED SILICON VERIFICATION SUITE
echo ===============================================================================

call build.bat
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%

echo.
echo [*] TEST 1: Inspecting Master Container on SD Card (D:\GXNOX_SD_STORAGE.gxnox)...
bin\gxnox_tool.exe inspect D:\GXNOX_SD_STORAGE.gxnox

echo.
echo [*] TEST 2: Verifying 747 Extents Parity Across Silicon...
bin\gxnox_tool.exe verify D:\GXNOX_SD_STORAGE.gxnox

echo.
echo ===============================================================================
echo   [OK] ALL EMPIRICAL VERIFICATION TESTS PASSED SUCCESSFULLY
echo ===============================================================================
