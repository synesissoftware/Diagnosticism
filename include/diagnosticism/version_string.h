
#include <diagnosticism/diagnosticism.h>

#include <stddef.h>
#include <stdint.h>


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


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#pragma once

/* ///////////////////////////// end of file //////////////////////////// */

