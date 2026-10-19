# Compilation & CLI Command Reference
### Guía de Compilación C99 y Manual de Comandos de la CLI

[Back to Wiki Home](Home.md)

---

## 🇬🇧 English: Compilation Instructions

The reference toolchain is implemented in strict **ANSI C99** with zero third-party dependencies. It compiles cleanly with zero warnings under `-O3 -Wall -Wextra`.

### 1. Windows Compilation (1-Click Script):
```cmd
build.bat
```

*Direct GCC MinGW Command:*
```cmd
gcc -O3 -Wall -Wextra -std=c99 -Isrc src\gxnox_core.c src\dual_parity.c src\neurocobol_rules.c src\main.c -o bin\gxnox_tool.exe -lpsapi
```

### 2. Linux / macOS Compilation:
```bash
make
```

### 3. Automated Test Suite:
```cmd
run_tests.bat
```

---

## 💻 Command Reference / Manual de Comandos

The CLI toolchain binary is located at `bin/gxnox_tool`:

### 1. `inspect` — Inspect Container Descriptors & Extent Tables
Reads Sector 0 and displays the master container header, capacity, transaction ID, feature flags, and extent allocation:
```bash
bin/gxnox_tool.exe inspect D:\GXNOX_SD_STORAGE.gxnox
```

### 2. `pack` — Ingest Directory Tree into a Dual-Bank Container
Recursively scans a source directory, generates compact 32-byte extent descriptors, and writes Even/Odd sector pairs to storage:
```bash
bin/gxnox_tool.exe pack C:\MyProject D:\OUTPUT.gxnox
```

### 3. `verify` — Parity Audit & Invariant Check
Scans all extents across physical silicon, verifying CRC32 checksums and NeuroCOBOL spatial invariants:
```bash
bin/gxnox_tool.exe verify D:\GXNOX_SD_STORAGE.gxnox
```

### 4. `heal` — Autonomous Bit-Rot Repair
Sweeps the container for compromised Even sectors and reconstructs them from the complementary Odd mirrors:
```bash
bin/gxnox_tool.exe heal D:\GXNOX_SD_STORAGE.gxnox
```

### 5. `corrupt-test` — Deliberate Bit-Rot Injection for Resilience Verification
Deliberately overwrites an Even sector with corrupted bytes (`0xEE`) to validate detection and sub-20 µs recovery:
```bash
bin/gxnox_tool.exe corrupt-test D:\GXNOX_SD_STORAGE.gxnox 150
```
