# DoomGram {#doomgram_page}

A **D**ecimal **O**rder-**O**f-**M**agnitude histo**G**ram records many timing events into twelve magnitude buckets and can summarise the distribution in a single 12-character **strip** — useful for logging cumulative execution costs in long-running, performance-sensitive applications.

This is a C port of the equivalent `stlsoft::doomgram` class from [STLSoft](https://github.com/synesissoftware/STLSoft).


## Magnitude buckets

Each recorded event is placed in exactly one bucket according to its duration:

| Index | Bucket macro | Magnitude |
| ----- | ------------ | --------- |
| 0 | `diagnosticism_doomgram_num_events_in_1ns()` | 1ns+ |
| 1 | `diagnosticism_doomgram_num_events_in_10ns()` | 10ns+ |
| 2 | `diagnosticism_doomgram_num_events_in_100ns()` | 100ns+ |
| 3 | `diagnosticism_doomgram_num_events_in_1us()` | 1µs+ |
| 4 | `diagnosticism_doomgram_num_events_in_10us()` | 10µs+ |
| 5 | `diagnosticism_doomgram_num_events_in_100us()` | 100µs+ |
| 6 | `diagnosticism_doomgram_num_events_in_1ms()` | 1ms+ |
| 7 | `diagnosticism_doomgram_num_events_in_10ms()` | 10ms+ |
| 8 | `diagnosticism_doomgram_num_events_in_100ms()` | 100ms+ |
| 9 | `diagnosticism_doomgram_num_events_in_1s()` | 1s+ |
| 10 | `diagnosticism_doomgram_num_events_in_10s()` | 10s+ |
| 11 | `diagnosticism_doomgram_num_events_ge_100s()` | 100s+ |

See @ref diagnosticism_doomgram for the full API.


## Strip encoding

`diagnosticism_doomgram_to_strip_12()` writes one character per bucket into a 12-element array. Within each bucket:

| Character | Meaning |
| --------- | ------- |
| `_` | No events in this bucket |
| `a`–`z` | Increasing event-count ranges within the bucket |
| `*` | Bucket count exceeds the representable strip range |

In production logging you typically emit only the strip (and perhaps min/max durations), not the full internal histogram.


## Example

Initialise a doomgram, record events, and obtain the strip:

\snippet doomgram/main.c doomgram_init
\snippet doomgram/main.c doomgram_push
\snippet doomgram/main.c doomgram_strip

Typical output from the **doomgram** example program:

```plaintext
strip: abbbaf_baaaa; min: 9ns;  max: 700000000000ns;  event_count: 120106
```

See @ref examples_page for build instructions.


<!-- ########################### end of file ########################### -->
