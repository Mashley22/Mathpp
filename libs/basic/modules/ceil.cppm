module;

#include <concepts>
#include <string_view>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:ceil;

import Mathpp.common;
import :abs;

namespace mathpp::priv {

template<std::floating_point T, std::signed_integral T_int_t>
[[nodiscard]] MATHPP_CONST_FUNC
inline constexpr T
ceilImpl(T val) MATHPP_NOEXCEPT {
  auto intVal = static_cast<T_int_t>(val);
  if (val > 0) {
    intVal++;
  }
  return static_cast<T>(intVal);
}

namespace {

[[maybe_unused]] constexpr std::string_view zeroErrMsg = "ceil zero!";
[[maybe_unused]] constexpr std::string_view nanErrMsg = "ceil nan!";
[[maybe_unused]] constexpr std::string_view infErrMsg = "ceil inf!";
[[maybe_unused]] constexpr std::string_view integralLimitErrMsg = 
  "ceil integral limit (number has not representable non integer part!)";

}

}

export namespace mathpp {

template<typename Policy, typename T>
concept CeilErrPolicy = requires {
  typename Policy::General;
  typename Policy::IntegralLimit;
} &&
GeneralErrPolicy<typename Policy::General, T> &&
ErrPolicy<typename Policy::IntegralLimit, T>;

template<typename GeneralPolicy, typename IntegralLimitPolicy>
struct CeilErrPolicySkeleton {
  using General = GeneralPolicy;
  using IntegralLimit = IntegralLimitPolicy;
};

template<floating_point T>
using CeilErrPolicyStd = CeilErrPolicySkeleton<
  GeneralErrPolicySkeleton<T, ErrPolicyPassThrough<T>, ErrPolicyPassThrough<T>, ErrPolicyPassThrough<T>>,
  ErrPolicyPassThrough<T>
>;

template<floating_point T>
using CeilErrPolicyFast = CeilErrPolicySkeleton<
  GeneralErrPolicySkeleton<
    T, 
    ErrPolicyDebugAssert<T, priv::zeroErrMsg>,
    ErrPolicyDebugAssert<T, priv::nanErrMsg>,
    ErrPolicyDebugAssert<T, priv::infErrMsg>
  >,
  ErrPolicyDebugAssert<T, priv::integralLimitErrMsg>
>;

template<floating_point T>
using CeilErrPolicyDefault = 
#ifdef MATHPP_USE_STANDARD_ERROR_POLICY
  CeilErrPolicyStd<T>;
#elifdef MATHPP_USE_FAST_ERROR_POLICY
  CeilErrPolicyFast<T>;
#endif

/**
 *@brief returns the closest integer to val not less than it.
 *
 * Error handling is done for the case of 0 and integral valued floats.
 * By default this is setup to match the return values for math.h:
 * - 0, NaNs and infinity are returned unmodified. 
 * - In this case all integral valued floats are returned unmodified.  
 * 
 * @note that the function naturally does not modify zeros, hence no the error policy may seem strange.
*/
template<floating_point T,
  CeilErrPolicy<T> ErrHandler = CeilErrPolicyDefault<T>
>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr T
ceil(T val) MATHPP_NOEXCEPT {
  using Int_t = std::conditional_t<std::is_same_v<T, long double>, long long, MatchSignedWidth_t<T>>;
  static_assert(!std::same_as<Int_t, void>, "Failed to find a signed integer type to match the floating point type");
  
  if constexpr (ErrHandler::General::Zero::requires_check) {
    if (val == 0) return ErrHandler::General::Zero::on_special(val);
  }

  if constexpr (ErrHandler::General::Nan::requires_check) {
    if (isnan(val)) return ErrHandler::General::Nan::on_special(val);
  }
  
  if constexpr (ErrHandler::General::Inf::requires_check) {
    if (isinf(val)) return ErrHandler::General::Inf::on_special(val);
  }
  
  if constexpr (ErrHandler::IntegralLimit::requires_check) { 
    if (abs(val) >= (1 / floating_point_traits<T>::epsilon))
      return ErrHandler::IntegralLimit::on_special(val);
  }

  return priv::ceilImpl<T, Int_t>(val);
}

}
