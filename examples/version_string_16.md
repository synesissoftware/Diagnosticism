# Diagnosticism Example - **version_string_16**


## Summary

Example illustrating use of `diagnosticism_calc_version_string_16()` to format version tuples into human-readable strings, including pre-release suffixes encoded in the `verAlphaBeta` argument (`-alphaN`, `-betaN`, `-rcN`, or a fourth dotted component). Components are `uint16_t` values with 16-bit pre-release encoding (e.g. `0x4001` → `-alpha1`, `0xC123` → `-rc291`, `0xFFFF` → final).

The 8-bit API `diagnosticism_calc_version_string()` is illustrated in [**examples/version_string.md**](./version_string.md). C++ wrappers are available in `<diagnosticism/version_string.hpp>`.


## Source

See [**examples/version_string_16/main.c**](./version_string_16/main.c).


## Execution

When built with `BUILD_EXAMPLES=ON` and executed, typical output (to the standard error stream) is:

```plaintext
1.2.3 (0x0000) -> "1.2.3"
0.1.0 (0x4321) -> "0.1.0-alpha801"
1.2.3 (0xc123) -> "1.2.3-rc291"
1.2.3 (0xffff) -> "1.2.3"
```


<!-- ########################### end of file ########################### -->
