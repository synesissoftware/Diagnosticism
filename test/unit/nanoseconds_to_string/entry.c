/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.nanoseconds_to_string/entry.c
 *
 * Purpose: Golden-parity tests for diagnosticism_nanoseconds_to_string().
 *
 * Created: 16th October 2026
 * Updated: 16th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <diagnosticism/nanoseconds_to_string.h>

#include <xtests/terse-api.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_ZERO(void);
static void TEST_ONE_SECOND(void);
static void TEST_123_MILLISECONDS(void);
static void TEST_123_456_789_NANOSECONDS(void);
static void TEST_STRINGS(void);
static void TEST_NEGATIVE_VALUES_STRINGS(void);
static void TEST_OBSERVED_EDGE_CASES(void);
static void TEST_WITH_PLUS_SIGN(void);
static void TEST_WITH_ASCII_ONLY(void);
static void TEST_BUFFER_AND_PNWRITTEN(void);


/* /////////////////////////////////////////////////////////////////////////
 * helpers
 */

static
void
check_ns(
    int64_t     nanoseconds
,   uint32_t    flags
,   char const* expected
)
{
    char        buffer[DIAGNOSTICISM_NS_TO_STRING_MIN_CCH];
    size_t      n;
    int const   r = diagnosticism_nanoseconds_to_string(
        STLSOFT_NUM_ELEMENTS(buffer)
    ,   &buffer[0]
    ,   nanoseconds
    ,   flags
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

    if (XTESTS_START_RUNNER("test.unit.nanoseconds_to_string", verbosity))
    {
        XTESTS_RUN_CASE(TEST_ZERO);
        XTESTS_RUN_CASE(TEST_ONE_SECOND);
        XTESTS_RUN_CASE(TEST_123_MILLISECONDS);
        XTESTS_RUN_CASE(TEST_123_456_789_NANOSECONDS);
        XTESTS_RUN_CASE(TEST_STRINGS);
        XTESTS_RUN_CASE(TEST_NEGATIVE_VALUES_STRINGS);
        XTESTS_RUN_CASE(TEST_OBSERVED_EDGE_CASES);
        XTESTS_RUN_CASE(TEST_WITH_PLUS_SIGN);
        XTESTS_RUN_CASE(TEST_WITH_ASCII_ONLY);
        XTESTS_RUN_CASE(TEST_BUFFER_AND_PNWRITTEN);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_ZERO(void)
{
    check_ns(0, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "0s");
    check_ns(0, DIAGNOSTICISM_NS_TO_STRING_F_PLUS, "0s");
}

static void TEST_ONE_SECOND(void)
{
    check_ns(1000000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "1s");
}

static void TEST_123_MILLISECONDS(void)
{
    check_ns(123000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "123ms");
}

static void TEST_123_456_789_NANOSECONDS(void)
{
    check_ns(123456789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "123.4ms");
}

static void TEST_STRINGS(void)
{
    /* µ = UTF-8 C2 B5 — same golden strings as Diagnosticism.Python */
    check_ns(9LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "9ns");
    check_ns(89LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "89ns");
    check_ns(789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "789ns");

    check_ns(6789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "6.789\xC2\xB5s");
    check_ns(56789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "56.78\xC2\xB5s");
    check_ns(456789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "456.7\xC2\xB5s");

    check_ns(3456789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "3.456ms");
    check_ns(23456789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "23.45ms");
    check_ns(123456789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "123.4ms");

    check_ns(9123456789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "9.123s");
    check_ns(89123456789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "89.12s");
    check_ns(789123456789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "789.1s");

    check_ns(80LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "80ns");
    check_ns(700LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "700ns");

    check_ns(6000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "6\xC2\xB5s");
    check_ns(50000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "50\xC2\xB5s");
    check_ns(400000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "400\xC2\xB5s");

    check_ns(3000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "3ms");
    check_ns(20000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "20ms");
    check_ns(100000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "100ms");

    check_ns(9000000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "9s");
    check_ns(10000000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "10s");
    check_ns(200000000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "200s");
    check_ns(3000000000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "3000s");
    check_ns(40000000000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "40000s");
    check_ns(500000000000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "500000s");
    check_ns(6000000000000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "6000000s");
    check_ns(70000000000000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "70000000s");

    check_ns(11111111111LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "11.11s");
    check_ns(222222222222LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "222.2s");
    check_ns(3333333333333LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "3333s");
    check_ns(44444444444444LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "44444s");
    check_ns(555555555555555LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "555555s");
    check_ns(6666666666666666LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "6666666s");
    check_ns(77777777777777777LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "77777777s");
}

static void TEST_NEGATIVE_VALUES_STRINGS(void)
{
    check_ns(-9LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-9ns");
    check_ns(-89LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-89ns");
    check_ns(-789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-789ns");

    check_ns(-6789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-6.789\xC2\xB5s");
    check_ns(-56789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-56.78\xC2\xB5s");
    check_ns(-456789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-456.7\xC2\xB5s");

    check_ns(-3456789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-3.456ms");
    check_ns(-23456789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-23.45ms");
    check_ns(-123456789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-123.4ms");

    check_ns(-9123456789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-9.123s");

    check_ns(-80LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-80ns");
    check_ns(-700LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-700ns");

    check_ns(-6000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-6\xC2\xB5s");
    check_ns(-50000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-50\xC2\xB5s");
    check_ns(-400000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-400\xC2\xB5s");

    check_ns(-3000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-3ms");
    check_ns(-20000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-20ms");
    check_ns(-100000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-100ms");

    check_ns(-9000000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-9s");
    check_ns(-10000000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-10s");
    check_ns(-200000000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-200s");
    check_ns(-3000000000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-3000s");
    check_ns(-40000000000000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-40000s");
}

static void TEST_OBSERVED_EDGE_CASES(void)
{
    check_ns(999772000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "999.7ms");
    check_ns(999800000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "999.8ms");
    check_ns(999974000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "999.9ms");

    check_ns(-999772000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-999.7ms");
    check_ns(-999800000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-999.8ms");
    check_ns(-999974000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-999.9ms");
}

static void TEST_WITH_PLUS_SIGN(void)
{
    check_ns(999772000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "999.7ms");
    check_ns(999800000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "999.8ms");
    check_ns(999974000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "999.9ms");

    check_ns(-999772000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-999.7ms");
    check_ns(-999800000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-999.8ms");
    check_ns(-999974000LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "-999.9ms");

    check_ns(999772000LL, DIAGNOSTICISM_NS_TO_STRING_F_PLUS, "+999.7ms");
    check_ns(999800000LL, DIAGNOSTICISM_NS_TO_STRING_F_PLUS, "+999.8ms");
    check_ns(999974000LL, DIAGNOSTICISM_NS_TO_STRING_F_PLUS, "+999.9ms");

    check_ns(-999772000LL, DIAGNOSTICISM_NS_TO_STRING_F_PLUS, "-999.7ms");
    check_ns(-999800000LL, DIAGNOSTICISM_NS_TO_STRING_F_PLUS, "-999.8ms");
    check_ns(-999974000LL, DIAGNOSTICISM_NS_TO_STRING_F_PLUS, "-999.9ms");
}

static void TEST_WITH_ASCII_ONLY(void)
{
    /* Default remains UTF-8 MICRO SIGN; ASCII_ONLY selects "us". */
    check_ns(6789LL, DIAGNOSTICISM_NS_TO_STRING_F_NONE, "6.789\xC2\xB5s");
    check_ns(6789LL, DIAGNOSTICISM_NS_TO_STRING_F_ASCII_ONLY, "6.789us");
    check_ns(56789LL, DIAGNOSTICISM_NS_TO_STRING_F_ASCII_ONLY, "56.78us");
    check_ns(456789LL, DIAGNOSTICISM_NS_TO_STRING_F_ASCII_ONLY, "456.7us");
    check_ns(6000LL, DIAGNOSTICISM_NS_TO_STRING_F_ASCII_ONLY, "6us");
    check_ns(
        6789LL
    ,   DIAGNOSTICISM_NS_TO_STRING_F_ASCII_ONLY | DIAGNOSTICISM_NS_TO_STRING_F_PLUS
    ,   "+6.789us"
    );
    check_ns(-6789LL, DIAGNOSTICISM_NS_TO_STRING_F_ASCII_ONLY, "-6.789us");

    /* Non-microsecond units are already ASCII; flag is a no-op for them. */
    check_ns(123456789LL, DIAGNOSTICISM_NS_TO_STRING_F_ASCII_ONLY, "123.4ms");
    check_ns(1LL, DIAGNOSTICISM_NS_TO_STRING_F_ASCII_ONLY, "1ns");
}

static void TEST_BUFFER_AND_PNWRITTEN(void)
{
    char        buffer[DIAGNOSTICISM_NS_TO_STRING_MIN_CCH];
    size_t      n;
    size_t      required;
    int         r;
    int         saved_errno;

    /* Size probe: cchBuffer==0 reports required capacity, leaves errno alone. */
    errno = 0;
    r = diagnosticism_nanoseconds_to_string(
        0
    ,   NULL
    ,   123456789LL
    ,   DIAGNOSTICISM_NS_TO_STRING_F_NONE
    ,   &required
    );

    TEST_INT_EQ(-1, r);
    XTESTS_TEST_BOOLEAN_TRUE(required > 1);
    TEST_INT_EQ(0, errno);

    saved_errno = errno = EINVAL;
    r = diagnosticism_nanoseconds_to_string(
        1
    ,   &buffer[0]
    ,   123456789LL
    ,   DIAGNOSTICISM_NS_TO_STRING_F_NONE
    ,   &n
    );

    TEST_INT_EQ(-1, r);
    TEST_INT_EQ((int)required, (int)n);
    TEST_INT_EQ(ERANGE, errno);
    TEST_INT_NE(saved_errno, errno);

    r = diagnosticism_nanoseconds_to_string(
        STLSOFT_NUM_ELEMENTS(buffer)
    ,   &buffer[0]
    ,   123456789LL
    ,   DIAGNOSTICISM_NS_TO_STRING_F_NONE
    ,   NULL
    );

    TEST_INT_EQ(0, r);
    TEST_MS_EQ("123.4ms", buffer);
}

/* ///////////////////////////// end of file //////////////////////////// */

