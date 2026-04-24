# Performance Benchmarks

## Overview

This document contains performance benchmarking data comparing `mathpp` implementations against standard library (`std`) functions, ON MY MACHINE. All measurements are in nanoseconds (ns) and based on 10,000 runs, each run consisting of calling the function >1000 times;

## Methodology

- **Sample Count**: 10,000 iterations per function
- **Unit**: Nanoseconds (ns)
- **Functions Tested**: `abs`, `trunc`, `ceil`, `ilogb`, `floor`
- **Data Types**: 32-bit and 64-bit floating-point numbers

## Setup

- **CPU:**: Ryzen 5 7640U
- **RAM:**: 16GB DDR5
- **OS**: Linux 6.19.6
- **Commit**: d45d9002ff403c3877090322d5d765dbf43b1581
- **Compiler**: clang 21.1.8
- **Compiler options:** run using gnu++23, O3 with flto=thin (cmake ipo default for clang), no-trapping-math, no-round-math and no-math-errno

## To Reproduce

- run the bash script, build/perf_val/benchmarks.sh
- the benchmarking executable will be built bin/Benchmarks
- run all by running the executable with -a

## Benchmark Results

### abs()

| Implementation | Mean | Std Dev | Min | Max | Median |
|---|---|---|---|---|---|
| std_f32 | 2921.64 | 420.35 | 2685 | 31249 | 2935 |
| mathpp_f32 | 2899.53 | 324.70 | 2765 | 13155 | 2805 |
| std_f64 | 3065.42 | 604.45 | 2825 | 22252 | 2966 |
| mathpp_f64 | 3122.09 | 900.67 | 2815 | 62187 | 2986 |

**Summary**: mathpp_f32 shows ~0.8% performance improvement with lower variance. mathpp_f64 shows ~1.9% slower but with comparable performance.

### trunc()

| Implementation | Mean | Std Dev | Min | Max | Median |
|---|---|---|---|---|---|
| std_f32 | 182.25 | 87.40 | 160 | 7554 | 171 |
| mathpp_f32 | 74.53 | 32.18 | 60 | 2295 | 70 |
| std_f64 | 172.30 | 134.34 | 160 | 10399 | 170 |
| mathpp_f64 | 96.80 | 18.82 | 90 | 912 | 91 |

**Summary**: mathpp shows significant performance wins: **59.1% faster** for f32 and **43.9% faster** for f64.

### ceil()

| Implementation | Mean | Std Dev | Min | Max | Median |
|---|---|---|---|---|---|
| std_f32 | 193.74 | 143.31 | 160 | 10119 | 190 |
| mathpp_f32 | 94.81 | 45.41 | 90 | 2916 | 90 |
| std_f64 | 174.73 | 49.99 | 160 | 3366 | 170 |
| mathpp_f64 | 94.85 | 50.72 | 80 | 4198 | 90 |

**Summary**: mathpp shows **51.0% improvement** for f32 and **45.7% improvement** for f64.

### ilogb()

| Implementation | Mean | Std Dev | Min | Max | Median |
|---|---|---|---|---|---|
| std_f32 | 3848.15 | 276.90 | 3787 | 15318 | 3817 |
| mathpp_f32 | 1791.98 | 542.55 | 1703 | 39845 | 1713 |
| std_f64 | 3897.07 | 353.47 | 3827 | 17944 | 3857 |
| mathpp_f64 | 1761.47 | 238.48 | 1703 | 8616 | 1723 |

**Summary**: mathpp shows exceptional performance: **53.5% faster** for f32 and **54.8% faster** for f64.

### floor()

| Implementation | Mean | Std Dev | Min | Max | Median |
|---|---|---|---|---|---|
| std_f32 | 199.88 | 112.04 | 160 | 3146 | 190 |
| mathpp_f32 | 93.74 | 40.65 | 80 | 2965 | 90 |
| std_f64 | 187.50 | 59.94 | 180 | 3717 | 181 |
| mathpp_f64 | 94.65 | 68.65 | 80 | 4268 | 90 |

**Summary**: mathpp shows **53.1% improvement** for f32 and **49.6% improvement** for f64.

### ldexp()

| Implementation | Mean | Std Dev | Min | Max | Median |
|---|---|---|---|---|---|
| std_f32 | 3706.92 | 2076.59 | 3466 | 54232 | 3476 |
| mathpp_f32 | 516.03 | 167.06 | 470 | 4829 | 501 |
| std_f64 | 3676.05 | 1639.17 | 3546 | 59702 | 3577 |
| mathpp_f64 | 514.96 | 134.70 | 481 | 4688 | 510 |

**Summary**: mathpp shows exceptional performance: **86% faster** for f32 and **86% faster** for f64.

## Performance Summary

| Function | f32 Improvement | f64 Improvement |
|---|---|---|
| abs | -0.8% | +1.9% |
| trunc | +59.1% | +43.9% |
| ceil | +51.0% | +45.7% |
| ilogb | +53.5% | +54.8% |
| floor | +53.1% | +49.6% |
| ldexp | +86.8% | +87.4% |

## Key Findings

- **Consistency**: mathpp functions show lower variance across most operations, indicating more predictable performance
- **Rounding Operations**: Functions like `trunc`, `ceil`, and `floor` benefit significantly from mathpp's optimized implementations (45-60% faster)
- **Logarithmic Operations**: `ilogb` sees major speedup (53%+) with notably reduced outliers
- **ldexp**: The `ldexp` function shows outstanding performance with 86%+ improvement over standard library
