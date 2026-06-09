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
stdSignbit(const std::array<T, NUM_COUNT>& arr) {
  timer.std.start();
  for (const auto& v : arr) {
    volatile T val = std::signbit(v);
    (void)val;
  }
  timer.std.stop();
  timer.std.recordAndReset();
}

template<typename T>
BENCHPP_BENCHMARK_FUNC
void
mathppSignbit(const std::array<T, NUM_COUNT>& arr) {
  timer.mathpp.start();
  for (const auto& v : arr) {
    volatile T val = mathpp::signbit(v);
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
    REQUIRE(std::signbit(v) == mathpp::signbit(v));
  }

  for (std::size_t i = 0; i < RUN_COUNT; i++) {
    stdSignbit(randArr);
    mathppSignbit(randArr);
  }

  REQUIRE(timer.cmpTimesWithinTolerance(TOLERANCE));
}

}

TEST_CASE( "floating point signbit", "[basic][signbit]" ) {
  runValidations<double>();
  runValidations<float>();
}

#else

namespace {

template<typename T, benchpp::Timer& timer>
BENCHPP_BENCHMARK_FUNC
void
stdSignbit(void){
  std::array<T, NUM_COUNT> arr = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND, UPPER_BOUND);
  timer.start();
  for (const auto& v : arr) {
    volatile bool val = std::signbit(v);
    (void)val;
  }
  timer.stop();
  timer.recordAndReset();
}

template<typename T, benchpp::Timer& timer>
BENCHPP_BENCHMARK_FUNC
void
mathppSignbit(void){
  std::array<T, NUM_COUNT> arr = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND, UPPER_BOUND);
  timer.start();
  for (const auto& v : arr) {
    volatile bool val = mathpp::signbit(v);
    (void)val;
  }
  timer.stop();
  timer.recordAndReset();
}

benchpp::Timer stdSignbit_f32Timer;
benchpp::Timer stdSignbit_f64Timer;
benchpp::Timer mathppSignbit_f32Timer;
benchpp::Timer mathppSignbit_f64Timer;

benchpp::BenchmarkInfo stdSignbit_f32 = {
  .name = "std_signbit32",
  .group = "signbit",
  .function = &stdSignbit<float32, stdSignbit_f32Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &stdSignbit_f32Timer
};

benchpp::BenchmarkInfo stdSignbit_f64 = {
  .name = "std_signbit64",
  .group = "signbit",
  .function = &stdSignbit<float64, stdSignbit_f64Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &stdSignbit_f64Timer
};

benchpp::BenchmarkInfo mathppSignbit_f32 = {
  .name = "mathpp_signbit32",
  .group = "signbit",
  .function = &mathppSignbit<float32, mathppSignbit_f32Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &mathppSignbit_f32Timer
};

benchpp::BenchmarkInfo mathppSignbit_f64 = {
  .name = "mathpp_signbit64",
  .group = "signbit",
  .function = &mathppSignbit<float64, mathppSignbit_f64Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &mathppSignbit_f64Timer
};

}

REGISTER_BENCHMARK(stdSignbit_f32);
REGISTER_BENCHMARK(stdSignbit_f64);
REGISTER_BENCHMARK(mathppSignbit_f32);
REGISTER_BENCHMARK(mathppSignbit_f64);

#endif /* MATHPP_PERF_VAL_AS_BENCHMARK */

}

