module;

#include <Mathpp/macros.hpp>

export module Mathpp.basic:fmod;

import Mathpp.common;
import :abs;
import :fma;
import :trunc;

namespace mathpp {

/**
 *
 *@brief a function which calculates the floating point remainder of the division 
 *       x / y, using an integer truncation method (i.e. returning x - trunc(x/y) * y),
 *       as such should be used only for small values of the quotient x/y.
 *
 *@note if x / y is very close to an integer value it is extremely likely to fail. 
 *      However the result (r) should be such that abs(r - y/2) is still consistent with std::fmod.
 *      I.e. the result of f(fmod(x, y)) where f is a function with period y, should be consistent
 *      between the fmods.
 *
*/
export 
template<floating_point T>
MATHPP_CONST_FUNC [[nodiscard]]
constexpr T
fmodTrunc(T x, T y) MATHPP_NOEXCEPT {
  if (y == static_cast<T>(0)) {
    return x;
  } 

  MATHPP_CHECK_ASSUME(abs(y / x) > floating_point_traits<T>::epsilon);

  T quotient = trunc(x / y);
  
  return fma(-quotient, y, x);
}

}
