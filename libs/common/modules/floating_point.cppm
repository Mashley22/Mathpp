module;

#include <concepts>
#include <numeric>
#include <stdfloat>

export module Mathpp.common:floating_point;

import :traits;

export namespace mathpp {

#ifdef __STDCPP_FLOAT32_T_
using float32 = std::float32_t;
#else
using float32 = float;
static_assert(std::numeric_limits<float>::is_iec559, "Unsupported floating point spec :(");
#endif
static_assert(sizeof(float32) == 4);

#ifdef __STDCPP_FLOAT64_T_
using float64 = std::float64_t;
#else
using float64 = double;
static_assert(std::numeric_limits<double>::is_iec559, "Unsupported floating point spec :(");
#endif
static_assert(sizeof(float64) == 8);

// left undefined so non-floats cause a compile error
template<std::floating_point T>
struct floating_point_traits;

template<std::floating_point T>
struct iec559_traits;

// Maybe change these to numeric limits ?
template<>
struct iec559_traits<float32> {
  using uint_type = MatchUnsignedWidth_t<float32>;
  
  static constexpr int total_bits    = 32;
  static constexpr int exponent_bits = 8;
  static constexpr int mantissa_bits = 23;
  
  static constexpr int exponent_bias = 127;
  static constexpr int max_exponent = 127;
  static constexpr int raw_exponent_max = 255;

  static constexpr uint_type sign_mask     = 0x80000000U; 
  static constexpr uint_type exponent_mask = 0x7F800000U; 
  static constexpr uint_type mantissa_mask = 0x007FFFFFU; 
  
};

template<>
struct iec559_traits<float64> {
  using uint_type = MatchUnsignedWidth_t<float64>;
  
  static constexpr int total_bits    = 64;
  static constexpr int exponent_bits = 11;
  static constexpr int mantissa_bits = 52;
  
  static constexpr int exponent_bias = 1023;
  static constexpr int max_exponent = 1023;
  static constexpr int raw_exponent_max = 2047;

  static constexpr uint_type sign_mask     = 0x8000000000000000ULL; 
  static constexpr uint_type exponent_mask = 0x7FF0000000000000ULL; 
  static constexpr uint_type mantissa_mask = 0x000FFFFFFFFFFFFFULL; 
  
};

namespace literals {
  constexpr float32 operator ""_f32(long double d) { 
    return static_cast<float32>(d); 
  }
  
  constexpr float32 operator ""_f32(unsigned long long int i) {
    return static_cast<float32>(i);
  }

  constexpr float64 operator ""_f64(long double d) { 
    return static_cast<float64>(d); 
  }
  
  constexpr float64 operator ""_f64(unsigned long long int i) {
    return static_cast<float64>(i);
  }
}

template<typename T>
concept floating_point = std::same_as<T, float32> || std::same_as<T, float64>;

}
