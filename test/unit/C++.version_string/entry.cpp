/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.C++.api_version/entry.cpp
 *
 * Purpose: Tests `diagnosticism::api_version()`.
 *
 * Created: 23rd August 2025
 * Updated: 23rd August 2025
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

static void TEST_1(void);


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity;

    XTESTS_COMMANDLINE_PARSE_VERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.C++.api_version", verbosity))
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
        std::string const s = diagnosticism::calc_version_string(0, 0, 0, 0);

        TEST_MS_EQ("0.0.0", s);
    }

    {
        std::string const s = diagnosticism::calc_version_string(0, 0, 0, 1);

        TEST_MS_EQ("0.0.0.1", s);
    }

    {
        std::string const s = diagnosticism::calc_version_string(1, 2, 3, 0);

        TEST_MS_EQ("1.2.3", s);
    }

    {
        std::string const s = diagnosticism::calc_version_string(0, 0, 3, 0);

        TEST_MS_EQ("0.0.3", s);
    }

    {
        std::string const s = diagnosticism::calc_version_string(1, 2, 3, 1);

        TEST_MS_EQ("1.2.3.1", s);
    }

    {
        std::string const s = diagnosticism::calc_version_string(0, 0, 3, 1);

        TEST_MS_EQ("0.0.3.1", s);
    }

    {
        std::string const s = diagnosticism::calc_version_string(123, 456, 789, 0xFFFF);

        TEST_MS_EQ("123.456.789", s);
    }

    {
        std::string const s = diagnosticism::calc_version_string(123, 456, 789, 0xFF);

        TEST_MS_EQ("123.456.789.255", s);
    }

    {
        std::string const s = diagnosticism::calc_version_string(0, 0, 1, 0x1234);

        TEST_MS_EQ("0.0.1.4660", s);
    }

    {
        std::string const s = diagnosticism::calc_version_string(0, 0, 1, 0x3FFF);

        TEST_MS_EQ("0.0.1.16383", s);
    }

    {
        std::string const s = diagnosticism::calc_version_string(0, 1, 0, 0x4321);

        TEST_MS_EQ("0.1.0-alpha801", s);
    }

    {
        std::string const s = diagnosticism::calc_version_string(0, 1, 0, 0x8765);

        TEST_MS_EQ("0.1.0-beta1893", s);
    }

    {
        std::string const s = diagnosticism::calc_version_string(1, 2, 3, 0xC123);

        TEST_MS_EQ("1.2.3-rc291", s);
    }

    {
        std::string const s = diagnosticism::calc_version_string(1, 2, 3, 0xFFFE);

        TEST_MS_EQ("1.2.3-rc16382", s);
    }

    {
        std::string const s = diagnosticism::calc_version_string(1, 2, 3, 0xFFFF);

        TEST_MS_EQ("1.2.3", s);
    }
}


/* ///////////////////////////// end of file //////////////////////////// */

