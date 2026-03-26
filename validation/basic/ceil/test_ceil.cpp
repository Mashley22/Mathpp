#include <numeric>
#include <iostream>

#include <catch2/catch_all.hpp>

import Mathpp.basic;
import Mathpp.common;

namespace mathpp {

using namespace mathpp::literals;

TEST_CASE( "floating point ceil", "[trunc][basic]" ) {

  SECTION( "float64_t (_f64)" ) {
    STATIC_REQUIRE(isNearlyEqual(ceil(3.7_f64),  4.0_f64));
    STATIC_REQUIRE(isNearlyEqual(ceil(-3.7_f64), -3.0_f64));

    STATIC_REQUIRE(isNearlyEqual(ceil(0.0_f64),  0.0_f64));
    STATIC_REQUIRE(isNearlyEqual(ceil(-0.0_f64), 0.0_f64));
  }

  SECTION( "float32_t (_f32)" ) {
    STATIC_REQUIRE(isNearlyEqual(ceil(3.7_f32),  4.0_f32));
    STATIC_REQUIRE(isNearlyEqual(ceil(-3.7_f32), -3.0_f32));

    STATIC_REQUIRE(isNearlyEqual(ceil(0.0_f32),  0.0_f32));
    STATIC_REQUIRE(isNearlyEqual(ceil(-0.0_f32), 0.0_f32));
  }

  SECTION( "long double" ) {
    STATIC_REQUIRE(isNearlyEqual(ceil(3.7l), 4.0l));
    STATIC_REQUIRE(isNearlyEqual(ceil(-3.7l), -3.0l));

    STATIC_REQUIRE(isNearlyEqual(ceil(0.0l), 0.0l));
    STATIC_REQUIRE(isNearlyEqual(ceil(-0.0l), 0.0l));
  }

  SECTION( "very big numbers (bigger than intmax)" ) {
    STATIC_REQUIRE(isNearlyEqual(ceil(1e74_f64),  1e74_f64));
    STATIC_REQUIRE(isNearlyEqual(ceil(-1e74_f64), -1e74_f64));

    STATIC_REQUIRE(isNearlyEqual(ceil(1e74l), 1e74l));
    STATIC_REQUIRE(isNearlyEqual(ceil(-1e74l), -1e74l));

    STATIC_REQUIRE(isNearlyEqual(ceil(1e24_f32),  1e24_f32));
    STATIC_REQUIRE(isNearlyEqual(ceil(-1e24_f32), -1e24_f32));
  }
}

}
