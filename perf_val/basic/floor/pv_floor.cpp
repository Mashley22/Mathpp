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

namespace {

pv_utils::Timer timer;

template<typename T>
BENCHPP_BENCHMARK_FUNC
void
stdFloor(const std::array<T, NUM_COUNT>& arr) {
  timer.std.start();
  for (const auto& v : arr) {
    volatile T val = std::floor(v);
    (void)val;
  }
  timer.std.stop();
  timer.std.recordAndReset();
}

template<typename T>
BENCHPP_BENCHMARK_FUNC
void
mathppFloor(const std::array<T, NUM_COUNT>& arr) {
  timer.mathpp.start();
  for (const auto& v : arr) {
    volatile T val = mathpp::floor(v);
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
    REQUIRE(isNearlyEqual(std::floor(v), mathpp::floor(v)));
  }

  for (std::size_t i = 0; i < RUN_COUNT; i++) {
    stdFloor(randArr);
    mathppFloor(randArr);
  }

  REQUIRE(timer.cmpTimesWithinTolerance(TOLERANCE));
}

}

TEST_CASE( "floor", "[basic][floor]" ) {
  runValidations<double>();
  runValidations<float>();
  runValidations<long double>();
}

#else

namespace {

template<typename T, benchpp::Timer& timer>
BENCHPP_BENCHMARK_FUNC
void
stdFloor(void){
  std::array<T, NUM_COUNT> arr = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND, UPPER_BOUND);
  timer.start();
  for (const auto& v : arr) {
    volatile T val = std::floor(v);
    (void)val;
  }
  timer.stop();
  timer.recordAndReset();
}

template<typename T, benchpp::Timer& timer>
BENCHPP_BENCHMARK_FUNC
void
mathppFloor(void){
  std::array<T, NUM_COUNT> arr = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND, UPPER_BOUND);
  timer.start();
  for (const auto& v : arr) {
    volatile T val = mathpp::floor(v);
    (void)val;
  }
  timer.stop();
  timer.recordAndReset();
}

benchpp::Timer stdFloor_f32Timer;
benchpp::Timer stdFloor_f64Timer;
benchpp::Timer mathppFloor_f32Timer;
benchpp::Timer mathppFloor_f64Timer;

benchpp::BenchmarkInfo stdFloor_f32 = {
  .name = "std_floor",
  .group = "std_f32",
  .function = &stdFloor<float32, stdFloor_f32Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &stdFloor_f32Timer
};

benchpp::BenchmarkInfo stdFloor_f64 = {
  .name = "std_floor",
  .group = "std_f64",
  .function = &stdFloor<float64, stdFloor_f64Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &stdFloor_f64Timer
};

benchpp::BenchmarkInfo mathppFloor_f32 = {
  .name = "mathpp_floor",
  .group = "mathpp_f32",
  .function = &mathppFloor<float32, mathppFloor_f32Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &mathppFloor_f32Timer
};

benchpp::BenchmarkInfo mathppFloor_f64 = {
  .name = "mathpp_floor",
  .group = "mathpp_f64",
  .function = &mathppFloor<float64, mathppFloor_f64Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &mathppFloor_f64Timer
};

}

REGISTER_BENCHMARK(stdFloor_f32);
REGISTER_BENCHMARK(stdFloor_f64);
REGISTER_BENCHMARK(mathppFloor_f32);
REGISTER_BENCHMARK(mathppFloor_f64);

#endif /* MATHPP_PERF_VAL_AS_BENCHMARK */

}
