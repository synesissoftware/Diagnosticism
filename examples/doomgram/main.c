
#include <diagnosticism/doomgram.h>

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    diagnosticism_doomgram_t    dg = DIAGNOSTICISM_DOOMGRAM_INITIALIZER;
    char                        strip[12 + 1];
    uint64_t                    min_ns;
    uint64_t                    max_ns;

    diagnosticism_doomgram_push_event_time_ns(&dg,   9);
    { for (int i = 0; i != 25; ++i)
    diagnosticism_doomgram_push_event_time_ns(&dg,  80);
    }
    { for (int i = 0; i != 15; ++i)
    diagnosticism_doomgram_push_event_time_ns(&dg, 700);
    }

    { for (int i = 0; i != 30; ++i)
    diagnosticism_doomgram_push_event_time_us(&dg,   6);
    }
    diagnosticism_doomgram_push_event_time_us(&dg,  50);
    { for (int i = 0; i != 120000; ++i)
    diagnosticism_doomgram_push_event_time_us(&dg, 400);
    }

    /* diagnosticism_doomgram_push_event_time_ms(&dg,   3); */
    { for (int i = 0; i != 22; ++i)
    diagnosticism_doomgram_push_event_time_ms(&dg,  20);
    }
    diagnosticism_doomgram_push_event_time_ms(&dg, 100);

    diagnosticism_doomgram_push_event_time_s(&dg,    9);
    { for (int i = 0; i != 7; ++i)
    diagnosticism_doomgram_push_event_time_s(&dg,   80);
    }
    { for (int i = 0; i != 3; ++i)
    diagnosticism_doomgram_push_event_time_s(&dg,  700);
    }

    diagnosticism_doomgram_to_strip_12(&dg, (char (*)[12])strip);
    strip[12] = '\0';

    if (!diagnosticism_doomgram_try_get_min_event_time_ns(&dg, &min_ns))
    {
        fprintf(stderr, "failed to obtain min event time\n");
        return EXIT_FAILURE;
    }

    if (!diagnosticism_doomgram_try_get_max_event_time_ns(&dg, &max_ns))
    {
        fprintf(stderr, "failed to obtain max event time\n");
        return EXIT_FAILURE;
    }

    fprintf(
        stderr
    ,   "strip: %s; min: %" PRIu64 "ns;  max: %" PRIu64 "ns;  event_count: %" PRIu64 "\n"
    ,   strip
    ,   min_ns
    ,   max_ns
    ,   dg.event_count
    );

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */
