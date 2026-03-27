#include <array>
#include <cmath>
#include <iostream>

#ifndef MATHPP_PERF_VAL_AS_BENCHMARK
#include <catch2/catch_all.hpp>
#endif

#include <Bench++/macros.hpp>

import Benchpp;
import Mathpp_pv_utils;

import Mathpp;

#define NUM_COUNT 100
#define RUN_COUNT 1000 * RUNTIME_SCALE

#define LOWER_BOUND -1000
#define UPPER_BOUND 1000

namespace mathpp {

namespace {

pv_utils::Timer timer;

template<typename T>
BENCHPP_BENCHMARK_FUNC
void
stdTrunc(const std::array<T, NUM_COUNT>& arr) {
  timer.std.start();
  for (const auto& v : arr) {
    volatile T val = std::trunc(v);
    (void)val;
  }
  timer.std.stop();
  timer.std.recordAndReset();
}

template<typename T>
BENCHPP_BENCHMARK_FUNC
void
mathppTrunc(const std::array<T, NUM_COUNT>& arr) {
  timer.mathpp.start();
  for (const auto& v : arr) {
    volatile T val = mathpp::trunc(v);
    (void)val;
  }
  timer.mathpp.stop();
  timer.mathpp.recordAndReset();
}

}

#ifndef MATHPP_PERF_VAL_AS_BENCHMARK

namespace {

template<typename T>
void
runValidations(void) {
  timer.clear();

  std::array<T, NUM_COUNT> randArr = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND, UPPER_BOUND);

  for (const auto& v : randArr) {
    REQUIRE(isNearlyEqual(std::trunc(v), mathpp::trunc(v)));
  }

  for (std::size_t i = 0; i < RUN_COUNT; i++) {
    stdTrunc(randArr);
    mathppTrunc(randArr);
  }

  REQUIRE(timer.cmpTimesWithinTolerance(TOLERANCE));
}

}

TEST_CASE( "trunc", "[basic][trunc]" ) {
  runValidations<double>();
  runValidations<float>();
  runValidations<long double>();
}

#else

namespace {

template<typename T, benchpp::Timer& timer>
BENCHPP_BENCHMARK_FUNC
void
stdTrunc(void){
  std::array<T, NUM_COUNT> arr = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND, UPPER_BOUND);
  timer.start();
  for (const auto& v : arr) {
    volatile T val = std::trunc(v);
    (void)val;
  }
  timer.stop();
  timer.recordAndReset();
}

template<typename T, benchpp::Timer& timer>
BENCHPP_BENCHMARK_FUNC
void
mathppTrunc(void){
  std::array<T, NUM_COUNT> arr = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND, UPPER_BOUND);
  timer.start();
  for (const auto& v : arr) {
    volatile T val = mathpp::trunc(v);
    (void)val;
  }
  timer.stop();
  timer.recordAndReset();
}

benchpp::Timer stdTrunc_f32Timer;
benchpp::Timer stdTrunc_f64Timer;
benchpp::Timer mathppTrunc_f32Timer;
benchpp::Timer mathppTrunc_f64Timer;

benchpp::BenchmarkInfo stdTrunc_f32 = {
  .name = "std_trunc",
  .group = "std_f32",
  .function = &stdTrunc<float32, stdTrunc_f32Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &stdTrunc_f32Timer
};

benchpp::BenchmarkInfo stdTrunc_f64 = {
  .name = "std_trunc",
  .group = "std_f64",
  .function = &stdTrunc<float64, stdTrunc_f64Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &stdTrunc_f64Timer
};

benchpp::BenchmarkInfo mathppTrunc_f32 = {
  .name = "mathpp_trunc",
  .group = "mathpp_f32",
  .function = &mathppTrunc<float32, mathppTrunc_f32Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &mathppTrunc_f32Timer
};

benchpp::BenchmarkInfo mathppTrunc_f64 = {
  .name = "mathpp_trunc",
  .group = "mathpp_f64",
  .function = &mathppTrunc<float64, mathppTrunc_f64Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &mathppTrunc_f64Timer
};

}

REGISTER_BENCHMARK(stdTrunc_f32);
REGISTER_BENCHMARK(stdTrunc_f64);
REGISTER_BENCHMARK(mathppTrunc_f32);
REGISTER_BENCHMARK(mathppTrunc_f64);

#endif /* MATHPP_PERF_VAL_AS_BENCHMARK */

}
