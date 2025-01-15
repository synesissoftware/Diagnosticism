
#include <diagnosticism/tracing.h>

#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>


int
diagnosticism_trace_impl(
    FILE*       stm
,   char const* file
,   int         line
,   char const* function
,   char const* args_fmt
,   ...
)
{
    const size_t BUF_SIZE   =    1024;

    int n;
    int r;
    char stub[1]; /* used solely to supply memory for any impl that does not ignore buff when bufsz is 0 */

    va_list args;
    va_start(args, args_fmt);

    /* TODO: use STLSoft's auto_buffer.h or similar to have a dynamically sized format on stack where possible */

    n = snprintf(&stub[0], 0, "%s:%d:%s(%s)\n", file, line, function, args_fmt);

    if (n < 0 || n >= (int)BUF_SIZE)
    {
        va_end(args);

        return -1;
    }
    else
    {
        char combined_fmt[BUF_SIZE];

        n = snprintf(&combined_fmt[0], sizeof(combined_fmt) / sizeof(combined_fmt[0]), "%s:%d:%s(%s)\n", file, line, function, args_fmt);

        assert(n > 0 && n < (int)BUF_SIZE);

        r = vfprintf(stm, combined_fmt, args);

        va_end(args);

        return r;
    }
}


