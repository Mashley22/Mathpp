module;

#include <bit>
#include <climits>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:copysign;

import Mathpp.common;

export namespace mathpp {

template<floating_point T>
[[nodiscard]] MATHPP_PURE_FUNC
constexpr T
copysign(T mag, T sign) MATHPP_NOEXCEPT {
  using Uint_t = MatchUnsignedWidth_t<T>;
  constexpr Uint_t sign_mask = Uint_t(1) << (sizeof(Uint_t) * CHAR_BIT - 1);
  
  auto mag_bits = std::bit_cast<Uint_t>(mag);
  auto sign_bits = std::bit_cast<Uint_t>(sign);
  
  Uint_t result_bits = (mag_bits & ~sign_mask) | (sign_bits & sign_mask);
  
  return std::bit_cast<T>(result_bits);
}

}
