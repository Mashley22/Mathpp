module;

#include <bit>
#include <cstdint>
#include <type_traits>

#include <Mathpp/macros.hpp>

export module Mathpp.basic:abs;

import Mathpp.common;

namespace {

template<typename T_uint>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr T_uint
floatingPointAbsMask(void) {
  return ~(T_uint{0}) >> 1;
}

}

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

template<Scalar T_out = double>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr double 
abs(double val) MATHPP_NOEXCEPT {
  using Uint_t = std::uint64_t;
  static_assert(sizeof(Uint_t) == sizeof(double));

  Uint_t bits = std::bit_cast<Uint_t>(val);

  bits &= floatingPointAbsMask<Uint_t>();

  return T_out(std::bit_cast<double>(bits));
}

template<Scalar T_out = float>
[[nodiscard]] MATHPP_CONST_FUNC
constexpr float 
abs(float val) MATHPP_NOEXCEPT {
  using Uint_t = std::uint32_t;
  static_assert(sizeof(Uint_t) == sizeof(float));

  Uint_t bits = std::bit_cast<Uint_t>(val);

  bits &= floatingPointAbsMask<Uint_t>();

  return T_out(std::bit_cast<float>(bits));
}

}
