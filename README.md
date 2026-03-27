# mathpp

A c++23 module-based mathematical library providing `constexpr`, `noexcept` and no state math functions with feature and performance parity to the standard library, focusing on core functionality and performance.
Focusing on floating point support for float and double using the iec559([IEEE754](https://en.wikipedia.org/wiki/IEEE_754-2008_revision)) standard.

## Features

- **c++ Modules**
- **Compile-time Evaluation**
- **Exception Safety**
- **Performance Parity with the c++ standard library** see [BENCHMARKS.md](./docs/BENCHMARKS.md)
- **Type Support**: Works with all fundamental types, and any types with the arithmetic operators
- **Naming is the same as cmath where applicable**

- **Nans and infs are in general undefined and will just be early returns**

## Requirements

- c++23 and modules support
- cmake, atleast 3.28, but the latest version is recommended
- a generator with c++ modules support

### For testing and performance evaluation see git submodules

## Usage

- add as subdirectory then using target_link_libraries link against Mathpp
- in general the library uses a float32/64 type, this should typically be an alias to either float or double/std::float32 etc. some functions are agnostic some aren't.

## Performance validation

Provided as a test suite, with a build script in build/perf_val directory, using ctest you can run all of them at once.
In general the performance tolerance is such that the mean performance is within statistical signficance of the stl.
Individual tests may fail due to statistical variances.
Will eventually provide a way to have more controls on this, i.e. run control, tolerance.
May also provide/check that the variance of each call/the jitter is equivalent / to view this.
