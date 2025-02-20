
#include <diagnosticism/diagnosticism.h>

#include <stdio.h>


DIAGNOSTICISM_CALL(int)
diagnosticism_trace_impl(
    FILE*       stm
,   char const* file
,   int         line
,   char const* function
,   char const* args_fmt
,   ...
);

#if 0
#elif defined(__GNUC__)

# define DIAGNOSTICISM_FUNCTION_                            __func__
#else

# define DIAGNOSTICISM_FUNCTION_                            __FUNCTION__
#endif

#define diagnosticism_trace(stm, ...)                       \
                                                            \
    diagnosticism_trace_impl(                               \
        (stm)                                               \
    ,   __FILE__                                            \
    ,   __LINE__                                            \
    , DIAGNOSTICISM_FUNCTION_                               \
    ,   __VA_ARGS__                                         \
    )


#pragma once


/* ///////////////////////////// end of file //////////////////////////// */

