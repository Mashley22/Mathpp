module;

#include <cstdint>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:pow;

import Mathpp.common;

export namespace mathpp {

template<Scalar T>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr T
pow(const T base, std::size_t exponent) MATHPP_NOEXCEPT {
  T retVal{1};
  
  for (std::size_t i = 0; i < exponent; i++) {
    retVal *= base;
  }

  return retVal;
}

}
