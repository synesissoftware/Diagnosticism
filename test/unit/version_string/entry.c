/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.version_string/entry.c
 *
 * Purpose: Tests Diagnosticism VersionString API.
 *
 * Created: 15th May 2025
 * Updated: 4th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <diagnosticism/version_string.h>

#include <xtests/terse-api.h>

#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_8(void);
static void TEST_8_BUFFER_AND_PNWRITTEN(void);
static void TEST_16(void);
static void TEST_16_BUFFER_AND_PNWRITTEN(void);


/* /////////////////////////////////////////////////////////////////////////
 * helpers
 */

static
void
check_8(
    int         verMajor
,   int         verMinor
,   int         verPatch
,   int         verAlphaBeta
,   char const* expected
)
{
    char        buffer[101];
    size_t      n;
    int const   r = diagnosticism_calc_version_string(
        &buffer[0]
    ,   STLSOFT_NUM_ELEMENTS(buffer)
    ,   verMajor
    ,   verMinor
    ,   verPatch
    ,   verAlphaBeta
    ,   &n
    );

    TEST_INT_EQ(0, r);
    TEST_INT_EQ(strlen(expected), n);
    TEST_MS_EQ(expected, buffer);
}

static
void
check_16(
    uint16_t    verMajor
,   uint16_t    verMinor
,   uint16_t    verPatch
,   uint16_t    verAlphaBeta
,   char const* expected
)
{
    char        buffer[101];
    size_t      n;
    int const   r = diagnosticism_calc_version_string_16(
        &buffer[0]
    ,   STLSOFT_NUM_ELEMENTS(buffer)
    ,   verMajor
    ,   verMinor
    ,   verPatch
    ,   verAlphaBeta
    ,   &n
    );

    TEST_INT_EQ(0, r);
    TEST_INT_EQ(strlen(expected), n);
    TEST_MS_EQ(expected, buffer);
}


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity;

    XTESTS_COMMANDLINE_PARSE_VERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.version_string", verbosity))
    {
        XTESTS_RUN_CASE(TEST_8);
        XTESTS_RUN_CASE(TEST_8_BUFFER_AND_PNWRITTEN);
        XTESTS_RUN_CASE(TEST_16);
        XTESTS_RUN_CASE(TEST_16_BUFFER_AND_PNWRITTEN);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_8(void)
{
    check_8(0, 0, 0, 0, "0.0.0");
    check_8(1, 2, 3, 0, "1.2.3");
    check_8(0, 0, 3, 0, "0.0.3");
    check_8(1, 2, 3, 1, "1.2.3.1");
    check_8(0, 0, 3, 1, "0.0.3.1");

    /* band thresholds and representative pre-release values */
    check_8(1, 2, 3, 0x3F, "1.2.3.63");
    check_8(1, 2, 3, 0x40, "1.2.3-alpha0");
    check_8(0, 1, 0, 0x41, "0.1.0-alpha1");
    check_8(1, 0, 0, 0x81, "1.0.0-beta1");
    check_8(1, 2, 3, 0xC1, "1.2.3-rc1");
    check_8(1, 2, 3, 0xFE, "1.2.3-rc62");
    check_8(123, 200, 21, 0xFF, "123.200.21");

    /* major=minor=0: pre-release bands become a fourth component */
    check_8(0, 0, 1, 0x41, "0.0.1.65");
    check_8(0, 0, 1, 0xFF, "0.0.1");

    /* elements are interpreted strictly as 8-bit values */
    check_8(0x101, 0x202, 0x303, 0x141, "1.2.3-alpha1");
}

static void TEST_8_BUFFER_AND_PNWRITTEN(void)
{
    {
        char        buffer[6];
        size_t      n = 99;
        int const   r = diagnosticism_calc_version_string(
            &buffer[0]
        ,   STLSOFT_NUM_ELEMENTS(buffer)
        ,   1
        ,   2
        ,   3
        ,   0
        ,   &n
        );

        TEST_INT_EQ(0, r);
        TEST_INT_EQ(5, n);
        TEST_MS_EQ("1.2.3", buffer);
    }

    {
        char        buffer[5];
        size_t      n = 0;
        int const   r = diagnosticism_calc_version_string(
            &buffer[0]
        ,   STLSOFT_NUM_ELEMENTS(buffer)
        ,   1
        ,   2
        ,   3
        ,   0
        ,   &n
        );

        TEST_INT_EQ(-1, r);
        TEST_INT_EQ(6, n);
    }

    {
        char        buffer[101];
        int const   r = diagnosticism_calc_version_string(
            &buffer[0]
        ,   STLSOFT_NUM_ELEMENTS(buffer)
        ,   1
        ,   2
        ,   3
        ,   0x41
        ,   NULL
        );

        TEST_INT_EQ(0, r);
        TEST_MS_EQ("1.2.3-alpha1", buffer);
    }
}

static void TEST_16(void)
{
    check_16(0, 0, 0, 0, "0.0.0");
    check_16(1, 2, 3, 0, "1.2.3");
    check_16(1, 2, 3, 1, "1.2.3.1");
    check_16(123, 456, 789, 0xFFFF, "123.456.789");
    check_16(123, 456, 789, 0xFF, "123.456.789.255");

    /* band thresholds and representative pre-release values */
    check_16(1, 2, 3, 0x3FFF, "1.2.3.16383");
    check_16(1, 2, 3, 0x4000, "1.2.3-alpha0");
    check_16(0, 1, 0, 0x4321, "0.1.0-alpha801");
    check_16(0, 1, 0, 0x8765, "0.1.0-beta1893");
    check_16(1, 2, 3, 0xC123, "1.2.3-rc291");
    check_16(1, 2, 3, 0xFFFE, "1.2.3-rc16382");
    check_16(1, 2, 3, 0xFFFF, "1.2.3");

    /* major=minor=0: pre-release bands become a fourth component */
    check_16(0, 0, 1, 0x4321, "0.0.1.17185");
    check_16(0, 0, 1, 0xFFFF, "0.0.1");
}

static void TEST_16_BUFFER_AND_PNWRITTEN(void)
{
    {
        char        buffer[6];
        size_t      n = 99;
        int const   r = diagnosticism_calc_version_string_16(
            &buffer[0]
        ,   STLSOFT_NUM_ELEMENTS(buffer)
        ,   1
        ,   2
        ,   3
        ,   0
        ,   &n
        );

        TEST_INT_EQ(0, r);
        TEST_INT_EQ(5, n);
        TEST_MS_EQ("1.2.3", buffer);
    }

    {
        char        buffer[5];
        size_t      n = 0;
        int const   r = diagnosticism_calc_version_string_16(
            &buffer[0]
        ,   STLSOFT_NUM_ELEMENTS(buffer)
        ,   1
        ,   2
        ,   3
        ,   0
        ,   &n
        );

        TEST_INT_EQ(-1, r);
        TEST_INT_EQ(6, n);
    }

    {
        char        buffer[101];
        int const   r = diagnosticism_calc_version_string_16(
            &buffer[0]
        ,   STLSOFT_NUM_ELEMENTS(buffer)
        ,   1
        ,   2
        ,   3
        ,   0x4001
        ,   NULL
        );

        TEST_INT_EQ(0, r);
        TEST_MS_EQ("1.2.3-alpha1", buffer);
    }
}


/* ///////////////////////////// end of file //////////////////////////// */

