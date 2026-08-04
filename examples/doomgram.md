# Diagnosticism Example - **doomgram**


## Summary

Example illustrating use of `diagnosticism_doomgram_t` to record a spread of operation timings across the magnitude range and emit the 12-character timing strip together with minimum and maximum recorded durations.

The program uses `{}`-guarded loops for repeated pushes at the same order-of-magnitude (e.g. 25 events at 80ns, 120000 events at 400µs), producing a non-uniform strip such as `abbbaf_baaaa`.


## Source

See [**examples/doomgram/main.c**](./doomgram/main.c).


## Execution

When built with `BUILD_EXAMPLES=ON` and executed, typical output (to the standard error stream) is:

```plaintext
strip: abbbaf_baaaa; min: 9ns;  max: 700000000000ns;  event_count: 120106
```


<!-- ########################### end of file ########################### -->
