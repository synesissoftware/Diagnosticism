/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.C++.version_string/entry.cpp
 *
 * Purpose: Tests `diagnosticism::calc_version_string()` and
 *          `diagnosticism::calc_version_string_16()`.
 *
 * Created: 23rd August 2025
 * Updated: 4th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <diagnosticism/version_string.hpp>

#include <xtests/terse-api.h>

#include <string>

#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_8(void);
static void TEST_16(void);


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity;

    XTESTS_COMMANDLINE_PARSE_VERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.C++.version_string", verbosity))
    {
        XTESTS_RUN_CASE(TEST_8);
        XTESTS_RUN_CASE(TEST_16);

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
    TEST_MS_EQ("0.0.0", diagnosticism::calc_version_string(0, 0, 0, 0));
    TEST_MS_EQ("0.0.0.1", diagnosticism::calc_version_string(0, 0, 0, 1));
    TEST_MS_EQ("1.2.3", diagnosticism::calc_version_string(1, 2, 3, 0));
    TEST_MS_EQ("0.0.3", diagnosticism::calc_version_string(0, 0, 3, 0));
    TEST_MS_EQ("1.2.3.1", diagnosticism::calc_version_string(1, 2, 3, 1));
    TEST_MS_EQ("0.0.3.1", diagnosticism::calc_version_string(0, 0, 3, 1));
    TEST_MS_EQ("1.2.3.63", diagnosticism::calc_version_string(1, 2, 3, 0x3F));
    TEST_MS_EQ("1.2.3-alpha0", diagnosticism::calc_version_string(1, 2, 3, 0x40));
    TEST_MS_EQ("0.1.0-alpha1", diagnosticism::calc_version_string(0, 1, 0, 0x41));
    TEST_MS_EQ("1.0.0-beta1", diagnosticism::calc_version_string(1, 0, 0, 0x81));
    TEST_MS_EQ("1.2.3-rc1", diagnosticism::calc_version_string(1, 2, 3, 0xC1));
    TEST_MS_EQ("1.2.3-rc62", diagnosticism::calc_version_string(1, 2, 3, 0xFE));
    TEST_MS_EQ("123.200.21", diagnosticism::calc_version_string(123, 200, 21, 0xFF));
    TEST_MS_EQ("0.0.1.65", diagnosticism::calc_version_string(0, 0, 1, 0x41));
    TEST_MS_EQ("0.0.1", diagnosticism::calc_version_string(0, 0, 1, 0xFF));
    TEST_MS_EQ("1.2.3-alpha1", diagnosticism::calc_version_string(0x101, 0x202, 0x303, 0x141));
}

static void TEST_16(void)
{
    TEST_MS_EQ("0.0.0", diagnosticism::calc_version_string_16(0, 0, 0, 0));
    TEST_MS_EQ("0.0.0.1", diagnosticism::calc_version_string_16(0, 0, 0, 1));
    TEST_MS_EQ("1.2.3", diagnosticism::calc_version_string_16(1, 2, 3, 0));
    TEST_MS_EQ("0.0.3", diagnosticism::calc_version_string_16(0, 0, 3, 0));
    TEST_MS_EQ("1.2.3.1", diagnosticism::calc_version_string_16(1, 2, 3, 1));
    TEST_MS_EQ("0.0.3.1", diagnosticism::calc_version_string_16(0, 0, 3, 1));
    TEST_MS_EQ("123.456.789", diagnosticism::calc_version_string_16(123, 456, 789, 0xFFFF));
    TEST_MS_EQ("123.456.789.255", diagnosticism::calc_version_string_16(123, 456, 789, 0xFF));
    TEST_MS_EQ("1.2.3.16383", diagnosticism::calc_version_string_16(1, 2, 3, 0x3FFF));
    TEST_MS_EQ("1.2.3-alpha0", diagnosticism::calc_version_string_16(1, 2, 3, 0x4000));
    TEST_MS_EQ("0.1.0-alpha801", diagnosticism::calc_version_string_16(0, 1, 0, 0x4321));
    TEST_MS_EQ("0.1.0-beta1893", diagnosticism::calc_version_string_16(0, 1, 0, 0x8765));
    TEST_MS_EQ("1.2.3-rc291", diagnosticism::calc_version_string_16(1, 2, 3, 0xC123));
    TEST_MS_EQ("1.2.3-rc16382", diagnosticism::calc_version_string_16(1, 2, 3, 0xFFFE));
    TEST_MS_EQ("1.2.3", diagnosticism::calc_version_string_16(1, 2, 3, 0xFFFF));
    TEST_MS_EQ("0.0.1.17185", diagnosticism::calc_version_string_16(0, 0, 1, 0x4321));
    TEST_MS_EQ("0.0.1", diagnosticism::calc_version_string_16(0, 0, 1, 0xFFFF));
}


/* ///////////////////////////// end of file //////////////////////////// */

