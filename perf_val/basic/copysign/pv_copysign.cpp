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

#define LOWER_BOUND_X -1e10
#define UPPER_BOUND_X 1e10

#define UPPER_BOUND_Y -1e10
#define LOWER_BOUND_Y -1e10

namespace mathpp {

#ifndef MATHPP_PERF_VAL_AS_BENCHMARK 

namespace {

pv_utils::Timer timer;

template<typename T>
BENCHPP_BENCHMARK_FUNC
void
stdCopysign(const std::array<T, NUM_COUNT>& arrX, const std::array<T, NUM_COUNT>& arrY) {
  timer.std.start();
  for (std::size_t i = 0; i < NUM_COUNT; i++) {
    volatile T val = std::copysign(arrX[i], arrY[i]);
    (void)val;
  }
  timer.std.stop();
  timer.std.recordAndReset();
}

template<typename T>
BENCHPP_BENCHMARK_FUNC
void
mathppCopysign(const std::array<T, NUM_COUNT>& arrX, const std::array<T, NUM_COUNT>& arrY) {
  timer.mathpp.start();
  for (std::size_t i = 0; i < NUM_COUNT; i++) {
    volatile T val = mathpp::copysign(arrX[i], arrY[i]);
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
    T mathppRes = mathpp::copysign(randArrX[i], randArrY[i]);
    T stdRes = std::copysign(randArrX[i], randArrY[i]);
    REQUIRE_THAT(mathppRes, Catch::Matchers::WithinRel(stdRes, mathpp::floating_point_traits<T>::epsilon));
  }

  for (std::size_t i = 0; i < RUN_COUNT; i++) {
    stdCopysign(randArrX, randArrY);
    mathppCopysign(randArrX, randArrY);
  }

  REQUIRE(timer.cmpTimesWithinTolerance(TOLERANCE));
}

}

TEST_CASE( "floating point fmod", "[basic][copysign]" ) {
  runValidations<double>();
  runValidations<float>();
}

#else

namespace {

template<typename T, benchpp::Timer& timer>
BENCHPP_BENCHMARK_FUNC
void
stdCopysign(void){
  std::array<T, NUM_COUNT> arrX = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND_X, UPPER_BOUND_X);
  std::array<T, NUM_COUNT> arrY = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND_Y, UPPER_BOUND_Y);
  timer.start();
  for (std::size_t i = 0; i < NUM_COUNT; i++) {
    volatile T val = std::copysign(arrX[i], arrY[i]);
    (void)val;
  }
  timer.stop();
  timer.recordAndReset();
}

template<typename T, benchpp::Timer& timer>
BENCHPP_BENCHMARK_FUNC
void
mathppCopysign(void){
  std::array<T, NUM_COUNT> arrX = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND_X, UPPER_BOUND_X);
  std::array<T, NUM_COUNT> arrY = pv_utils::generateRandomArray<T, NUM_COUNT>(LOWER_BOUND_Y, UPPER_BOUND_Y);
  timer.start();
  for (std::size_t i = 0; i < NUM_COUNT; i++) {
    volatile T val = mathpp::copysign(arrX[i], arrY[i]);
    (void)val;
  }
  timer.stop();
  timer.recordAndReset();
}

benchpp::Timer stdCopysign_f32Timer;
benchpp::Timer stdCopysign_f64Timer;
benchpp::Timer mathppCopysign_f32Timer;
benchpp::Timer mathppCopysign_f64Timer;

benchpp::BenchmarkInfo stdCopysign_f32 = {
  .name = "std_copysign32",
  .group = "copysign",
  .function = &stdCopysign<float32, stdCopysign_f32Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &stdCopysign_f32Timer
};

benchpp::BenchmarkInfo stdCopysign_f64 = {
  .name = "std_copysign64",
  .group = "copysign",
  .function = &stdCopysign<float64, stdCopysign_f64Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &stdCopysign_f64Timer
};

benchpp::BenchmarkInfo mathppCopysign_f32 = {
  .name = "mathpp_copysign32",
  .group = "copysign",
  .function = &mathppCopysign<float32, mathppCopysign_f32Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &mathppCopysign_f32Timer
};

benchpp::BenchmarkInfo mathppCopysign_f64 = {
  .name = "mathpp_copysign64",
  .group = "copysign",
  .function = &mathppCopysign<float64, mathppCopysign_f64Timer>,
  .runNum = RUN_COUNT,
  .p_timer = &mathppCopysign_f64Timer
};

}

REGISTER_BENCHMARK(stdCopysign_f32);
REGISTER_BENCHMARK(stdCopysign_f64);
REGISTER_BENCHMARK(mathppCopysign_f32);
REGISTER_BENCHMARK(mathppCopysign_f64);

#endif /* MATHPP_PERF_VAL_AS_BENCHMARK */

}
