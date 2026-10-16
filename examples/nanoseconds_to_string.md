# Diagnosticism - Example - **nanoseconds_to_string**


## Summary

Example illustrating use of `diagnosticism_nanoseconds_to_string()` to format nanosecond counts as compact duration strings (`ns` / `µs` / `ms` / `s`). Demonstrates the default UTF-8 microsecond unit (`µs`), `DIAGNOSTICISM_NS_TO_STRING_F_ASCII_ONLY` (`"us"`), `DIAGNOSTICISM_NS_TO_STRING_F_PLUS`, and a `cchBuffer == 0` size probe that reports required capacity without writing `errno`.


## Source

See [**examples/nanoseconds_to_string/main.c**](./nanoseconds_to_string/main.c).


## Execution

When built with `BUILD_EXAMPLES=ON` and executed, typical output (to the standard error stream) is:

```plaintext
0 (flags=0x00000000) -> "0s" (2 chars)
123456789 (flags=0x00000000) -> "123.4ms" (7 chars)
6789 (flags=0x00000000) -> "6.789µs" (8 chars)
6789 (flags=0x00000002) -> "6.789us" (7 chars)
999772000 (flags=0x00000001) -> "+999.7ms" (8 chars)
size probe for 6789ns -> required capacity 9 (errno untouched)
```

Note: counts are C `char` units (UTF-8 bytes). The `"6.789µs"` line includes MICRO SIGN U+00B5 as the two-byte sequence `C2 B5`, so its payload length is 8 rather than 7.


<!-- ########################### end of file ########################### -->
