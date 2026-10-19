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

#include "gxnox_core.h"
#include <string.h>
#include <time.h>

/* Fast CRC32 (IEEE 802.3 standard polynomial) */
uint32_t gxnox_crc32(const uint8_t *data, size_t length) {
    uint32_t crc = 0xFFFFFFFF;
    for (size_t i = 0; i < length; i++) {
        crc ^= (uint32_t)data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc >>= 1;
            }
        }
    }
    return ~crc;
}

/* Fast 64-bit Rolling Hash (CRC64-ECMA) */
uint64_t gxnox_crc64_block(const uint8_t *data, size_t length) {
    uint64_t crc = 0xFFFFFFFFFFFFFFFFULL;
    for (size_t i = 0; i < length; i++) {
        crc ^= (uint64_t)data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xC96C5795D7870F42ULL;
            } else {
                crc >>= 1;
            }
        }
    }
    return ~crc;
}

/* 64-bit Hash for Filename Tokenization (Murmur-inspired high entropy) */
uint64_t gxnox_hash_name(const char *name) {
    uint64_t h = 0xCBF29CE484222325ULL;
    if (!name) return h;
    while (*name) {
        h ^= (uint64_t)(unsigned char)(*name++);
        h *= 0x100000001B3ULL;
    }
    return h;
}

/* Initialize Master Header Descriptor (Sector 0) */
void gxnox_header_init(GxMasterHeaderV3 *hdr, uint64_t total_bytes, uint32_t flags) {
    if (!hdr) return;
    memset(hdr, 0, sizeof(GxMasterHeaderV3));
    hdr->magic = (uint32_t)GXNOX_MAGIC;
    hdr->version = GXNOX_VERSION;
    hdr->transaction_id = 1001;
    hdr->timestamp_epoch_utc = (uint64_t)time(NULL);
    hdr->total_allocated_bytes = total_bytes;
    hdr->allocated_blocks_count = (uint32_t)(total_bytes / GXNOX_SECTOR_SIZE);
    hdr->authority_signature = (uint32_t)GXNOX_AUTHORITY_JMM;
    hdr->feature_flags = flags;
    hdr->parity_checksum_crc64 = gxnox_crc64_block((const uint8_t*)hdr, 48);
}

/* Validate Master Header Magic and Authority Signature */
bool gxnox_header_validate(const GxMasterHeaderV3 *hdr) {
    if (!hdr) return false;
    if (hdr->magic != (uint32_t)GXNOX_MAGIC) return false;
    if (hdr->version != GXNOX_VERSION) return false;
    if (hdr->authority_signature != (uint32_t)GXNOX_AUTHORITY_JMM) return false;
    return true;
}
