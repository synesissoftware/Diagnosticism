
#include <diagnosticism/version_string.h>

#include <stdio.h>
#include <stdlib.h>


static int
print_version_string_16(
    uint16_t    verMajor
,   uint16_t    verMinor
,   uint16_t    verPatch
,   uint16_t    verAlphaBeta
)
{
    char        buffer[101];
    size_t      n;
    int const   r = diagnosticism_calc_version_string_16(
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
    ,   "%u.%u.%u (0x%04x) -> \"%s\"\n"
    ,   (unsigned)verMajor
    ,   (unsigned)verMinor
    ,   (unsigned)verPatch
    ,   (unsigned)verAlphaBeta
    ,   buffer
    );

    return EXIT_SUCCESS;
}


int main(void)
{
    if (EXIT_SUCCESS != print_version_string_16(1, 2, 3, 0))
    {
        return EXIT_FAILURE;
    }

    if (EXIT_SUCCESS != print_version_string_16(0, 1, 0, 0x4321))
    {
        return EXIT_FAILURE;
    }

    if (EXIT_SUCCESS != print_version_string_16(1, 2, 3, 0xC123))
    {
        return EXIT_FAILURE;
    }

    if (EXIT_SUCCESS != print_version_string_16(1, 2, 3, 0xFFFF))
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

