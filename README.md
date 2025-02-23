# Diagnosticism <!-- omit in toc -->

Miscellaneous Diagnostic facilities for C (and C++)


## Table of Contents <!-- omit in toc -->


- [Introduction](#introduction)
- [Installation](#installation)
- [Components](#components)
  - [C API / core library](#c-api--core-library)
  - [C++ API](#c-api)
- [Examples](#examples)
- [Project Information](#project-information)
  - [Where to get help](#where-to-get-help)
  - [Contribution guidelines](#contribution-guidelines)
  - [Dependencies](#dependencies)
  - [Related projects](#related-projects)
  - [License](#license)


## Introduction

**Diagnosticism** is a standalone library of simple components for aiding in diagnostics for C and C++ projects.


## Installation

Detailed instructions - via **CMake**, via bundling, via custom makefile
parameters - are provided in the accompanying [INSTALL.md](./INSTALL.md)
file.


## Components

### C API / core library

T.B.C.


### C++ API

T.B.C.


## Examples

Examples are provided in the ```examples``` directory, along with a markdown description for each.


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

Projects in which **Diagnosticism** is used include:

T.B.C.


Projects in which **Diagnosticism** is used for testing include:

T.B.C.


### License

**Diagnosticism** is released under the 3-clause BSD license. See [LICENSE](./LICENSE) for details.


<!-- ########################### end of file ########################### -->

