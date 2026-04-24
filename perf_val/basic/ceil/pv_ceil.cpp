#include <array>
#include <cmath>

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

#ifndef MATHPP_PERF_VAL_AS_BENCHMARK

namespace {

pv_utils::Timer timer;

template<typename T>
BENCHPP_BENCHMARK_FUNC
void
stdCeil(const std::array<T, NUM_COUNT>& arr) {
  timer.std.start();
  for (const auto& v : arr) {
    volatile T val = std::ceil(v);
    (void)val;
  }
  timer.std.stop();
  timer.std.recordAndReset();
}

template<typename T>
BENCHPP_BENCHMARK_FUNC
void
mathppCeil(const std::array<T, NUM_COUNT>& arr) {
  timer.mathpp.start();
  for (const auto& v : arr) {
    volatile T val = mathpp::ceil(v);
    (void)val;
  }
  timer.mathpp.stop();
  timer.mathpp.recordAndReset();
}

template<typename T>
void
runValidations(void) {
  timer.clear();

  std::array<T, NUM_COUNT> randArr = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND, UPPER_BOUND);

  for (const auto& v : randArr) {
    REQUIRE(isNearlyEqual(std::ceil(v), mathpp::ceil(v)));
  }

  for (std::size_t i = 0; i < RUN_COUNT; i++) {
    stdCeil(randArr);
    mathppCeil(randArr);
  }

  REQUIRE(timer.cmpTimesWithinTolerance(TOLERANCE));
}

}

TEST_CASE( "ceil", "[basic][ceil]" ) {
  runValidations<double>();
  runValidations<float>();
  runValidations<long double>();
}

#else

namespace {

template<typename T, benchpp::Timer& timer>
BENCHPP_BENCHMARK_FUNC
void
stdCeil(void){
  std::array<T, NUM_COUNT> arr = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND, UPPER_BOUND);
  timer.start();
  for (const auto& v : arr) {
    volatile T val = std::ceil(v);
    (void)val;
  }
  timer.stop();
  timer.recordAndReset();
}

template<typename T, benchpp::Timer& timer>
BENCHPP_BENCHMARK_FUNC
void
mathppCeil(void){
  std::array<T, NUM_COUNT> arr = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND, UPPER_BOUND);
  timer.start();
  for (const auto& v : arr) {
    volatile T val = mathpp::ceil(v);
    (void)val;
  }
  timer.stop();
  timer.recordAndReset();
}

benchpp::Timer stdCeil_f32Timer;
benchpp::Timer stdCeil_f64Timer;
benchpp::Timer mathppCeil_f32Timer;
benchpp::Timer mathppCeil_f64Timer;

benchpp::BenchmarkInfo stdCeil_f32 = {
  .name = "std_ceil32",
  .group = "ceil",
  .function = &stdCeil<float32, stdCeil_f32Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &stdCeil_f32Timer
};

benchpp::BenchmarkInfo stdCeil_f64 = {
  .name = "std_ceil64",
  .group = "ceil",
  .function = &stdCeil<float64, stdCeil_f64Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &stdCeil_f64Timer
};

benchpp::BenchmarkInfo mathppCeil_f32 = {
  .name = "mathpp_ceil32",
  .group = "ceil",
  .function = &mathppCeil<float32, mathppCeil_f32Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &mathppCeil_f32Timer
};

benchpp::BenchmarkInfo mathppCeil_f64 = {
  .name = "mathpp_ceil64",
  .group = "ceil",
  .function = &mathppCeil<float64, mathppCeil_f64Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &mathppCeil_f64Timer
};

}

REGISTER_BENCHMARK(stdCeil_f32);
REGISTER_BENCHMARK(stdCeil_f64);
REGISTER_BENCHMARK(mathppCeil_f32);
REGISTER_BENCHMARK(mathppCeil_f64);

#endif /* MATHPP_PERF_VAL_AS_BENCHMARK */

}
