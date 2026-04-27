module;

#include <bit>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:ldexp;

import Mathpp.common;

#define LDEXP_ERROR_CASES(val) \
  if (val == static_cast<T>(0) || isnan(val) || isinf(val)) { \
    return val; \
  }

export namespace mathpp {

/**
 *@brief returns val multipled by 2 raised to the power of exp
*/
template<floating_point T>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr T
ldexp(T val, int exp) MATHPP_NOEXCEPT {
  LDEXP_ERROR_CASES(val);

  using Uint_t = MatchUnsignedWidth_t<T>;
  
  auto bits = std::bit_cast<Uint_t>(val);

  bits += static_cast<Uint_t>(exp) << floating_point_traits<T>::mantissa_bits;

  return std::bit_cast<T>(bits);
}

}
