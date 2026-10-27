# Diagnosticism - Changes <!-- omit in toc -->


## 0.4.1 - 27th October 2026

* Defined `HAS_shwild` and `HAS_SHWILD` when **shwild** is detected, and stopped defining `DIAGNOSTICISM_HAS_SHWILD`;


## 0.4.0 - 16th October 2026

* Added `diagnosticism_nanoseconds_to_string()` compact duration formatter (**nanoseconds_to_string.h** / **nanoseconds_to_string.c**) with golden parity vs **Diagnosticism.Python** / **Diagnosticism.Rust** (`ns` / `µs` / `ms` / `s`, optional `+` flag, UTF-8 MICRO SIGN by default; `DIAGNOSTICISM_NS_TO_STRING_F_ASCII_ONLY` selects `"us"`);
* Added C++ wrappers `diagnosticism::nanoseconds_to_string()` (**nanoseconds_to_string.hpp**) returning `std::string` or writing via a mutating `T_string&` (`assign(char const*, size_t)`);
* Added unit programs **test.unit.nanoseconds_to_string** and **test.unit.C++.nanoseconds_to_string** (Python golden table; C++ return and mutating-ref overloads);
* Added **example.nanoseconds_to_string** (**examples/nanoseconds_to_string/**) covering units, flags, and size probe;
* Documented the new API under **README.md** Components, with **since** badges for introduction versions;
* Boilerplate gold: **.sis/ci_scratch_tests_allowed_to_fail.txt** and **.sis/ci_scratch_tests_skip_interactive.txt**; tip **run_all_scratch_tests** / **run_all_examples** / **run_all_unit_tests** helpers; CI scratch steps pass `--skip-interactive`;


## 0.3.2 - 13th October 2026

* Modular GitHub Actions CI (**ci.yml** + **ci-cell.yml** + **install-sis-deps**; execute-bit restore; Windows **.cmd** dogfood; install-smoke);
* Tip **run_all_examples** / **run_all_scratch_tests** helpers with allowed-to-fail support; **example.*** target names; **.sis/ci_examples_allowed_to_fail.txt** for **example.abort**;
* **test.scratch.versions** dogfoods `diagnosticism_calc_version_string()` and prints conditional **STLSoft** / **shwild** efferents;
* **NEWS.md** three-column **Details** chronology;
* Migrated version low-byte macro to `DIAGNOSTICISM_VER_RELSTATUS` (legacy `DIAGNOSTICISM_VER_ALPHABETA` retained as a documentation-hidden alias);
* Merged **dev** packaging fix so **Diagnosticism::core** no longer exports a false **STLSoft** interface dependency (see **0.3.1-alpha1**);


## 0.3.1 - 10th October 2026

* Applied **misc-dev-scripts** **0.6.0** editor/Git/`.sis` drop-in templates on **boilerplate**;
* Restored historical **.gitignore** patterns as a sorted union with **misc-dev-scripts** gold section layout;


## 0.3.1-alpha1 - 10th August 2026

* **CMake**: removed erroneous `PUBLIC` link of **STLSoft::STLSoft** from **Diagnosticism::core** (exported interface no longer advertises a transitive **STLSoft** dependency);
* **CMake**: stopped applying directory-wide `include_directories()` for **STLSoft**; test programs receive **STLSoft** privately via **target_link_STLSoft()**;
* **CMake**: example helper macros no longer link **STLSoft**; automated-test helper links **STLSoft** `PRIVATE` only;
* **CMake**: **diagnosticism-config.cmake.in** documents that the installed package has no `find_dependency()` requirements;
* **README.md** / **INSTALL.md** / **prepare_cmake.sh**: clarified that **STLSoft**, **xTests**, and **shwild** are test-build dependencies only;


## 0.3.0 - 9th August 2026

0.3.0 release;


## 0.3.0-alpha3 - 5th August 2026

* fixed CMake install so **compiler.h** and **language.h** install under **include/diagnosticism/internal/** (not flattened into **include/diagnosticism/**);
* installed **abort.h** with the other top-level public headers;


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

