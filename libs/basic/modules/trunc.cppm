module;

#include <concepts>
#include <string_view>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:trunc;

import Mathpp.common;
import :abs;

namespace mathpp::priv {

template<std::floating_point T, std::signed_integral T_int_t>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr T
truncImpl(T val) MATHPP_NOEXCEPT {
  return static_cast<T>(static_cast<T_int_t>(val));
}

}

namespace {

[[maybe_unused]] constexpr std::string_view zeroErrMsg = "ceil zero!";
[[maybe_unused]] constexpr std::string_view nanErrMsg = "ceil nan!";
[[maybe_unused]] constexpr std::string_view infErrMsg = "ceil inf!";
[[maybe_unused]] constexpr std::string_view integralLimitErrMsg = 
  "trunc integral limit (number has not representable non integer part!)";

}

export namespace mathpp {

template<typename Policy, typename T>
concept TruncErrPolicy = requires {
  typename Policy::General;
  typename Policy::IntegralLimit;
} &&
GeneralErrPolicy<typename Policy::General, T> &&
ErrPolicy<typename Policy::IntegralLimit, T>;

template<typename GeneralPolicy, typename IntegralLimitPolicy>
struct TruncErrPolicySkeleton {
  using General = GeneralPolicy;
  using IntegralLimit = IntegralLimitPolicy;
};

template<floating_point T>
using TruncErrPolicyStd = TruncErrPolicySkeleton<
  GeneralErrPolicySkeleton<T, ErrPolicyPassThrough<T>, ErrPolicyPassThrough<T>, ErrPolicyPassThrough<T>>,
  ErrPolicyPassThrough<T>
>;

template<floating_point T>
using TruncErrPolicyFast = TruncErrPolicySkeleton<
  GeneralErrPolicySkeleton<
    T, 
    ErrPolicyDebugAssert<T, zeroErrMsg>,
    ErrPolicyDebugAssert<T, nanErrMsg>,
    ErrPolicyDebugAssert<T, infErrMsg>
  >,
  ErrPolicyDebugAssert<T, integralLimitErrMsg>
>;

template<floating_point T>
using TruncErrPolicyDefault = 
#ifdef MATHPP_USE_STANDARD_ERROR_POLICY
  TruncErrPolicyStd<T>;
#elifdef MATHPP_USE_FAST_ERROR_POLICY
  TruncErrPolicyFast<T>;
#endif

template<
  std::floating_point T,
  TruncErrPolicy<T> ErrHandler = TruncErrPolicyDefault<T>
>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr T
trunc(T val) MATHPP_NOEXCEPT {
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
  
  return priv::truncImpl<T, Int_t>(val);
}

}
