module;

#include <bit>
#include <string_view>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:ldexp;

import Mathpp.common;
import :abs;

namespace mathpp::priv {

template<mathpp::floating_point T>
struct LdexpInfo {
  T val;
  int exp;
};

}

namespace {

[[maybe_unused]] constexpr std::string_view zeroErrMsg = "ldexp zero";
[[maybe_unused]] constexpr std::string_view nanErrMsg = "ldexp nan";
[[maybe_unused]] constexpr std::string_view infErrMsg = "ldexp inf";
[[maybe_unused]] constexpr std::string_view overflowErrMsg = "ldexp overflow";
[[maybe_unused]] constexpr std::string_view underflowErrMsg = "ldexp underflow";

}

export namespace mathpp {

template<typename Policy, typename T>
concept LdexpErrPolicy = requires {
  typename Policy::General;
  typename Policy::Overflow;
  typename Policy::Underflow;
} &&
GeneralErrPolicy<typename Policy::General, priv::LdexpInfo<T>, T> &&
ErrPolicy<typename Policy::Underflow, priv::LdexpInfo<T>, T> &&
ErrPolicy<typename Policy::Overflow, priv::LdexpInfo<T>, T>;

template<floating_point T>
struct LdexpErrPolicyStd {

  struct General {
    struct Zero {
      static constexpr bool requires_check = true;
      [[nodiscard]] static MATHPP_CONST_FUNC constexpr T
      on_special(priv::LdexpInfo<T> params) MATHPP_NOEXCEPT {
        return params.val;
      }
    };

    struct Nan {
      static constexpr bool requires_check = true;
      [[nodiscard]] static MATHPP_CONST_FUNC constexpr T
      on_special(priv::LdexpInfo<T> params) MATHPP_NOEXCEPT {
        return params.val;
      }
    };

    struct Inf {
      static constexpr bool requires_check = true;
      [[nodiscard]] static MATHPP_CONST_FUNC constexpr T
      on_special(priv::LdexpInfo<T> params) MATHPP_NOEXCEPT {
        return params.val;
      }
    };

    static constexpr SubnormalErrPolicy subnormal_policy = SubnormalErrPolicy::STANDARD;
  };
  
  struct Overflow {
    static constexpr bool requires_check = true;
    [[nodiscard]] static MATHPP_CONST_FUNC constexpr T
    on_special([[maybe_unused]] priv::LdexpInfo<T> params) MATHPP_NOEXCEPT {
      return floating_point_traits<T>::overflow_val;
    }
  };

  struct Underflow {
    static constexpr bool requires_check = true;
    [[nodiscard]] static MATHPP_CONST_FUNC constexpr T
    on_special([[maybe_unused]] priv::LdexpInfo<T> params) MATHPP_NOEXCEPT {
      return floating_point_traits<T>::overflow_val;
    }
  };
};

template<floating_point T>
struct LdexpErrPolicyFast {

  using General = GeneralErrPolicySkeleton<
    T, 
    ErrPolicyDebugAssert<priv::LdexpInfo<T>, zeroErrMsg, T>,
    ErrPolicyDebugAssert<priv::LdexpInfo<T>, nanErrMsg, T>,
    ErrPolicyDebugAssert<priv::LdexpInfo<T>, infErrMsg, T>,
    SubnormalErrPolicy::ASSERT_NOT
  >;

  using Overflow = ErrPolicyDebugAssert<priv::LdexpInfo<T>, overflowErrMsg, T>;
  using underflow = ErrPolicyDebugAssert<priv::LdexpInfo<T>, underflowErrMsg, T>;
};

template<floating_point T>
using LdexpErrPolicyDefault = 
#ifdef MATHPP_USE_STANDARD_ERROR_POLICY
  LdexpErrPolicyStd<T>;
#elifdef MATHPP_USE_FAST_ERROR_POLICY
  LdexpErrPolicyFast<T>;
#endif

/**
 *@brief returns val multipled by 2 raised to the power of exp
 *
 * Error handling for inputs 0s, infs and nans is delegated by the policy,
 * by default following math.h:
 * 0, infinity and NaN are returned unmodified 
*/
template<floating_point T,
  LdexpErrPolicy<T> ErrHandler = LdexpErrPolicyDefault<T>
>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr T
ldexp(T val, int exp) MATHPP_NOEXCEPT {

  auto ldexpNormalImpl = [](T val, int exp) -> T {
    using Uint_t = MatchUnsignedWidth_t<T>;
    auto bits = std::bit_cast<Uint_t>(val);
    bits += static_cast<Uint_t>(exp) << floating_point_traits<T>::mantissa_bits;
    return std::bit_cast<T>(bits);
  };

  auto willOverflow = [&]() -> bool {
    MATHPP_CHECK_ASSUME(exp > 0);

    if (exp > floating_point_traits<T>::max_exponent) 
      return true;
    T maxVal = ldexpNormalImpl(std::numeric_limits<T>::max(), -exp);
    return abs(val) > maxVal;
  };

  auto willUnderflow = [&]() -> bool {
    MATHPP_CHECK_ASSUME(exp < 0);

    if (exp > floating_point_traits<T>::max_exponent + floating_point_traits<T>::mantissa_bits)
      return true;

    T minVal = ldexpNormalImpl(std::numeric_limits<T>::min(), -exp);

    return abs(val) < minVal;
  };

  priv::LdexpInfo<T> info = { .val = val, .exp = exp};

  if constexpr (ErrHandler::General::Zero::requires_check) {
    if (val == 0) return ErrHandler::General::Zero::on_special(info);
  }

  if constexpr (ErrHandler::General::Inf::requires_check) {
    if (isinf(val)) return ErrHandler::General::Inf::on_special(info);
  }

  if constexpr (ErrHandler::General::Nan::requires_check) {
    if (isnan(val)) return ErrHandler::General::Nan::on_special(info);
  }

  if constexpr (ErrHandler::Underflow::requires_check) {
    if (exp < 0 && willUnderflow()) return ErrHandler::Underflow::on_special(info);
  }

  if constexpr (ErrHandler::Overflow::requires_check) {
    if (exp > 0 && willOverflow()) return ErrHandler::Overflow::on_special(info);
  }

  return ldexpNormalImpl(val, exp);
}

}
