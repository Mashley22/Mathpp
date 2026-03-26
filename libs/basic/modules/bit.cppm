module;

#include <bit>
#include <concepts>
#include <numeric>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:bit;

import Mathpp.common;

#ifndef __has_builtin
  #define __has_builtin(x)
#endif 

namespace mathpp::priv {

template<Scalar T>
[[nodiscard]] MATHPP_PURE_FUNC
constexpr bool 
customSignbit(T val) MATHPP_NOEXCEPT {
  if constexpr (floating_point<T>) {

    auto mostSignificantBit = [](T x) {
      auto bits = std::bit_cast<MatchUnsignedWidth_t<T>>(x);
      return (bits >> (sizeof(MatchUnsignedWidth_t<T>) - 1));
    };

    return mostSignificantBit(val) != 0;
  }

  if (val == 0) {
    return (1 / val) < 0;
  }
  
  return val < 0;
}

}

export namespace mathpp {

template<Scalar T>
[[nodiscard]] MATHPP_PURE_FUNC
constexpr bool 
signbit(T val) MATHPP_NOEXCEPT {
  if constexpr (std::floating_point<T>) {
    if constexpr (MATHPP_HAS_CONSTEXPR_BUILTIN(__builtin_signbit) ||
                  (MATHPP_HAS_BUILTIN(__builtin_signbit) && !std::is_constant_evaluated())) {
      return __builtin_signbit(val);
    }
  }
  return priv::customSignbit(val);
}

}
