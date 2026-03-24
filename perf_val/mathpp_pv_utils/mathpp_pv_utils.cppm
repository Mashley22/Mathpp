module;

#include <concepts>
#include <random>

export module Mathpp_pv_utils;

import Benchpp;

export namespace mathpp::pv_utils {

template<typename T, std::size_t N>
requires std::is_arithmetic_v<T>
[[nodiscard]] std::array<T, N>
generateRandomArray(T lower_bound, T upper_bound) {
  std::array<T, N> arr{};

  std::random_device rd;
  std::mt19937 gen(rd());

  if constexpr (std::is_integral_v<T>) {
    std::uniform_int_distribution<T> dist(lower_bound, upper_bound);
    for (auto& v : arr)
      v = dist(gen);
  } else if constexpr (std::is_floating_point_v<T>) {
    std::uniform_real_distribution<T> dist(lower_bound, upper_bound);
    for (auto& v : arr)
      v = dist(gen);
  }

  return arr;
}

struct Timer {
  benchpp::Timer std;
  benchpp::Timer mathpp;

  [[nodiscard]] bool 
  cmpTimesWithinTolerance(double tolerance) {
    auto stdStats = benchpp::Stats<benchpp::TimeCount_t>::generate(std.times());
    auto mathppStats = benchpp::Stats<benchpp::TimeCount_t>::generate(mathpp.times());

    double combinedStddevOfMean = std::sqrt(stdStats.varianceOfMean() + mathppStats.varianceOfMean());

    return mathppStats.mean < stdStats.mean + combinedStddevOfMean * tolerance;
  }

  void
  clear(void) {
    std = benchpp::Timer{};
    mathpp = benchpp::Timer{};
  }

};

}
