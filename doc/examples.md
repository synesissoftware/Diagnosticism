# Examples {#examples_page}

Runnable example programs live under `examples/`. Build them with **CMake** using `-DBUILD_EXAMPLES=ON` (see [INSTALL.md](https://github.com/synesissoftware/Diagnosticism/blob/master/INSTALL.md)).


## doomgram

Records a spread of operation timings across the magnitude range and prints the 12-character timing strip together with minimum and maximum recorded durations.

* Source: `examples/doomgram/main.c`
* Topic page: @ref doomgram_page
* API: @ref diagnosticism_doomgram

Typical output:

```plaintext
strip: abbbaf_baaaa; min: 9ns;  max: 700000000000ns;  event_count: 120106
```


## tracing

Illustrates `diagnosticism_trace()` at several call sites.

* Source: `examples/tracing/main.c`
* Topic page: @ref tracing_page
* API: @ref diagnosticism_tracing

Typical output:

```plaintext
examples/tracing/main.c:22:main(argc=1, argv=...)
examples/tracing/main.c:10:f()
examples/tracing/main.c:15:g(argument=the argument to g)
```


<!-- ########################### end of file ########################### -->
