module;

#include <type_traits>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:abs;

import Mathpp.common;

export namespace mathpp {

template<Scalar T>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr T
abs(T val) {
  static_assert(!std::is_unsigned_v<T>); // dont use is_signed_v, think about it

  if (val >= T(0)) {
    return val;
  }
  return -val;
}

}
