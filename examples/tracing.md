# Diagnosticism Example - **tracing**


## Summary

Example illustrating use of the `diagnosticism_trace()` macro to write call-site trace lines to a `FILE*` stream. Each line includes the source file, line number, function name, and an optional `printf`-style formatted message.


## Source

See [**examples/tracing/main.c**](./tracing/main.c).


## Execution

When built with `BUILD_EXAMPLES=ON` and executed, typical output (to the standard error stream) is:

```plaintext
examples/tracing/main.c:22:main(argc=1, argv=...)
examples/tracing/main.c:10:f()
examples/tracing/main.c:15:g(argument=the argument to g)
```

Paths will vary according to the build location; the format is `file:line:function(message)`.


<!-- ########################### end of file ########################### -->
