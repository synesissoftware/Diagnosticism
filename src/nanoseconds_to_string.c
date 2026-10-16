/* /////////////////////////////////////////////////////////////////////////
 * File:    diagnosticism/nanoseconds_to_string.c
 *
 * Purpose: Compact nanosecond duration formatting.
 *
 * Created: 16th October 2026
 * Updated: 16th October 2026
 *
 * Home:    https://github.com/synesissoftware/Diagnosticism/
 *
 * Copyright (c) 2026, Matthew Wilson and Synesis Information Systems
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer;
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution;
 * - Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <diagnosticism/nanoseconds_to_string.h>

#include <assert.h>
#include <errno.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

static uint64_t const s_scales[12] =
{
    1ull,
    10ull,
    100ull,
    1000ull,
    10000ull,
    100000ull,
    1000000ull,
    10000000ull,
    100000000ull,
    1000000000ull,
    10000000000ull,
    100000000000ull,
};

/* UTF-8 MICRO SIGN U+00B5 (C2 B5) + 's' — default microsecond suffix. */
static char const s_suffix_us_utf8[] =
{
        (char)0xC2
    ,   (char)0xB5
    ,   's'
    ,   '\0'
};

static char const* const s_suffixes_ascii[4] =
{
        "ns"
    ,   "us"
    ,   "ms"
    ,   "s"
};

static char const* const s_suffixes_utf8[4] =
{
        "ns"
    ,   s_suffix_us_utf8
    ,   "ms"
    ,   "s"
};


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

static
size_t
diag_ns_write_u64_(
    char*       buf
,   uint64_t    n
,   size_t      pos
)
{
    if (0 == n)
    {
        buf[pos] = '0';

        return pos + 1;
    }
    else
    {
        size_t const    start   =   pos;
        size_t          i;
        size_t          j;
        char            t;

        while (0 != n)
        {
            buf[pos++] = (char)('0' + (unsigned)(n % 10));
            n /= 10;
        }

        /* reverse digits written into [start, pos) */
        for (i = start, j = pos; i < j; ++i)
        {
            --j;
            t = buf[i];
            buf[i] = buf[j];
            buf[j] = t;
        }

        return pos;
    }
}

static
size_t
diag_ns_write_frac_min_width_2_(
    char*       buf
,   size_t      pos
,   uint64_t    frac
)
{
    assert(frac < 100);

    if (frac >= 10)
    {
        return diag_ns_write_u64_(buf, frac, pos);
    }
    else
    {
        buf[pos] = '0';
        buf[pos + 1] = (char)('0' + (unsigned)frac);

        return pos + 2;
    }
}

static
size_t
diag_ns_write_bytes_(
    char*           buf
,   size_t          pos
,   char const*     bytes
,   size_t          len
)
{
    memcpy(&buf[pos], bytes, len);

    return pos + len;
}

static
void
diag_ns_scale_index_(
    uint64_t    n
,   size_t*     oom
,   uint64_t*   divisor
)
{
    size_t i;

    assert(n > 0);
    assert(NULL != oom);
    assert(NULL != divisor);

    if (n >= 100000000000ull)
    {
        *oom = 11;
        *divisor = s_scales[11];

        return;
    }

    /* floor(log10(n)), matching Rust `ilog10` / Python `_scale_index`. */
    i = 0;

    while (n >= 10)
    {
        n /= 10;
        ++i;
    }

    *oom = i;
    *divisor = s_scales[i];
}

static
size_t
diag_ns_format_parts_(
    char*           buf
,   char            sign_byte
,   uint64_t        whole
,   uint64_t        frac
,   char const*     suffix
)
{
    size_t      pos = 0;
    size_t      suffix_len;

    if ('\0' != sign_byte)
    {
        buf[pos++] = sign_byte;
    }

    pos = diag_ns_write_u64_(buf, whole, pos);

    if (0 != frac && whole <= 999)
    {
        buf[pos++] = '.';

        if (whole > 99)
        {
            pos = diag_ns_write_u64_(buf, frac, pos);
        }
        else if (whole > 9)
        {
            pos = diag_ns_write_frac_min_width_2_(buf, pos, frac);
        }
        else
        {
            pos = diag_ns_write_u64_(buf, frac, pos);
        }
    }

    suffix_len = strlen(suffix);
    pos = diag_ns_write_bytes_(buf, pos, suffix, suffix_len);

    return pos;
}


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

DIAGNOSTICISM_CALL(int)
diagnosticism_nanoseconds_to_string(
    size_t      cchBuffer
,   char        buffer[/*cchBuffer*/]
,   int64_t     nanoseconds
,   uint32_t    flags
,   size_t*     pnWritten
)
{
    char        local[DIAGNOSTICISM_NS_TO_STRING_MIN_CCH];
    size_t      n;
    size_t      dummy;
    char        sign_byte;
    uint64_t    v;
    size_t      oom;
    uint64_t    divisor;
    char const* suffix;
    uint64_t    divisor_0;
    size_t      i;
    uint64_t    divisor_1;
    uint64_t    whole;
    uint64_t    frac;

    assert(0 == cchBuffer || NULL != buffer);

    if (NULL == pnWritten)
    {
        pnWritten = &dummy;
    }

    /* Zero is always "0s" with no sign (even if PLUS is requested). */
    if (0 == nanoseconds)
    {
        n = diag_ns_write_bytes_(local, 0, "0s", 2);
    }
    else
    {
        if (nanoseconds < 0)
        {
            sign_byte = '-';

            if (INT64_MIN == nanoseconds)
            {
                v = (uint64_t)INT64_MAX + 1ull;
            }
            else
            {
                v = (uint64_t)(-nanoseconds);
            }
        }
        else
        {
            if (0 != (flags & DIAGNOSTICISM_NS_TO_STRING_F_PLUS))
            {
                sign_byte = '+';
            }
            else
            {
                sign_byte = '\0';
            }

            v = (uint64_t)nanoseconds;
        }

        diag_ns_scale_index_(v, &oom, &divisor);

        /* ASCII_ONLY selects the all-ASCII table ("us"); else UTF-8 ("µs"). */
        if (0 != (flags & DIAGNOSTICISM_NS_TO_STRING_F_ASCII_ONLY))
        {
            suffix = s_suffixes_ascii[oom / 3];
        }
        else
        {
            suffix = s_suffixes_utf8[oom / 3];
        }

        if (oom < 3)
        {
            n = diag_ns_format_parts_(local, sign_byte, v, 0, suffix);
        }
        else
        {
            divisor_0 = divisor / 1000ull;
            i = oom % 3;

            if (0 == i)
            {
                divisor_1 = 1000ull;
            }
            else if (1 == i)
            {
                divisor_1 = 100ull;
            }
            else
            {
                divisor_1 = 10ull;
            }

            v /= divisor_0;

            whole = v / divisor_1;
            frac = v - (whole * divisor_1);

            n = diag_ns_format_parts_(local, sign_byte, whole, frac, suffix);
        }
    }

    /* Need room for the n payload characters plus a terminating NUL. */
    if (cchBuffer < n + 1)
    {
        /* On undersize (including the cchBuffer==0 size probe), *pnWritten
         * is the required capacity (including NUL), not a count of
         * characters written — nothing was copied to buffer.
         */
        *pnWritten = n + 1;

        /* Size probe: cchBuffer==0 reports the required capacity without
         * treating the call as a write failure, so errno is left alone.
         * A non-zero but too-small buffer is a real range failure → ERANGE
         * (EINVAL would imply a bad argument).
         */
        if (0 != cchBuffer)
        {
            errno = ERANGE;
        }

        return -1;
    }

    memcpy(buffer, local, n);
    buffer[n] = '\0';
    *pnWritten = n;

    return 0;
}

/* ///////////////////////////// end of file //////////////////////////// */

