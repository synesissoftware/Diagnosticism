
#include <diagnosticism/diagnosticism.h>


/* /////////////////////////////////////////////////////////////////////////
 * API types
 */



/* /////////////////////////////////////////////////////////////////////////
 * API functions & macros
 */

/** Obtains from the environment the value of the environment variable
 * mathcing @c name
 *
 * @param name The name of the environment variable to be ;
 * @param defaultValueOrNull An optional default value to be used ;
 *
 * @return Pointer to the value of the named environment variable, or
 *  @c defaultValueOrNull if
 */
DIAGNOSTICISM_CALL(char const*)
diagnosticism_getenv(
    char const*             name
,   char const*             defaultValueOrNull
);

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

