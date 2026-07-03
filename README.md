# Diagnosticism <!-- omit in toc -->

Simple diagnostics utilities for C (and C++) — part of the cross-language **Diagnosticism** family.

![Language](https://img.shields.io/badge/c-000000?style=flat&logo=c&logoColor=white)
![Language](https://img.shields.io/badge/c++-000000?style=flat&logo=c%2B%2B&logoColor=white)
[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
[![GitHub release](https://img.shields.io/github/v/release/synesissoftware/Diagnosticism.svg)](https://github.com/synesissoftware/Diagnosticism/releases/latest)
[![CI](https://github.com/synesissoftware/Diagnosticism/actions/workflows/ci.yml/badge.svg)](https://github.com/synesissoftware/Diagnosticism/actions/workflows/ci.yml)
[![Last Commit](https://img.shields.io/github/last-commit/synesissoftware/Diagnosticism)](https://github.com/synesissoftware/Diagnosticism/commits/master)


## Introduction

**Diagnosticism** is a library providing miscellaneous discrete and simple diagnostics facilities to supplement what is available in the standard library. It is implemented in several languages, providing enhancements that are necessary (and possible). For example, [**Diagnosticism.Python**](https://github.com/synesissoftware/Diagnosticism.Python) can provide the `trace()` function that can capture the callstack information to issue into a diagnostic log statement.

In **C** and **C++**, which offer only modest built-in diagnostic support, the facilities are aimed at lightweight, low-overhead utilities that integrate cleanly with existing code. For example, the **DoomGram** component records duration events into an order-of-magnitude histogram and can summarise many thousands of timings in a single 12-character strip — useful for logging cumulative execution costs in long-running performance-sensitive applications. (See the [Components](#components) section below for more on this.) The `diagnosticism_trace()` macro provides a simple call-site trace facility, writing file, line, function, and a `printf`-style message to a chosen stream; see [**examples/tracing/**](./examples/tracing/).

Other facilities include environment-variable helpers (`diagnosticism_getenv()`, `diagnosticism_getenv_atoi()`), version-string formatting (`diagnosticism_calc_version_string()` and the C++ wrapper `diagnosticism::calc_version_string()`), and a small core API for library initialisation and version discovery. Further facilities will be added over time (and will be listed in the [Components](#components) section below).


## Table of Contents <!-- omit in toc -->


- [Introduction](#introduction)
- [Installation](#installation)
  - [CMake consumer projects](#cmake-consumer-projects)
  - [API documentation (Doxygen)](#api-documentation-doxygen)
- [Components](#components)
  - [C API / core library](#c-api--core-library)
    - [Constants](#constants)
    - [Types](#types)
    - [Functions](#functions)
    - [Macros](#macros)
  - [C++ API](#c-api)
    - [Functions (C++)](#functions-c)
- [Examples](#examples)
  - [Example - DoomGram](#example---doomgram)
  - [Example - tracing](#example---tracing)
- [Project Information](#project-information)
  - [Where to get help](#where-to-get-help)
  - [Contribution guidelines](#contribution-guidelines)
  - [Dependencies](#dependencies)
  - [Related projects](#related-projects)
  - [License](#license)


## Installation

Detailed instructions — via **CMake** — are provided in the accompanying [INSTALL.md](./INSTALL.md) file.


### CMake consumer projects

After installing **Diagnosticism** (see [INSTALL.md](./INSTALL.md)), consumer **CMake** projects may link against the library as follows:

```cmake
cmake_minimum_required(VERSION 3.20)
project(myapp C)

find_package(Diagnosticism REQUIRED)

add_executable(myapp main.c)
target_link_libraries(myapp PRIVATE Diagnosticism::core)
```

Ensure `CMAKE_PREFIX_PATH` includes the install prefix (for example `/usr/local` or the path passed to `cmake --install`).


### API documentation (Doxygen)

HTML API reference for the public headers may be generated locally:

```bash
$ ./generate_doxygen.sh
```

Open `_build/doxygen/html/index.html` in a browser (or `<build-dir>/doxygen/html/index.html` when `SIS_CMAKE_BUILD_DIR` is set). Requires [Doxygen](https://www.doxygen.nl/) on `PATH`.


## Components

The C library is organised by header under `include/diagnosticism/`. Include `<diagnosticism/diagnosticism.h>` for the core API, and the component headers as required.


### C API / core library


#### Constants

The following version constants are defined in `<diagnosticism/diagnosticism.h>`:

* `DIAGNOSTICISM_VER_MAJOR`, `DIAGNOSTICISM_VER_MINOR`, `DIAGNOSTICISM_VER_PATCH` - the major, minor, and patch components of the library version;
* `DIAGNOSTICISM_VER_ALPHABETA` - the alpha/beta component of the library version (0xFF when not applicable);
* `DIAGNOSTICISM_VER` - a composite 32-bit encoding of the library version;


#### Types

The following types are defined in the public C headers:

* `diag_uint32_t` - an unsigned 32-bit integer type used by the core API (`<diagnosticism/diagnosticism.h>`);
* `diagnosticism_doomgram_t` - a **D**ecimal **O**rder-**O**f-**M**agnitude histo**G**ram structure that records duration values efficiently in the orders of magnitude 1ns+, 10ns+, 100ns+, 1µs+, ..., 10s+, 100s+ (`<diagnosticism/doomgram.h>`). This is a C port of the equivalent `stlsoft::doomgram` class from the **STLSoft** libraries;


#### Functions

The following functions comprise the public C API:

Core API (`<diagnosticism/diagnosticism.h>`):

* `diagnosticism_api_version()` - obtains the **Diagnosticism** version (at time of compilation); may be called without having initialised the API;
* `diagnosticism_api_init()` - initialises the **Diagnosticism** API;
* `diagnosticism_api_uninit()` - uninitialises the **Diagnosticism** API;

DoomGram (`<diagnosticism/doomgram.h>`):

* `diagnosticism_doomgram_push_event_time_ns()` - records an event of the given duration in nanoseconds;
* `diagnosticism_doomgram_push_event_time_us()` - records an event of the given duration in microseconds;
* `diagnosticism_doomgram_push_event_time_ms()` - records an event of the given duration in milliseconds;
* `diagnosticism_doomgram_push_event_time_s()` - records an event of the given duration in seconds;
* `diagnosticism_doomgram_clear()` - resets all fields of a doomgram to their initial state;
* `diagnosticism_doomgram_try_get_total_event_time_ns()` - attempts to obtain the cumulative event time (in nanoseconds), which may fail if overflow has occurred;
* `diagnosticism_doomgram_try_get_min_event_time_ns()` - attempts to obtain the minimum recorded event time (in nanoseconds);
* `diagnosticism_doomgram_try_get_max_event_time_ns()` - attempts to obtain the maximum recorded event time (in nanoseconds);
* `diagnosticism_doomgram_to_strip_12()` - writes a terse 12-character histogram strip summarising the order-of-magnitude distribution; useful for logging cumulative execution costs in long-running performance-sensitive applications. Each character encodes the event count in one magnitude bucket, using `_` for zero, `a`-`z` for increasing count ranges, and `*` when a bucket's count exceeds the representable range;

Environment variables (`<diagnosticism/ev.h>`):

* `diagnosticism_getenv()` - obtains the value of a named environment variable, or a caller-supplied default when the variable is not set (in which case `errno` is set to `ENOENT`);
* `diagnosticism_getenv_atoi()` - obtains the value of a named environment variable interpreted as an integer, or a caller-supplied default when the variable is not set (in which case `errno` is set to `ENOENT`); returns 0 when the value cannot be interpreted as an integer;

Tracing (`<diagnosticism/tracing.h>`):

* `diagnosticism_trace_impl()` - low-level implementation used by the `diagnosticism_trace()` macro; writes a trace line to a given `FILE*` stream, including file, line, and function, followed by a `printf`-style formatted message;

Version strings (`<diagnosticism/version_string.h>`):

* `diagnosticism_calc_version_string()` - formats a version number (major, minor, patch, and optional alpha/beta/rc/build component) into a caller-supplied buffer; returns the number of characters written, or a negative value on failure. The `verAlphaBeta` argument encodes pre-release information: values in the ranges 0x4000+, 0x8000+, and 0xC000+ yield `-alphaN`, `-betaN`, and `-rcN` suffixes respectively; 0xFFFF suppresses any suffix; other non-zero values are appended as a fourth dotted component;


#### Macros

The following macros are defined in the public C headers:

Core API (`<diagnosticism/diagnosticism.h>`):

* `DIAGNOSTICISM_CALL(rt)` - expands to the appropriate linkage/return-type decoration for C and C++ (`extern "C" rt` in C++, `rt` in C);

DoomGram (`<diagnosticism/doomgram.h>`):

* `DIAGNOSTICISM_DOOMGRAM_INITIALIZER` - brace initialiser for a zeroed `diagnosticism_doomgram_t` instance;
* `diagnosticism_doomgram_num_events_in_1ns()` through `diagnosticism_doomgram_num_events_ge_100s()` - elicit the event count for each order-of-magnitude bucket;
* `diagnosticism_doomgram_try_get_total_event_time_ns_raw()` - obtains the cumulative event time (in nanoseconds) without regard to overflow;

Tracing (`<diagnosticism/tracing.h>`):

* `diagnosticism_trace(stm, ...)` - writes a trace line to `stm` at the call site, automatically supplying `__FILE__`, `__LINE__`, and the current function name together with a `printf`-style formatted message. For example:

```C
#include <diagnosticism/tracing.h>

diagnosticism_trace(stderr, "argc=%d", argc);
diagnosticism_trace(stderr, "argument=%s", argument);
```

See the example program in [**examples/tracing/**](./examples/tracing/).


### C++ API

The C++ API is intentionally small: a thin convenience layer over selected C functions. Include the C++ headers directly (they pull in the corresponding C headers).


#### Functions (C++)

Version strings (`<diagnosticism/version_string.hpp>`):

* `diagnosticism::calc_version_string()` - C++ wrapper around `diagnosticism_calc_version_string()` that returns a `std::string`; throws `std::runtime_error` on failure. For example:

```C++
#include <diagnosticism/version_string.hpp>

std::string const s = diagnosticism::calc_version_string(1, 2, 3, 0);
// s == "1.2.3"
```


## Examples

Examples are provided in the ```examples``` directory, along with a markdown description for each. A detailed list is provided in [EXAMPLES.md](./EXAMPLES.md).


### Example - DoomGram

The example program **doomgram** (in the **examples** directory) illustrates use of `diagnosticism_doomgram_t` to accumulate many timing events and obtain the 12-character timing strip. Each strip character corresponds to one order-of-magnitude bucket (from 1ns+ through 100s+). Within a bucket, `_` means no events, `a`-`z` encodes increasing event counts, and `*` indicates overflow of the representable range.

The program records a spread of durations across the magnitude range, using `{}`-guarded loops where several events share the same order-of-magnitude. See [**examples/doomgram/main.c**](./examples/doomgram/main.c) and [**examples/doomgram.md**](./examples/doomgram.md).

```C
// examples/doomgram/main.c (extract)

diagnosticism_doomgram_push_event_time_ns(&dg,   9);
{ for (int i = 0; i != 25; ++i)
diagnosticism_doomgram_push_event_time_ns(&dg,  80);
}
{ for (int i = 0; i != 15; ++i)
diagnosticism_doomgram_push_event_time_ns(&dg, 700);
}

{ for (int i = 0; i != 30; ++i)
diagnosticism_doomgram_push_event_time_us(&dg,   6);
}
diagnosticism_doomgram_push_event_time_us(&dg,  50);
{ for (int i = 0; i != 120000; ++i)
diagnosticism_doomgram_push_event_time_us(&dg, 400);
}

/* diagnosticism_doomgram_push_event_time_ms(&dg,   3); */
{ for (int i = 0; i != 22; ++i)
diagnosticism_doomgram_push_event_time_ms(&dg,  20);
}
diagnosticism_doomgram_push_event_time_ms(&dg, 100);

diagnosticism_doomgram_push_event_time_s(&dg,    9);
/* ... further s-bucket pushes ... */

diagnosticism_doomgram_to_strip_12(&dg, (char (*)[12])strip);
strip[12] = '\0';

diagnosticism_doomgram_try_get_min_event_time_ns(&dg, &min_ns);
diagnosticism_doomgram_try_get_max_event_time_ns(&dg, &max_ns);

fprintf(stderr,
    "strip: %s; min: %" PRIu64 "ns;  max: %" PRIu64 "ns;  event_count: %" PRIu64 "\n",
    strip, min_ns, max_ns, dg.event_count);
```

Typical output is:

```plaintext
strip: abbbaf_baaaa; min: 9ns;  max: 700000000000ns;  event_count: 120106
```

indicating, among other buckets:
- `a` in the 1ns+ bucket (1 event at 9ns);
- `b` in the 10ns+ and 100ns+ buckets (25 events at 80ns; 15 at 700ns);
- `b` in the 1µs+ bucket (30 events at 6µs);
- `f` in the 100µs+ bucket (120000 events at 400µs);
- `_` in the 1ms+ bucket (the single `3ms` push is commented out in the example source);
- and further non-uniform counts across the remaining magnitude buckets.

In a live system one would log only the strip (and perhaps min/max), not the full internal histogram state.


### Example - tracing

The example program **tracing** (in the **examples** directory) illustrates use of `diagnosticism_trace()` at the call site. See [**examples/tracing/main.c**](./examples/tracing/main.c) and [**examples/tracing.md**](./examples/tracing.md).

```C
#include <diagnosticism/tracing.h>

diagnosticism_trace(stderr, "argc=%d, argv=...", argc);
diagnosticism_trace(stderr, "argument=%s", argument);
```

Typical output (to `stderr`) is along the lines of:

```plaintext
examples/tracing/main.c:22:main(argc=1, argv=...)
examples/tracing/main.c:10:f()
examples/tracing/main.c:15:g(argument=the argument to g)
```


## Project Information

### Where to get help

[GitHub Page](https://github.com/synesissoftware/Diagnosticism "GitHub Page")


### Contribution guidelines

Defect reports, feature requests, and pull requests are welcome on https://github.com/synesissoftware/Diagnosticism.


### Dependencies

#### STLSoft (optional) <!-- omit in toc -->

The original (~2005) implementation used **STLSoft** for discrimination of compilers and for library support. For modern compilers with broad support for the latest language standards this is not necessary. Hence, if the preprocessor symbol `Diagnosticism_NO_STLSOFT` is specified then all dependencies on **STLSoft** are removed and basic **C++-14** features are used instead. (This is done in the **CMake** configuration provided - see [INSTALL.md](./INSTALL.md).)

If you _do_ need **STLSoft**, then version 1.10.6 or later is recommended. If you're using a _very_ old compiler you may wish to use STLSoft-1.9, for which version 1.9.136 is recommended. Further, the makefiles require definition of the environment variable `STLSOFT` that should be set to the root directory of a clone of **STLSoft**.

* [STLSoft 1.9](http://github.com/synesissoftware/STLSoft-1.9/)
* [STLSoft 1.10](http://github.com/synesissoftware/STLSoft-1.10/) (Recommended)


### Related projects

Other implementations in the **Diagnosticism** family:

* [**Diagnosticism.Go**](https://github.com/synesissoftware/Diagnosticism.Go);
* [**Diagnosticism.Python**](https://github.com/synesissoftware/Diagnosticism.Python);
* [**Diagnosticism.Rust**](https://github.com/synesissoftware/Diagnosticism.Rust);
* [**Diagnosticism.Ruby**](https://github.com/synesissoftware/Diagnosticism.Ruby);
* [**Diagnosticism.NET**](https://github.com/synesissoftware/Diagnosticism.NET);

The **DoomGram** component in this (C) library is ported from [`stlsoft::doomgram`](https://github.com/synesissoftware/STLSoft-1.11) in **STLSoft** (see [Dependencies](#dependencies)).


### License

**Diagnosticism** is released under the 3-clause BSD license. See [LICENSE](./LICENSE) for details.


<!-- ########################### end of file ########################### -->

