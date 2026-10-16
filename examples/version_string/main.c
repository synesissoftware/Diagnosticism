
#include <diagnosticism/version_string.h>

#include <stdio.h>
#include <stdlib.h>


static int
print_version_string(
    int verMajor
,   int verMinor
,   int verPatch
,   int verAlphaBeta
)
{
    char        buffer[101];
    size_t      n;
    int const   r = diagnosticism_calc_version_string(
        buffer, sizeof(buffer) / sizeof(buffer[0])
    ,   verMajor, verMinor, verPatch, verAlphaBeta
    ,   &n
    );

    if (0 != r)
    {
        fprintf(stderr, "failed to format version string\n");
        return EXIT_FAILURE;
    }

    buffer[n] = '\0';

    fprintf(
        stderr
    ,   "%d.%d.%d (0x%02x) -> \"%s\"\n"
    ,   verMajor
    ,   verMinor
    ,   verPatch
    ,   verAlphaBeta & 0xFF
    ,   buffer
    );

    return EXIT_SUCCESS;
}


int main(void)
{
    if (EXIT_SUCCESS != print_version_string(1, 2, 3, 0))
    {
        return EXIT_FAILURE;
    }

    if (EXIT_SUCCESS != print_version_string(1, 2, 3, 0x42))
    {
        return EXIT_FAILURE;
    }

    if (EXIT_SUCCESS != print_version_string(1, 2, 3, 0x83))
    {
        return EXIT_FAILURE;
    }

    if (EXIT_SUCCESS != print_version_string(1, 2, 3, 0xC1))
    {
        return EXIT_FAILURE;
    }

    if (EXIT_SUCCESS != print_version_string(1, 2, 3, 0xFF))
    {
        return EXIT_FAILURE;
    }

    if (EXIT_SUCCESS != print_version_string(1, 2, 3, 0x05))
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

