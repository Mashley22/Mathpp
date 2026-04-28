module;

#include <cassert>
#include <concepts>
#include <string_view>

#include <Mathpp/macros.hpp>

export module Mathpp.common:err_policy;

import :traits;
import :check;

export namespace mathpp {

/**
 *@brief The error policy concept, the requires check is mostly provided for compatibility
 *       with the \ref ErrPolicyDoNothing
*/
template<typename T, typename S, typename T_output = S>
concept ErrPolicy = Scalar<S> && requires(S val) {
  { T::requires_check } -> std::convertible_to<bool>;

  { T::on_special(val) } -> std::same_as<T_output>;
};

/**
 *@brief The error policy concept to cover the general 3 types of possible errors, nans, infs, and zeros.
 *       See \ref GeneralErrPolicySkeleton for a struct to help make this more convenient.
*/
template<typename T, typename S, typename T_output = S>
concept GeneralErrPolicy = Scalar<S> && requires {
  typename T::Zero;
  typename T::Nan;
  typename T::Inf;
} && 
ErrPolicy<typename T::Zero, S, T_output> &&
ErrPolicy<typename T::Nan, S, T_output> &&
ErrPolicy<typename T::Inf, S, T_output>;

/**
 *@brief Assumes that a special case does not happen and hence can be ignored.
 *       Does NOT debug assert, for that use \ref ErrPolicyDebugAssert
*/
template<Scalar S, typename T_output = S>
struct ErrPolicyDoNothing {
  static constexpr bool requires_check = false;

  static MATHPP_CONST_FUNC constexpr T_output
  on_special([[maybe_unused]] S val) MATHPP_NOEXCEPT {}

};

/**
 *@brief Similiar to \ref ErrPolicyDoNothing but adds a debug only assert.
*/
template<Scalar S, const std::string_view& msg, typename T_output = S>
struct ErrPolicyDebugAssert {
  #ifdef NDEBUG
  static constexpr bool requires_check = false;
  #else
  static constexpr bool requires_check = true;
  #endif

  [[noreturn]] static MATHPP_CONST_FUNC constexpr T_output
  on_special([[maybe_unused]] S val) MATHPP_NOEXCEPT { 
    MATHPP_CHECK(false, std::string(msg));
  }
};

/**
 *@brief Returns the special value. 
*/
template<Scalar S>
struct ErrPolicyPassThrough {
  static constexpr bool requires_check = true;

  static MATHPP_CONST_FUNC constexpr S 
  on_special(S val) MATHPP_NOEXCEPT { return val; }
};

/**
 *@brief a struct to make covering the generic 3 types of possible errors easier.
 *       see \ref GeneralErrPolicy
 */
template<Scalar S,
  ErrPolicy<S> ErrPolicyZero = ErrPolicyPassThrough<S>,
  ErrPolicy<S> ErrPolicyNan = ErrPolicyPassThrough<S>,
  ErrPolicy<S> ErrPolicyInf = ErrPolicyPassThrough<S>
>
struct GeneralErrPolicySkeleton {
  using Zero = ErrPolicyZero;
  using Nan = ErrPolicyNan;
  using Inf = ErrPolicyInf;
};

/**
 *@brief An alias to apply the same error policy over all the three common error types in
 *       \ref GeneralErrPolicy
 */
template<Scalar S, ErrPolicy<S> Policy>
using EqualErrPolicy = GeneralErrPolicySkeleton<S, Policy, Policy, Policy>;

}

static_assert(mathpp::ErrPolicy<mathpp::ErrPolicyDoNothing<float>, float>);

static constexpr std::string_view str = "Hello";
static_assert(mathpp::ErrPolicy<mathpp::ErrPolicyDebugAssert<float, str>, float>);

static_assert(mathpp::ErrPolicy<mathpp::ErrPolicyPassThrough<float>, float>);

static_assert(mathpp::GeneralErrPolicy<mathpp::GeneralErrPolicySkeleton<float>, float>);
