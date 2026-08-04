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


/** Formats a version number into a caller-supplied buffer (8-bit elements).
 *
 * Each of @a verMajor, @a verMinor, @a verPatch, and @a verAlphaBeta is
 * interpreted strictly as an 8-bit value (the low eight bits of the @c int
 * argument). Formats major, minor, patch, and an optional pre-release
 * component encoded in @a verAlphaBeta:
 *
 * - @c 0x40+ yields @c -alphaN (e.g. @c 0x41 is @c -alpha1)
 * - @c 0x80+ yields @c -betaN (e.g. @c 0x81 is @c -beta1)
 * - @c 0xC0+ yields @c -rcN (e.g. @c 0xC1 is @c -rc1)
 * - @c 0xFF suppresses any suffix (final)
 * - other non-zero values are appended as a fourth dotted component
 *
 * @param buffer Character buffer into which to write the result.
 * @param cchBuffer Size of @a buffer in characters.
 * @param verMajor Major version component (8-bit).
 * @param verMinor Minor version component (8-bit).
 * @param verPatch Patch version component (8-bit).
 * @param verAlphaBeta Alpha/beta/rc/build encoding (see above).
 * @param pnWritten Receives the number of characters written (excluding the
 *  terminating null); may be NULL.
 *
 * @return 0 on success, or -1 on failure (buffer too small or invalid
 *  input).
 *
 * @pre NULL != buffer
 *
 * @see diagnosticism_calc_version_string_16()
 */
DIAGNOSTICISM_CALL(int)
diagnosticism_calc_version_string(
    char        buffer[]    /* cchBuffer */
,   size_t      cchBuffer
,   int         verMajor
,   int         verMinor
,   int         verPatch
,   int         verAlphaBeta
,   size_t*     pnWritten
);

/** Formats a version number into a caller-supplied buffer (16-bit
 * elements).
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
 *
 * @see diagnosticism_calc_version_string()
 */
DIAGNOSTICISM_CALL(int)
diagnosticism_calc_version_string_16(
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

