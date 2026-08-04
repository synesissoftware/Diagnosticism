
/** @file diagnosticism/tracing.h
 * @brief Call-site trace macro.
 *
 * @see @ref tracing_page "Tracing overview"
 *
 * @defgroup diagnosticism_tracing Tracing
 * @{
 */

#ifndef DIAGNOSTICISM_INCL_DIAGNOSTICISM_H_TRACING
#define DIAGNOSTICISM_INCL_DIAGNOSTICISM_H_TRACING


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <diagnosticism/diagnosticism.h>

#include <stdio.h>


/** Low-level implementation used by the diagnosticism_trace() macro.
 *
 * Writes a trace line to @a stm in the form `file:line:function(message)`.
 *
 * @param stm Output stream (for example @c stderr).
 * @param file Source file name (typically @c __FILE__).
 * @param line Source line number (typically @c __LINE__).
 * @param function Current function name.
 * @param args_fmt `printf`-style format string for the message portion.
 *
 * @return Non-negative value on success, or negative on failure.
 *
 * @see diagnosticism_trace()
 */
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

/** @def diagnosticism_trace(stm, ...)
 * @brief Writes a trace line to @a stm at the call site.
 *
 * Automatically supplies @c __FILE__, @c __LINE__, and the current function
 * name together with a `printf`-style formatted message.
 *
 * @param stm Output stream (for example @c stderr).
 * @param ... Format string and arguments for the message portion.
 *
 * @see @ref tracing_page "Tracing overview"
 * @see diagnosticism_trace_impl()
 *
 * @snippet tracing/main.c tracing_call
 */
#define diagnosticism_trace(stm, ...)                       \
                                                            \
    diagnosticism_trace_impl(                               \
        (stm)                                               \
    ,   __FILE__                                            \
    ,   __LINE__                                            \
    ,   DIAGNOSTICISM_FUNCTION_                             \
    ,   __VA_ARGS__                                         \
    )


/** @} */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !DIAGNOSTICISM_INCL_DIAGNOSTICISM_H_TRACING */

/* ///////////////////////////// end of file //////////////////////////// */
