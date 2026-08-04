/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.version_string/entry.c
 *
 * Purpose: Tests Diagnosticism VersionString API.
 *
 * Created: 15th May 2025
 * Updated: 6th July 2025
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

static void TEST_1(void);


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
        XTESTS_RUN_CASE(TEST_1);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_1(void)
{
    {
        char            buffer[101];
        size_t          n;
        size_t const    r = diagnosticism_calc_version_string(&buffer[0], STLSOFT_NUM_ELEMENTS(buffer), 0, 0, 0, 0, &n);

        TEST_INT_EQ(0, r);
        TEST_INT_EQ(5, n);
        TEST_MS_EQ("0.0.0", buffer);
    }

    {
        char            buffer[101];
        size_t          n;
        size_t const    r = diagnosticism_calc_version_string(&buffer[0], STLSOFT_NUM_ELEMENTS(buffer), 1, 2, 3, 0, &n);

        TEST_INT_EQ(0, r);
        TEST_INT_EQ(5, n);
        TEST_MS_EQ("1.2.3", buffer);
    }

    {
        char            buffer[101];
        size_t          n;
        size_t const    r = diagnosticism_calc_version_string(&buffer[0], STLSOFT_NUM_ELEMENTS(buffer), 0, 0, 3, 0, &n);

        TEST_INT_EQ(0, r);
        TEST_INT_EQ(5, n);
        TEST_MS_EQ("0.0.3", buffer);
    }

    {
        char            buffer[101];
        size_t          n;
        size_t const    r = diagnosticism_calc_version_string(&buffer[0], STLSOFT_NUM_ELEMENTS(buffer), 1, 2, 3, 1, &n);

        TEST_INT_EQ(0, r);
        TEST_INT_EQ(7, n);
        TEST_MS_EQ("1.2.3.1", buffer);
    }

    {
        char            buffer[101];
        size_t          n;
        size_t const    r = diagnosticism_calc_version_string(&buffer[0], STLSOFT_NUM_ELEMENTS(buffer), 0, 0, 3, 1, &n);

        TEST_INT_EQ(0, r);
        TEST_INT_EQ(7, n);
        TEST_MS_EQ("0.0.3.1", buffer);
    }

    {
        char            buffer[101];
        size_t          n;
        size_t const    r = diagnosticism_calc_version_string(&buffer[0], STLSOFT_NUM_ELEMENTS(buffer), 123, 456, 789, 0xFFFF, &n);

        TEST_INT_EQ(0, r);
        TEST_INT_EQ(11, n);
        TEST_MS_EQ("123.456.789", buffer);
    }

    {
        char            buffer[101];
        size_t          n;
        size_t const    r = diagnosticism_calc_version_string(&buffer[0], STLSOFT_NUM_ELEMENTS(buffer), 123, 456, 789, 0xFF, &n);

        TEST_INT_EQ(0, r);
        TEST_INT_EQ(15, n);
        TEST_MS_EQ("123.456.789.255", buffer);
    }

    {
        char            buffer[101];
        size_t          n;
        size_t const    r = diagnosticism_calc_version_string(&buffer[0], STLSOFT_NUM_ELEMENTS(buffer), 0, 0, 1, 0x1234, &n);

        TEST_INT_EQ(0, r);
        TEST_INT_EQ(10, n);
        TEST_MS_EQ("0.0.1.4660", buffer);
    }

    {
        char            buffer[101];
        size_t          n;
        size_t const    r = diagnosticism_calc_version_string(&buffer[0], STLSOFT_NUM_ELEMENTS(buffer), 0, 0, 1, 0x3fff, &n);

        TEST_INT_EQ(0, r);
        TEST_INT_EQ(11, n);
        TEST_MS_EQ("0.0.1.16383", buffer);
    }

    {
        char            buffer[101];
        size_t          n;
        size_t const    r = diagnosticism_calc_version_string(&buffer[0], STLSOFT_NUM_ELEMENTS(buffer), 0, 1, 0, 0x4321, &n);

        TEST_INT_EQ(0, r);
        TEST_INT_EQ(14, n);
        TEST_MS_EQ("0.1.0-alpha801", buffer);
    }

    {
        char            buffer[101];
        size_t          n;
        size_t const    r = diagnosticism_calc_version_string(&buffer[0], STLSOFT_NUM_ELEMENTS(buffer), 0, 1, 0, 0x8765, &n);

        TEST_INT_EQ(0, r);
        TEST_INT_EQ(14, n);
        TEST_MS_EQ("0.1.0-beta1893", buffer);
    }

    {
        char            buffer[101];
        size_t          n;
        size_t const    r = diagnosticism_calc_version_string(&buffer[0], STLSOFT_NUM_ELEMENTS(buffer), 1, 2, 3, 0xC123, &n);

        TEST_INT_EQ(0, r);
        TEST_INT_EQ(11, n);
        TEST_MS_EQ("1.2.3-rc291", buffer);
    }

    {
        char            buffer[101];
        size_t          n;
        size_t const    r = diagnosticism_calc_version_string(&buffer[0], STLSOFT_NUM_ELEMENTS(buffer), 1, 2, 3, 0xFFFE, &n);

        TEST_INT_EQ(0, r);
        TEST_INT_EQ(13, n);
        TEST_MS_EQ("1.2.3-rc16382", buffer);
    }

    {
        char            buffer[101];
        size_t          n;
        size_t const    r = diagnosticism_calc_version_string(&buffer[0], STLSOFT_NUM_ELEMENTS(buffer), 1, 2, 3, 0xFFFF, &n);

        TEST_INT_EQ(0, r);
        TEST_INT_EQ(5, n);
        TEST_MS_EQ("1.2.3", buffer);
    }
}


/* ///////////////////////////// end of file //////////////////////////// */

