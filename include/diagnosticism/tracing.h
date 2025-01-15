

#include <stdio.h>

int
diagnosticism_trace_impl(
    FILE*       stm
,   char const* file
,   int         line
,   char const* function
,   char const* args_fmt
,   ...
);

#define diagnosticism_trace(stm, ...)                       \
                                                            \
    diagnosticism_trace_impl(                               \
        (stm)                                               \
    ,   __FILE__                                            \
    ,   __LINE__                                            \
    ,   __FUNCTION__                                        \
    ,   __VA_ARGS__                                         \
    )


#pragma once
