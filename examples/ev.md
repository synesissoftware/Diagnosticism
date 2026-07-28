# Diagnosticism Example - **ev**


## Summary

Example illustrating use of `diagnosticism_getenv()` and `diagnosticism_getenv_atoi()` to read environment variables with optional defaults.

When a named variable is not set, both functions set `errno` to `ENOENT` and return the caller-supplied default. `diagnosticism_getenv_atoi()` returns `0` when the variable is set but cannot be interpreted as an integer.

The program sets several `DIAGNOSTICISM_EXAMPLE_*` variables at startup so that output is deterministic.


## Source

See [**examples/ev/main.c**](./ev/main.c).


## Execution

When built with `BUILD_EXAMPLES=ON` and executed, typical output (to the standard error stream) is:

```plaintext
getenv("DIAGNOSTICISM_EXAMPLE_NAME", NULL) -> "Diagnosticism" (errno=0)
getenv("DIAGNOSTICISM_EXAMPLE_MISSING", default-value) -> "default-value" (errno=2)
getenv_atoi("DIAGNOSTICISM_EXAMPLE_PORT", 0) -> 8080 (errno=0)
getenv_atoi("DIAGNOSTICISM_EXAMPLE_MISSING", 42) -> 42 (errno=2)
getenv_atoi("DIAGNOSTICISM_EXAMPLE_BADINT", 99) -> 0 (errno=22)
```

(`errno=2` is `ENOENT` on POSIX systems. When the variable is set but not parseable as an integer, `atoi()` may leave `errno` at `EINVAL` (22) on some platforms.)


<!-- ########################### end of file ########################### -->
