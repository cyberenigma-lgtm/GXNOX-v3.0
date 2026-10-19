/*
 * ============================================================================
 * GXNOX DUAL-BANK PAR/IMPAR (+1) & NEUROCOBOL 3.0 DETERMINISTIC SHIELD
 * Reference Header in 100% ANSI C99 / Hardware Register Alignment
 *
 * Architecture: Even-Bank Direct Data (2k) + Odd-Bank Backward Mirror (2k+1)
 *               Active Bit-Rot Self-Healing & Anti-Ransomware Invariant Shield
 * Author: Jose Manuel Moreno (JMM)
 * Safe Creative Registration ID: 2609046909131
 * ============================================================================
 */

#ifndef GXNOX_DUAL_PARITY_H
#define GXNOX_DUAL_PARITY_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GXNOX_SECTOR_SIZE        4096ULL
#define NEUROCOBOL_MASK_KEY      0xA5C3F05AULL
#define NEUROCOBOL_SHIFT_PLUS1   1

/* Feature Flag for Dual-Bank Shield */
#define FLAG_DUAL_BANK_PAR_IMPAR 0x0040
#define FLAG_NEUROCOBOL_VERIFIED 0x0080
#define FLAG_SELF_HEALING_ACTIVE 0x0100

#pragma pack(push, 1)

/* 32-Byte Ultra-Compact Tokenized Extent Entry */
typedef struct {
    uint64_t filename_hash;      /* 0x00: xxHash64 of filename (Zero-RAM String Pool) */
    uint64_t lba_offset_par;     /* 0x08: Even LBA sector offset (2k) */
    uint32_t uncompressed_size;  /* 0x10: Actual payload size in bytes */
    uint32_t packed_size;        /* 0x14: Packed size in Even bank (aligned to 4KB) */
    uint32_t crc32_parity;       /* 0x18: CRC32 checksum of clean Even data */
    uint16_t cache_line_offset;  /* 0x1C: 64-byte alignment marker */
    uint16_t flags;              /* 0x1E: Feature bits (Dual-bank, compressed, etc.) */
} GxCompactExtent32;             /* TOTAL: EXACTLY 32 BYTES */

/* Extended Master Header Descriptor */
typedef struct {
    uint32_t magic;                     /* 0x00: 0x584E5847 ("GXNX") */
    uint32_t version;                   /* 0x04: 3 */
    uint64_t transaction_id;            /* 0x08: Atomic state checkpoint */
    uint64_t timestamp_epoch_utc;       /* 0x10: Epoch timestamp */
    uint64_t total_allocated_bytes;     /* 0x18: Total capacity */
    uint32_t allocated_blocks_count;    /* 0x20: Number of 4KB blocks */
    uint32_t authority_signature;       /* 0x24: 0x4A4D4D43 ("JMM") */
    uint64_t parity_checksum_crc64;     /* 0x28: Rolling CRC64 checksum */
    uint32_t feature_flags;             /* 0x30: Feature bitmask */
    uint8_t  reserved_alignment_pad[12];/* 0x34: 64-byte boundary pad */
    uint8_t  hmac_sha256_digest[32];    /* 0x40: Cryptographic seal */
    float    vector_embeddings[104];    /* 0x60: Semantic index */
} GxMasterHeaderV3;

#pragma pack(pop)

/* Checksum calculation */
uint32_t gxnox_crc32(const uint8_t *data, size_t length);
uint64_t gxnox_hash_name(const char *name);

/* NeuroCOBOL 3.0 Deterministic Invariant Check: LBA_impar == LBA_par + 1 sector */
static inline bool neurocobol_verify_dual_lba_invariant(uint64_t lba_par, uint64_t lba_impar) {
    return (lba_impar == lba_par + GXNOX_SECTOR_SIZE);
}

/* Encode Clean Even Sector (2k) into Backward-Inverted Dimensional Mirror (+1) for Odd Sector (2k+1) */
void gxnox_encode_impar_mirror(const uint8_t *par_block, uint8_t *impar_block, size_t block_size);

/* Decode & Reconstruct Clean Even Sector from Odd Sector Mirror */
void gxnox_decode_impar_mirror(const uint8_t *impar_block, uint8_t *restored_par_block, size_t block_size);

/* Active Self-Healing Engine: Validates Parity; if corrupted, rebuilds from Odd bank and verifies CRC */
bool gxnox_self_heal_sector(const uint8_t *impar_block, uint8_t *repaired_par_block, size_t block_size, uint32_t expected_crc);

#if defined(_WIN32)
#include <windows.h>
bool gxnox_write_shielded_block(HANDLE hFile, uint64_t lba_par_offset, const uint8_t *clean_data, size_t block_size, uint32_t *out_crc);
bool gxnox_read_shielded_block(HANDLE hFile, uint64_t lba_par_offset, uint8_t *dest_buffer, size_t block_size, uint32_t expected_crc, bool *was_repaired);
#endif

#ifdef __cplusplus
}
#endif

#endif /* GXNOX_DUAL_PARITY_H */
