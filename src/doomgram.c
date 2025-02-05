
#include <diagnosticism/doomgram.h>

#include <assert.h>
#include <stdatomic.h>


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

bool
try_add_ns_to_total_and_update_minmax_and_count_(
    diagnosticism_doomgram_t*   dg
,   uint64_t                    time_in_ns
)
{
    uint64_t const new_total_event_time_ns = time_in_ns + dg->total_event_time_ns;

    if (new_total_event_time_ns < dg->total_event_time_ns)
    {
        dg->has_overflowed = true;

        return false;
    }
    else
    {
        dg->total_event_time_ns = new_total_event_time_ns;

        if (0 == dg->event_count++)
        {
            dg->min_event_time_ns = time_in_ns;
            dg->max_event_time_ns = time_in_ns;
        }
        else
        {
            if (time_in_ns < dg->min_event_time_ns)
            {
                dg->min_event_time_ns = time_in_ns;
            }

            if (time_in_ns > dg->max_event_time_ns)
            {
                dg->max_event_time_ns = time_in_ns;
            }
        }

        return true;
    }
}


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_push_event_time_ns(
    diagnosticism_doomgram_t*   dg
,   uint64_t                    time_in_ns
)
{
    assert(!m_has_overflowed);

    if (!try_add_ns_to_total_and_update_minmax_and_count_(dg, time_in_ns))
    {
        return false;
    }
    else
    {
        // Algorithm:
        //
        // We assume that most events will be down in the sub-1ms range, so
        // branch accordingly.

        if (0 != (time_in_ns & ~0x3FFFFFFF))
        {
            goto gt_1073741823;
        }

        if (time_in_ns >= 1000000)
        {


            // >= 1ms

            if (time_in_ns >= 1000000000)
            {
gt_1073741823:

                // >= 1s

                if (time_in_ns >= 100000000000)
                {
                    dg->oom_event_counts[11] += 1;
                }
                else if (time_in_ns >= 10000000000)
                {
                    dg->oom_event_counts[10] += 1;
                }
                else
                {
                    dg->oom_event_counts[9] += 1;
                }
            }
            else
            {
                // < 1s

                if (time_in_ns >= 100000000)
                {
                    dg->oom_event_counts[8] += 1;
                }
                else if (time_in_ns >= 10000000)
                {
                    dg->oom_event_counts[7] += 1;
                }
                else
                {
                    dg->oom_event_counts[6] += 1;
                }
            }
        }
        else
        {
            // < 1ms

            if (time_in_ns >= 1000)
            {
                // >= 1µs

                if (time_in_ns >= 100000)
                {
                    dg->oom_event_counts[5] += 1;
                }
                else if (time_in_ns >= 10000)
                {
                    dg->oom_event_counts[4] += 1;
                }
                else
                {
                    dg->oom_event_counts[3] += 1;
                }
            }
            else
            {

                // < 1µs

                if (time_in_ns >= 100)
                {
                    dg->oom_event_counts[2] += 1;
                }
                else if (time_in_ns >= 10)
                {
                    dg->oom_event_counts[1] += 1;
                }
                else if (time_in_ns >= 1)
                {
                    dg->oom_event_counts[0] += 1;
                }
            }
        }

        return true;
    }
}

DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_push_event_time_us(
    diagnosticism_doomgram_t*   dg
,   uint64_t                    time_in_us
)
{
    // TODO: implement separately, since already know µs

    uint64_t const time_in_ns = time_in_us * 1000;

    if (!try_add_ns_to_total_and_update_minmax_and_count_(dg, time_in_ns))
    {
        return false;
    }
    else
    {
        // possible slots:
        //
        // - 1µs
        // - 10µs
        // - 100µs
        // - 1ms
        // - 10ms
        // - 100ms
        // - 1s
        // - 10s
        // - 100s

        if (0 != (time_in_us & ~0xfffff))
        {
            goto ge_fffff;
        }

        if (time_in_us < 1000000)
        {
            if (time_in_us < 1000)
            {
                if (time_in_us >= 100)
                {
                    dg->oom_event_counts[5] += 1;
                }
                else if (time_in_us >= 10)
                {
                    dg->oom_event_counts[4] += 1;
                }
                else if (time_in_us >= 1)
                {
                    dg->oom_event_counts[3] += 1;
                }
            }
            else
            {
                // 1s+

                if (time_in_us >= 100000)
                {
                    dg->oom_event_counts[8] += 1;
                }
                else if (time_in_us >= 10000)
                {
                    dg->oom_event_counts[7] += 1;
                }
                else
                {
                    dg->oom_event_counts[6] += 1;
                }
            }
        }
        else
        {
ge_fffff:

            if (time_in_us >= 100000000)
            {
                dg->oom_event_counts[11] += 1;
            }
            else if (time_in_us >= 10000000)
            {
                dg->oom_event_counts[10] += 1;
            }
            else // if (time_in_us != 0)
            {
                dg->oom_event_counts[9] += 1;
            }
        }

        return true;
    }
}

DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_push_event_time_ms(
    diagnosticism_doomgram_t*   dg
,   uint64_t                    time_in_ms
)
{
    uint64_t const time_in_ns = time_in_ms * 1000000;

    if (!try_add_ns_to_total_and_update_minmax_and_count_(dg, time_in_ns))
    {
        return false;
    }
    else
    {
        // possible slots:
        //
        // - 1ms
        // - 10ms
        // - 100ms
        // - 1s
        // - 10s
        // - 100s

        if (0 != (time_in_ms & ~0x1ffff))
        {
            goto ge_1ffff;
        }

        if (time_in_ms < 1000)
        {
            if (time_in_ms >= 100)
            {
                dg->oom_event_counts[8] += 1;
            }
            else if (time_in_ms >= 10)
            {
                dg->oom_event_counts[7] += 1;
            }
            else if (time_in_ms >= 1)
            {
                dg->oom_event_counts[6] += 1;
            }
        }
        else
        {
            // 1s+

            if (time_in_ms >= 100000)
            {
ge_1ffff:

                dg->oom_event_counts[11] += 1;
            }
            else if (time_in_ms >= 10000)
            {
                dg->oom_event_counts[10] += 1;
            }
            else
            {
                dg->oom_event_counts[9] += 1;
            }
        }

        return true;
    }
}

DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_push_event_time_s(
    diagnosticism_doomgram_t*   dg
,   uint64_t                    time_in_s
)
{
    uint64_t const time_in_ns = time_in_s * 1000000000;

    if (!try_add_ns_to_total_and_update_minmax_and_count_(dg, time_in_ns))
    {
        return false;
    }
    else
    {
        if (time_in_s >= 100)
        {
            dg->oom_event_counts[11] += 1;
        }
        else if (time_in_s >= 10)
        {
            dg->oom_event_counts[10] += 1;
        }
        else if (time_in_s >= 1)
        {
            dg->oom_event_counts[9] += 1;
        }

        return true;
    }
}


DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_try_get_total_event_time_ns(
    diagnosticism_doomgram_t*   dg
,   uint64_t*                   value
)
{
    assert(NULL != dg);

    if (NULL != value)
    {
        *value = dg->total_event_time_ns;
    }

    return !dg->has_overflowed;

}

DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_try_get_min_event_time_ns(
    diagnosticism_doomgram_t*   dg
,   uint64_t*                   value
)
{
    uint64_t dummy;

    assert(NULL != dg);

    if (NULL == value)
    {
        value = &dummy;
    }

    if (0 != dg->event_count)
    {
        *value = dg->min_event_time_ns;

        return true;
    }
    else
    {
        *value = 0;

        return false;
    }
}

DIAGNOSTICISM_CALL(bool)
diagnosticism_doomgram_try_get_max_event_time_ns(
    diagnosticism_doomgram_t*   dg
,   uint64_t*                   value
)
{
    uint64_t dummy;

    assert(NULL != dg);

    if (NULL == value)
    {
        value = &dummy;
    }

    if (0 != dg->event_count)
    {
        *value = dg->max_event_time_ns;

        return true;
    }
    else
    {
        *value = 0;

        return false;
    }
}


DIAGNOSTICISM_CALL(int)
diagnosticism_doomgram_dump_to_stream(
    FILE*                       stm
,   diagnosticism_doomgram_t*   dg
,   char const*                 var_name
)
{
    assert(NULL != dg);

    if (NULL != var_name && '\0' != *var_name)
    {
        return fprintf(stm
        ,   "%s = { \
.event_count=%llu, \
.total_event_time_ns=%llu, \
.min_event_time_ns=%llu, \
.max_event_time_ns=%llu, \
.oom_event_counts = { %llu, %llu, %llu, %llu, %llu, %llu, %llu, %llu, %llu, %llu, %llu, %llu }, \
.has_overflowed=%s \
}"
        ,   var_name
        ,   dg->event_count
        ,   dg->total_event_time_ns
        ,   dg->min_event_time_ns
        ,   dg->max_event_time_ns
        ,   dg->oom_event_counts[ 0]
        ,   dg->oom_event_counts[ 1]
        ,   dg->oom_event_counts[ 2]
        ,   dg->oom_event_counts[ 3]
        ,   dg->oom_event_counts[ 4]
        ,   dg->oom_event_counts[ 5]
        ,   dg->oom_event_counts[ 6]
        ,   dg->oom_event_counts[ 7]
        ,   dg->oom_event_counts[ 8]
        ,   dg->oom_event_counts[ 9]
        ,   dg->oom_event_counts[10]
        ,   dg->oom_event_counts[11]
        ,   dg->has_overflowed ? "true" : "false"
        );
    }
    else
    {
        ;
    }

    return 0;
}



/* ///////////////////////////// end of file //////////////////////////// */

