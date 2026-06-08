#include <catch2/catch_all.hpp>

import Mathpp.basic;
import Mathpp.common;

namespace mathpp {

using namespace mathpp::literals;

template<floating_point T>
constexpr void
truncStandardErrors(void) {
  STATIC_REQUIRE(isinf(
    trunc<T, TruncErrPolicyStd<T>>(
      std::numeric_limits<T>::infinity()
    )
  ));

  STATIC_REQUIRE(isinf(
    trunc<T, TruncErrPolicyStd<T>>(
      -std::numeric_limits<T>::infinity()
    )
  ));

  STATIC_REQUIRE(isnan(
    trunc<T, TruncErrPolicyStd<T>>(
      std::numeric_limits<T>::quiet_NaN()
    )
  ));

  STATIC_REQUIRE(isnan(
    trunc<T, TruncErrPolicyStd<T>>(
      std::numeric_limits<T>::signaling_NaN()
    )
  ));

  STATIC_REQUIRE(trunc<T, TruncErrPolicyStd<T>>(0) == 0);

  STATIC_REQUIRE(trunc<T, TruncErrPolicyStd<T>>(-0) == 0);
}

TEST_CASE( "floating point trunc", "[trunc][basic]" ) {

  SECTION( "float64" ) {
    STATIC_REQUIRE(isNearlyEqual(trunc(3.7_f64),  3.0_f64));
    STATIC_REQUIRE(isNearlyEqual(trunc(-3.7_f64), -3.0_f64));

    STATIC_REQUIRE(isNearlyEqual(trunc(0.0_f64),  0.0_f64));
    STATIC_REQUIRE(isNearlyEqual(trunc(-0.0_f64), 0.0_f64));
  }

  SECTION( "float32" ) {
    STATIC_REQUIRE(isNearlyEqual(trunc(3.7_f32),  3.0_f32));
    STATIC_REQUIRE(isNearlyEqual(trunc(-3.7_f32), -3.0_f32));

    STATIC_REQUIRE(isNearlyEqual(trunc(0.0_f32),  0.0_f32));
    STATIC_REQUIRE(isNearlyEqual(trunc(-0.0_f32), 0.0_f32));
  }

  SECTION( "very big numbers (bigger than intmax)" ) {
    STATIC_REQUIRE(isNearlyEqual(trunc(1e24_f32),  1e24_f32));
    STATIC_REQUIRE(isNearlyEqual(trunc(-1e24_f32), -1e24_f32));

    STATIC_REQUIRE(isNearlyEqual(trunc(1e74_f64),  1e74_f64));
    STATIC_REQUIRE(isNearlyEqual(trunc(-1e74_f64), -1e74_f64));
  }

  SECTION( "standard errors" ) {
    truncStandardErrors<float32>();
    truncStandardErrors<float64>();
  }
}

}
