
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
 * @param name The name of the environment variable to be obtained;
 * @param defaultValueOrNull An optional default value to be used in the
 *  case that no such environment variable exists;
 *
 * @return Pointer to the value of the named environment variable, or
 *  @c defaultValueOrNull if no such environment variable exists.
 */
DIAGNOSTICISM_CALL(char const*)
diagnosticism_getenv(
    char const*             name
,   char const*             defaultValueOrNull
);

/** Obtains from the environment the value of the environment variable
 * matching @c name, and interpreting it as an integer.
 *
 * @param name The name of the environment variable to be obtained;
 * @param defaultValue An optional default value to be used in the case that
 *  no such environment variable exists;
 *
 * @return Integer value of the named environment variable, or 0 if the
 *  value cannot be interpreted as an integer, or @c defaultValue if no such
 *  environment variable exists (in which case @c errno is set
 *  to @c ENOENTY).
 */
DIAGNOSTICISM_CALL(int)
diagnosticism_getenv_atoi(
    char const*             name
,   int                     defaultValue
);


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#pragma once

/* ///////////////////////////// end of file //////////////////////////// */

