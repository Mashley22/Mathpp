module;

#include <concepts>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:ceil;

import Mathpp.common;
import :abs;

namespace mathpp {

namespace priv {


template<std::floating_point T, std::signed_integral T_int_t>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr T
ceilImpl(T val) MATHPP_NOEXCEPT {
  auto intVal = static_cast<T_int_t>(val);
  if (val > 0) {
    intVal++;
  }
  return static_cast<T>(intVal);
}

}

export
template<floating_point T>
using ceilIec559ErrorPolicy = 
GeneralErrPolicySkeleton<T, ErrPolicyPassThrough<T>, ErrPolicyPassThrough<T>, ErrPolicyPassThrough<T>>;

/**
 *@brief returns the closest integer to val not less than it.
 *
 * Error handling is done for the case of 0 and integral valued floats.
 * By default this is setup to match the return values for the iec559/IEE 754:
 * - 0, NaNs and infinity are returned unmodified. 
 * - In this case all integral valued floats are returned unmodified.  
 * 
 * @note that the function naturally does not modify zeros, hence no the error policy may seem strange.
*/
export
template<floating_point T,
  GeneralErrPolicy<T> ErrHandler = ceilIec559ErrorPolicy<T>,
  ErrPolicy<T> IntegralLimitHandler = ErrPolicyPassThrough<T>>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr T
ceil(T val) MATHPP_NOEXCEPT {
  using Int_t = std::conditional_t<std::is_same_v<T, long double>, long long, MatchSignedWidth_t<T>>;
  static_assert(!std::same_as<Int_t, void>, "Failed to find a signed integer type to match the floating point type");
  
  if constexpr (ErrHandler::Zero::requires_check) {
    if (val == 0) return ErrHandler::Zero::on_special(val);
  }

  if constexpr (ErrHandler::Nan::requires_check) {
    if (isnan(val)) return ErrHandler::Nan::on_special(val);
  }
  
  if constexpr (ErrHandler::Inf::requires_check) {
    if (isinf(val)) return ErrHandler::Inf::on_special(val);
  }
  
  if constexpr (IntegralLimitHandler::requires_check) { 
    if (abs(val) >= (1 / floating_point_traits<T>::epsilon))
      return IntegralLimitHandler::on_special(val);
  }

  return priv::ceilImpl<T, Int_t>(val);
}

}
