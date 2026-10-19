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

#ifndef DUAL_PARITY_H
#define DUAL_PARITY_H

#include "gxnox_core.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NEUROCOBOL_MASK_KEY      0xA5C3F05AULL
#define NEUROCOBOL_SHIFT_PLUS1   1

/* Encode Clean Even Sector (2k) into Backward-Inverted Mirror (+1) for Odd Sector (2k+1) */
void gxnox_encode_impar_mirror(const uint8_t *par_block, uint8_t *impar_block, size_t block_size);

/* Decode Clean Even Sector from Odd Sector Mirror */
void gxnox_decode_impar_mirror(const uint8_t *impar_block, uint8_t *restored_par_block, size_t block_size);

/* Active Self-Healing Engine: Validates Parity; if corrupted, rebuilds from Odd mirror and verifies CRC */
bool gxnox_self_heal_sector(const uint8_t *impar_block, uint8_t *repaired_par_block, size_t block_size, uint32_t expected_crc);

#if defined(_WIN32)
/* Atomic Block Write and Read on Windows Systems */
bool gxnox_write_shielded_block(HANDLE hFile, uint64_t lba_par_offset, const uint8_t *clean_data, size_t block_size, uint32_t *out_crc);
bool gxnox_read_shielded_block(HANDLE hFile, uint64_t lba_par_offset, uint8_t *dest_buffer, size_t block_size, uint32_t expected_crc, bool *was_repaired);
#endif

#ifdef __cplusplus
}
#endif

#endif /* DUAL_PARITY_H */
