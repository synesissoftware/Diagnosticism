
#include <diagnosticism/diagnosticism.h>

#include <stdio.h>


/**
 *
 * @param stm The stream on which to emit. May not be NULL;
 * @param program_name The name of the program. May not be NULL or empty
 *   string;
 * @param msg An optional message. If NULL or empty, then a default message
 *   will be applied;
 */
DIAGNOSTICISM_CALL_NORETURN
diagnosticism_abort(
    FILE*       stm
,   char const* program_name
,   char const* msg
);

DIAGNOSTICISM_CALL_NORETURN
diagnosticism_abortf(
    FILE*       stm
,   char const* program_name
,   char const* fmt
,   ...
);


#pragma once
