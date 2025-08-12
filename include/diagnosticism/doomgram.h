
#include <diagnosticism/diagnosticism.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


/* /////////////////////////////////////////////////////////////////////////
 * API types
 */

/** Decimal Order-Of-Magnitude frequency histoGRAM
 *
 * \note This is a C port of the equivalent `stlsoft::doomgram` class from
 * the **STLSoft** libraries
 * (https://github.com/synesissoftware/STLSoft-1.11).
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
typedef struct diagnosticism_doomgram_t                     diagnosticism_doomgram_t;
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


/** Attempts to obtain the total event time (in nanoseconds), which may be
 * fail if overflow has occurred.
 *
 * \param dg The doomgram whose value is to be elicited;
 * \param value Pointer to a variable into which the value is to be written;
 *
 * @pre NULL != dg
 */
DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_try_get_total_event_time_ns(
    diagnosticism_doomgram_t*   dg
,   uint64_t*                   value
);

/** \def diagnosticism_doomgram_try_get_total_event_time_ns_raw(dg)
 *
 * Obtains the total event time (in nanoseconds) without consideration as to
 * whether overflow has occurred.
 *
 * \param dg The doomgram whose value is to be elicited;
 */
#define diagnosticism_doomgram_try_get_total_event_time_ns_raw(pdg)         ((pdg)->total_event_time_ns)

/** Attempts to obtain the minimum event time (in nanoseconds), which may be
 * fail if overflow has occurred.
 *
 * \param dg The doomgram whose value is to be elicited;
 * \param value Pointer to a variable into which the value is to be written;
 *
 * @pre NULL != dg
 */
DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_try_get_min_event_time_ns(
    diagnosticism_doomgram_t*   dg
,   uint64_t*                   value
);

/** Attempts to obtain the maximum event time (in nanoseconds), which may be
 * fail if overflow has occurred.
 *
 * \param dg The doomgram whose value is to be elicited;
 * \param value Pointer to a variable into which the value is to be written;
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

/** Converts to string form according to given options.
 *
 * \param dg The doomgram whose value is to be elicited;
 * \param ar Array of 12 characters into which to write the results;
 */
DIAGNOSTICISM_CALL(char const*)
diagnosticism_doomgram_to_strip_12(
    diagnosticism_doomgram_t*   dg
,   char                      (*ar)[12]
);


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#pragma once

/* ///////////////////////////// end of file //////////////////////////// */

