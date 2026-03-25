module;

#include <bit>
#include <cstdint>
#include <numeric>
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

  using UintIn_t = MatchUnsignedWidth_t<T_in>;

  if constexpr (std::floating_point<T_in> && 
                std::numeric_limits<T_in>::is_iec559 &&
                !std::is_same_v<UintIn_t, void>) {

    auto floatingPointAbsMask = [](){
      return ~(UintIn_t{0}) >> 1;
    };

    UintIn_t bits = std::bit_cast<UintIn_t>(val);

    bits &= floatingPointAbsMask();

    return T_out(std::bit_cast<T_in>(bits));
  }
  else {
    if (val >= T_in(0)) {
      return T_out(val);
    }
    return T_out(T_out(0) - T_out(val));
  }
}

}
