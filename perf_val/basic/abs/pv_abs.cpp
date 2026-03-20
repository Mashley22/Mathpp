#include <array>
#include <cmath>
#include <random>

#include <catch2/catch_all.hpp>

#include <Bench++/macros.hpp>

import Benchpp;

import Mathpp;

#define NUM_COUNT 10000
#define RUN_COUNT 1000

#define LOWER_BOUND -1000
#define UPPER_BOUND 1000

#define TOLERANCE 5

namespace mathpp {

namespace {

benchpp::Timer stdTimer;
benchpp::Timer mathppTimer;

template<typename T>
requires std::is_arithmetic_v<T>
[[nodiscard]] std::array<T, NUM_COUNT>
generateRandomArray(void) {
  std::array<T, NUM_COUNT> arr{};

  std::random_device rd;
  std::mt19937 gen(rd());

  if constexpr (std::is_integral_v<T>) {
    std::uniform_int_distribution<T> dist(LOWER_BOUND, UPPER_BOUND);
    for (auto& v : arr)
      v = dist(gen);
  } else if constexpr (std::is_floating_point_v<T>) {
    std::uniform_real_distribution<T> dist(LOWER_BOUND, UPPER_BOUND);
    for (auto& v : arr)
      v = dist(gen);
  }

  return arr;
}

template<typename T>
BENCHPP_BENCHMARK_FUNC
void
stdAbs(const std::array<T, NUM_COUNT>& arr) {
  stdTimer.start();
  for (const auto& v : arr) {
    volatile T val = std::abs(v);
    (void)val;
  }
  stdTimer.stop();
  stdTimer.recordAndReset();
}

template<typename T>
BENCHPP_BENCHMARK_FUNC
void
mathppAbs(const std::array<T, NUM_COUNT>& arr) {
  mathppTimer.start();
  for (const auto& v : arr) {
    volatile T val = mathpp::abs(v);
    (void)val;
  }
  mathppTimer.stop();
  mathppTimer.recordAndReset();
}

template<typename T>
void
runValidations(void) {
  stdTimer = benchpp::Timer{};
  mathppTimer = benchpp::Timer{};

  std::array<T, NUM_COUNT> randArr = generateRandomArray<T>();

  for (std::size_t i = 0; i < RUN_COUNT; i++) {
    stdAbs(randArr);
    mathppAbs(randArr);
  }

  auto stdStats = benchpp::Stats<benchpp::TimeCount_t>::generate(stdTimer.times());
  auto mathppStats = benchpp::Stats<benchpp::TimeCount_t>::generate(mathppTimer.times());

  double combinedStddevOfMean = std::sqrt(stdStats.varianceOfMean() + mathppStats.varianceOfMean());

  REQUIRE(mathppStats.mean < stdStats.mean + combinedStddevOfMean * TOLERANCE);

}

}

TEST_CASE( "integer abs", "[basic][abs]" ) {
  runValidations<std::int32_t>();
  runValidations<std::int64_t>();
}

TEST_CASE( "floating point abs", "[basic][abs]" ) {
  runValidations<double>();
  runValidations<float>();
}

}
