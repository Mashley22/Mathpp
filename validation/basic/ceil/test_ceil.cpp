#include <numeric>

#include <catch2/catch_all.hpp>

import Mathpp.basic;
import Mathpp.common;

namespace mathpp {

using namespace mathpp::literals;

namespace {

template<floating_point T>
constexpr void
ceilIec559Errors(void) {
  STATIC_REQUIRE(isinf(
    ceil<T, ceilIec559ErrorPolicy<T>>(
      std::numeric_limits<T>::infinity()
    )
  ));

  STATIC_REQUIRE(isinf(
    ceil<T, ceilIec559ErrorPolicy<T>>(
      -std::numeric_limits<T>::infinity()
    )
  ));

  STATIC_REQUIRE(isnan(
    ceil<T, ceilIec559ErrorPolicy<T>>(
      std::numeric_limits<T>::quiet_NaN()
    )
  ));

  STATIC_REQUIRE(isnan(
    ceil<T, ceilIec559ErrorPolicy<T>>(
      std::numeric_limits<T>::signaling_NaN()
    )
  ));

  STATIC_REQUIRE(ceil<T, ceilIec559ErrorPolicy<T>>(0) == 0);

  STATIC_REQUIRE(ceil<T, ceilIec559ErrorPolicy<T>>(-0) == 0);
}

TEST_CASE( "floating point ceil", "[trunc][basic]" ) {

  SECTION( "float64" ) {
    STATIC_REQUIRE(isNearlyEqual(ceil(3.7_f64),  4.0_f64));
    STATIC_REQUIRE(isNearlyEqual(ceil(-3.7_f64), -3.0_f64));

    STATIC_REQUIRE(isNearlyEqual(ceil(0.0_f64),  0.0_f64));
    STATIC_REQUIRE(isNearlyEqual(ceil(-0.0_f64), 0.0_f64));
  }

  SECTION( "float32" ) {
    STATIC_REQUIRE(isNearlyEqual(ceil(3.7_f32),  4.0_f32));
    STATIC_REQUIRE(isNearlyEqual(ceil(-3.7_f32), -3.0_f32));

    STATIC_REQUIRE(isNearlyEqual(ceil(0.0_f32),  0.0_f32));
    STATIC_REQUIRE(isNearlyEqual(ceil(-0.0_f32), 0.0_f32));
  }

  SECTION( "very big numbers (bigger than the integral limit)" ) {
    STATIC_REQUIRE(isNearlyEqual(ceil(1e74_f64),  1e74_f64));
    STATIC_REQUIRE(isNearlyEqual(ceil(-1e74_f64), -1e74_f64));

    STATIC_REQUIRE(isNearlyEqual(ceil(1e24_f32),  1e24_f32));
    STATIC_REQUIRE(isNearlyEqual(ceil(-1e24_f32), -1e24_f32));
  }

  SECTION( "iec 559 handling" ) {
    ceilIec559Errors<float32>();
    ceilIec559Errors<float64>();
  }
}

}

}
