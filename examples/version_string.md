# Diagnosticism Example - **version_string**


## Summary

Example illustrating use of `diagnosticism_calc_version_string()` to format version tuples into human-readable strings, including pre-release suffixes encoded in the `verAlphaBeta` argument (`-alphaN`, `-betaN`, `-rcN`, or a fourth dotted component).

A C++ wrapper `diagnosticism::calc_version_string()` is available in `<diagnosticism/version_string.hpp>`.


## Source

See [**examples/version_string/main.c**](./version_string/main.c).


## Execution

When built with `BUILD_EXAMPLES=ON` and executed, typical output (to the standard error stream) is:

```plaintext
1.2.3 (0x0000) -> "1.2.3"
0.1.0 (0x4321) -> "0.1.0-alpha801"
1.2.3 (0xc123) -> "1.2.3-rc291"
1.2.3 (0xffff) -> "1.2.3"
```


<!-- ########################### end of file ########################### -->
