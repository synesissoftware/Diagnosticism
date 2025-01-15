/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.api_init/entry.c
 *
 * Purpose: Tests Diagnosticism API (un)initialisation.
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
 * forward declarations
 */

static void test_init_simple(void);
/*
static void test_init_dependency_failure(void);
static void test_init_allocator(void);
 */


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
        XTESTS_RUN_CASE(test_init_simple);


        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void test_init_simple(void)
{
    diag_uint32_t const init_flags  =   0
                                    ;
    void*               init_param  =   NULL;

    int const           r           =   diagnosticism_api_init(init_flags, init_param);

    XTESTS_TEST_INTEGER_EQUAL(0, r);

    diagnosticism_api_uninit();

    XTESTS_TEST_PASSED();
}


/* ///////////////////////////// end of file //////////////////////////// */

