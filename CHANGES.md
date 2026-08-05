# Diagnosticism - CHANGES <!-- omit in toc -->


## 0.3.0-alpha2 - 5th August 2026

* added Abort API (`diagnosticism_abort()`, `diagnosticism_abortf()`) in **abort.h** / **abort.c**;
* added **abort** example program (**examples/abort/**);
* added `DIAGNOSTICISM_CALL_NORETURN`;
* added **include/diagnosticism/internal/compiler.h** and **include/diagnosticism/internal/language.h** stubs;


## 0.3.0-alpha1 - 5th August 2026

* changed `diagnosticism_calc_version_string()` to take `int` version elements interpreted strictly as 8-bit values (`0x41` alpha1, `0x81` beta1, `0xC1` rc1, `0xFF` final);
* added `diagnosticism_calc_version_string_16()` (prior 16-bit behaviour) and `diagnosticism::calc_version_string_16()`;
* added **version_string_16** example program (**examples/version_string_16/**);
* expanded version-string unit tests with thorough 8-bit and 16-bit coverage;
* ensured C/C++/CMake sources end with a full blank line;
* completed `@pre` contract assertions in **doomgram** API implementations;
* added **.sis/project_name.txt**; helper scripts load `ProjectName` for status messages;
* boilerplate: version **0.3.0-alpha1**; added `DIAGNOSTICISM_VER_REVISION`;


## 0.2.2-alpha1 - 4th August 2026

* fixed unnecessary dependency on **cstring** when not building tests;
* **CMake** enhancements: version parsing accepts `VER_PATCH` or `VER_REVISION`; **`_BUILD_AS_UNIX`** / **`_BUILD_AS_WIN32`** OS discrimination; **`X_CMAKE_C_FULLSTANDARD`** in **LanguageFullVersion.cmake**;
* helper scripts: **run_all_scratch_tests.sh** propagates failure status from scratch/performance programs; help text for scratch and unit runners clarified;
* markdown title canonicalisation (**CHANGES.md**, **EXAMPLES.md**);
* boilerplate: **BuildType.cmake** tidy;


## 0.2.1 - 1st August 2026

* added `diagnosticism_doomgram_clear()`;
* added **doomgram** example program (**examples/doomgram/**);
* **clang** v17 compatibility;
* removed unnecessary dependency on **<stdatomic.h>**;
* removed unnecessary dependencies on **CLASP** and **cstring** from **CMake** configuration;
* examples link only **core** (`define_example_program()` no longer links **CLASP**);
* added [EXAMPLES.md](./EXAMPLES.md), [examples/tracing.md](./examples/tracing.md), and **generate_doxygen.sh** API documentation;
* added **ev** example program (**examples/ev/**) with markdown walkthroughs;
* added **version_string** example program (**examples/version_string/**) with markdown walkthroughs;
* expanded Doxygen documentation (**doc/** topic pages, header API comments, example snippets);
* added GitHub Actions CI (`.github/workflows/ci.yml`);
* fixed undefined `m_has_overflowed` identifier in `diagnosticism_doomgram_push_event_time_ns()` (debug builds);
* fixed **CMake** install omitting `<diagnosticism/version_string.hpp>`;
* **README.md** improvements (Components, DoomGram example, related projects, **EXAMPLES.md**, tracing example, **CMake** consumer quick-start, Doxygen);
* boilerplate:
  * include-guards for all public headers;
  * **STLSoft** references now to **https://github.com/synesissoftware/STLSoft**;
  * **README.md** layout;
  * comment lengths;
  * CMake fixes;
  * ignores;
  * markdown file consistency;
  * trivial improvements to CI;
  * helper scripts;
  * **LICENSE**;


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

