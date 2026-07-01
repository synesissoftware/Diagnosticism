# Diagnosticism {#mainpage}

**Diagnosticism** is a library of simple, lightweight diagnostics utilities for **C** and **C++**. It is part of a cross-language family of libraries that provide complementary facilities in Go, Python, Rust, Ruby, and .NET.

The C/C++ edition focuses on low-overhead utilities that integrate cleanly with existing code: order-of-magnitude timing histograms (**DoomGram**), call-site tracing, environment-variable helpers, and version-string formatting.


## Components

| Module | Header | Summary |
| ------ | ------ | ------- |
| @ref diagnosticism_core | `<diagnosticism/diagnosticism.h>` | Version constants, linkage macros, and core API entry points |
| @ref diagnosticism_doomgram | `<diagnosticism/doomgram.h>` | Decimal order-of-magnitude timing histogram |
| @ref diagnosticism_ev | `<diagnosticism/ev.h>` | Environment-variable helpers |
| @ref diagnosticism_tracing | `<diagnosticism/tracing.h>` | Call-site trace macro |
| @ref diagnosticism_version | `<diagnosticism/version_string.h>` | Version-string formatting (C and C++) |

See also @ref examples_page for runnable example programs.


## Quick start

Include the core header and link against the **Diagnosticism** `core` library:

```c
#include <diagnosticism/diagnosticism.h>

uint32_t const ver = diagnosticism_api_version();
```

Consumer **CMake** projects may use `find_package(Diagnosticism)` and link `Diagnosticism::core`. See [INSTALL.md](https://github.com/synesissoftware/Diagnosticism/blob/master/INSTALL.md) for build and install instructions.


## Related projects

* [Diagnosticism.Go](https://github.com/synesissoftware/Diagnosticism.Go)
* [Diagnosticism.Python](https://github.com/synesissoftware/Diagnosticism.Python)
* [Diagnosticism.Rust](https://github.com/synesissoftware/Diagnosticism.Rust)
* [Diagnosticism.Ruby](https://github.com/synesissoftware/Diagnosticism.Ruby)
* [Diagnosticism.NET](https://github.com/synesissoftware/Diagnosticism.NET)

The **DoomGram** component is ported from [`stlsoft::doomgram`](https://github.com/synesissoftware/STLSoft-1.11) in **STLSoft**.


<!-- ########################### end of file ########################### -->
