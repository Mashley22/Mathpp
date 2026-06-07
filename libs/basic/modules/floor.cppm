module;

#include <concepts>
#include <string_view>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:floor;

import Mathpp.common;
import :abs;

namespace mathpp::priv {

template<std::floating_point T, std::signed_integral T_int_t>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr T
floorImpl(T val) MATHPP_NOEXCEPT {
  auto intVal = static_cast<T_int_t>(val);
  if (val < 0) {
    intVal--;
  }
  return static_cast<T>(intVal);
}

}

namespace {

[[maybe_unused]] constexpr std::string_view zeroErrMsg = "ceil zero!";
[[maybe_unused]] constexpr std::string_view nanErrMsg = "ceil nan!";
[[maybe_unused]] constexpr std::string_view infErrMsg = "ceil inf!";
[[maybe_unused]] constexpr std::string_view integralLimitErrMsg = 
  "floor integral limit (number has not representable non integer part!)";

}

export namespace mathpp {

template<typename Policy, typename T>
concept FloorErrPolicy = requires {
  typename Policy::General;
  typename Policy::IntegralLimit;
} &&
GeneralErrPolicy<typename Policy::General, T> &&
ErrPolicy<typename Policy::IntegralLimit, T>;

template<typename GeneralPolicy, typename IntegralLimitPolicy>
struct FloorErrPolicySkeleton {
  using General = GeneralPolicy;
  using IntegralLimit = IntegralLimitPolicy;
};

template<floating_point T>
using FloorErrPolicyStd = FloorErrPolicySkeleton<
  GeneralErrPolicySkeleton<T, ErrPolicyPassThrough<T>, ErrPolicyPassThrough<T>, ErrPolicyPassThrough<T>>,
  ErrPolicyPassThrough<T>
>;

template<floating_point T>
using FloorErrPolicyFast = FloorErrPolicySkeleton<
  GeneralErrPolicySkeleton<
    T, 
    ErrPolicyDebugAssert<T, zeroErrMsg>,
    ErrPolicyDebugAssert<T, nanErrMsg>,
    ErrPolicyDebugAssert<T, infErrMsg>
  >,
  ErrPolicyDebugAssert<T, integralLimitErrMsg>
>;

template<floating_point T>
using FloorErrPolicyDefault = 
#ifdef MATHPP_USE_STANDARD_ERROR_POLICY
  FloorErrPolicyStd<T>;
#elifdef MATHPP_USE_FAST_ERROR_POLICY
  FloorErrPolicyFast<T>;
#endif

template<
  std::floating_point T, 
  FloorErrPolicy<T> ErrHandler = FloorErrPolicyDefault<T>
>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr T
floor(T val) MATHPP_NOEXCEPT {
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

  return priv::floorImpl<T, Int_t>(val);
}

}
