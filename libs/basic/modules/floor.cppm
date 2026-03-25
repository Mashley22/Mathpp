module;

#include <concepts>
#include <numeric>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:floor;

import Mathpp.common;

namespace mathpp {

namespace priv {

template<std::floating_point T, std::signed_integral T_int_t>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr T
floorSmall(T val) MATHPP_NOEXCEPT {
  auto intVal = static_cast<T_int_t>(val);
  if (val < 0) {
    intVal--;
  }
  return static_cast<T>(intVal);
}

template<std::floating_point T>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr T
floorLarge(T val) MATHPP_NOEXCEPT {
  return val;
}

}

export
template<std::floating_point T>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr T
floor(T val) MATHPP_NOEXCEPT {
  using Int_t = std::conditional_t<std::is_same_v<T, long double>, long long, MatchSignedWidth_t<T>>;
  
  static_assert(!std::same_as<Int_t, void>, "Failed to find a signed integer type to match the floating point type");

  if (val >= static_cast<T>(std::numeric_limits<Int_t>::max()) ||
      val <= static_cast<T>(std::numeric_limits<Int_t>::lowest())) {
    return priv::floorLarge(val);
  }
  return priv::floorSmall<T, Int_t>(val);
}

}
