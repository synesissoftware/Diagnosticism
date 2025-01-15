
#include <diagnosticism/abort.h>

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>


DIAGNOSTICISM_CALL_NORETURN
diagnosticism_abort(
    FILE*       stm
,   char const* program_name
,   char const* msg
)
{
    assert(NULL != program_name);

    if (NULL == msg || '\0' == msg[0])
    {
        msg = "abort invoked";
    }

    (void)fprintf(stm, "%s: %s\n", program_name, msg);

    abort();
}

DIAGNOSTICISM_CALL_NORETURN
diagnosticism_abortf(
    FILE*       stm
,   char const* program_name
,   char const* fmt
,   ...
)
{
    const size_t BUF_SIZE   =    1024;

    int n;
    char stub[1]; /* used solely to supply memory for any impl that does not ignore buff when bufsz is 0 */

    va_list args;
    va_start(args, fmt);

    n = snprintf(&stub[0], 0, "%s: %s\n", program_name, fmt);

    if (n < 0 || n >= (int)BUF_SIZE)
    {
        (void)fprintf(stm, "%s: `diagnosticism_abortf()` ARGUMENT LIST TOO LONG\n", program_name);

        va_end(args);
    }
    else
    {
        char combined_fmt[BUF_SIZE];

        n = snprintf(&combined_fmt[0], sizeof(combined_fmt) / sizeof(combined_fmt[0]), "%s: %s\n", program_name, fmt);

        assert(n > 0 && n < (int)BUF_SIZE);

        (void)vfprintf(stm, combined_fmt, args);

        va_end(args);
    }

    abort();
}

