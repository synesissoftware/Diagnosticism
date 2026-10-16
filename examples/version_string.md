# Diagnosticism - Example - **version_string**


## Summary

Example illustrating use of `diagnosticism_calc_version_string()` to format version tuples into human-readable strings, including pre-release suffixes encoded in the `verAlphaBeta` argument (`-alphaN`, `-betaN`, `-rcN`, final `0xFF`, or a fourth dotted component). Components are `int` values interpreted as 8-bit quantities (e.g. `0x42` → `-alpha2`, `0x83` → `-beta3`, `0xC1` → `-rc1`, `0xFF` → final, `0x05` → `.5`).

A 16-bit variant is illustrated in [**examples/version_string_16.md**](./version_string_16.md). C++ wrappers `diagnosticism::calc_version_string()` / `diagnosticism::calc_version_string_16()` are available in `<diagnosticism/version_string.hpp>`.


## Source

See [**examples/version_string/main.c**](./version_string/main.c).


## Execution

When built with `BUILD_EXAMPLES=ON` and executed, typical output (to the standard error stream) is:

```plaintext
1.2.3 (0x00) -> "1.2.3"
1.2.3 (0x42) -> "1.2.3-alpha2"
1.2.3 (0x83) -> "1.2.3-beta3"
1.2.3 (0xc1) -> "1.2.3-rc1"
1.2.3 (0xff) -> "1.2.3"
1.2.3 (0x05) -> "1.2.3.5"
```


<!-- ########################### end of file ########################### -->
