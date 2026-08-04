
/** @file diagnosticism/version_string.h
 * @brief Version-string formatting (C API).
 *
 * @defgroup diagnosticism_version Version strings
 * @{
 */

#ifndef DIAGNOSTICISM_INCL_DIAGNOSTICISM_H_VERSION_STRING
#define DIAGNOSTICISM_INCL_DIAGNOSTICISM_H_VERSION_STRING


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <diagnosticism/diagnosticism.h>

#include <stddef.h>
#include <stdint.h>


/** Formats a version number into a caller-supplied buffer.
 *
 * Formats @a verMajor, @a verMinor, @a verPatch, and an optional
 * pre-release component encoded in @a verAlphaBeta:
 *
 * - @c 0x4000+ yields @c -alphaN
 * - @c 0x8000+ yields @c -betaN
 * - @c 0xC000+ yields @c -rcN
 * - @c 0xFFFF suppresses any suffix
 * - other non-zero values are appended as a fourth dotted component
 *
 * @param buffer Character buffer into which to write the result.
 * @param cchBuffer Size of @a buffer in characters.
 * @param verMajor Major version component.
 * @param verMinor Minor version component.
 * @param verPatch Patch version component.
 * @param verAlphaBeta Alpha/beta/rc/build encoding (see above).
 * @param pnWritten Receives the number of characters written (excluding the
 *  terminating null); may be NULL.
 *
 * @return 0 on success, or -1 on failure (buffer too small or invalid
 *  input).
 *
 * @pre NULL != buffer
 */
DIAGNOSTICISM_CALL(int)
diagnosticism_calc_version_string(
    char        buffer[]    /* cchBuffer */
,   size_t      cchBuffer
,   uint16_t    verMajor
,   uint16_t    verMinor
,   uint16_t    verPatch
,   uint16_t    verAlphaBeta
,   size_t*     pnWritten
);


/** @} */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !DIAGNOSTICISM_INCL_DIAGNOSTICISM_H_VERSION_STRING */

/* ///////////////////////////// end of file //////////////////////////// */
