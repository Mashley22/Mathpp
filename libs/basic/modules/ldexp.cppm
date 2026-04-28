module;

#include <bit>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:ldexp;

import Mathpp.common;

export namespace mathpp {

template<floating_point T>
using ldexpIec559ErrorPolicy = 
GeneralErrPolicySkeleton<T, ErrPolicyPassThrough<T>, ErrPolicyPassThrough<T>, ErrPolicyPassThrough<T>>;

/**
 *@brief returns val multipled by 2 raised to the power of exp
 *
 * Error handling is delegated by the policy, by default following the iec559/IEEE 754:
 * - 0, infs, and nans and just returned straight out.
*/
template<floating_point T,
  GeneralErrPolicy<T> ErrHandler = ldexpIec559ErrorPolicy<T>
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
