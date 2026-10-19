# ==============================================================================
# INDUSTRIAL PACKAGING SCRIPT FOR SAFE CREATIVE INTELLECTUAL PROPERTY DEPOSIT
# Standard: GXNOX Storage Container Specification (v3.0)
# Author: Jose Manuel Moreno (JMM)
# ==============================================================================

$ErrorActionPreference = "Stop"

$repoRoot = "C:\IAGROK\Sovereign-Bunker-GXNOX"
$zipPath = "C:\IAGROK\PAQUETE_REGISTRO_SAFECREATIVE_GXNOX_V3.zip"
$stageDir = Join-Path $repoRoot "staging_pkg\GXNOX_v3_Specification_Reference_C99"

Write-Host "==============================================================================="
Write-Host "  GXNOX v3.0 PACKAGING FOR INTELLECTUAL PROPERTY REGISTRATION (SAFE CREATIVE)"
Write-Host "==============================================================================="

if (Test-Path $zipPath) {
    Remove-Item -Path $zipPath -Force
    Write-Host "[*] Removed previous zip file: $zipPath"
}

if (Test-Path (Join-Path $repoRoot "staging_pkg")) {
    Remove-Item -Path (Join-Path $repoRoot "staging_pkg") -Recurse -Force
}

New-Item -ItemType Directory -Path $stageDir -Force | Out-Null
Write-Host "[*] Created clean staging directory: $stageDir"

# Copy directories
Copy-Item -Path (Join-Path $repoRoot "src") -Destination $stageDir -Recurse -Force
Copy-Item -Path (Join-Path $repoRoot "docs") -Destination $stageDir -Recurse -Force
Copy-Item -Path (Join-Path $repoRoot "tests") -Destination $stageDir -Recurse -Force
Copy-Item -Path (Join-Path $repoRoot "bin") -Destination $stageDir -Recurse -Force

# Copy root specification files
$filesToCopy = @(
    "build.bat",
    "run_tests.bat",
    "Makefile",
    "gxnox_container.upl",
    "LICENSE",
    "README.md",
    "DOCUMENTACION_TECNICA_Y_PRUEBAS_EMPIRICAS_GXNOX.md"
)

foreach ($file in $filesToCopy) {
    $src = Join-Path $repoRoot $file
    if (Test-Path $src) {
        Copy-Item -Path $src -Destination $stageDir -Force
        Write-Host "  -> Packaged: $file"
    } else {
        Write-Warning "File not found: $src"
    }
}

Write-Host "[*] Compressing repository into $zipPath ..."
Compress-Archive -Path "$stageDir\*" -DestinationPath $zipPath -CompressionLevel Optimal

# Cleanup staging
Remove-Item -Path (Join-Path $repoRoot "staging_pkg") -Recurse -Force

# Telemetry verification
$zipItem = Get-Item $zipPath
$sha256 = (Get-FileHash -Path $zipPath -Algorithm SHA256).Hash

Write-Host ""
Write-Host "==============================================================================="
Write-Host "  [OK] REGISTRATION PACKAGE CREATED SUCCESSFULLY"
Write-Host "==============================================================================="
Write-Host "  Target File  : $zipPath"
Write-Host "  Size (Bytes) : $($zipItem.Length) bytes ($([math]::Round($zipItem.Length / 1MB, 2)) MB)"
Write-Host "  SHA256 Hash  : $sha256"
Write-Host "  Date / Time  : $($zipItem.LastWriteTime)"
Write-Host "==============================================================================="
