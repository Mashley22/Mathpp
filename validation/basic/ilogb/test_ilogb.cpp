#include <math.h>

#include <catch2/catch_all.hpp>

import Mathpp.basic;
import Mathpp.common;

namespace mathpp {

using namespace mathpp::literals;

namespace {

template<floating_point T>
constexpr void
ilogbStandardErrors(void) {
  STATIC_REQUIRE(ilogb<T, IlogbErrPolicyStd<T>>(std::numeric_limits<T>::infinity()) == INT_MAX);
  STATIC_REQUIRE(ilogb<T, IlogbErrPolicyStd<T>>(-std::numeric_limits<T>::infinity()) == INT_MAX);

  STATIC_REQUIRE(ilogb<T, IlogbErrPolicyStd<T>>(std::numeric_limits<T>::quiet_NaN()) == FP_ILOGBNAN);

  STATIC_REQUIRE(ilogb<T, IlogbErrPolicyStd<T>>(std::numeric_limits<T>::signaling_NaN()) == FP_ILOGBNAN);

  STATIC_REQUIRE(ilogb<T, IlogbErrPolicyStd<T>>(0) == FP_ILOGB0);

  STATIC_REQUIRE(ilogb<T, IlogbErrPolicyStd<T>>(-0) == FP_ILOGB0);
}

TEST_CASE( "ilogb", "[basic][ilogb]" ) {

  SECTION( "float64" ) {
    STATIC_REQUIRE(ilogb(1e100_f64) == 332);
    STATIC_REQUIRE(ilogb(1e-100_f64) == -333);
    STATIC_REQUIRE(ilogb(1_f64) == 0);
    STATIC_REQUIRE(ilogb(2_f64) == 1);
  }

  SECTION( "float32" ) {
    STATIC_REQUIRE(ilogb(1e-20_f32) == -67);
    STATIC_REQUIRE(ilogb(1_f32) == 0);
    STATIC_REQUIRE(ilogb(2_f32) == 1);
  }

  SECTION( "standard error handling" ) {
    ilogbStandardErrors<float32>();
    ilogbStandardErrors<float64>();
  }

}

}

}
