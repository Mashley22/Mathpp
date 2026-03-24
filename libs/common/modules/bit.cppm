module;

#include <concepts>
#include <numeric>
#include <utility>

#include <Mathpp/macros.hpp>

export module Mathpp.common:bit;

import :traits;
import :check;

#ifndef __has_builtin
  #define __has_builtin(x)
#endif 

namespace mathpp::priv {

namespace {

template<mathpp::Scalar T>
[[nodiscard]] MATHPP_PURE_FUNC
constexpr bool 
customSignbit(T val) MATHPP_NOEXCEPT {
  if constexpr (std::numeric_limits<T>::is_iec559 &&
                !std::same_as<MatchUnsignedWidth<T>, void>) {

    auto mostSignificantBit = [](T x) {
      MatchUnsignedWidth<T> bits = std::bit_cast<MatchUnsignedWidth>(x);
      return (bits >> (sizeof(MatchUnsignedWidth<T>) - 1));
    };

    return mostSignificantBit(val) != 0;
  }
  else {
    if (val == 0) {
      return (1 / val) < 0;
    }
    else if (val < 0) {
      return true;
    }
    else {
      return false;
    }
  }
}

}

}

export namespace mathpp {

template<Scalar T>
[[nodiscard]] MATHPP_PURE_FUNC
constexpr bool 
signbit(T val) MATHPP_NOEXCEPT {
  if constexpr (std::floating_point<T>) {
    if constexpr (std::is_constant_evaluated()) {
      if constexpr (MATHPP_HAS_CONSTEXPR_BUILTIN(__builtin_signbit)) {
        return __builtin_signbit(val);
      }
      else {
        return priv::customSignbit(val);
      }
    }
    else {
      if constexpr (MATHPP_HAS_BUILTIN(__builtin_signbit)) {
        return __builtin_signbit(val);
      }
      else {
        return priv::customSignbit(val);
      }
    }
  }
  else {
    return priv::customSignbit(val);
  }

  std::unreachable();
}

}
