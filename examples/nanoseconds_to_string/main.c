
#include <diagnosticism/nanoseconds_to_string.h>

#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>


static int
print_ns(
    int64_t     nanoseconds
,   uint32_t    flags
)
{
    char        buffer[DIAGNOSTICISM_NS_TO_STRING_MIN_CCH];
    size_t      n;
    int const   r = diagnosticism_nanoseconds_to_string(
        sizeof(buffer) / sizeof(buffer[0])
    ,   buffer
    ,   nanoseconds
    ,   flags
    ,   &n
    );

    if (0 != r)
    {
        fprintf(stderr, "failed to format duration (errno=%d)\n", errno);

        return EXIT_FAILURE;
    }

    fprintf(
        stderr
    ,   "%" PRId64 " (flags=0x%08x) -> \"%s\" (%zu chars)\n"
    ,   nanoseconds
    ,   (unsigned)flags
    ,   buffer
    ,   n
    );

    return EXIT_SUCCESS;
}


int main(void)
{
    size_t  required;
    int     r;

    if (EXIT_SUCCESS != print_ns(0, DIAGNOSTICISM_NS_TO_STRING_F_NONE))
    {
        return EXIT_FAILURE;
    }

    if (EXIT_SUCCESS != print_ns(123456789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE))
    {
        return EXIT_FAILURE;
    }

    /* Default microsecond unit is UTF-8 "µs". */
    if (EXIT_SUCCESS != print_ns(6789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE))
    {
        return EXIT_FAILURE;
    }

    /* ASCII_ONLY selects the alternative "us". */
    if (EXIT_SUCCESS != print_ns(6789LL, DIAGNOSTICISM_NS_TO_STRING_F_ASCII_ONLY))
    {
        return EXIT_FAILURE;
    }

    if (EXIT_SUCCESS != print_ns(
            999772000LL
        ,   DIAGNOSTICISM_NS_TO_STRING_F_PLUS
        )
    )
    {
        return EXIT_FAILURE;
    }

    /* Size probe: cchBuffer==0 reports required capacity without errno. */
    errno = 0;
    r = diagnosticism_nanoseconds_to_string(
        0
    ,   NULL
    ,   6789LL
    ,   DIAGNOSTICISM_NS_TO_STRING_F_NONE
    ,   &required
    );

    if (-1 != r || 0 == required || 0 != errno)
    {
        fprintf(
            stderr
        ,   "size probe failed (r=%d, required=%zu, errno=%d)\n"
        ,   r
        ,   required
        ,   errno
        );

        return EXIT_FAILURE;
    }

    fprintf(
        stderr
    ,   "size probe for 6789ns -> required capacity %zu (errno untouched)\n"
    ,   required
    );

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */
