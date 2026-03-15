module;

#include <cstdint>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:factorial;

import Mathpp.common;

export namespace mathpp {

template<Scalar T>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr T
factorial(const std::size_t val) MATHPP_NOEXCEPT() {
  T retVal{1};

  for (std::size_t i = 1; i <= val; i++) {
    retVal *= i;
  }

  return retVal;
}

}
