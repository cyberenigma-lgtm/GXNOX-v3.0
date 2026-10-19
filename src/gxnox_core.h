/* ============================================================================
 * ESTÁNDAR DE CONTENEDOR DE ALMACENAMIENTO EN BLOQUE GXNOX v3.0
 * ----------------------------------------------------------------------------
 * Autor y Titular de los Derechos: José Manuel Moreno (JMM)
 * 
 * TRÍADA DE PROPIEDAD INTELECTUAL Y PATENTES DE SOFTWARE ENCADENADAS:
 * 1. MÁSTER CONTENEDOR GXNOX v3.0 : Safe Creative ID 2610197364465 (19/10/2026)
 * 2. ARQUITECTURA PAR/IMPAR +1    : Safe Creative ID 2609046909131 (04/09/2026)
 * 3. RUNTIME NEUROCOBOL V3.0      : Safe Creative ID 2609217054592 (21/09/2026)
 * 
 * SELLO BINARIO DE AUTORIDAD (SILICON MASTER SIGNATURE): 0x434D4D4A ("JMM")
 * 
 * Estatus Legal: TODOS LOS DERECHOS RESERVADOS. Queda estrictamente prohibida
 * la reproducción, modificación o implementación comercial no autorizada del
 * formato .gxnox, de la geometría Dual-Bank o de sus árbitros de coma fija.
 * ============================================================================ */

#ifndef GXNOX_CORE_H
#define GXNOX_CORE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#if defined(_WIN32)
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define GXNOX_MAGIC                 0x584E5847ULL /* "GXNX" Little-Endian */
#define GXNOX_VERSION               3
#define GXNOX_AUTHORITY_JMM        0x4A4D4D43ULL /* "JMM" Standard Authority Seal */

#define GXNOX_SECTOR_SIZE           4096ULL       /* Tier 1: LBA Macro-Block */
#define GXNOX_CACHE_LINE_SIZE       64ULL         /* Tier 2: CPU Cache Line */
#define GXNOX_MAX_EXTENTS           1024

/* Feature Bitmask Flags */
#define FLAG_TIER1_MACRO_LBA        0x0001
#define FLAG_TIER2_CACHE_LINE       0x0002
#define FLAG_TIER3_BITWISE          0x0004
#define FLAG_ZERO_SLACK             0x0008
#define FLAG_SIMD_COMPRESSION       0x0010
#define FLAG_DEDUPLICATION          0x0020
#define FLAG_DUAL_BANK_PAR_IMPAR    0x0040
#define FLAG_NEUROCOBOL_VERIFIED    0x0080
#define FLAG_SELF_HEALING_ACTIVE    0x0100

#pragma pack(push, 1)

/* 32-Byte Ultra-Compact Tokenized Extent Entry (Zero-RAM Design) */
typedef struct {
    uint64_t filename_hash;      /* 0x00: xxHash/Murmur64 of filename */
    uint64_t lba_offset_par;     /* 0x08: Even LBA sector offset (2k) */
    uint32_t uncompressed_size;  /* 0x10: Actual uncompressed payload bytes */
    uint32_t packed_size;        /* 0x14: Packed size in silicio (aligned to 4KB) */
    uint32_t crc32_parity;       /* 0x18: CRC32 checksum of clean data */
    uint16_t cache_line_offset;  /* 0x1C: 64-byte alignment marker */
    uint16_t flags;              /* 0x1E: Feature bits */
} GxCompactExtent32;             /* TOTAL: EXACTLY 32 BYTES */

/* Master Header (Sector 0, 4096-byte boundary) */
typedef struct {
    uint32_t magic;                     /* 0x00: 0x584E5847 ("GXNX") */
    uint32_t version;                   /* 0x04: 3 */
    uint64_t transaction_id;            /* 0x08: Atomic Transaction/Checkpoint ID */
    uint64_t timestamp_epoch_utc;       /* 0x10: Creation timestamp */
    uint64_t total_allocated_bytes;     /* 0x18: Total capacity in bytes */
    uint32_t allocated_blocks_count;    /* 0x20: Number of 4KB blocks */
    uint32_t authority_signature;       /* 0x24: 0x4A4D4D43 ("JMM") */
    uint64_t parity_checksum_crc64;     /* 0x28: Rolling CRC64 parity */
    uint32_t feature_flags;             /* 0x30: Feature bitmask */
    uint8_t  reserved_alignment_pad[12];/* 0x34: Alignment to 64-byte boundary */
    uint8_t  hmac_sha256_digest[32];    /* 0x40: Cryptographic signature */
    float    vector_embeddings[104];    /* 0x60: Semantic AI vector index */
} GxMasterHeaderV3;

#pragma pack(pop)

/* Checksums and tokenization */
uint32_t gxnox_crc32(const uint8_t *data, size_t length);
uint64_t gxnox_crc64_block(const uint8_t *data, size_t length);
uint64_t gxnox_hash_name(const char *name);

/* Header lifecycle */
void gxnox_header_init(GxMasterHeaderV3 *hdr, uint64_t total_bytes, uint32_t flags);
bool gxnox_header_validate(const GxMasterHeaderV3 *hdr);

#ifdef __cplusplus
}
#endif

#endif /* GXNOX_CORE_H */
