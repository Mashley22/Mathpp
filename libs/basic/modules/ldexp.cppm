module;

#include <bit>
#include <cmath>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:ldexp;

import Mathpp.common;

export namespace mathpp {

/**
 *@brief returns val multipled by 2 raised to the power of exp
*/
template<floating_point T>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr T
ldexp(T val, int exp) MATHPP_NOEXCEPT {
  if (val == T(0)) {
    return 0;
  }

  using Uint_t = MatchUnsignedWidth_t<T>;
  
  auto bits = std::bit_cast<Uint_t>(val);

  bits += static_cast<Uint_t>(exp) << floating_point_traits<T>::mantissa_bits;

  return std::bit_cast<T>(bits);
}

}
