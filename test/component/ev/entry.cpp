/* /////////////////////////////////////////////////////////////////////////
 * File:    ev/entry.c
 *
 * Purpose: Tests Diagnosticism API (un)initialisation.
 *
 * Created: 5th July 2025
 * Updated: 5th July 2025
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <diagnosticism/ev.h>

#include <platformstl/system/environment_variable_scope.hpp>

#include <xtests/terse-api.h>

#include <errno.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_getenv(void);


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity;

    XTESTS_COMMANDLINE_PARSE_VERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.api_init", verbosity))
    {
        XTESTS_RUN_CASE(TEST_getenv);


        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_getenv(void)
{
    platformstl::environment_variable_scope scoper_EV1("EV1", "value1");
    platformstl::environment_variable_scope scoper_EV2("EV2", NULL);

    {
        errno = 0;

        char const* const v = diagnosticism_getenv("EV1", NULL);

        TEST_INT_EQ(0, errno);

        TEST_PTR_NE(NULL, v);
        TEST_MS_EQ("value1", v);
    }

    {
        errno = 0;

        char const* const v = diagnosticism_getenv("EV1", "value2");

        TEST_INT_EQ(0, errno);

        TEST_PTR_NE(NULL, v);
        TEST_MS_EQ("value1", v);
    }

    {
        errno = 0;

        char const* const v = diagnosticism_getenv("EV2", NULL);

        TEST_INT_EQ(ENOENT, errno);

        TEST_PTR_EQ(NULL, v);
    }

    {
        errno = 0;

        char const* const v = diagnosticism_getenv("EV2", "value2");

        TEST_INT_EQ(ENOENT, errno);

        TEST_PTR_NE(NULL, v);
        TEST_MS_EQ("value2", v);
    }
}


/* ///////////////////////////// end of file //////////////////////////// */

