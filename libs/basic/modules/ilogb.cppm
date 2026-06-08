module;

#include <bit>
#include <string_view>
#include <math.h>
#include <limits.h>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:ilogb;

import Mathpp.common;

namespace {

[[maybe_unused]] constexpr std::string_view zeroErrMsg = "ilogb zero";
[[maybe_unused]] constexpr std::string_view nanErrMsg = "ilog nan";
[[maybe_unused]] constexpr std::string_view infErrMsg = "ilogb inf";

}

export namespace mathpp {

template<floating_point T>
struct IlogbErrPolicyStd {
struct Zero {
  static constexpr bool requires_check = true;
  
  MATHPP_CONST_FUNC [[nodiscard]] 
  static constexpr int
  on_special([[maybe_unused]] T val) MATHPP_NOEXCEPT {
    return FP_ILOGB0;
  }
};

struct Nan {
  static constexpr bool requires_check = true;
  
  MATHPP_CONST_FUNC [[nodiscard]] 
  static constexpr int
  on_special([[maybe_unused]] T val) MATHPP_NOEXCEPT {
    return FP_ILOGBNAN;
  }
};

struct Inf {
  static constexpr bool requires_check = true;
  
  MATHPP_CONST_FUNC [[nodiscard]] 
  static constexpr int
  on_special([[maybe_unused]] T val) MATHPP_NOEXCEPT {
    return INT_MAX;
  }
};
};

template<floating_point T>
struct IlogbErrPolicyFast {
  using Zero = ErrPolicyDebugAssert<T, zeroErrMsg, int>;
  using Nan = ErrPolicyDebugAssert<T, nanErrMsg, int>;
  using Inf = ErrPolicyDebugAssert<T, infErrMsg, int>;
};

template<floating_point T>
using IlogbErrPolicyDefault = 
#ifdef MATHPP_USE_STANDARD_ERROR_POLICY
  IlogbErrPolicyStd<T>;
#elifdef MATHPP_USE_FAST_ERROR_POLICY
  IlogbErrPolicyFast<T>;
#endif

/**
 *@brief returns the unbiased exponent value of a floating point number.
 *
 * Error handling for 0s, nans, and infs is delegated by the error policy,
 * by default following the matches the return values in math.h:
 * - 0 returns FP_ILOGB0
 * - NAN returns FP_ILOGNAN
 * - infinity returns INT_MAX  
*/
template<floating_point T,
  GeneralErrPolicy<T, int> ErrHandler = IlogbErrPolicyDefault<T>
>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr int 
ilogb(T x) MATHPP_NOEXCEPT {

  if constexpr (ErrHandler::Zero::requires_check) {
    if (x == 0) return ErrHandler::Zero::on_special(x);
  }

  if constexpr (ErrHandler::Inf::requires_check) {
    if (isinf(x)) return ErrHandler::Inf::on_special(x);
  }

  if constexpr (ErrHandler::Nan::requires_check) {
    if (isnan(x)) return ErrHandler::Nan::on_special(x);
  }

  int biasedExp = biasedExponent(x);
   
  {
    bool subnormal = (biasedExp == 0);
    if (subnormal) {
      int leadingZeros = std::countl_zero(mantissa(x)) -
                         floating_point_traits<T>::total_bits + floating_point_traits<T>::mantissa_bits;
      return -floating_point_traits<T>::subnormal_exponent - leadingZeros;
    }
  }

  return biasedExp - floating_point_traits<T>::exponent_bias;
}

/**
 *@brief a more nicely named wrapper for /ref ilogb
*/
template<floating_point T,
  GeneralErrPolicy<T, int> ErrHandler = IlogbErrPolicyDefault<T>
>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr int
unbiased_exponent(T x) MATHPP_NOEXCEPT {
  return ilogb<T, ErrHandler>(x);
}

}
