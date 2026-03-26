#include <array>
#include <cmath>
#include <random>

#include <catch2/catch_all.hpp>

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

}
