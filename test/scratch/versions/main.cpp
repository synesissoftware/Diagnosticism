/* /////////////////////////////////////////////////////////////////////////
 * File:    test/scratch/versions/main.cpp
 *
 * Purpose: Scratch version reporter for Diagnosticism (self-formatted)
 *          and optional test-time efferent siblings.
 *
 * Created: 5th August 2026
 * Updated: 27th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <diagnosticism/diagnosticism.h>
#include <diagnosticism/version_string.h>

#ifdef HAS_STLSoft
# include <stlsoft/stlsoft.h>
#endif /* HAS_STLSoft */
#ifdef HAS_shwild
# include <shwild/shwild.h>
#endif /* HAS_shwild */
#ifdef HAS_xTests
# include <xtests/xtests.h>
#endif /* HAS_xTests */

#include <iomanip>
#include <iostream>

#include <stdlib.h>


#define PROGRAM_NAME                                        "test.scratch.versions"


template<
    typename T_stream
,   typename T_integer
>
int
version(
    T_stream&   stm
,   char const* prefix
,   char const* libname
,   char const* macroname
,   T_integer   libver
)
{
    char        buffer[101];
    size_t      n;
    int const   r = diagnosticism_calc_version_string(
        buffer
    ,   sizeof(buffer) / sizeof(buffer[0])
    ,   (int)((libver >> 24) & 0xff)
    ,   (int)((libver >> 16) & 0xff)
    ,   (int)((libver >> 8) & 0xff)
    ,   (int)((libver >> 0) & 0xff)
    ,   &n
    );

    if (0 != r)
    {
        std::cerr
            << PROGRAM_NAME
            << ": failed to format version string for "
            << libname
            << std::endl
            ;

        return EXIT_FAILURE;
    }

    buffer[n] = '\0';

    stm
        << prefix
        << libname
        << ": "
        << buffer
        << " ("
        << macroname
        << " = 0x"
        << std::hex << std::setfill('0') << std::setw(8)
        << static_cast<unsigned>(libver)
        << std::dec
        << ")"
        << std::endl
        ;

    return EXIT_SUCCESS;
}

int main(int /* argc */, char* /* argv */[])
{
    int efferents_count = 0;

    {
        unsigned const libver = DIAGNOSTICISM_VER;

        if (EXIT_SUCCESS != version(std::cout, "", "Diagnosticism", "DIAGNOSTICISM_VER", libver))
        {
            return EXIT_FAILURE;
        }
    }

#ifdef HAS_STLSoft

    if (0 == efferents_count++)
    {
        std::cout << "\n" << "efferent dependencies:" << std::endl;
    }

    {
        unsigned const libver = _STLSOFT_VER;

        if (EXIT_SUCCESS != version(std::cout, "\t", "STLSoft", "_STLSOFT_VER", libver))
        {
            return EXIT_FAILURE;
        }
    }
#endif /* HAS_STLSoft */

#ifdef HAS_shwild

    if (0 == efferents_count++)
    {
        std::cout << "\n" << "efferent dependencies:" << std::endl;
    }

    {
        unsigned const libver = SHWILD_VER;

        if (EXIT_SUCCESS != version(std::cout, "\t", "shwild", "SHWILD_VER", libver))
        {
            return EXIT_FAILURE;
        }
    }
#endif /* HAS_shwild */

#ifdef HAS_xTests

    if (0 == efferents_count++)
    {
        std::cout << "\n" << "efferent dependencies:" << std::endl;
    }

    {
        unsigned const libver = _XTESTS_VER;

        if (EXIT_SUCCESS != version(std::cout, "\t", "xTests", "_XTESTS_VER", libver))
        {
            return EXIT_FAILURE;
        }
    }
#endif /* HAS_xTests */

    return EXIT_SUCCESS;
}

/* ///////////////////////////// end of file //////////////////////////// */

