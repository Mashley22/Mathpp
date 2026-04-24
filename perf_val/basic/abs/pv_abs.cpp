#include <array>
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

namespace mathpp {

#ifndef MATHPP_PERF_VAL_AS_BENCHMARK 

namespace {

pv_utils::Timer timer;

template<typename T>
BENCHPP_BENCHMARK_FUNC
void
stdAbs(const std::array<T, NUM_COUNT>& arr) {
  timer.std.start();
  for (const auto& v : arr) {
    volatile T val = std::abs(v);
    (void)val;
  }
  timer.std.stop();
  timer.std.recordAndReset();
}

template<typename T>
BENCHPP_BENCHMARK_FUNC
void
mathppAbs(const std::array<T, NUM_COUNT>& arr) {
  timer.mathpp.start();
  for (const auto& v : arr) {
    volatile T val = mathpp::abs(v);
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
    REQUIRE(isNearlyEqualRel(std::abs(v), mathpp::abs(v), std::numeric_limits<T>::epsilon()));
  }

  for (std::size_t i = 0; i < RUN_COUNT; i++) {
    stdAbs(randArr);
    mathppAbs(randArr);
  }

  REQUIRE(timer.cmpTimesWithinTolerance(TOLERANCE));
}

}

TEST_CASE( "integer abs", "[basic][abs]" ) {
  runValidations<std::int32_t>();
  runValidations<std::int64_t>();
}

TEST_CASE( "floating point abs", "[basic][abs]" ) {
  // doesn't work for long double ... :(
  runValidations<double>();
  runValidations<float>();
}

#else

namespace {

template<typename T, benchpp::Timer& timer>
BENCHPP_BENCHMARK_FUNC
void
stdAbs(void){
  std::array<T, NUM_COUNT> arr = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND, UPPER_BOUND);
  timer.start();
  for (const auto& v : arr) {
    volatile T val = std::abs(v);
    (void)val;
  }
  timer.stop();
  timer.recordAndReset();
}

template<typename T, benchpp::Timer& timer>
BENCHPP_BENCHMARK_FUNC
void
mathppAbs(void){
  std::array<T, NUM_COUNT> arr = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND, UPPER_BOUND);
  timer.start();
  for (const auto& v : arr) {
    volatile T val = mathpp::abs(v);
    (void)val;
  }
  timer.stop();
  timer.recordAndReset();
}

benchpp::Timer stdAbs_f32Timer;
benchpp::Timer stdAbs_f64Timer;
benchpp::Timer mathppAbs_f32Timer;
benchpp::Timer mathppAbs_f64Timer;

benchpp::BenchmarkInfo stdAbs_f32 = {
  .name = "std_abs32",
  .group = "abs",
  .function = &stdAbs<float32, stdAbs_f32Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &stdAbs_f32Timer
};

benchpp::BenchmarkInfo stdAbs_f64 = {
  .name = "std_abs32",
  .group = "abs",
  .function = &stdAbs<float64, stdAbs_f64Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &stdAbs_f64Timer
};

benchpp::BenchmarkInfo mathppAbs_f32 = {
  .name = "mathpp_abs32",
  .group = "abs",
  .function = &mathppAbs<float32, mathppAbs_f32Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &mathppAbs_f32Timer
};

benchpp::BenchmarkInfo mathppAbs_f64 = {
  .name = "mathpp_abs64",
  .group = "abs",
  .function = &mathppAbs<float64, mathppAbs_f64Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &mathppAbs_f64Timer
};

}

REGISTER_BENCHMARK(stdAbs_f32);
REGISTER_BENCHMARK(stdAbs_f64);
REGISTER_BENCHMARK(mathppAbs_f32);
REGISTER_BENCHMARK(mathppAbs_f64);

#endif /* MATHPP_PERF_VAL_AS_BENCHMARK */

}
