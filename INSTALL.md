# Diagnosticism - Installation and Use <!-- omit in toc -->

## Table of Contents <!-- omit in toc -->

- [Using CMake](#using-cmake)
  - [Obtain the latest distribution of **Diagnosticism**](#obtain-the-latest-distribution-of-diagnosticism)
  - [Prepare the CMake configuration](#prepare-the-cmake-configuration)
    - [Visual C++ with Static Dependency on Standard Library](#visual-c-with-static-dependency-on-standard-library)
  - [Build](#build)
  - [Install](#install)


**Diagnosticism** is a classic-form C/C++ library, insofar as it has implementation files in its **src** directory and header files in its **include/Diagnosticism** directory. Thus, once "installed", one must simply include **diagnosticism/_XXXX_*_.h** (where **_XXXX_** might be **doomgram**, or **ev**, or another of the API header headers).

You may elect to compile in the **src** file(s) needed, but the standard way to do so is to build and install the library via **CMake** as described below:


## Using CMake

### Obtain the latest distribution of **Diagnosticism**

You can obtain a **.zip** or **.tar.gz** at the [Releases page](https://github.com/synesissoftware/Diagnosticism/releases), e.g.:

```bash
$ mkdir -p ~/open-source
$ cd ~/open-source
$ curl -L -O https://github.com/synesissoftware/Diagnosticism/archive/refs/tags/0.2.0-beta4.tar.gz
$ gunzip 0.2.0-beta4.tar.gz
$ cd Diagnosticism-0.2.0-beta4
```

Or you may prefer to clone the project via git

```bash
$ mkdir -p ~/open-source
$ cd ~/open-source
$ git clone https://github.com/synesissoftware/Diagnosticism/
$ cd Diagnosticism
```

### Prepare the CMake configuration


Prepare the CMake configuration, via the **prepare_cmake.sh** script, as in:

```bash
$ ./prepare_cmake.sh
```

By default, this will create a **_build** directory under the project directory. If you want to use a specific directory you can do so via the environment variable `SIS_CMAKE_BUILD_DIR`.

```bash
$ export SIS_CMAKE_BUILD_DIR=/tmp/Diagnosticism
$ ./prepare_cmake.sh
```

> **NOTE**: If you provide the flag `--run-make` (=== `-m`) then the script will also run a build, so the [Build](#build) step can be skipped.


#### Visual C++ with Static Dependency on Standard Library

```bash
$ export SIS_CMAKE_BUILD_DIR=/tmp/Diagnosticism
$ ./prepare_cmake.sh --msvc-mt
```


### Build

```bash
$ ./build_cmake.sh
```

> **NOTE**: If you provide the flag `--run-make` (=== `-m`) in step 3 then you do not need this step.


4. As a check, execute the built test program files via the **build_run_all_unit_tests.sh** script, as in:

  ```bash
  $ ./run_all_unit_tests.sh -M
  ```

> **NOTE**: If you do not provide the flag `--no-make` (=== `-M`) then the script will also run a build.


### Install

1. Install the library on the host, via `cmake`, as in:


  ```bash
  $ sudo cmake --install ${SIS_CMAKE_BUILD_DIR:-./_build} --config Release
  ```


<!-- ########################### end of file ########################### -->

