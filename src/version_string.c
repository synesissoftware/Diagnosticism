
#include <diagnosticism/version_string.h>

#include <assert.h>
#include <errno.h>
#include <stdio.h>


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

static
int
diagnosticism_calc_version_string_(
    char        buffer[]    /* cchBuffer */
,   size_t      cchBuffer
,   uint16_t    verMajor
,   uint16_t    verMinor
,   uint16_t    verPatch
,   uint16_t    verAlphaBeta
)
{
    if (0xFFFF == verAlphaBeta)
    {
        goto major_minor_patch;
    }

    if (0 != verMajor ||
        0 != verMinor)
    {
        if (verAlphaBeta >= 0xC000)
        {
            return snprintf(&buffer[0], cchBuffer, "%u.%u.%u-rc%u", verMajor, verMinor, verPatch, verAlphaBeta - 0xC000);
        }

        if (verAlphaBeta >= 0x8000)
        {
            return snprintf(&buffer[0], cchBuffer, "%u.%u.%u-beta%u", verMajor, verMinor, verPatch, verAlphaBeta - 0x8000);
        }

        if (verAlphaBeta >= 0x4000)
        {
            return snprintf(&buffer[0], cchBuffer, "%u.%u.%u-alpha%u", verMajor, verMinor, verPatch, verAlphaBeta - 0x4000);
        }
    }

    if (0 != verAlphaBeta)
    {
        return snprintf(&buffer[0], cchBuffer, "%u.%u.%u.%u", verMajor, verMinor, verPatch, verAlphaBeta);
    }
    else
    {
major_minor_patch:

        return snprintf(&buffer[0], cchBuffer, "%u.%u.%u", verMajor, verMinor, verPatch);
    }
}


/* /////////////////////////////////////////////////////////////////////////
 * API functions
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
)
{
    size_t dummy;

    assert(NULL != buffer);

    if (NULL == pnWritten)
    {
        pnWritten = &dummy;
    }

    {
        int const r = diagnosticism_calc_version_string_(&buffer[0], cchBuffer, verMajor, verMinor, verPatch, verAlphaBeta);

        if (r < 0)
        {
            errno = EINVAL;

            return -1;
        }
        else
        {
            size_t const n = (size_t)r;

            if (cchBuffer < n + 1)
            {
                *pnWritten = n + 1;

                return -1;
            }
            else
            {
                *pnWritten = n;

                return 0;
            }
        }
    }
}


/* ///////////////////////////// end of file //////////////////////////// */

