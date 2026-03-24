module;

#include <cmath>
#include <type_traits>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:fma;

import Mathpp.common;

#ifndef __has_builtin
  #define __has__builtin(x) 
#endif

export namespace mathpp {

template<Scalar T>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr T
fma(T x, T y, T z) MATHPP_NOEXCEPT {

  if (std::is_constant_evaluated()) {
    if (MATHPP_IS_CONSTEXPR(std::fma(x, y, z))) {
      return std::fma(x, y, z);
    }
    else {

      if constexpr (std::is_same_v<T, float> &&
                    MATHPP_HAS_CONSTEXPR_BUILTIN(__builtin_fmaf)) {
        return __builtin_fmaf(x, y, z);
      }
      else if constexpr (std::is_same_v<T, double> &&
                         MATHPP_HAS_CONSTEXPR_BUILTIN(__builtin_fma)) {
        return __builtin_fma(x, y, z);
      }
      else if constexpr (std::is_same_v<T, long double> &&
                         MATHPP_HAS_CONSTEXPR_BUILTIN(__builtin_fmal)) {
        return __builtin_fmal(x, y, z);
      }

      return x * y + z;
    }
  }

  if constexpr (std::is_same_v<T, float> &&
                MATHPP_HAS_BUILTIN(__builtin_fmaf)) {
     return __builtin_fmaf(x, y, z);
  }
  else if constexpr (std::is_same_v<T, double> && 
                     MATHPP_HAS_BUILTIN(__builtin_fma)) {
      return __builtin_fma(x, y, z);
  }
  else if constexpr (std::is_same_v<T, long double> &&
                     MATHPP_HAS_BUILTIN(__builtin_fmal)) {
    return __builtin_fmal(x, y, z);
  }

  return x * y + z;
}

}
