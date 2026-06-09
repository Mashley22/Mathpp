module;

#include <bit>
#include <climits>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:signbit;

import Mathpp.common;

export namespace mathpp {

template<Scalar T>
[[nodiscard]] MATHPP_PURE_FUNC
constexpr bool 
signbit(T val) MATHPP_NOEXCEPT {
  if constexpr (floating_point<T>) {

    auto mostSignificantBit = [](T x) {
      auto bits = std::bit_cast<MatchUnsignedWidth_t<T>>(x);
      return (bits >> (sizeof(T) * CHAR_BIT - 1));
    };

    return mostSignificantBit(val) != 0;
  }

  return val < 0;
}

}
