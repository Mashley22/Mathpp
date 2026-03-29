module;

#include <bit>
#include <cmath>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:ilogb;

import Mathpp.common;

export namespace mathpp {

/**
 *@brief returns the unbiased exponent value of a floating point number.
 *
 *@returns 0 if the input is 0
 *
 *@note UNDEFINED for nan
 *
*/
template<floating_point T>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr int 
ilogb(T x) MATHPP_NOEXCEPT {
  MATHPP_CHECK(!std::isnan(x));

  if (x == 0) {
    return 0;
  }

  int biasedExp = biasedExponent(x);

  if (biasedExp == 0) {
    int leadingZeros = std::countl_zero(mantissa(x)) - floating_point_traits<T>::total_bits + floating_point_traits<T>::mantissa_bits;
    return -floating_point_traits<T>::subnormal_exponent - leadingZeros;
  }
  return biasedExp - floating_point_traits<T>::exponent_bias;
}

/**
 *@brief a more nicely named wrapper for ilogb
*/
template<floating_point T>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr int
unbiased_exponent(T x) MATHPP_NOEXCEPT {
  return ilogb(x);
}

}
