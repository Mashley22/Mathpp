module;

#include <cmath>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:compare;

import Mathpp.common;
import :abs;

export namespace mathpp {

/**
 *@brief combines the relativeTolerance and absoluteTolerance and checks whether
 *       a and b lie in the range
 *
 *@note relative tolerance is fraction and hence may be different to the value type if the value
 *      type is integral
 *
 *@tparam T type of the values to compare, and the absolute tolerance      
 *@tparam T_relTolerance the type of the relative tolerance, if T is integral, T_relTolerance != T
 *
 *@param[in] a one of the values to compare
 *@param[in] b the other value to compare
 *@param[in] relativeTolerance the relative tolerance, it is symmetric between the value parameters
 *@param[in] absoluteTolerance the absolute tolerance
 *
*/
template<Scalar T, Scalar T_relTolerance = T> 
[[nodiscard]] MATHPP_CONST_FUNC
constexpr bool
isNearlyEqual(T a, T b, T_relTolerance relativeTolerance, T absoluteTolerance) MATHPP_NOEXCEPT {
  MATHPP_CHECK(relativeTolerance >= T_relTolerance(0) && relativeTolerance < T_relTolerance(1));
  MATHPP_CHECK(absoluteTolerance >= T(0));

  T absDelta = abs(a - b);
  T relativeToleranceAsAbsolute = static_cast<T>(static_cast<T_relTolerance>(std::max(abs(a), abs(b))) * relativeTolerance);
  T totalTolerance = relativeToleranceAsAbsolute + absoluteTolerance;

  return absDelta <= totalTolerance;
}

/**
 *@brief \ref isNearlyEqual but with only a relative tolerance
*/
template<Scalar T, Scalar T_relTolerance = T>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr bool
isNearlyEqualRel(T a, T b, T_relTolerance relativeTolerance) MATHPP_NOEXCEPT {
  return isNearlyEqual<T, T_relTolerance>(a, b, relativeTolerance, T(0));
}

/**
 *@brief \ref isNearlyEqual but with only an absolute tolerance
*/
template<Scalar T>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr bool
isNearlyEqualAbs(T a, T b, T absoluteTolerance) MATHPP_NOEXCEPT {
  return isNearlyEqual<T, T>(a, b, T(0), absoluteTolerance);
}

/**
 *@brief convenience function for floating point numbers
 */
template<typename T>
requires std::is_arithmetic_v<T>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr bool 
isNearlyEqual(T a, T b, T relativeTolerance = std::numeric_limits<T>::epsilon()) MATHPP_NOEXCEPT {
  return isNearlyEqualRel(a, b, relativeTolerance);
}

}
