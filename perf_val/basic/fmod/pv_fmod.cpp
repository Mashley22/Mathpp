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

#define LOWER_BOUND_X -1000
#define UPPER_BOUND_X 1000

#define UPPER_BOUND_Y 10
#define LOWER_BOUND_Y -10

namespace mathpp {

#ifndef MATHPP_PERF_VAL_AS_BENCHMARK 

namespace {

pv_utils::Timer timer;

template<typename T>
BENCHPP_BENCHMARK_FUNC
void
stdFmod(const std::array<T, NUM_COUNT>& arrX, const std::array<T, NUM_COUNT>& arrY) {
  timer.std.start();
  for (std::size_t i = 0; i < NUM_COUNT; i++) {
    volatile T val = std::fmod(arrX[i], arrY[i]);
    (void)val;
  }
  timer.std.stop();
  timer.std.recordAndReset();
}

template<typename T>
BENCHPP_BENCHMARK_FUNC
void
mathppFmod(const std::array<T, NUM_COUNT>& arrX, const std::array<T, NUM_COUNT>& arrY) {
  timer.mathpp.start();
  for (std::size_t i = 0; i < NUM_COUNT; i++) {
    volatile T val = mathpp::fmodTrunc(arrX[i], arrY[i]);
    (void)val;
  }
  timer.mathpp.stop();
  timer.mathpp.recordAndReset();
}

template<typename T>
void
runValidations(void) {

  timer.clear();

  std::array<T, NUM_COUNT> randArrX = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND_X, UPPER_BOUND_X);
  std::array<T, NUM_COUNT> randArrY = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND_Y, UPPER_BOUND_Y);

  for (std::size_t i = 0; i < NUM_COUNT; i++) {
    T mathppRes = mathpp::abs(mathpp::fmodTrunc(randArrX[i], randArrY[i]) - (randArrY[i] / 2));
    T stdRes = mathpp::abs(std::fmod(randArrX[i], randArrY[i]) - (randArrY[i] / 2));
    REQUIRE_THAT(mathppRes, Catch::Matchers::WithinRel(stdRes, mathpp::floating_point_traits<T>::epsilon));
  }

  for (std::size_t i = 0; i < RUN_COUNT; i++) {
    stdFmod(randArrX, randArrY);
    mathppFmod(randArrX, randArrY);
  }

  REQUIRE(timer.cmpTimesWithinTolerance(TOLERANCE));
}

}

TEST_CASE( "floating point fmod", "[basic][fmod]" ) {
  runValidations<double>();
  runValidations<float>();
}

#else

namespace {

template<typename T, benchpp::Timer& timer>
BENCHPP_BENCHMARK_FUNC
void
stdFmod(void){
  std::array<T, NUM_COUNT> arrX = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND_X, UPPER_BOUND_X);
  std::array<T, NUM_COUNT> arrY = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND_Y, UPPER_BOUND_Y);
  timer.start();
  for (std::size_t i = 0; i < NUM_COUNT; i++) {
    volatile T val = std::fmod(arrX[i], arrY[i]);
    (void)val;
  }
  timer.stop();
  timer.recordAndReset();
}

template<typename T, benchpp::Timer& timer>
BENCHPP_BENCHMARK_FUNC
void
mathppFmodTrunc(void){
  std::array<T, NUM_COUNT> arrX = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND_X, UPPER_BOUND_X);
  std::array<T, NUM_COUNT> arrY = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND_Y, UPPER_BOUND_Y);
  timer.start();
  for (std::size_t i = 0; i < NUM_COUNT; i++) {
    volatile T val = mathpp::fmodTrunc(arrX[i], arrY[i]);
    (void)val;
  }
  timer.stop();
  timer.recordAndReset();
}

benchpp::Timer stdFmod_f32Timer;
benchpp::Timer stdFmod_f64Timer;
benchpp::Timer mathppFmodTrunc_f32Timer;
benchpp::Timer mathppFmodTrunc_f64Timer;

benchpp::BenchmarkInfo stdFmod_f32 = {
  .name = "std_fmod32",
  .group = "fmod",
  .function = &stdFmod<float32, stdFmod_f32Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &stdFmod_f32Timer
};

benchpp::BenchmarkInfo stdFmod_f64 = {
  .name = "std_fmod64",
  .group = "fmod",
  .function = &stdFmod<float64, stdFmod_f64Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &stdFmod_f64Timer
};

benchpp::BenchmarkInfo mathppFmodTrunc_f32 = {
  .name = "mathpp_fmod_trunc32",
  .group = "fmod",
  .function = &mathppFmodTrunc<float32, mathppFmodTrunc_f32Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &mathppFmodTrunc_f32Timer
};

benchpp::BenchmarkInfo mathppFmodTrunc_f64 = {
  .name = "mathpp_fmod_trunc64",
  .group = "fmod",
  .function = &mathppFmodTrunc<float64, mathppFmodTrunc_f64Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &mathppFmodTrunc_f64Timer
};

}

REGISTER_BENCHMARK(stdFmod_f32);
REGISTER_BENCHMARK(stdFmod_f64);
REGISTER_BENCHMARK(mathppFmodTrunc_f32);
REGISTER_BENCHMARK(mathppFmodTrunc_f64);

#endif /* MATHPP_PERF_VAL_AS_BENCHMARK */

}
