#!/usr/bin/env python3
"""
Generate performance validation test scripts for Mathpp functions.
Usage: python generate_perf_test.py <function_name> [output_dir]
Example: python generate_perf_test.py ldexp validation/basic/ldexp/
"""

import sys
import argparse
from pathlib import Path
from typing import Optional

TEMPLATE = '''#include <array>
#include <cmath>

#ifndef MATHPP_PERF_VAL_AS_BENCHMARK
#include <catch2/catch_all.hpp>
#endif

#include <Bench++/macros.hpp>

import Benchpp;
import Mathpp_pv_utils;

import Mathpp;

#define NUM_COUNT 10000
#define RUN_COUNT 1000 * RUNTIME_SCALE

#define LOWER_BOUND -1000
#define UPPER_BOUND 1000

namespace mathpp {{

#ifndef MATHPP_PERF_VAL_AS_BENCHMARK 

namespace {{

pv_utils::Timer timer;

template<typename T>
BENCHPP_BENCHMARK_FUNC
void
std{func_name_pascal}(const std::array<T, NUM_COUNT>& arr) {{
  timer.std.start();
  for (const auto& v : arr) {{
    volatile T val = std::{func_name}(v);
    (void)val;
  }}
  timer.std.stop();
  timer.std.recordAndReset();
}}

template<typename T>
BENCHPP_BENCHMARK_FUNC
void
mathpp{func_name_pascal}(const std::array<T, NUM_COUNT>& arr) {{
  timer.mathpp.start();
  for (const auto& v : arr) {{
    volatile T val = mathpp::{func_name}(v);
    (void)val;
  }}
  timer.mathpp.stop();
  timer.mathpp.recordAndReset();
}}

template<typename T>
void
runValidations(void) {{

  timer.clear();

  std::array<T, NUM_COUNT> randArr = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND, UPPER_BOUND);

  for (const auto& v : randArr) {{
    REQUIRE(isNearlyEqualRel(std::{func_name}(v), mathpp::{func_name}(v), std::numeric_limits<T>::epsilon()));
  }}

  for (std::size_t i = 0; i < RUN_COUNT; i++) {{
    std{func_name_pascal}(randArr);
    mathpp{func_name_pascal}(randArr);
  }}

  REQUIRE(timer.cmpTimesWithinTolerance(TOLERANCE));
}}

}}

TEST_CASE( "floating point {func_name}", "[basic][{func_name}]" ) {{
  runValidations<double>();
  runValidations<float>();
}}

#else

namespace {{

template<typename T, benchpp::Timer& timer>
BENCHPP_BENCHMARK_FUNC
void
std{func_name_pascal}(void){{
  std::array<T, NUM_COUNT> arr = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND, UPPER_BOUND);
  timer.start();
  for (const auto& v : arr) {{
    volatile T val = std::{func_name}(v);
    (void)val;
  }}
  timer.stop();
  timer.recordAndReset();
}}

template<typename T, benchpp::Timer& timer>
BENCHPP_BENCHMARK_FUNC
void
mathpp{func_name_pascal}(void){{
  std::array<T, NUM_COUNT> arr = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND, UPPER_BOUND);
  timer.start();
  for (const auto& v : arr) {{
    volatile T val = mathpp::{func_name}(v);
    (void)val;
  }}
  timer.stop();
  timer.recordAndReset();
}}

benchpp::Timer std{func_name_pascal}_f32Timer;
benchpp::Timer std{func_name_pascal}_f64Timer;
benchpp::Timer mathpp{func_name_pascal}_f32Timer;
benchpp::Timer mathpp{func_name_pascal}_f64Timer;

benchpp::BenchmarkInfo std{func_name_pascal}_f32 = {{
  .name = "std_{func_name}32",
  .group = "{func_name}",
  .function = &std{func_name_pascal}<float32, std{func_name_pascal}_f32Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &std{func_name_pascal}_f32Timer
}};

benchpp::BenchmarkInfo std{func_name_pascal}_f64 = {{
  .name = "std_{func_name}64",
  .group = "{func_name}",
  .function = &std{func_name_pascal}<float64, std{func_name_pascal}_f64Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &std{func_name_pascal}_f64Timer
}};

benchpp::BenchmarkInfo mathpp{func_name_pascal}_f32 = {{
  .name = "mathpp_{func_name}32",
  .group = "{func_name}",
  .function = &mathpp{func_name_pascal}<float32, mathpp{func_name_pascal}_f32Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &mathpp{func_name_pascal}_f32Timer
}};

benchpp::BenchmarkInfo mathpp{func_name_pascal}_f64 = {{
  .name = "mathpp_{func_name}64",
  .group = "{func_name}",
  .function = &mathpp{func_name_pascal}<float64, mathpp{func_name_pascal}_f64Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &mathpp{func_name_pascal}_f64Timer
}};

}}

REGISTER_BENCHMARK(std{func_name_pascal}_f32);
REGISTER_BENCHMARK(std{func_name_pascal}_f64);
REGISTER_BENCHMARK(mathpp{func_name_pascal}_f32);
REGISTER_BENCHMARK(mathpp{func_name_pascal}_f64);

#endif /* MATHPP_PERF_VAL_AS_BENCHMARK */

}}
'''

def pascal_case(s: str) -> str:
    """Convert snake_case or lowercase to PascalCase."""
    return ''.join(word.capitalize() for word in s.split('_'))

def generate_perf_test(func_name: str, output_dir: Optional[str] = None) -> str:
    """
    Generate a performance test file for the given function.
    
    Args:
        func_name: Name of the function (e.g., 'ldexp', 'floor')
        output_dir: Optional directory to write the file. If not provided, returns the content.
        
    Returns:
        The generated C++ code as a string.
    """
    func_name_pascal = pascal_case(func_name)
    
    content = TEMPLATE.format(
        func_name=func_name,
        func_name_pascal=func_name_pascal
    )
    
    if output_dir:
        output_path = Path(output_dir)
        output_path.mkdir(parents=True, exist_ok=True)
        
        test_file = output_path / f"pv_{func_name}.cpp"
        test_file.write_text(content)
        print(f"✓ Generated: {test_file}")
        return str(test_file)
    
    return content

def main():
    parser = argparse.ArgumentParser(
        description="Generate performance validation test scripts for Mathpp functions"
    )
    parser.add_argument(
        "function",
        help="Function name (e.g., ldexp, floor, ceil)"
    )
    parser.add_argument(
        "-o", "--output",
        help="Output directory (if not specified, prints to stdout)",
        default=None
    )
    parser.add_argument(
        "-b", "--batch",
        nargs="+",
        help="Generate tests for multiple functions (overrides function argument)"
    )
    
    args = parser.parse_args()
    
    if args.batch:
        functions = args.batch
    else:
        functions = [args.function]
    
    for func in functions:
        if args.output:
            generate_perf_test(func, args.output)
        else:
            content = generate_perf_test(func)
            print(f"\n{'='*60}")
            print(f"Generated test for: {func}")
            print(f"{'='*60}\n")
            print(content)

if __name__ == "__main__":
    main()
