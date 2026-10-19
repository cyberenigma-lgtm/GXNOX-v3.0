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

#include "dual_parity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Encode Clean Even Sector (2k) into Backward-Inverted Mirror (+1) for Odd Sector (2k+1)
 * Formula: Impar[i] = Par[N - 1 - i] ^ (KeyByte + 1)
 */
void gxnox_encode_impar_mirror(const uint8_t *par_block, uint8_t *impar_block, size_t block_size) {
    uint8_t key_byte = (uint8_t)(NEUROCOBOL_MASK_KEY & 0xFF);
    uint8_t dynamic_salt = key_byte + NEUROCOBOL_SHIFT_PLUS1;

    for (size_t i = 0; i < block_size; i++) {
        impar_block[i] = par_block[block_size - 1 - i] ^ dynamic_salt;
    }
}

/*
 * Decode Clean Even Sector from Odd Sector Mirror
 * Formula: Restored[j] = Impar[N - 1 - j] ^ (KeyByte + 1)
 */
void gxnox_decode_impar_mirror(const uint8_t *impar_block, uint8_t *restored_par_block, size_t block_size) {
    uint8_t key_byte = (uint8_t)(NEUROCOBOL_MASK_KEY & 0xFF);
    uint8_t dynamic_salt = key_byte + NEUROCOBOL_SHIFT_PLUS1;

    for (size_t i = 0; i < block_size; i++) {
        restored_par_block[i] = impar_block[block_size - 1 - i] ^ dynamic_salt;
    }
}

/*
 * Active Self-Healing Engine:
 * Rebuilds the damaged Even sector from the Odd mirror and verifies its CRC32 checksum.
 * Returns true if restored block matches the expected golden checksum.
 */
bool gxnox_self_heal_sector(const uint8_t *impar_block, uint8_t *repaired_par_block, size_t block_size, uint32_t expected_crc) {
    gxnox_decode_impar_mirror(impar_block, repaired_par_block, block_size);
    uint32_t actual_crc = gxnox_crc32(repaired_par_block, block_size);
    return (actual_crc == expected_crc);
}

#if defined(_WIN32)

/*
 * Write Dual-Bank Protected Block to Silicon Disk:
 * Writes Even Bank (LBA 2k) and Odd Bank (LBA 2k+1) atomically.
 */
bool gxnox_write_shielded_block(HANDLE hFile, uint64_t lba_par_offset, const uint8_t *clean_data, size_t block_size, uint32_t *out_crc) {
    if (!clean_data || block_size != GXNOX_SECTOR_SIZE) return false;

    uint64_t lba_impar_offset = lba_par_offset + GXNOX_SECTOR_SIZE;

    /* Invariant Check: Delta == 1 sector */
    if (lba_impar_offset != lba_par_offset + GXNOX_SECTOR_SIZE) {
        return false;
    }

    uint32_t clean_crc = gxnox_crc32(clean_data, block_size);
    if (out_crc) *out_crc = clean_crc;

    uint8_t impar_mirror[GXNOX_SECTOR_SIZE];
    gxnox_encode_impar_mirror(clean_data, impar_mirror, GXNOX_SECTOR_SIZE);

    /* Write Even Bank */
    LARGE_INTEGER li;
    li.QuadPart = (LONGLONG)lba_par_offset;
    SetFilePointerEx(hFile, li, NULL, FILE_BEGIN);
    DWORD written = 0;
    if (!WriteFile(hFile, clean_data, (DWORD)block_size, &written, NULL) || written != block_size) {
        return false;
    }

    /* Write Odd Bank */
    li.QuadPart = (LONGLONG)lba_impar_offset;
    SetFilePointerEx(hFile, li, NULL, FILE_BEGIN);
    written = 0;
    if (!WriteFile(hFile, impar_mirror, (DWORD)block_size, &written, NULL) || written != block_size) {
        return false;
    }

    return true;
}

/*
 * Read Protected Block with Autonomous Self-Healing:
 * Reads Even Bank (LBA 2k). If CRC fails, reads Odd Bank (LBA 2k+1),
 * repairs in RAM and re-commits the clean data back to disk.
 */
bool gxnox_read_shielded_block(HANDLE hFile, uint64_t lba_par_offset, uint8_t *dest_buffer, size_t block_size, uint32_t expected_crc, bool *was_repaired) {
    if (!dest_buffer || block_size != GXNOX_SECTOR_SIZE) return false;
    if (was_repaired) *was_repaired = false;

    uint64_t lba_impar_offset = lba_par_offset + GXNOX_SECTOR_SIZE;

    LARGE_INTEGER li;
    li.QuadPart = (LONGLONG)lba_par_offset;
    SetFilePointerEx(hFile, li, NULL, FILE_BEGIN);
    DWORD read_bytes = 0;
    if (!ReadFile(hFile, dest_buffer, (DWORD)block_size, &read_bytes, NULL) || read_bytes != block_size) {
        return false;
    }

    uint32_t current_crc = gxnox_crc32(dest_buffer, block_size);
    if (current_crc == expected_crc) {
        return true;
    }

    /* Corruption detected: trigger self-healing */
    uint8_t impar_mirror[GXNOX_SECTOR_SIZE];
    li.QuadPart = (LONGLONG)lba_impar_offset;
    SetFilePointerEx(hFile, li, NULL, FILE_BEGIN);
    read_bytes = 0;
    if (!ReadFile(hFile, impar_mirror, (DWORD)block_size, &read_bytes, NULL) || read_bytes != block_size) {
        return false;
    }

    uint8_t repaired_data[GXNOX_SECTOR_SIZE];
    if (!gxnox_self_heal_sector(impar_mirror, repaired_data, GXNOX_SECTOR_SIZE, expected_crc)) {
        return false;
    }

    memcpy(dest_buffer, repaired_data, block_size);
    if (was_repaired) *was_repaired = true;

    /* Re-write repaired block back to disk */
    li.QuadPart = (LONGLONG)lba_par_offset;
    SetFilePointerEx(hFile, li, NULL, FILE_BEGIN);
    DWORD written = 0;
    WriteFile(hFile, repaired_data, (DWORD)block_size, &written, NULL);

    return true;
}

#endif
