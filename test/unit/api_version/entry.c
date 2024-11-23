/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.api_version/entry.c
 *
 * Purpose: Tests `diagnosticism_api_version()`.
 *
 * Created: 23rd November 2024
 * Updated: 23rd November 2024
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <diagnosticism/diagnosticism.h>

#include <xtests/xtests.h>


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity;

    XTESTS_COMMANDLINE_PARSE_VERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.api_version", verbosity))
    {
        if (XTESTS_CASE_BEGIN("test-version", "tests that the compiled version is the same as that defined in the header on which the build depends"))
        {
            diag_uint32_t const version = diagnosticism_api_version();

            XTESTS_TEST_INTEGER_EQUAL(DIAGNOSTICISM_VER, version);

            XTESTS_CASE_END("test-version");
        }


        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */

