
/** @file diagnosticism/ev.h
 * @brief Environment-variable helpers.
 *
 * @defgroup diagnosticism_ev Environment variables
 * @{
 */

#ifndef DIAGNOSTICISM_INCL_DIAGNOSTICISM_H_EV
#define DIAGNOSTICISM_INCL_DIAGNOSTICISM_H_EV


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <diagnosticism/diagnosticism.h>


/* /////////////////////////////////////////////////////////////////////////
 * API types
 */



/* /////////////////////////////////////////////////////////////////////////
 * API functions & macros
 */

/** Obtains from the environment the value of the environment variable
 * matching @c name.
 *
 * @param name The name of the environment variable to be obtained.
 * @param defaultValueOrNull An optional default value to be used in the
 *  case that no such environment variable exists.
 *
 * @return Pointer to the value of the named environment variable, or
 *  @c defaultValueOrNull if no such environment variable exists (in which
 *  case @c errno is set to @c ENOENT).
 */
DIAGNOSTICISM_CALL(char const*)
diagnosticism_getenv(
    char const*             name
,   char const*             defaultValueOrNull
);

/** Obtains from the environment the value of the environment variable
 * matching @c name, and interpreting it as an integer.
 *
 * @param name The name of the environment variable to be obtained.
 * @param defaultValue An optional default value to be used in the case that
 *  no such environment variable exists.
 *
 * @return Integer value of the named environment variable, or
 *  @c defaultValue if no such environment variable exists (in which case
 *  @c errno is set to @c ENOENT); returns 0 when the value cannot be
 *  interpreted as an integer.
 */
DIAGNOSTICISM_CALL(int)
diagnosticism_getenv_atoi(
    char const*             name
,   int                     defaultValue
);


/** @} */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !DIAGNOSTICISM_INCL_DIAGNOSTICISM_H_EV */

/* ///////////////////////////// end of file //////////////////////////// */

