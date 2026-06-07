module;

#include <bit>
#include <string_view>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:ldexp;

import Mathpp.common;

namespace {

[[maybe_unused]] constexpr std::string_view zeroErrMsg = "ldexp zero";
[[maybe_unused]] constexpr std::string_view nanErrMsg = "ldexp nan";
[[maybe_unused]] constexpr std::string_view infErrMsg = "ldexp inf";

}

export namespace mathpp {

template<floating_point T>
using LdexpErrPolicyStd = 
GeneralErrPolicySkeleton<T, ErrPolicyPassThrough<T>, ErrPolicyPassThrough<T>, ErrPolicyPassThrough<T>>;

template<floating_point T>
using LdexpErrPolicyFast = GeneralErrPolicySkeleton<
  T, 
  ErrPolicyDebugAssert<T, zeroErrMsg>,
  ErrPolicyDebugAssert<T, nanErrMsg>,
  ErrPolicyDebugAssert<T, infErrMsg>
>;

template<floating_point T>
using LdexpErrPolicyDefault = 
#ifdef MATHPP_USE_STANDARD_ERROR_POLICY
  LdexpErrPolicyStd<T>;
#elifdef MATHPP_USE_FAST_ERROR_POLICY
  LdLdexpErrPolicyFast<T>;
#endif

/**
 *@brief returns val multipled by 2 raised to the power of exp
 *
 * Error handling for inputs 0s, infs and nans is delegated by the policy,
 * by default following math.h:
 * 0, infinity and NaN are returned unmodified 
*/
template<floating_point T,
  GeneralErrPolicy<T> ErrHandler = LdexpErrPolicyDefault<T>
>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr T
ldexp(T val, int exp) MATHPP_NOEXCEPT {

  if constexpr (ErrHandler::Zero::requires_check) {
    if (val == 0) return ErrHandler::Zero::on_special(val);
  }

  if constexpr (ErrHandler::Inf::requires_check) {
    if (isinf(val)) return ErrHandler::Inf::on_special(val);
  }

  if constexpr (ErrHandler::Nan::requires_check) {
    if (isnan(val)) return ErrHandler::Nan::on_special(val);
  }

  using Uint_t = MatchUnsignedWidth_t<T>;
  
  auto bits = std::bit_cast<Uint_t>(val);

  bits += static_cast<Uint_t>(exp) << floating_point_traits<T>::mantissa_bits;

  return std::bit_cast<T>(bits);
}

}
