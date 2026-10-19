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

#ifndef NEUROCOBOL_RULES_H
#define NEUROCOBOL_RULES_H

#include "gxnox_core.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Deterministic Invariant Verifier */
bool neurocobol_verify_spatial_delta(uint64_t lba_par, uint64_t lba_impar);

/* Pre-Commit Block Parity Verifier */
bool neurocobol_verify_block_invariants(const uint8_t *par_block, const uint8_t *impar_block, size_t block_size);

#ifdef __cplusplus
}
#endif

#endif /* NEUROCOBOL_RULES_H */
