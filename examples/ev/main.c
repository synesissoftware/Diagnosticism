
#include <diagnosticism/ev.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


#if defined(_WIN32)

# include <stdlib.h>

# define EXAMPLE_SET_ENV(name, value)     _putenv_s((name), (value))

#else

# include <stdlib.h>

# define EXAMPLE_SET_ENV(name, value)     setenv((name), (value), 1)

#endif


static void
report_getenv(
    char const* name
,   char const* defaultValueOrNull
)
{
    errno = 0;

    char const* const   v = diagnosticism_getenv(name, defaultValueOrNull);
    int const           e = errno;

    fprintf(
        stderr
    ,   "getenv(\"%s\", %s) -> \"%s\" (errno=%d)\n"
    ,   name
    ,   defaultValueOrNull ? defaultValueOrNull : "NULL"
    ,   v ? v : ""
    ,   e
    );
}


static void
report_getenv_atoi(
    char const* name
,   int         defaultValue
)
{
    errno = 0;

    int const   v = diagnosticism_getenv_atoi(name, defaultValue);
    int const   e = errno;

    fprintf(
        stderr
    ,   "getenv_atoi(\"%s\", %d) -> %d (errno=%d)\n"
    ,   name
    ,   defaultValue
    ,   v
    ,   e
    );
}


int main(void)
{
    EXAMPLE_SET_ENV("DIAGNOSTICISM_EXAMPLE_NAME", "Diagnosticism");
    EXAMPLE_SET_ENV("DIAGNOSTICISM_EXAMPLE_PORT", "8080");
    EXAMPLE_SET_ENV("DIAGNOSTICISM_EXAMPLE_BADINT", "not-a-number");

    errno = 0;

    report_getenv("DIAGNOSTICISM_EXAMPLE_NAME", NULL);
    report_getenv("DIAGNOSTICISM_EXAMPLE_MISSING", "default-value");

    report_getenv_atoi("DIAGNOSTICISM_EXAMPLE_PORT", 0);
    report_getenv_atoi("DIAGNOSTICISM_EXAMPLE_MISSING", 42);
    report_getenv_atoi("DIAGNOSTICISM_EXAMPLE_BADINT", 99);

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

