/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.C++.nanoseconds_to_string/entry.cpp
 *
 * Purpose: Tests `diagnosticism::nanoseconds_to_string()` C++ overloads.
 *
 * Created: 16th October 2026
 * Updated: 16th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <diagnosticism/nanoseconds_to_string.hpp>

#include <stlsoft/string/simple_string.hpp>
#include <stlsoft/string/static_string.hpp>

#include <xtests/terse-api.h>

#include <string>

#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_RETURN_std_string(void);
static void TEST_MUTATING_std_string(void);
static void TEST_MUTATING_CUSTOM_STRING(void);
static void TEST_MUTATING_simple_string(void);
static void TEST_MUTATING_static_string(void);


/* /////////////////////////////////////////////////////////////////////////
 * helpers
 */

namespace
{

struct stub_string
{
    std::string inner;

    void
    assign(
        char const* s
    ,   size_t      n
    )
    {
        inner.assign(s, n);
    }
};

template <typename T_string>
void
check_mutating(
    T_string&   s
,   int64_t     nanoseconds
,   uint32_t    flags
,   char const* expected
)
{
    T_string& r = diagnosticism::nanoseconds_to_string(s, nanoseconds, flags);

    TEST_MS_EQ(expected, s.c_str());
    TEST_POINTER_EQUAL(&s, &r);
}

} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity;

    XTESTS_COMMANDLINE_PARSE_VERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.C++.nanoseconds_to_string", verbosity))
    {
        XTESTS_RUN_CASE(TEST_RETURN_std_string);
        XTESTS_RUN_CASE(TEST_MUTATING_std_string);
        XTESTS_RUN_CASE(TEST_MUTATING_CUSTOM_STRING);
        XTESTS_RUN_CASE(TEST_MUTATING_simple_string);
        XTESTS_RUN_CASE(TEST_MUTATING_static_string);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_RETURN_std_string(void)
{
    TEST_MS_EQ("0s", diagnosticism::nanoseconds_to_string(0));
    TEST_MS_EQ("0s", diagnosticism::nanoseconds_to_string(0, DIAGNOSTICISM_NS_TO_STRING_F_PLUS));
    TEST_MS_EQ("123.4ms", diagnosticism::nanoseconds_to_string(123456789LL));
    TEST_MS_EQ("6.789\xC2\xB5s", diagnosticism::nanoseconds_to_string(6789LL));
    TEST_MS_EQ("6.789us", diagnosticism::nanoseconds_to_string(6789LL, DIAGNOSTICISM_NS_TO_STRING_F_ASCII_ONLY));
    TEST_MS_EQ("+999.7ms", diagnosticism::nanoseconds_to_string(999772000LL, DIAGNOSTICISM_NS_TO_STRING_F_PLUS));
    TEST_MS_EQ("-999.7ms", diagnosticism::nanoseconds_to_string(-999772000LL, DIAGNOSTICISM_NS_TO_STRING_F_PLUS));
    TEST_MS_EQ("70000000s", diagnosticism::nanoseconds_to_string(70000000000000000LL));
}

static void TEST_MUTATING_std_string(void)
{
    std::string s("stale");

    check_mutating(s, 123456789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "123.4ms");
    check_mutating(s, 6789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "6.789\xC2\xB5s");
    check_mutating(s, 999772000LL, DIAGNOSTICISM_NS_TO_STRING_F_PLUS, "+999.7ms");
}

static void TEST_MUTATING_CUSTOM_STRING(void)
{
    stub_string s;

    s.inner = "stale";

    diagnosticism::nanoseconds_to_string(s, 123456789LL);
    TEST_MS_EQ("123.4ms", s.inner.c_str());

    diagnosticism::nanoseconds_to_string(s, 0, DIAGNOSTICISM_NS_TO_STRING_F_PLUS);
    TEST_MS_EQ("0s", s.inner.c_str());
}

static void TEST_MUTATING_simple_string(void)
{
    stlsoft::simple_string s("stale");

    check_mutating(s, 123456789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "123.4ms");
    check_mutating(s, 6789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "6.789\xC2\xB5s");
    check_mutating(s, 999772000LL, DIAGNOSTICISM_NS_TO_STRING_F_PLUS, "+999.7ms");
    check_mutating(s, 0, DIAGNOSTICISM_NS_TO_STRING_F_PLUS, "0s");
}

static void TEST_MUTATING_static_string(void)
{
    stlsoft::basic_static_string<char, DIAGNOSTICISM_NS_TO_STRING_MIN_CCH> s("stale");

    check_mutating(s, 123456789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "123.4ms");
    check_mutating(s, 6789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "6.789\xC2\xB5s");
    check_mutating(s, 999772000LL, DIAGNOSTICISM_NS_TO_STRING_F_PLUS, "+999.7ms");
    check_mutating(s, 70000000000000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "70000000s");
}

/* ///////////////////////////// end of file //////////////////////////// */

