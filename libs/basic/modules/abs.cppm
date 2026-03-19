module;

#include <type_traits>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:abs;

import Mathpp.common;

export namespace mathpp {

template<Scalar T_in, Scalar T_out = T_in>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr T_out
abs(T_in val) MATHPP_NOEXCEPT {
  static_assert(!std::is_unsigned_v<T_in>);

  if (val >= T_in(0)) {
    return T_out(val);
  }
  return T_out(T_out(0) - val);
}

}
