/* /////////////////////////////////////////////////////////////////////////
 * File:    diagnosticm/diagnosticm.h
 *
 * Purpose: Main header file for Diagnosticm (C-API).
 *
 * Created: 23rd November 2024
 * Updated: 23rd August 2025
 *
 * Home:    https://github.com/synesissoftware/Diagnosticism/
 *
 * Copyright (c) 2024-2025, Matthew Wilson and Synesis Information Systems
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
 *   ontributors may be used to endorse or promote products derived from
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


/** \file diagnosticm/diagnosticm.h
 *
 * [C, C++] Main header file for Diagnosticm (C-API).
 */

#ifndef DIAGNOSTICISM_INCL_DIAGNOSTICISM_H_DIAGNOSTICISM
#define DIAGNOSTICISM_INCL_DIAGNOSTICISM_H_DIAGNOSTICISM

#ifndef DIAGNOSTICISM_DOCUMENTATION_SKIP_SECTION
# define DIAGNOSTICISM_VER_DIAGNOSTICISM_H_DIAGNOSTICISM_MAJOR  0
# define DIAGNOSTICISM_VER_DIAGNOSTICISM_H_DIAGNOSTICISM_MINOR  0
# define DIAGNOSTICISM_VER_DIAGNOSTICISM_H_DIAGNOSTICISM_PATCH  9
# define DIAGNOSTICISM_VER_DIAGNOSTICISM_H_DIAGNOSTICISM_EDIT   10
#endif /* !DIAGNOSTICISM_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * version information
 */

/**
 * \def DIAGNOSTICISM_VER_MAJOR
 *
 * The Major version number of the DIAGNOSTICISM library
 *
 * \def DIAGNOSTICISM_VER_MINOR
 *
 * Minor version number of the DIAGNOSTICISM library
 *
 * \def DIAGNOSTICISM_VER_PATCH
 *
 * The patch number of the DIAGNOSTICISM library
 *
 * \def DIAGNOSTICISM_VER
 *
 * The composite version of the DIAGNOSTICISM library
 */

#define DIAGNOSTICISM_VER_MAJOR         0
#define DIAGNOSTICISM_VER_MINOR         2
#define DIAGNOSTICISM_VER_PATCH         0
#define DIAGNOSTICISM_VER_ALPHABETA     0x84

#define DIAGNOSTICISM_VER \
    (0\
        |   (   DIAGNOSTICISM_VER_MAJOR       << 24   ) \
        |   (   DIAGNOSTICISM_VER_MINOR       << 16   ) \
        |   (   DIAGNOSTICISM_VER_PATCH       <<  8   ) \
        |   (   DIAGNOSTICISM_VER_ALPHABETA   <<  0   ) \
    )


/* /////////////////////////////////////////////////////////////////////////
 * includes - 1
 */

#include <stdint.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * macros
 */

/** \def DIAGNOSTICISM_CALL(rt)
 *
 * \param rt The return type.
 */
#ifndef DIAGNOSTICISM_CALL
# ifdef __cplusplus
#  define DIAGNOSTICISM_CALL(rt)                            extern "C" rt
# else
#  define DIAGNOSTICISM_CALL(rt)                            rt
# endif
#endif


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

typedef uint32_t                                            diag_uint32_t;



/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

/** Obtains the Diagnosticism version (at time of compilation).
 *
 * @note Can be called without having initialised the API.
 *
 * @see diagnosticism_api_init.
 */
DIAGNOSTICISM_CALL(diag_uint32_t)
diagnosticism_api_version(void);



/** Initialises the Diagnosticism API.
 *
 */
DIAGNOSTICISM_CALL(int)
diagnosticism_api_init(
    diag_uint32_t   init_flags
,   void*           init_param
);

/** Uninitialises the Diagnosticism API.
 *
 */
DIAGNOSTICISM_CALL(void)
diagnosticism_api_uninit(void);


/* /////////////////////////////////////////////////////////////////////////
 * API functions (C++)
 */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !DIAGNOSTICISM_INCL_DIAGNOSTICISM_H_DIAGNOSTICISM */

/* ///////////////////////////// end of file //////////////////////////// */

