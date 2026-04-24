#include <array>
#include <cmath>

#ifndef MATHPP_PERF_VAL_AS_BENCHMARK
#include <catch2/catch_all.hpp>
#endif

#include <Bench++/macros.hpp>

import Benchpp;
import Mathpp_pv_utils;

import Mathpp;

#define NUM_COUNT 2000
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
stdIlogb(const std::array<T, NUM_COUNT>& arr) {
  timer.std.start();
  for (const auto& v : arr) {
    volatile int val = std::ilogb(v);
    (void)val;
  }
  timer.std.stop();
  timer.std.recordAndReset();
}

template<typename T>
BENCHPP_BENCHMARK_FUNC
void
mathppIlogb(const std::array<T, NUM_COUNT>& arr) {
  timer.mathpp.start();
  for (const auto& v : arr) {
    volatile int val = mathpp::ilogb(v);
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
    REQUIRE(isNearlyEqual(std::ilogb(v), mathpp::ilogb(v)));
  }

  for (std::size_t i = 0; i < RUN_COUNT; i++) {
    stdIlogb(randArr);
    mathppIlogb(randArr);
  }

  REQUIRE(timer.cmpTimesWithinTolerance(TOLERANCE));
}

}

TEST_CASE( "ilogb", "[basic][ilogb]" ) {
  runValidations<float64>();
  runValidations<float32>();
  // no long double ... :(
}

#else

namespace {

template<typename T, benchpp::Timer& timer>
BENCHPP_BENCHMARK_FUNC
void
stdIlogb(void){
  std::array<T, NUM_COUNT> arr = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND, UPPER_BOUND);
  timer.start();
  for (const auto& v : arr) {
    volatile int val = std::ilogb(v);
    (void)val;
  }
  timer.stop();
  timer.recordAndReset();
}

template<typename T, benchpp::Timer& timer>
BENCHPP_BENCHMARK_FUNC
void
mathppIlogb(void){
  std::array<T, NUM_COUNT> arr = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND, UPPER_BOUND);
  timer.start();
  for (const auto& v : arr) {
    volatile int val = mathpp::ilogb(v);
    (void)val;
  }
  timer.stop();
  timer.recordAndReset();
}

benchpp::Timer stdIlogb_f32Timer;
benchpp::Timer stdIlogb_f64Timer;
benchpp::Timer mathppIlogb_f32Timer;
benchpp::Timer mathppIlogb_f64Timer;

benchpp::BenchmarkInfo stdIlogb_f32 = {
  .name = "std_ilogb32",
  .group = "ilogb",
  .function = &stdIlogb<float32, stdIlogb_f32Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &stdIlogb_f32Timer
};

benchpp::BenchmarkInfo stdIlogb_f64 = {
  .name = "std_ilogb64",
  .group = "ilogb",
  .function = &stdIlogb<float64, stdIlogb_f64Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &stdIlogb_f64Timer
};

benchpp::BenchmarkInfo mathppIlogb_f32 = {
  .name = "mathpp_ilogb32",
  .group = "ilogb",
  .function = &mathppIlogb<float32, mathppIlogb_f32Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &mathppIlogb_f32Timer
};

benchpp::BenchmarkInfo mathppIlogb_f64 = {
  .name = "mathpp_ilogb64",
  .group = "ilogb",
  .function = &mathppIlogb<float64, mathppIlogb_f64Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &mathppIlogb_f64Timer
};

}

REGISTER_BENCHMARK(stdIlogb_f32);
REGISTER_BENCHMARK(stdIlogb_f64);
REGISTER_BENCHMARK(mathppIlogb_f32);
REGISTER_BENCHMARK(mathppIlogb_f64);

#endif /* MATHPP_PERF_VAL_AS_BENCHMARK */

}
