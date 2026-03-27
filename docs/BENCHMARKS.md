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
- **Compiler**: clang 21.1.8
- **Compiler options:** run using gnu++23, O3 with flto=thin (cmake ipo default for clang), no-trapping-math and no-round-math

## Benchmark Results

### abs()

| Implementation | Mean | Std Dev | Min | Max | Median |
|---|---|---|---|---|---|
| std_f32 | 2894.97 | 1309.38 | 2674 | 103731 | 2895 |
| mathpp_f32 | 2853.64 | 925.25 | 2715 | 25657 | 2745 |
| std_f64 | 2958.03 | 1222.44 | 2775 | 88723 | 2925 |
| mathpp_f64 | 2948.31 | 841.31 | 2765 | 27831 | 2916 |

**Summary**: mathpp_f32 shows ~1.4% performance improvement with lower variance. mathpp_f64 shows ~0.3% performance improvement with reduced variance.

### trunc()

| Implementation | Mean | Std Dev | Min | Max | Median |
|---|---|---|---|---|---|
| std_f32 | 192.57 | 76.75 | 180 | 7164 | 190 |
| mathpp_f32 | 74.20 | 43.38 | 60 | 932 | 70 |
| std_f64 | 219.34 | 227.17 | 160 | 3867 | 180 |
| mathpp_f64 | 97.83 | 58.02 | 90 | 2675 | 90 |

**Summary**: mathpp shows significant performance wins: **61.5% faster** for f32 and **55.4% faster** for f64.

### ceil()

| Implementation | Mean | Std Dev | Min | Max | Median |
|---|---|---|---|---|---|
| std_f32 | 209.33 | 213.52 | 180 | 13855 | 190 |
| mathpp_f32 | 99.83 | 77.78 | 80 | 902 | 90 |
| std_f64 | 185.80 | 169.63 | 160 | 12844 | 180 |
| mathpp_f64 | 107.10 | 106.94 | 80 | 2766 | 90 |

**Summary**: mathpp shows **52.3% improvement** for f32 and **42.4% improvement** for f64.

### ilogb()

| Implementation | Mean | Std Dev | Min | Max | Median |
|---|---|---|---|---|---|
| std_f32 | 4396.61 | 2466.57 | 4167 | 57777 | 4198 |
| mathpp_f32 | 1722.22 | 286.72 | 1673 | 15218 | 1693 |
| std_f64 | 4029.01 | 478.68 | 3786 | 34263 | 4207 |
| mathpp_f64 | 1734.05 | 517.97 | 1683 | 15619 | 1703 |

**Summary**: mathpp shows exceptional performance: **60.8% faster** for f32 and **56.9% faster** for f64.

### floor()

| Implementation | Mean | Std Dev | Min | Max | Median |
|---|---|---|---|---|---|
| std_f32 | 229.10 | 321.27 | 180 | 22521 | 190 |
| mathpp_f32 | 108.51 | 109.51 | 80 | 2244 | 90 |
| std_f64 | 192.63 | 127.65 | 180 | 6142 | 181 |
| mathpp_f64 | 96.15 | 61.99 | 80 | 3236 | 90 |

**Summary**: mathpp shows **52.6% improvement** for f32 and **50.1% improvement** for f64.

## Performance Summary

| Function | f32 Improvement | f64 Improvement |
|---|---|---|
| abs | +1.4% | +0.3% |
| trunc | +61.5% | +55.4% |
| ceil | +52.3% | +42.4% |
| ilogb | +60.8% | +56.9% |
| floor | +52.6% | +50.1% |

## Key Findings

- **Consistency**: mathpp functions show lower variance across most operations, indicating more predictable performance
- **Rounding Operations**: Functions like `trunc`, `ceil`, and `floor` benefit significantly from mathpp's optimized implementations (50-60% faster)
- **Logarithmic Operations**: `ilogb` sees the largest speedup (60%+) with dramatically reduced outliers
- **Edge Cases**: Standard library functions show occasional spikes to extreme values, while mathpp maintains tighter bounds

## Notes

- For reproducible results in your environment, build the benchmarks using benchmark.sh provided in build/perf_val directory
