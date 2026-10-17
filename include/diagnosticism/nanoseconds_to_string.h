
/** @file diagnosticism/nanoseconds_to_string.h
 * @brief Compact nanosecond duration formatting (C API).
 *
 * @defgroup diagnosticism_nanoseconds_to_string Nanosecond duration strings
 * @{
 */


#ifndef DIAGNOSTICISM_INCL_DIAGNOSTICISM_H_NANOSECONDS_TO_STRING
#define DIAGNOSTICISM_INCL_DIAGNOSTICISM_H_NANOSECONDS_TO_STRING


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <diagnosticism/diagnosticism.h>

#include <stddef.h>
#include <stdint.h>


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

/** Minimum buffer capacity (including the terminating NUL character) that
 * is always sufficient for `diagnosticism_nanoseconds_to_string()`.
 *
 * Covers signs, up to ~10 whole digits, a fractional part, and a UTF-8
 * microsecond suffix (`µs`).
 */
#define DIAGNOSTICISM_NS_TO_STRING_MIN_CCH                  (32u)

/** No special formatting flags. */
#define DIAGNOSTICISM_NS_TO_STRING_F_NONE                   (0u)

/** Request an explicit leading `+` on positive (non-zero) durations. */
#define DIAGNOSTICISM_NS_TO_STRING_F_PLUS                   (1u << 0)

/** Emit the microsecond unit as ASCII `"us"` instead of UTF-8 `"µs"`. */
#define DIAGNOSTICISM_NS_TO_STRING_F_ASCII_ONLY             (1u << 1)


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

/** Formats a nanosecond count as a compact human-readable duration string.
 *
 * The output adapts the unit (`ns`, `µs`, `ms`, `s`) and decimal precision
 * to keep roughly three significant digits in the numeric portion. Units
 * stop at seconds — large magnitudes remain integer seconds (e.g.
 * `3000s`). By default the microsecond unit uses the UTF-8 MICRO SIGN
 * U+00B5 (`µ`); pass `DIAGNOSTICISM_NS_TO_STRING_F_ASCII_ONLY` for `"us"`.
 *
 * Default (non-ASCII-only) behaviour matches Diagnosticism.Python /
 * Diagnosticism.Rust `nanoseconds_to_string()`.
 *
 * @param cchBuffer Size of @a buffer in characters (including room for the
 *   terminating NUL character). Pass `0` to probe for the required capacity
 *   without writing (and without setting `errno`);
 * @param buffer Character buffer into which to write the UTF-8 result, or
 *   unused when @a cchBuffer is `0`;
 * @param nanoseconds The duration, in nanoseconds;
 * @param flags `DIAGNOSTICISM_NS_TO_STRING_F_*` flags;
 *   `DIAGNOSTICISM_NS_TO_STRING_F_PLUS` and
 *   `DIAGNOSTICISM_NS_TO_STRING_F_ASCII_ONLY` are recognised;
 * @param pnWritten On success, receives the number of characters written
 *   (excluding the terminating NUL). When @a cchBuffer is `0` (size probe)
 *   or otherwise too small, receives the required capacity including the
 *   terminating NUL (so a retry can size the buffer). May be NULL;
 *
 * @return 0 on success, or -1 when the result does not fit (including the
 *   size-probe case `@a cchBuffer == 0`).
 *
 * @pre 0 == cchBuffer || NULL != buffer
 *
 * @note Zero is always `"0s"` with no sign, even when
 *   `DIAGNOSTICISM_NS_TO_STRING_F_PLUS` is set.
 *
 * @note When @a cchBuffer is `0`, this is a size probe: `*pnWritten` (if
 *   non-NULL) receives the required capacity and `errno` is not written.
 *   When @a cchBuffer is non-zero but too small, `errno` is set to
 *   `ERANGE`. Callers that always pass at least
 *   `DIAGNOSTICISM_NS_TO_STRING_MIN_CCH` need not handle either path.
 *
 * @see DIAGNOSTICISM_NS_TO_STRING_MIN_CCH
 */
DIAGNOSTICISM_CALL(int)
diagnosticism_nanoseconds_to_string(
    size_t      cchBuffer
,   char        buffer[/*cchBuffer*/]
,   int64_t     nanoseconds
,   uint32_t    flags
,   size_t*     pnWritten
);


/** @} */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !DIAGNOSTICISM_INCL_DIAGNOSTICISM_H_NANOSECONDS_TO_STRING */

/* ///////////////////////////// end of file //////////////////////////// */

