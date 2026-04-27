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
template<typename T, typename S>
concept ErrPolicy = Scalar<S> && requires(S val) {
  { T::requires_check } -> std::convertible_to<bool>;

  { T::on_special(val) } -> std::same_as<S>;
};

/**
 *@brief Assumes that a special case does not happen and hence can be ignored.
 *       Does NOT debug assert, for that use \ref ErrPolicyDebugAssert
*/
template<Scalar S>
struct ErrPolicyDoNothing {
  static constexpr bool requires_check = false;

  static MATHPP_CONST_FUNC constexpr S 
  on_special(S val) MATHPP_NOEXCEPT { return val; }

};

/**
 *@brief Similiar to \ref ErrPolicyDoNothing but adds a debug only assert.
*/
template<Scalar S, const std::string_view& msg>
struct ErrPolicyDebugAssert {
  #ifdef NDEBUG
  static constexpr bool requires_check = false;
  #else
  static constexpr bool requires_check = true;
  #endif

  [[noreturn]] static MATHPP_CONST_FUNC constexpr S
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

}

static_assert(mathpp::ErrPolicy<mathpp::ErrPolicyDoNothing<float>, float>);

static constexpr std::string_view str = "Hello";
static_assert(mathpp::ErrPolicy<mathpp::ErrPolicyDebugAssert<float, str>, float>);

static_assert(mathpp::ErrPolicy<mathpp::ErrPolicyPassThrough<float>, float>);
