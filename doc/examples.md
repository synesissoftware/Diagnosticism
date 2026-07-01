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


## ev

Illustrates environment-variable helpers with defaults and `errno` behaviour.

* Source: `examples/ev/main.c`
* API: @ref diagnosticism_ev

Typical output:

```plaintext
getenv("DIAGNOSTICISM_EXAMPLE_NAME", NULL) -> "Diagnosticism" (errno=0)
getenv("DIAGNOSTICISM_EXAMPLE_MISSING", default-value) -> "default-value" (errno=2)
getenv_atoi("DIAGNOSTICISM_EXAMPLE_PORT", 0) -> 8080 (errno=0)
getenv_atoi("DIAGNOSTICISM_EXAMPLE_MISSING", 42) -> 42 (errno=2)
getenv_atoi("DIAGNOSTICISM_EXAMPLE_BADINT", 99) -> 0 (errno=22)
```


<!-- ########################### end of file ########################### -->
