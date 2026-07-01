# **Diagnosticism** Changes


## 0.2.1 - 1st July 2026

* added `diagnosticism_doomgram_clear()`;
* added **doomgram** example program (`examples/doomgram/`);
* **clang** v17 compatibility;
* removed unnecessary dependency on **<stdatomic.h>**;
* removed unnecessary dependencies on **CLASP** and **cstring** from **CMake** configuration;
* examples link only `core` (`define_example_program()` no longer links **CLASP**);
* added [EXAMPLES.md](./EXAMPLES.md), [examples/tracing.md](./examples/tracing.md), and `generate_doxygen.sh` API documentation;
* expanded Doxygen documentation (`doc/` topic pages, header API comments, example snippets);
* fixed undefined `m_has_overflowed` identifier in `diagnosticism_doomgram_push_event_time_ns()` (debug builds);
* fixed **CMake** install omitting `<diagnosticism/version_string.hpp>`;
* **README.md** improvements (Components, DoomGram example, related projects, **EXAMPLES.md**, tracing example, **CMake** consumer quick-start, Doxygen);


## 0.2.0 - 25th August 2025

* minor mods for release;
* automatic detection of MinGW;
* dependency fix;


## 0.2.0-beta4 - 23rd August 2025

* added `diagnosticism::calc_version_string()`;


## 0.2.0-beta3 - 12th August 2025

* misc. changes;
* documentation markup;


## 0.2.0-beta2 - 11th August 2025

* CMake distribution fixes;


## 0.2.0-beta1 - 7th July 2025

* added `diagnosticism_calc_version_string()`;
* added `diagnosticism_getenv()`, `diagnosticism_getenv_atoi()`;


## 0.1.1 - 23rd February 2025

* tidying;


## 0.1.0 - 20th February 2025

* added **doomgram** API;


## 0.0.1 - 23rd November 2024

* initial version;


<!-- ########################### end of file ########################### -->

