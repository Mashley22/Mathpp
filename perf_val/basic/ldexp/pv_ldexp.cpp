#include <array>
#include <cmath>

#ifndef MATHPP_PERF_VAL_AS_BENCHMARK
#include <catch2/catch_all.hpp>
#endif

#include <Bench++/macros.hpp>

import Benchpp;
import Mathpp_pv_utils;

import Mathpp;

#define NUM_COUNT 1000
#define RUN_COUNT 1000 * RUNTIME_SCALE

#define LOWER_BOUND -1000
#define UPPER_BOUND 1000

#define EXPONENT 10

namespace mathpp {

#ifndef MATHPP_PERF_VAL_AS_BENCHMARK

namespace {

pv_utils::Timer timer;

template<typename T>
BENCHPP_BENCHMARK_FUNC
void
stdLdexp(const std::array<T, NUM_COUNT>& arr) {
  timer.std.start();
  for (const auto& v : arr) {
    volatile T val = std::ldexp(v, EXPONENT);
    (void)val;
  }
  timer.std.stop();
  timer.std.recordAndReset();
}

template<typename T>
BENCHPP_BENCHMARK_FUNC
void
mathppLdexp(const std::array<T, NUM_COUNT>& arr) {
  timer.mathpp.start();
  for (const auto& v : arr) {
    volatile T val = mathpp::ldexp(v, EXPONENT);
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
    REQUIRE(isNearlyEqualRel(std::ldexp(v, EXPONENT), mathpp::ldexp(v, EXPONENT), std::numeric_limits<T>::epsilon()));
  }

  for (std::size_t i = 0; i < RUN_COUNT; i++) {
    stdLdexp(randArr);
    mathppLdexp(randArr);
  }

  REQUIRE(timer.cmpTimesWithinTolerance(TOLERANCE));
}

}

TEST_CASE( "ldexp", "[basic][ldexp]" ) {
  runValidations<float32>();
  runValidations<float64>();
}

#else

namespace {

template<typename T, benchpp::Timer& timer>
BENCHPP_BENCHMARK_FUNC
void
stdLdexp(void){
  std::array<T, NUM_COUNT> arr = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND, UPPER_BOUND);
  timer.start();
  for (const auto& v : arr) {
    volatile T val = std::ldexp(v, EXPONENT);
    (void)val;
  }
  timer.stop();
  timer.recordAndReset();
}

template<typename T, benchpp::Timer& timer>
BENCHPP_BENCHMARK_FUNC
void
mathppLdexp(void){
  std::array<T, NUM_COUNT> arr = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND, UPPER_BOUND);
  timer.start();
  for (const auto& v : arr) {
    volatile T val = mathpp::ldexp(v, EXPONENT);
    (void)val;
  }
  timer.stop();
  timer.recordAndReset();
}

benchpp::Timer stdLdexp_f32Timer;
benchpp::Timer stdLdexp_f64Timer;
benchpp::Timer mathppLdexp_f32Timer;
benchpp::Timer mathppLdexp_f64Timer;

benchpp::BenchmarkInfo stdLdexp_f32 = {
  .name = "std_ldexp",
  .group = "std_f32",
  .function = &stdLdexp<float32, stdLdexp_f32Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &stdLdexp_f32Timer
};

benchpp::BenchmarkInfo stdLdexp_f64 = {
  .name = "std_ldexp",
  .group = "std_f64",
  .function = &stdLdexp<float64, stdLdexp_f64Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &stdLdexp_f64Timer
};

benchpp::BenchmarkInfo mathppLdexp_f32 = {
  .name = "mathpp_ldexp",
  .group = "mathpp_f32",
  .function = &mathppLdexp<float32, mathppLdexp_f32Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &mathppLdexp_f32Timer
};

benchpp::BenchmarkInfo mathppLdexp_f64 = {
  .name = "mathpp_ldexp",
  .group = "mathpp_f64",
  .function = &mathppLdexp<float64, mathppLdexp_f64Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &mathppLdexp_f64Timer
};

}

REGISTER_BENCHMARK(stdLdexp_f32);
REGISTER_BENCHMARK(stdLdexp_f64);
REGISTER_BENCHMARK(mathppLdexp_f32);
REGISTER_BENCHMARK(mathppLdexp_f64);

#endif /* MATHPP_PERF_VAL_AS_BENCHMARK */

}
