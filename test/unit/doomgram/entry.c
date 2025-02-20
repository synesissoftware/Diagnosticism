/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.doomgram/entry.c
 *
 * Purpose: Tests Diagnosticism Doomgram.
 *
 * Created: 5th February 2025
 * Updated: 5th February 2025
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <diagnosticism/doomgram.h>

#include <xtests/terse-api.h>

#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_doomgram_INITIALISE_0(void);
static void TEST_doomgram_INITIALISE_1(void);
static void TEST_doomgram_SINGLE_TIMING_EVENT(void);
static void TEST_doomgram_ZERO_TIME_EVENTS(void);
static void TEST_doomgram_UNIFORM_SPREAD_TIMINGS_1(void);
static void TEST_doomgram_UNIFORM_SPREAD_TIMINGS_2(void);
static void TEST_doomgram_UNIFORM_SPREAD_TIMINGS_3(void);
static void TEST_doomgram_UNIFORM_SPREAD_TIMINGS_4(void);
static void TEST_doomgram_SEVERAL_DISTINCT_TIMINGS(void);
static void TEST_doomgram_SEVERAL_INTERSECTING_TIMINGS(void);
static void TEST_doomgram_MANY_CUMULATIVE_TIMINGS(void);
static void TEST_doomgram_OVERFLOW_BY_SECONDS(void);
static void TEST_doomgram_OVERFLOW_BY_MICROSECONDS(void);


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity;

    XTESTS_COMMANDLINE_PARSE_VERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.doomgram", verbosity))
    {
        XTESTS_RUN_CASE(TEST_doomgram_INITIALISE_0);
        XTESTS_RUN_CASE(TEST_doomgram_INITIALISE_1);
        XTESTS_RUN_CASE(TEST_doomgram_SINGLE_TIMING_EVENT);
        XTESTS_RUN_CASE(TEST_doomgram_ZERO_TIME_EVENTS);
        XTESTS_RUN_CASE(TEST_doomgram_UNIFORM_SPREAD_TIMINGS_1);
        XTESTS_RUN_CASE(TEST_doomgram_UNIFORM_SPREAD_TIMINGS_2);
        XTESTS_RUN_CASE(TEST_doomgram_UNIFORM_SPREAD_TIMINGS_3);
        XTESTS_RUN_CASE(TEST_doomgram_UNIFORM_SPREAD_TIMINGS_4);
        XTESTS_RUN_CASE(TEST_doomgram_SEVERAL_DISTINCT_TIMINGS);
        XTESTS_RUN_CASE(TEST_doomgram_SEVERAL_INTERSECTING_TIMINGS);
        XTESTS_RUN_CASE(TEST_doomgram_MANY_CUMULATIVE_TIMINGS);
        XTESTS_RUN_CASE(TEST_doomgram_OVERFLOW_BY_SECONDS);
        XTESTS_RUN_CASE(TEST_doomgram_OVERFLOW_BY_MICROSECONDS);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_doomgram_INITIALISE_0(void)
{
    diagnosticism_doomgram_t dg = { 0 };

    TEST_INT_EQ(0, dg.event_count);
    TEST_INT_EQ(0, dg.total_event_time_ns);
    TEST_INT_EQ(0, dg.min_event_time_ns);
    TEST_INT_EQ(0, dg.max_event_time_ns);
    TEST_INT_EQ(0, dg.event_count);
    TEST_INT_EQ(0, dg.oom_event_counts[ 0]);
    TEST_INT_EQ(0, dg.oom_event_counts[ 1]);
    TEST_INT_EQ(0, dg.oom_event_counts[ 2]);
    TEST_INT_EQ(0, dg.oom_event_counts[ 3]);
    TEST_INT_EQ(0, dg.oom_event_counts[ 4]);
    TEST_INT_EQ(0, dg.oom_event_counts[ 5]);
    TEST_INT_EQ(0, dg.oom_event_counts[ 6]);
    TEST_INT_EQ(0, dg.oom_event_counts[ 7]);
    TEST_INT_EQ(0, dg.oom_event_counts[ 8]);
    TEST_INT_EQ(0, dg.oom_event_counts[ 9]);
    TEST_INT_EQ(0, dg.oom_event_counts[10]);
    TEST_INT_EQ(0, dg.oom_event_counts[11]);
    TEST_BOOLEAN_FALSE(dg.has_overflowed);
}

static void TEST_doomgram_INITIALISE_1(void)
{
    diagnosticism_doomgram_t dg = DIAGNOSTICISM_DOOMGRAM_INITIALIZER;

    TEST_INT_EQ(0, dg.event_count);
    TEST_INT_EQ(0, dg.total_event_time_ns);
    TEST_INT_EQ(0, dg.min_event_time_ns);
    TEST_INT_EQ(0, dg.max_event_time_ns);
    TEST_INT_EQ(0, dg.event_count);
    TEST_INT_EQ(0, dg.oom_event_counts[ 0]);
    TEST_INT_EQ(0, dg.oom_event_counts[ 1]);
    TEST_INT_EQ(0, dg.oom_event_counts[ 2]);
    TEST_INT_EQ(0, dg.oom_event_counts[ 3]);
    TEST_INT_EQ(0, dg.oom_event_counts[ 4]);
    TEST_INT_EQ(0, dg.oom_event_counts[ 5]);
    TEST_INT_EQ(0, dg.oom_event_counts[ 6]);
    TEST_INT_EQ(0, dg.oom_event_counts[ 7]);
    TEST_INT_EQ(0, dg.oom_event_counts[ 8]);
    TEST_INT_EQ(0, dg.oom_event_counts[ 9]);
    TEST_INT_EQ(0, dg.oom_event_counts[10]);
    TEST_INT_EQ(0, dg.oom_event_counts[11]);
    TEST_BOOLEAN_FALSE(dg.has_overflowed);
}

static void TEST_doomgram_SINGLE_TIMING_EVENT(void)
{
    diagnosticism_doomgram_t    dg  =   DIAGNOSTICISM_DOOMGRAM_INITIALIZER;
    uint64_t                    v;

#if 0

    fprintf(stderr, "%s:%d:%s: before ", __STLSOFT_FILE_LINE_FUNCTION__);
    diagnosticism_doomgram_dump_to_stream(stderr, &dg, "dg");
    fprintf(stderr, "\n");
#endif

    diagnosticism_doomgram_push_event_time_ms(&dg, 13);

#if 0

    fprintf(stderr, "%s:%d:%s: after ", __STLSOFT_FILE_LINE_FUNCTION__);
    diagnosticism_doomgram_dump_to_stream(stderr, &dg, "dg");
    fprintf(stderr, "\n");
#endif

    TEST_BOOLEAN_FALSE(dg.has_overflowed);

    TEST_INTEGER_EQUAL(1, dg.event_count);
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_total_event_time_ns(&dg, NULL));
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_total_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(13000000u, v);
    TEST_INTEGER_EQUAL(13000000u, diagnosticism_doomgram_try_get_total_event_time_ns_raw(&dg));
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_min_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(13000000, v);
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_max_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(13000000u, v);
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_1ns(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_10ns(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_100ns(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_1us(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_10us(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_100us(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_1ms(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_10ms(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_100ms(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_1s(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_10s(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_ge_100s(&dg));

    {
        char    strip[12];

        diagnosticism_doomgram_to_strip_12(&dg, &strip);

        TEST_MULTIBYTE_STRING_EQUAL_N("_______a____", strip, 12);
    }
}

static void TEST_doomgram_ZERO_TIME_EVENTS(void)
{
    diagnosticism_doomgram_t    dg  =   DIAGNOSTICISM_DOOMGRAM_INITIALIZER;
    uint64_t                    v;

    diagnosticism_doomgram_push_event_time_ns(&dg, 0);
    diagnosticism_doomgram_push_event_time_us(&dg, 0);
    diagnosticism_doomgram_push_event_time_ms(&dg, 0);
    diagnosticism_doomgram_push_event_time_s(&dg, 0);

    TEST_BOOLEAN_FALSE(dg.has_overflowed);

    TEST_INTEGER_EQUAL(4, dg.event_count);
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_total_event_time_ns(&dg, NULL));
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_total_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(0, v);
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_try_get_total_event_time_ns_raw(&dg));
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_min_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(0, v);
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_max_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(0, v);
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_1ns(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_10ns(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_100ns(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_1us(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_10us(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_100us(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_1ms(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_10ms(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_100ms(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_1s(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_10s(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_ge_100s(&dg));

    {
        char    strip[12];

        diagnosticism_doomgram_to_strip_12(&dg, &strip);

        TEST_MULTIBYTE_STRING_EQUAL_N("____________", strip, 12);
    }
}

static void TEST_doomgram_UNIFORM_SPREAD_TIMINGS_1(void)
{
    diagnosticism_doomgram_t    dg  =   DIAGNOSTICISM_DOOMGRAM_INITIALIZER;
    uint64_t                    v;

    diagnosticism_doomgram_push_event_time_ns(&dg,   9);
    diagnosticism_doomgram_push_event_time_ns(&dg,  80);
    diagnosticism_doomgram_push_event_time_ns(&dg, 700);
    diagnosticism_doomgram_push_event_time_us(&dg,   6);
    diagnosticism_doomgram_push_event_time_us(&dg,  50);
    diagnosticism_doomgram_push_event_time_us(&dg, 400);
    diagnosticism_doomgram_push_event_time_ms(&dg,   3);
    diagnosticism_doomgram_push_event_time_ms(&dg,  20);
    diagnosticism_doomgram_push_event_time_ms(&dg, 100);
    diagnosticism_doomgram_push_event_time_s(&dg,    9);
    diagnosticism_doomgram_push_event_time_s(&dg,   80);
    diagnosticism_doomgram_push_event_time_s(&dg,  700);


    TEST_BOOLEAN_FALSE(dg.has_overflowed);

    TEST_INTEGER_EQUAL(12, dg.event_count);
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_total_event_time_ns(&dg, NULL));
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_total_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(789123456789u, v);
    TEST_INTEGER_EQUAL(789123456789u, diagnosticism_doomgram_try_get_total_event_time_ns_raw(&dg));
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_min_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(9, v);
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_max_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(700000000000u, v);
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_1ns(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_10ns(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_100ns(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_1us(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_10us(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_100us(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_1ms(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_10ms(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_100ms(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_1s(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_10s(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_ge_100s(&dg));

    {
        char    strip[12];

        diagnosticism_doomgram_to_strip_12(&dg, &strip);

        TEST_MULTIBYTE_STRING_EQUAL_N("aaaaaaaaaaaa", strip, 12);
    }
}

static void TEST_doomgram_UNIFORM_SPREAD_TIMINGS_2(void)
{
    diagnosticism_doomgram_t    dg  =   DIAGNOSTICISM_DOOMGRAM_INITIALIZER;
    uint64_t                    v;

    diagnosticism_doomgram_push_event_time_ns(&dg,      9);
    diagnosticism_doomgram_push_event_time_ns(&dg,     80);
    diagnosticism_doomgram_push_event_time_ns(&dg,    700);
    diagnosticism_doomgram_push_event_time_ns(&dg,   6000);
    diagnosticism_doomgram_push_event_time_ns(&dg,  50000);
    diagnosticism_doomgram_push_event_time_ns(&dg, 400000);
    diagnosticism_doomgram_push_event_time_ms(&dg,      3);
    diagnosticism_doomgram_push_event_time_ms(&dg,     20);
    diagnosticism_doomgram_push_event_time_ms(&dg,    100);
    diagnosticism_doomgram_push_event_time_ms(&dg,   9000);
    diagnosticism_doomgram_push_event_time_ms(&dg,  80000);
    diagnosticism_doomgram_push_event_time_ms(&dg, 700000);


    TEST_BOOLEAN_FALSE(dg.has_overflowed);

    TEST_INTEGER_EQUAL(12, dg.event_count);
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_total_event_time_ns(&dg, NULL));
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_total_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(789123456789u, v);
    TEST_INTEGER_EQUAL(789123456789u, diagnosticism_doomgram_try_get_total_event_time_ns_raw(&dg));
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_min_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(9, v);
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_max_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(700000000000u, v);
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_1ns(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_10ns(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_100ns(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_1us(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_10us(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_100us(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_1ms(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_10ms(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_100ms(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_1s(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_10s(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_ge_100s(&dg));

    {
        char    strip[12];

        diagnosticism_doomgram_to_strip_12(&dg, &strip);

        TEST_MULTIBYTE_STRING_EQUAL_N("aaaaaaaaaaaa", strip, 12);
    }
}

static void TEST_doomgram_UNIFORM_SPREAD_TIMINGS_3(void)
{
    diagnosticism_doomgram_t    dg  =   DIAGNOSTICISM_DOOMGRAM_INITIALIZER;
    uint64_t                    v;

    diagnosticism_doomgram_push_event_time_ns(&dg,            9);
    diagnosticism_doomgram_push_event_time_ns(&dg,           80);
    diagnosticism_doomgram_push_event_time_ns(&dg,          700);
    diagnosticism_doomgram_push_event_time_ns(&dg,         6000);
    diagnosticism_doomgram_push_event_time_ns(&dg,        50000);
    diagnosticism_doomgram_push_event_time_ns(&dg,       400000);
    diagnosticism_doomgram_push_event_time_ns(&dg,      3000000);
    diagnosticism_doomgram_push_event_time_ns(&dg,     20000000);
    diagnosticism_doomgram_push_event_time_ns(&dg,    100000000);
    diagnosticism_doomgram_push_event_time_ns(&dg,   9000000000);
    diagnosticism_doomgram_push_event_time_ns(&dg,  80000000000);
    diagnosticism_doomgram_push_event_time_ns(&dg, 700000000000);


    TEST_BOOLEAN_FALSE(dg.has_overflowed);

    TEST_INTEGER_EQUAL(12, dg.event_count);
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_total_event_time_ns(&dg, NULL));
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_total_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(789123456789u, v);
    TEST_INTEGER_EQUAL(789123456789u, diagnosticism_doomgram_try_get_total_event_time_ns_raw(&dg));
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_min_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(9, v);
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_max_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(700000000000u, v);
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_1ns(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_10ns(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_100ns(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_1us(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_10us(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_100us(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_1ms(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_10ms(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_100ms(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_1s(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_10s(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_ge_100s(&dg));

    {
        char    strip[12];

        diagnosticism_doomgram_to_strip_12(&dg, &strip);

        TEST_MULTIBYTE_STRING_EQUAL_N("aaaaaaaaaaaa", strip, 12);
    }
}

static void TEST_doomgram_UNIFORM_SPREAD_TIMINGS_4(void)
{
    diagnosticism_doomgram_t    dg  =   DIAGNOSTICISM_DOOMGRAM_INITIALIZER;
    uint64_t                    v;

    diagnosticism_doomgram_push_event_time_us(&dg,         6);
    diagnosticism_doomgram_push_event_time_us(&dg,        50);
    diagnosticism_doomgram_push_event_time_us(&dg,       400);
    diagnosticism_doomgram_push_event_time_us(&dg,      3000);
    diagnosticism_doomgram_push_event_time_us(&dg,     20000);
    diagnosticism_doomgram_push_event_time_us(&dg,    100000);
    diagnosticism_doomgram_push_event_time_us(&dg,   9000000);
    diagnosticism_doomgram_push_event_time_us(&dg,  80000000);
    diagnosticism_doomgram_push_event_time_us(&dg, 700000000);


    TEST_BOOLEAN_FALSE(dg.has_overflowed);

    TEST_INTEGER_EQUAL(9, dg.event_count);
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_total_event_time_ns(&dg, NULL));
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_total_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(789123456000u, v);
    TEST_INTEGER_EQUAL(789123456000u, diagnosticism_doomgram_try_get_total_event_time_ns_raw(&dg));
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_min_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(6000, v);
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_max_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(700000000000u, v);
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_1ns(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_10ns(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_100ns(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_1us(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_10us(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_100us(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_1ms(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_10ms(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_100ms(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_1s(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_10s(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_ge_100s(&dg));

    {
        char    strip[12];

        diagnosticism_doomgram_to_strip_12(&dg, &strip);

        TEST_MULTIBYTE_STRING_EQUAL_N("___aaaaaaaaa", strip, 12);
    }
}

static void TEST_doomgram_SEVERAL_DISTINCT_TIMINGS(void)
{
    diagnosticism_doomgram_t    dg  =   DIAGNOSTICISM_DOOMGRAM_INITIALIZER;
    uint64_t                    v;

    diagnosticism_doomgram_push_event_time_ns(&dg, 23);
    diagnosticism_doomgram_push_event_time_ns(&dg, 10);
    diagnosticism_doomgram_push_event_time_us(&dg, 7);
    diagnosticism_doomgram_push_event_time_us(&dg, 7);
    diagnosticism_doomgram_push_event_time_us(&dg, 89);
    diagnosticism_doomgram_push_event_time_ms(&dg, 248);
    diagnosticism_doomgram_push_event_time_s(&dg, 5);
    diagnosticism_doomgram_push_event_time_s(&dg, 309);


    TEST_BOOLEAN_FALSE(dg.has_overflowed);

    TEST_INTEGER_EQUAL(8, dg.event_count);
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_total_event_time_ns(&dg, NULL));
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_total_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(314248103033u, v);
    TEST_INTEGER_EQUAL(314248103033u, diagnosticism_doomgram_try_get_total_event_time_ns_raw(&dg));
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_min_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(10, v);
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_max_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(309000000000u, v);
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_1ns(&dg));
    TEST_INTEGER_EQUAL(2, diagnosticism_doomgram_num_events_in_10ns(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_100ns(&dg));
    TEST_INTEGER_EQUAL(2, diagnosticism_doomgram_num_events_in_1us(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_10us(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_100us(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_1ms(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_10ms(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_100ms(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_1s(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_10s(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_ge_100s(&dg));

    {
        char    strip[12];

        diagnosticism_doomgram_to_strip_12(&dg, &strip);

        TEST_MULTIBYTE_STRING_EQUAL_N("_a_aa___aa_a", strip, 12);
    }
}

static void TEST_doomgram_SEVERAL_INTERSECTING_TIMINGS(void)
{
    diagnosticism_doomgram_t    dg  =   DIAGNOSTICISM_DOOMGRAM_INITIALIZER;
    uint64_t                    v;

    diagnosticism_doomgram_push_event_time_ns(&dg, 11);
    diagnosticism_doomgram_push_event_time_ns(&dg, 19);
    diagnosticism_doomgram_push_event_time_ns(&dg, 19);
    diagnosticism_doomgram_push_event_time_us(&dg, 7);
    diagnosticism_doomgram_push_event_time_us(&dg, 7);
    diagnosticism_doomgram_push_event_time_us(&dg, 89);
    diagnosticism_doomgram_push_event_time_ms(&dg, 248);
    diagnosticism_doomgram_push_event_time_ms(&dg, 4321);
    diagnosticism_doomgram_push_event_time_s(&dg, 5);
    diagnosticism_doomgram_push_event_time_s(&dg, 309);

    TEST_BOOLEAN_FALSE(dg.has_overflowed);

    TEST_INTEGER_EQUAL(10, dg.event_count);
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_total_event_time_ns(&dg, NULL));
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_total_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(318569103049u, v);
    TEST_INTEGER_EQUAL(318569103049u, diagnosticism_doomgram_try_get_total_event_time_ns_raw(&dg));
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_min_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(11, v);
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_max_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(309000000000u, v);
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_1ns(&dg));
    TEST_INTEGER_EQUAL(3, diagnosticism_doomgram_num_events_in_10ns(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_100ns(&dg));
    TEST_INTEGER_EQUAL(2, diagnosticism_doomgram_num_events_in_1us(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_10us(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_100us(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_1ms(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_10ms(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_in_100ms(&dg));
    TEST_INTEGER_EQUAL(2, diagnosticism_doomgram_num_events_in_1s(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_10s(&dg));
    TEST_INTEGER_EQUAL(1, diagnosticism_doomgram_num_events_ge_100s(&dg));

    {
        char    strip[12];

        diagnosticism_doomgram_to_strip_12(&dg, &strip);

        TEST_MULTIBYTE_STRING_EQUAL_N("_a_aa___aa_a", strip, 12);
    }
}

static void TEST_doomgram_MANY_CUMULATIVE_TIMINGS(void)
{
    diagnosticism_doomgram_t    dg  =   DIAGNOSTICISM_DOOMGRAM_INITIALIZER;
    uint64_t                    v;

    { for (int i = 0; 10000 != i; ++i)
    {
        diagnosticism_doomgram_push_event_time_ns(&dg, 1);
    }}

    { for (int i = 0; 1000 != i; ++i)
    {
        diagnosticism_doomgram_push_event_time_us(&dg, 1);
    }}

    { for (int i = 0; 100 != i; ++i)
    {
        diagnosticism_doomgram_push_event_time_ms(&dg, 1);
    }}

    { for (int i = 0; 10 != i; ++i)
    {
        diagnosticism_doomgram_push_event_time_s(&dg, 1);
    }}

    TEST_BOOLEAN_FALSE(dg.has_overflowed);

    TEST_INTEGER_EQUAL(11110, dg.event_count);
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_total_event_time_ns(&dg, NULL));
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_total_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(10101010000u, v);
    TEST_INTEGER_EQUAL(10101010000u, diagnosticism_doomgram_try_get_total_event_time_ns_raw(&dg));
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_min_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(1, v);
    TEST_BOOLEAN_TRUE(diagnosticism_doomgram_try_get_max_event_time_ns(&dg, &v));
    TEST_INTEGER_EQUAL(1000000000u, v);
    TEST_INTEGER_EQUAL(10000, diagnosticism_doomgram_num_events_in_1ns(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_10ns(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_100ns(&dg));
    TEST_INTEGER_EQUAL(1000, diagnosticism_doomgram_num_events_in_1us(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_10us(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_100us(&dg));
    TEST_INTEGER_EQUAL(100, diagnosticism_doomgram_num_events_in_1ms(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_10ms(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_100ms(&dg));
    TEST_INTEGER_EQUAL(10, diagnosticism_doomgram_num_events_in_1s(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_in_10s(&dg));
    TEST_INTEGER_EQUAL(0, diagnosticism_doomgram_num_events_ge_100s(&dg));

    {
        char    strip[12];

        diagnosticism_doomgram_to_strip_12(&dg, &strip);

        TEST_MULTIBYTE_STRING_EQUAL_N("e__d__c__b__", strip, 12);
    }
}

static void TEST_doomgram_OVERFLOW_BY_SECONDS(void)
{
    diagnosticism_doomgram_t dg = DIAGNOSTICISM_DOOMGRAM_INITIALIZER;


    // uint64 max:
    //
    // 18,446,744,073,709,551,615 ns
    //     18,446,744,073,709,551 µs
    //         18,446,744,073,709 ms
    //             18,446,744,073  s

    // 18446744073 max

    // add in max # seconds
    {
        bool r = diagnosticism_doomgram_push_event_time_s(&dg, 18446744073);

        TEST_BOOLEAN_TRUE(r);
    }

    // add in 0 more
    {
        bool r = diagnosticism_doomgram_push_event_time_s(&dg, 0);

        TEST_BOOLEAN_TRUE(r);
    }

    // add in 1 more to overflow
    {
        bool r = diagnosticism_doomgram_push_event_time_s(&dg, 1);

        TEST_BOOLEAN_FALSE(r);
    }
}

static void TEST_doomgram_OVERFLOW_BY_MICROSECONDS(void)
{
    diagnosticism_doomgram_t dg = DIAGNOSTICISM_DOOMGRAM_INITIALIZER;



    // uint64 max:
    //
    // 18,446,744,073,709,551,615 ns
    //     18,446,744,073,709,551 µs
    //         18,446,744,073,709 ms
    //             18,446,744,073  s

    // 18446744073 max

    // add in max-1 # microseconds
    {
        bool r = diagnosticism_doomgram_push_event_time_us(&dg, 18446744073709550);

        TEST_BOOLEAN_TRUE(r);
    }

    // add in 1 more to max
    {
        bool r = diagnosticism_doomgram_push_event_time_us(&dg, 1);

        TEST_BOOLEAN_TRUE(r);
    }

    // add in 0 more
    {
        bool r = diagnosticism_doomgram_push_event_time_us(&dg, 0);

        TEST_BOOLEAN_TRUE(r);
    }

    // add in 1 more to overflow
    {
        bool r = diagnosticism_doomgram_push_event_time_us(&dg, 1);

        TEST_BOOLEAN_FALSE(r);
    }
}


/* ///////////////////////////// end of file //////////////////////////// */

