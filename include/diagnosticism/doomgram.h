
#include <diagnosticism/diagnosticism.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


/* /////////////////////////////////////////////////////////////////////////
 * API types
 */

/** T.B.C.
 *
 *
 */
struct diagnosticism_doomgram_t
{
    uint64_t    event_count;
    uint64_t    total_event_time_ns;
    uint64_t    min_event_time_ns;
    uint64_t    max_event_time_ns;
    uint64_t    oom_event_counts[12];
    bool        has_overflowed;
};
#ifndef __cplusplus
typedef struct diagnosticism_doomgram_t diagnosticism_doomgram_t;
#endif

#define DIAGNOSTICISM_DOOMGRAM_INITIALIZER                          \
                                                                    \
    {                                                               \
        .event_count = 0,                                           \
        .total_event_time_ns = 0,                                   \
        .min_event_time_ns = 0,                                     \
        .max_event_time_ns = 0,                                     \
        .oom_event_counts = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },  \
        .has_overflowed = 0,                                        \
    }


/* /////////////////////////////////////////////////////////////////////////
 * API functions & macros
 */

/** Pushes an event with the given number of nanoseconds. */
DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_push_event_time_ns(
    diagnosticism_doomgram_t*   dg
,   uint64_t                    time_in_ns
);
/** Pushes an event with the given number of microseconds. */
DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_push_event_time_us(
    diagnosticism_doomgram_t*   dg
,   uint64_t                    time_in_us
);
/** Pushes an event with the given number of milliseconds. */
DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_push_event_time_ms(
    diagnosticism_doomgram_t*   dg
,   uint64_t                    time_in_ms
);
/** Pushes an event with the given number of seconds. */
DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_push_event_time_s(
    diagnosticism_doomgram_t*   dg
,   uint64_t                    time_in_s
);


#define diagnosticism_doomgram_num_events_in_1ns(pdg)       ((pdg)->oom_event_counts[ 0])
#define diagnosticism_doomgram_num_events_in_10ns(pdg)      ((pdg)->oom_event_counts[ 1])
#define diagnosticism_doomgram_num_events_in_100ns(pdg)     ((pdg)->oom_event_counts[ 2])
#define diagnosticism_doomgram_num_events_in_1us(pdg)       ((pdg)->oom_event_counts[ 3])
#define diagnosticism_doomgram_num_events_in_10us(pdg)      ((pdg)->oom_event_counts[ 4])
#define diagnosticism_doomgram_num_events_in_100us(pdg)     ((pdg)->oom_event_counts[ 5])
#define diagnosticism_doomgram_num_events_in_1ms(pdg)       ((pdg)->oom_event_counts[ 6])
#define diagnosticism_doomgram_num_events_in_10ms(pdg)      ((pdg)->oom_event_counts[ 7])
#define diagnosticism_doomgram_num_events_in_100ms(pdg)     ((pdg)->oom_event_counts[ 8])
#define diagnosticism_doomgram_num_events_in_1s(pdg)        ((pdg)->oom_event_counts[ 9])
#define diagnosticism_doomgram_num_events_in_10s(pdg)       ((pdg)->oom_event_counts[10])
#define diagnosticism_doomgram_num_events_ge_100s(pdg)      ((pdg)->oom_event_counts[11])


/**
 *
 * @pre NULL != dg
 */
DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_try_get_total_event_time_ns(
    diagnosticism_doomgram_t*   dg
,   uint64_t*                   value
);

#define diagnosticism_doomgram_try_get_total_event_time_ns_raw(pdg)         ((pdg)->total_event_time_ns)

/**
 *
 * @pre NULL != dg
 */
DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_try_get_min_event_time_ns(
    diagnosticism_doomgram_t*   dg
,   uint64_t*                   value
);

/**
 *
 * @pre NULL != dg
 */
DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_try_get_max_event_time_ns(
    diagnosticism_doomgram_t*   dg
,   uint64_t*                   value
);


#ifndef DIAGNOSTICISM_DOCUMENTATION_SKIP_SECTION

DIAGNOSTICISM_CALL(int)
diagnosticism_doomgram_dump_to_stream(
    FILE*                       stm
,   diagnosticism_doomgram_t*   dg
,   char const*                 var_name
);
#endif /* !DIAGNOSTICISM_DOCUMENTATION_SKIP_SECTION */


#pragma once


/* ///////////////////////////// end of file //////////////////////////// */

