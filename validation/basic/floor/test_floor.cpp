#include <catch2/catch_all.hpp>

import Mathpp.basic;
import Mathpp.common;

namespace mathpp {

using namespace mathpp::literals;

namespace {

template<floating_point T>
constexpr void
floorStandardErrors(void) {
  STATIC_REQUIRE(isinf(
    floor<T, FloorErrPolicyStd<T>>(
      std::numeric_limits<T>::infinity()
    )
  ));

  STATIC_REQUIRE(isinf(
    floor<T, FloorErrPolicyStd<T>>(
      -std::numeric_limits<T>::infinity()
    )
  ));

  STATIC_REQUIRE(isnan(
    floor<T, FloorErrPolicyStd<T>>(
      std::numeric_limits<T>::quiet_NaN()
    )
  ));

  STATIC_REQUIRE(isnan(
    floor<T, FloorErrPolicyStd<T>>(
      std::numeric_limits<T>::signaling_NaN()
    )
  ));

  STATIC_REQUIRE(floor<T, FloorErrPolicyStd<T>>(0) == 0);

  STATIC_REQUIRE(floor<T, FloorErrPolicyStd<T>>(-0) == 0);
}

}

TEST_CASE( "floating point floor", "[trunc][basic]" ) {

  SECTION( "float64" ) {
    STATIC_REQUIRE(isNearlyEqual(floor(3.7_f64),  3.0_f64));
    STATIC_REQUIRE(isNearlyEqual(floor(-3.7_f64), -4.0_f64));

    STATIC_REQUIRE(isNearlyEqual(floor(0.0_f64),  0.0_f64));
    STATIC_REQUIRE(isNearlyEqual(floor(-0.0_f64), 0.0_f64));
  }

  SECTION( "float32" ) {
    STATIC_REQUIRE(isNearlyEqual(floor(3.7_f32),  3.0_f32));
    STATIC_REQUIRE(isNearlyEqual(floor(-3.7_f32), -4.0_f32));

    STATIC_REQUIRE(isNearlyEqual(floor(0.0_f32),  0.0_f32));
    STATIC_REQUIRE(isNearlyEqual(floor(-0.0_f32), 0.0_f32));
  }

  SECTION( "very big numbers (bigger than intmax)" ) {
    STATIC_REQUIRE(isNearlyEqual(floor(1e24_f32),  1e24_f32));
    STATIC_REQUIRE(isNearlyEqual(floor(-1e24_f32), -1e24_f32));

    STATIC_REQUIRE(isNearlyEqual(floor(1e74_f64),  1e74_f64));
    STATIC_REQUIRE(isNearlyEqual(floor(-1e74_f64), -1e74_f64));
  }

  SECTION( "standard errors" ) {
    floorStandardErrors<float32>();
    floorStandardErrors<float64>();
  }
}

}
