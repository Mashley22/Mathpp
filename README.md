# mathpp

A c++23 module-based mathematical library providing `constexpr`, `noexcept` and no state math functions with feature and performance parity to the standard library, focusing on core functionality without extreme edge case handling.

## Features

- **c++ Modules**
- **Compile-time Evaluation**
- **Exception Safety**
- **Performance Parity with the c++ standard library**
- **Type Support**: Works with all fundamental types, and any types with the arithmetic operators
- **Naming is the same as cmath where applicable, better names are provided as seen fit**

- **Edge Cases are not checked :), i.e. no Nans or infs anywhere**

## Requirements

- c++23 and modules support
- cmake, atleast 3.28, but the latest version is recommended
- a generator with c++ modules support

### For testing and performance evaluation see git submodules

## Usage

- add as subdirectory then using target_link_libraries link against Mathpp

## Errors and edge cases

In general errors and edge cases are not well dealt with.
This is on purpose to provide the noexcept constexpr stuff.
If more robust error checking and edge case handling is neccessary than use something else or 
sanitize inputs.

## Performance validation

Provided as a test suite in build/perf_val directory, using ctest you can run all of them at once.
In general the performance tolerance is such that the mean performance is within statistical signficance of the stl.
Individual tests may fail due to statistical variances.
Will eventually provide a way to have more controls on this, i.e. run control, tolerance.
May also provide/check that the variance of each call/the jitter is equivalent / to view this.
