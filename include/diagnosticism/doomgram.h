
/** @file diagnosticism/doomgram.h
 * @brief Decimal order-of-magnitude timing histogram (DoomGram).
 *
 * @see @ref doomgram_page "DoomGram overview"
 *
 * @defgroup diagnosticism_doomgram DoomGram
 * @{
 */

#include <diagnosticism/diagnosticism.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


/* /////////////////////////////////////////////////////////////////////////
 * API types
 */

/** Decimal Order-Of-Magnitude frequency histoGRAM.
 *
 * Records timing events into twelve magnitude buckets (1ns+ through 100s+)
 * and can summarise the distribution in a 12-character strip via
 * diagnosticism_doomgram_to_strip_12().
 *
 * @note Instances are not thread-safe; callers must provide external
 *  synchronisation if a doomgram is shared between threads.
 *
 * @see @ref doomgram_page "DoomGram overview"
 * @see diagnosticism_doomgram_to_strip_12()
 *
 * This is a C port of the equivalent `stlsoft::doomgram` class from
 * [STLSoft](https://github.com/synesissoftware/STLSoft-1.11).
 */
struct diagnosticism_doomgram_t
{
    uint64_t    event_count;            /**< Total number of recorded events. */
    uint64_t    total_event_time_ns;    /**< Cumulative event time in nanoseconds. */
    uint64_t    min_event_time_ns;      /**< Minimum recorded event time in nanoseconds. */
    uint64_t    max_event_time_ns;      /**< Maximum recorded event time in nanoseconds. */
    uint64_t    oom_event_counts[12];   /**< Per-bucket event counts (see @ref doomgram_page). */
    bool        has_overflowed;         /**< Set when cumulative time would overflow `uint64_t`. */
};
#ifndef __cplusplus
typedef struct diagnosticism_doomgram_t                     diagnosticism_doomgram_t;
#endif

/** @def DIAGNOSTICISM_DOOMGRAM_INITIALIZER
 * @brief Brace initialiser for a zeroed diagnosticism_doomgram_t instance.
 */
#define DIAGNOSTICISM_DOOMGRAM_INITIALIZER                          \
                                                                    \
    {                                                               \
        .event_count = 0,                                           \
        .total_event_time_ns = 0,                                   \
        .min_event_time_ns = 0,                                     \
        .max_event_time_ns = 0,                                     \
        .oom_event_counts = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, \
        .has_overflowed = 0,                                        \
    }


/* /////////////////////////////////////////////////////////////////////////
 * API functions & macros
 */

/** Resets all fields of the doomgram to their initial state.
 *
 * @param dg The doomgram to clear.
 *
 * @pre NULL != dg
 */
DIAGNOSTICISM_CALL(void)
diagnosticism_doomgram_clear(
    diagnosticism_doomgram_t*   dg
);

/** Pushes an event with the given duration in nanoseconds.
 *
 * @param dg The doomgram to update.
 * @param time_in_ns Event duration in nanoseconds.
 *
 * @return `true` on success, or `false` if cumulative time would overflow.
 *
 * @pre NULL != dg
 */
DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_push_event_time_ns(
    diagnosticism_doomgram_t*   dg
,   uint64_t                    time_in_ns
);

/** Pushes an event with the given duration in microseconds.
 *
 * @param dg The doomgram to update.
 * @param time_in_us Event duration in microseconds.
 *
 * @return `true` on success, or `false` if cumulative time would overflow.
 *
 * @pre NULL != dg
 */
DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_push_event_time_us(
    diagnosticism_doomgram_t*   dg
,   uint64_t                    time_in_us
);

/** Pushes an event with the given duration in milliseconds.
 *
 * @param dg The doomgram to update.
 * @param time_in_ms Event duration in milliseconds.
 *
 * @return `true` on success, or `false` if cumulative time would overflow.
 *
 * @pre NULL != dg
 */
DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_push_event_time_ms(
    diagnosticism_doomgram_t*   dg
,   uint64_t                    time_in_ms
);

/** Pushes an event with the given duration in seconds.
 *
 * @param dg The doomgram to update.
 * @param time_in_s Event duration in seconds.
 *
 * @return `true` on success, or `false` if cumulative time would overflow.
 *
 * @pre NULL != dg
 */
DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_push_event_time_s(
    diagnosticism_doomgram_t*   dg
,   uint64_t                    time_in_s
);


#define diagnosticism_doomgram_num_events_in_1ns(pdg)       ((pdg)->oom_event_counts[ 0])

/** @def diagnosticism_doomgram_num_events_in_10ns(pdg)
 * @brief Event count in the 10ns+ magnitude bucket.
 */
#define diagnosticism_doomgram_num_events_in_10ns(pdg)      ((pdg)->oom_event_counts[ 1])

/** @def diagnosticism_doomgram_num_events_in_100ns(pdg)
 * @brief Event count in the 100ns+ magnitude bucket.
 */
#define diagnosticism_doomgram_num_events_in_100ns(pdg)     ((pdg)->oom_event_counts[ 2])

/** @def diagnosticism_doomgram_num_events_in_1us(pdg)
 * @brief Event count in the 1µs+ magnitude bucket.
 */
#define diagnosticism_doomgram_num_events_in_1us(pdg)       ((pdg)->oom_event_counts[ 3])

/** @def diagnosticism_doomgram_num_events_in_10us(pdg)
 * @brief Event count in the 10µs+ magnitude bucket.
 */
#define diagnosticism_doomgram_num_events_in_10us(pdg)      ((pdg)->oom_event_counts[ 4])

/** @def diagnosticism_doomgram_num_events_in_100us(pdg)
 * @brief Event count in the 100µs+ magnitude bucket.
 */
#define diagnosticism_doomgram_num_events_in_100us(pdg)     ((pdg)->oom_event_counts[ 5])

/** @def diagnosticism_doomgram_num_events_in_1ms(pdg)
 * @brief Event count in the 1ms+ magnitude bucket.
 */
#define diagnosticism_doomgram_num_events_in_1ms(pdg)       ((pdg)->oom_event_counts[ 6])

/** @def diagnosticism_doomgram_num_events_in_10ms(pdg)
 * @brief Event count in the 10ms+ magnitude bucket.
 */
#define diagnosticism_doomgram_num_events_in_10ms(pdg)      ((pdg)->oom_event_counts[ 7])

/** @def diagnosticism_doomgram_num_events_in_100ms(pdg)
 * @brief Event count in the 100ms+ magnitude bucket.
 */
#define diagnosticism_doomgram_num_events_in_100ms(pdg)     ((pdg)->oom_event_counts[ 8])

/** @def diagnosticism_doomgram_num_events_in_1s(pdg)
 * @brief Event count in the 1s+ magnitude bucket.
 */
#define diagnosticism_doomgram_num_events_in_1s(pdg)        ((pdg)->oom_event_counts[ 9])

/** @def diagnosticism_doomgram_num_events_in_10s(pdg)
 * @brief Event count in the 10s+ magnitude bucket.
 */
#define diagnosticism_doomgram_num_events_in_10s(pdg)       ((pdg)->oom_event_counts[10])

/** @def diagnosticism_doomgram_num_events_ge_100s(pdg)
 * @brief Event count in the 100s+ magnitude bucket.
 */
#define diagnosticism_doomgram_num_events_ge_100s(pdg)      ((pdg)->oom_event_counts[11])


/** Attempts to obtain the total event time in nanoseconds.
 *
 * @param dg The doomgram whose value is to be elicited.
 * @param value Pointer to a variable into which the value is written.
 *
 * @return `true` on success, or `false` if overflow has occurred.
 *
 * @pre NULL != dg
 * @pre NULL != value
 */
DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_try_get_total_event_time_ns(
    diagnosticism_doomgram_t*   dg
,   uint64_t*                   value
);

/** @def diagnosticism_doomgram_try_get_total_event_time_ns_raw(pdg)
 *
 * @brief Obtains the total event time in nanoseconds without regard to overflow.
 *
 * @param pdg The doomgram whose value is to be elicited.
 */
#define diagnosticism_doomgram_try_get_total_event_time_ns_raw(pdg)         ((pdg)->total_event_time_ns)

/** Attempts to obtain the minimum event time in nanoseconds.
 *
 * @param dg The doomgram whose value is to be elicited.
 * @param value Pointer to a variable into which the value is written.
 *
 * @return `true` on success, or `false` if overflow has occurred.
 *
 * @pre NULL != dg
 * @pre NULL != value
 */
DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_try_get_min_event_time_ns(
    diagnosticism_doomgram_t*   dg
,   uint64_t*                   value
);

/** Attempts to obtain the maximum event time in nanoseconds.
 *
 * @param dg The doomgram whose value is to be elicited.
 * @param value Pointer to a variable into which the value is written.
 *
 * @return `true` on success, or `false` if overflow has occurred.
 *
 * @pre NULL != dg
 * @pre NULL != value
 */
DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_try_get_max_event_time_ns(
    diagnosticism_doomgram_t*   dg
,   uint64_t*                   value
);


#ifndef DIAGNOSTICISM_DOCUMENTATION_SKIP_SECTION

/** Writes a textual dump of the doomgram to a stream (primarily for debugging).
 *
 * @param stm Output stream.
 * @param dg The doomgram to dump.
 * @param var_name Name to use for the variable in the output.
 *
 * @return Non-negative value on success, or negative on failure.
 *
 * @pre NULL != stm
 * @pre NULL != dg
 * @pre NULL != var_name
 */
DIAGNOSTICISM_CALL(int)
diagnosticism_doomgram_dump_to_stream(
    FILE*                       stm
,   diagnosticism_doomgram_t*   dg
,   char const*                 var_name
);
#endif /* !DIAGNOSTICISM_DOCUMENTATION_SKIP_SECTION */

/** Writes a 12-character histogram strip summarising the magnitude distribution.
 *
 * Each character encodes the event count in one bucket: `_` for zero,
 * `a`–`z` for increasing ranges, and `*` when a bucket exceeds the
 * representable range. See @ref doomgram_page for details.
 *
 * @param dg The doomgram whose distribution is to be summarised.
 * @param ar Array of 12 characters into which to write the strip.
 *
 * @return Pointer to the first element of @a ar.
 *
 * @pre NULL != dg
 * @pre NULL != ar
 *
 * @snippet doomgram/main.c doomgram_strip
 */
DIAGNOSTICISM_CALL(char const*)
diagnosticism_doomgram_to_strip_12(
    diagnosticism_doomgram_t*   dg
,   char                      (*ar)[12]
);


/** @} */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#pragma once

/* ///////////////////////////// end of file //////////////////////////// */
