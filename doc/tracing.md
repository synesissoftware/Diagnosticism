# Tracing {#tracing_page}

The `diagnosticism_trace()` macro writes a single trace line to a caller-supplied `FILE*` stream. Each line includes the source file, line number, current function name, and an optional `printf`-style formatted message.


## Output format

```
file:line:function(message)
```

When the format string is empty, the parentheses are empty:

```
examples/tracing/main.c:10:f()
```

When arguments are supplied:

```
examples/tracing/main.c:15:g(argument=the argument to g)
```

Paths reflect the build location; only the format is stable.


## Example

\snippet tracing/main.c tracing_call

See @ref diagnosticism_tracing for the macro and @ref examples_page for the full example program.


<!-- ########################### end of file ########################### -->
