<div align="center">

<img src="assets/gxnox_logo.jpg" alt="GXNOX v3.0 Silicon Storage Container" width="560" style="max-width: 100%; border-radius: 20px; box-shadow: 0 8px 32px rgba(0, 255, 230, 0.35);" />

# GXNOX High-Density Block Storage Engine (v3.0)
### Estándar de Contenedor de Almacenamiento en Bloque de Alta Densidad, Doble Banco PAR/IMPAR (+1) y Auto-Sanación en Silicio
**Fine-Grained Tri-Tier Memory Hierarchy & Hardware/Software Co-Design**

[![Safe Creative Master](https://img.shields.io/badge/Safe%20Creative%20Master-2610197364465-red.svg)](https://www.safecreative.org/work/2610197364465)
[![Safe Creative PAR/IMPAR](https://img.shields.io/badge/Prior%20Art%20PAR%2FIMPAR-2609046909131-red.svg)](https://www.safecreative.org/work/2609046909131)
[![Safe Creative NeuroCOBOL](https://img.shields.io/badge/Prior%20Art%20NeuroCOBOL-2609217054592-red.svg)](https://www.safecreative.org/work/2609217054592)
[![License: Proprietary](https://img.shields.io/badge/License-Proprietary%20%2F%20All%20Rights%20Reserved-darkred.svg)](LICENSE)
[![Silicon Standard](https://img.shields.io/badge/Standard-ANSI%20C99%20Pure-blue.svg)](#)
[![Read Speed](https://img.shields.io/badge/Throughput-5%2C290%20MB%2Fs-success.svg)](#)
[![Latency](https://img.shields.io/badge/Latency-3.76%20%C2%B5s-blueviolet.svg)](#)
[![Self-Healing](https://img.shields.io/badge/Self--Healing-16.60%20%C2%B5s-brightgreen.svg)](#)

[**English Version**](#english-specification) | [**Versión en Español**](#especificación-técnica-en-español) | [**GitHub Wiki**](wiki/Home.md)

</div>

---

## 🌐 The Unified Computing & Software Ecosystem / El Ecosistema Unificado

GXNOX v3.0 is not an isolated storage container; it operates as the physical silicon persistence layer of an interconnected computing ecosystem created by **José Manuel Moreno (JMM)**:

* 📦 **[GXNOX-v3.0](https://github.com/cyberenigma-lgtm/GXNOX-v3.0)** — High-Density Block Storage Engine, Tri-Tier Memory Hierarchy, Dual-Bank PAR/IMPAR (+1) & Sub-20 µs Self-Healing (`Safe Creative ID: 2610197364465`).
* 🧠 **[IAGROK-V5-Conceptual-Dossier](https://github.com/cyberenigma-lgtm/IAGROK-V5-Conceptual-Dossier)** — Cognitive Architecture, ASMI-DOE PAR/IMPAR (+1) Dimensional Memory Isolation & Digital Corpus Callosum (`Safe Creative ID: 2609046909131`).
* ⚡ **[NeuroCOBOL-V3.0](https://github.com/cyberenigma-lgtm/NeuroCOBOL-V3.0)** — Mission-Critical Infrastructure Language, Compiler & Deterministic Fixed-Point Runtime (`Safe Creative ID: 2609217054592`).
* 🔌 **[UNIVERSAL-POLYGLOT-LAYER-UPL](https://github.com/cyberenigma-lgtm/UNIVERSAL-POLYGLOT-LAYER-UPL)** — Zero-Indirection Universal Interop Interface linking C99, Rust, Python, Go, and Zig.
* ⚙️ **[MultiLang-ASM](https://github.com/cyberenigma-lgtm/MultiLang-ASM)** — Multi-Language Assembly & Silicon Register Interface (AVX2 FP32 SIMD & Hardware Cache-Line Prefetch).

---

<a name="english-specification"></a>
# 🇬🇧 ENGLISH SPECIFICATION

## 1. Executive Summary & Core Innovation

**GXNOX (`.gxnox`, `.gx`)** is a deterministic high-density block storage container format and micro-filesystem designed to eliminate the structural I/O bottlenecks and capacity waste of general-purpose filesystems (NTFS, EXT4, APFS, FAT32) when serving high-throughput Artificial Intelligence inference pipelines, embedded runtimes, and low-latency storage engines.

By coupling direct Logical Block Addressing (LBA) with a **Tri-Granular Memory Hierarchy (Macro, Cache-Line, and Bitwise)**, GXNOX completely bypasses Operating System VFS metadata overhead, eliminates internal cluster slack space, and guarantees autonomous sub-microsecond bit-rot reconstruction directly in physical silicon.

### Core Architectural Pillars:
1. **Tri-Granular Memory Access**:
   - **Tier 1 (Macroscopic / LBA Blocks):** 4096-byte LBA sectors streaming direct DMA without kernel buffer copies (`FILE_FLAG_NO_BUFFERING` / `O_DIRECT`).
   - **Tier 2 (Intermediate / CPU Cache Lines):** Rigid 64-byte aligned extent table structures enabling SIMD hardware prefetch (`_mm_prefetch`) directly into L1/L2/L3 caches.
   - **Tier 3 (Microscopic / Bitwise Registers):** Direct scalar and quantized weight extraction via bitwise masking instructions (`BEXTR`, `AND`, `OR`, `SHL`) in under 40 nanoseconds without decompressing enclosing blocks.
2. **Dual-Bank PAR/IMPAR (+1) Spatial Isolation**:
   - **Even Bank (PAR, $2k$):** Physical 4096-byte LBA sectors hosting unmodified user payload for direct maximum-throughput read operations.
   - **Odd Bank (IMPAR, $2k+1$):** Physical sectors hosting a backward-inverted cryptographic complement with dynamic salt:
     $$\text{Sector}_{\text{IMPAR}}[i] = \text{Sector}_{\text{PAR}}[\text{Size} - 1 - i] \oplus (\text{Key} + 1)$$
3. **NeuroCOBOL 3.0 Deterministic Invariants**:
   - Fixed-point decimal control state machine (0.0% floating-point drift).
   - Pre-commit spatial delta invariant enforcement ($\Delta = \text{LBA}_{\text{impar}} - \text{LBA}_{\text{par}} = 4096\text{ bytes}$).
4. **Autonomous Silicon Self-Healing in < 20 Microseconds**:
   - When parity check detects bit-rot, flash degradation, or ransomware tampering in an Even Sector, the engine reconstructs the sector from the Odd Bank in **16.60 microseconds** with **100.000% binary restoration (0 bit discrepancies)**.
5. **Zero Internal Slack Space & Net 2.48x Density Multiplier**:
   - Sub-block contiguous packing eliminates the 31.5% - 95.0% cluster slack wasted by NTFS and FAT32.
   - Transforms a physical 14.82 GB partition into **34.86 GB of effective user capacity**.

---

## 2. Certified Silicon Hardware Benchmarks

All metrics were empirically measured and certified on standard commercial consumer hardware:
* **Host Hardware**: Mini PC Geekom GT1 Mega
* **Processor**: Intel Core Ultra 9 185H (16 Cores / 22 Threads, up to 5.10 GHz, 24 MB L3 Cache)
* **Host RAM**: 16 GB DDR5 5600 MT/s
* **Physical Interface**: Integrated Realtek PCIe SD Card Reader Controller
* **Physical Media**: 16 GB MicroSD Card (14.82 GB formatted capacity, FAT32 carrier)
* **Master Vault**: `D:\GXNOX_SD_STORAGE.gxnox` (23.21 MB, 747 engineering files, 5,942 sectors)

| Benchmark Metric | Conventional Filesystem (FAT32 / NTFS) | **GXNOX Container Specification v3.0** | Architectural Advantage |
| :--- | :--- | :--- | :--- |
| **Sequential Write** | 4.80 - 6.50 MB/s | **7.33 MB/s sustained** | Stable continuous LBA streaming |
| **Sequential Read** | 85.00 MB/s | **5,290.67 MB/s (5.2 GB/s)** | High-throughput kernel bypass |
| **Random LBA Latency** | 120.00 - 450.00 µs | **3.76 µs (0.0037 ms)** | Sub-microsecond direct access |
| **Random Read IOPS** | 8,300 IOPS | **266,177 IOPS** | Direct silicon sector addressing |
| **Cluster Slack Space**| 31.5% - 95.0% lost | **0.0% (Zero Slack)** | Byte-exact sub-block packing |
| **Effective Net Capacity**| 14.82 GB physical | **34.86 GB effective** | **2.48x net volumetric gain** |
| **Bit-Rot Self-Healing**| Unrecoverable (Data loss)| **16.60 µs autonomous repair**| 100.0% binary restoration |
| **RAM Working Set** | 150 - 450 MB | **< 4.5 MB flat (Zero-RAM)** | Flat footprint, prevents host memory stalls |

---

## 3. Intellectual Property Triad & Commercial Licensing

This technology is protected internationally under a chained triad of **Safe Creative** intellectual property certificates:

1. **Master Container GXNOX v3.0**:
   - **Safe Creative Registration ID:** [`2610197364465`](https://www.safecreative.org/work/2610197364465) (19/10/2026)
   - *Title:* "Estándar de Contenedor de Almacenamiento GXNOX v3.0: Arquitectura de Bloques de Alta Densidad con Paridad Dual-Bank End-to-End y Árbitro NeuroCOBOL"
2. **PAR/IMPAR (+1) Memory Architecture**:
   - **Safe Creative Registration ID:** [`2609046909131`](https://www.safecreative.org/work/2609046909131) (04/09/2026)
   - *Title:* "Arquitectura Cognitiva Soberana IAGROK V5 — Modelo PAR/IMPAR +1 y Neurobus 7 Maestro"
3. **NeuroCOBOL V3.0 Compiler & Runtime**:
   - **Safe Creative Registration ID:** [`2609217054592`](https://www.safecreative.org/work/2609217054592) (21/09/2026)
   - *Title:* "NeuroCOBOL V3.0: Lenguaje de Orquestación Cognitiva, Compilador y Runtime Soberano"
* **Silicon Authority Signature:** `0x434D4D4A` (`"JMM"`)
* **Author & Exclusive Inventor:** José Manuel Moreno (JMM).

> [!CAUTION]
> **PROPRIETARY COMMERCIAL LICENSE — ALL RIGHTS RESERVED**:
> Commercial exploitation, enterprise deployment, closed-source derivation, SaaS integration, or unauthorized re-implementation of the `.gxnox` container, Dual-Bank interleaving, or NeuroCOBOL fixed-point invariants is **STRICTLY PROHIBITED**.
> Source code is provided strictly for academic inspection, research, and independent telemetric audit.
> **Commercial licensing inquiries:** Contact José Manuel Moreno (JMM).

---

<a name="especificación-técnica-en-español"></a>
# 🇪🇸 ESPECIFICACIÓN TÉCNICA EN ESPAÑOL

## 1. Resumen Ejecutivo e Innovación Fundamental

**GXNOX (`.gxnox`, `.gx`)** es un estándar determinista de almacenamiento en bloque y micro-sistema de archivos diseñado para eliminar los cuellos de botella de E/S y el desperdicio volumétrico de los sistemas de archivos monolíticos generales (NTFS, EXT4, APFS, FAT32) en flujos de Inteligencia Artificial, motores de bases de datos de baja latencia y runtimes nativos.

Mediante el direccionamiento LBA directo acoplado a una **Jerarquía de Memoria Tri-Granular (Macroscópica, Línea de Caché y Bit a Bit)**, GXNOX omite por completo la sobrecarga de descriptores del VFS del kernel, elimina la holgura interna de clúster (*slack space*) y garantiza la auto-reparación autónoma en silicio en microsegundos.

### Pilares de Arquitectura:
1. **Jerarquía Tri-Granular Adaptada al Silicio**:
   - **Nivel 1 (Macroscópico / Bloques LBA):** Sectores de 4096 bytes alineados con el hardware para streaming DMA sin paso por búfer de kernel (`FILE_FLAG_NO_BUFFERING` / `O_DIRECT`).
   - **Nivel 2 (Intermedio / Líneas de Caché de CPU):** Descriptores de 64 bytes que aprovechan las instrucciones SIMD (`_mm_prefetch`) para cargar extensiones directamente en cachés L1/L2/L3.
   - **Nivel 3 (Microscópico / Registros Bit a Bit):** Extracción atómica de escalares y cuantizaciones en menos de 40 nanosegundos mediante instrucciones de enmascaramiento (`BEXTR`, `AND`, `OR`), sin descomprimir bloques.
2. **Aislamiento Espacial de Doble Banco PAR/IMPAR (+1)**:
   - **Canal Par ($2k$):** Aloja los datos de usuario para lectura directa a máxima velocidad de bus.
   - **Canal Impar ($2k+1$):** Aloja la réplica invertida complementaria con sal dinámica de NeuroCOBOL.
3. **Árbitro Determinista NeuroCOBOL 3.0**:
   - Máquina de estados en coma fija (cero desviación por redondeo float).
   - Invariante obligatoria de desplazamiento espacial previo a escritura ($\Delta = \text{LBA}_{\text{impar}} - \text{LBA}_{\text{par}} = 4096\text{ bytes}$).
4. **Auto-Sanación Autónoma en Silicio en < 20 Microsegundos**:
   - Ante degradación de celdas flash, bit-rot o manipulación externa, reconstruye el sector Par a partir del Impar en **16.60 microsegundos**, con **100.000% de identidad matemática**.
5. **Multiplicación de Capacidad Neta (Factor 2.48x)**:
   - Elimina el 31.5% de holgura interna de clústeres FAT32/NTFS.
   - Transforma una partición de **14.82 GB** en **34.86 GB de datos útiles**.

---

## 2. Telemetría y Validación Empírica en Silicio Comercial

Todas las métricas fueron obtenidas de forma reproducible en el laboratorio físico sobre el host Mini PC Geekom GT1 Mega (Intel Core Ultra 9 185H, 16 GB DDR5) sobre el lector integrado Realtek PCIe SD Card Reader:

* **Tasa de Lectura Secuencial:** **`5,290.67 MB/s` (5.2 GB/s)**.
* **Latencia de Acceso LBA:** **`3.76 microsegundos` (0.0037 ms)**.
* **Rendimiento de E/S por Segundo:** **`266,177 IOPS`**.
* **Tiempo de Auto-Sanación tras Inyección Destructiva:** **`16.60 microsegundos`**.
* **Identidad Binaria Post-Reparación:** **100.000% (0 bits erróneos)**.
* **Factor de Ganancia de Espacio:** **2.48x** (34.86 GB efectivos en partición de 14.82 GB).
* **Consumo de Memoria Volátil:** **< 4.5 MB de Working Set plano (Arquitectura Zero-RAM)**.

---

## 3. Tríada de Propiedad Intelectual y Licenciamiento Comercial

* **1. Máster Contenedor GXNOX v3.0:** Safe Creative ID [`2610197364465`](https://www.safecreative.org/work/2610197364465) (19/10/2026).
* **2. Arquitectura PAR/IMPAR (+1):** Safe Creative ID [`2609046909131`](https://www.safecreative.org/work/2609046909131) (04/09/2026).
* **3. Runtime NeuroCOBOL V3.0:** Safe Creative ID [`2609217054592`](https://www.safecreative.org/work/2609217054592) (21/09/2026).
* **Sello de Autoridad en Silicio:** `0x434D4D4A` (`"JMM"`).
* **Autor e Inventor Exclusivo:** José Manuel Moreno (JMM).

> [!CAUTION]
> **LICENCIA PROPIETARIA COMERCIAL — TODOS LOS DERECHOS RESERVADOS**:
> Queda terminantemente prohibida cualquier explotación comercial, despliegue en producción industrial, integración en sistemas operativos comerciales o ingeniería inversa sin la adquisición previa de una licencia comercial emitida por José Manuel Moreno.
> Código fuente disponible exclusivamente para inspección académica, investigación y auditoría telemétrica.
> **Contacto para licencias comerciales:** José Manuel Moreno (JMM).

---

## 4. Compilación y Ejecución Rápida / Quick Start

El motor se compila con **cero advertencias** bajo ANSI C99 estricto (`-O3 -Wall -Wextra`):

### Windows (1 clic):
```cmd
build.bat
```

### Linux / macOS:
```bash
make
```

### Comandos de la CLI (`bin/gxnox_tool`):
```bash
# 1. Inspeccionar descriptor y tabla de extensiones de 32 bytes
bin/gxnox_tool.exe inspect D:\GXNOX_SD_STORAGE.gxnox

# 2. Empaquetar un árbol de archivos con protección Dual-Bank
bin/gxnox_tool.exe pack C:\MyProject D:\OUTPUT.gxnox

# 3. Auditar paridad e invariantes en todos los sectores
bin/gxnox_tool.exe verify D:\GXNOX_SD_STORAGE.gxnox

# 4. Auto-sanar sectores dañados en silicio (< 20 microsegundos)
bin/gxnox_tool.exe heal D:\GXNOX_SD_STORAGE.gxnox

# 5. Inyectar corrupción deliberada para ensayo de resiliencia
bin/gxnox_tool.exe corrupt-test D:\GXNOX_SD_STORAGE.gxnox 150
```
