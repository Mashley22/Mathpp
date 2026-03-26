#include <catch2/catch_test_macros.hpp>

#include <Mathpp/macros.hpp>

import Mathpp.common;
import Mathpp.basic;

namespace mathpp {

using namespace mathpp::literals;

TEST_CASE( "compare" , "[compare][common]" ) {

  SECTION( "integral type" ) {
    STATIC_REQUIRE(!isNearlyEqualAbs(0, 5, 3));
    STATIC_REQUIRE(!isNearlyEqualAbs(0, -5, 3));
    STATIC_REQUIRE(isNearlyEqualAbs(2, 5, 3));
    STATIC_REQUIRE(isNearlyEqualAbs(-2, -5, 3));

    STATIC_REQUIRE(isNearlyEqualAbs(2, -1, 3));
    STATIC_REQUIRE(isNearlyEqualAbs(-2, 1, 3));

    STATIC_REQUIRE(!isNearlyEqualRel<int, float64>(2, 5, 0.3_f64));
    STATIC_REQUIRE(isNearlyEqualRel<int, float64>(2, 5, 0.8_f64));
    STATIC_REQUIRE(!isNearlyEqualRel<int, float64>(-2, -5, 0.3_f64));
    STATIC_REQUIRE(isNearlyEqualRel<int, float64>(-2, -5, 0.8_f64));
    
    STATIC_REQUIRE(isNearlyEqual<int, float64>(2, 10, 0.75_f64, 1));
    STATIC_REQUIRE(isNearlyEqual<int, float64>(-2, -10, 0.75_f64, 1));
  }

  SECTION( "float64 (_f64)" ) {
    STATIC_REQUIRE(!isNearlyEqualAbs(0.0_f64, 5.0_f64, 3.0_f64));
    STATIC_REQUIRE(!isNearlyEqualAbs(0.0_f64, -5.0_f64, 3.0_f64));
    STATIC_REQUIRE(isNearlyEqualAbs(2.0_f64, 5.0_f64, 3.0_f64));
    STATIC_REQUIRE(isNearlyEqualAbs(-2.0_f64, -5.0_f64, 3.0_f64));

    STATIC_REQUIRE(isNearlyEqualAbs(2.0_f64, -1.0_f64, 3.0_f64));
    STATIC_REQUIRE(isNearlyEqualAbs(-2.0_f64, 1.0_f64, 3.0_f64));

    STATIC_REQUIRE(!isNearlyEqualRel(2.0_f64, 5.0_f64, 0.3_f64));
    STATIC_REQUIRE(isNearlyEqualRel(2.0_f64, 5.0_f64, 0.8_f64));
    STATIC_REQUIRE(!isNearlyEqualRel(-2.0_f64, -5.0_f64, 0.3_f64));
    STATIC_REQUIRE(isNearlyEqualRel(-2.0_f64, -5.0_f64, 0.8_f64));

    STATIC_REQUIRE(isNearlyEqual(2.0_f64, 10.0_f64, 0.75_f64, 1.0_f64));
    STATIC_REQUIRE(isNearlyEqual(-2.0_f64, -10.0_f64, 0.75_f64, 1.0_f64));
  }

  SECTION( "float32 (_f32)" ) {
    STATIC_REQUIRE(!isNearlyEqualAbs(0.0_f32, 5.0_f32, 3.0_f32));
    STATIC_REQUIRE(!isNearlyEqualAbs(0.0_f32, -5.0_f32, 3.0_f32));
    STATIC_REQUIRE(isNearlyEqualAbs(2.0_f32, 5.0_f32, 3.0_f32));
    STATIC_REQUIRE(isNearlyEqualAbs(-2.0_f32, -5.0_f32, 3.0_f32));

    STATIC_REQUIRE(isNearlyEqualAbs(2.0_f32, -1.0_f32, 3.0_f32));
    STATIC_REQUIRE(isNearlyEqualAbs(-2.0_f32, 1.0_f32, 3.0_f32));

    STATIC_REQUIRE(!isNearlyEqualRel(2.0_f32, 5.0_f32, 0.3_f32));
    STATIC_REQUIRE(isNearlyEqualRel(2.0_f32, 5.0_f32, 0.8_f32));
    STATIC_REQUIRE(!isNearlyEqualRel(-2.0_f32, -5.0_f32, 0.3_f32));
    STATIC_REQUIRE(isNearlyEqualRel(-2.0_f32, -5.0_f32, 0.8_f32));

    STATIC_REQUIRE(isNearlyEqual(2.0_f32, 10.0_f32, 0.75_f32, 1.0_f32));
    STATIC_REQUIRE(isNearlyEqual(-2.0_f32, -10.0_f32, 0.75_f32, 1.0_f32));
  }

  SECTION( "double" ) {
    STATIC_REQUIRE(!isNearlyEqualAbs(0.0, 5.0, 3.0));
    STATIC_REQUIRE(!isNearlyEqualAbs(0.0, -5.0, 3.0));
    STATIC_REQUIRE(isNearlyEqualAbs(2.0, 5.0, 3.0));
    STATIC_REQUIRE(isNearlyEqualAbs(-2.0, -5.0, 3.0));

    STATIC_REQUIRE(isNearlyEqualAbs(2.0, -1.0, 3.0));
    STATIC_REQUIRE(isNearlyEqualAbs(-2.0, 1.0, 3.0));

    STATIC_REQUIRE(!isNearlyEqualRel(2.0, 5.0, 0.3));
    STATIC_REQUIRE(isNearlyEqualRel(2.0, 5.0, 0.8));
    STATIC_REQUIRE(!isNearlyEqualRel(-2.0, -5.0, 0.3));
    STATIC_REQUIRE(isNearlyEqualRel(-2.0, -5.0, 0.8));

    STATIC_REQUIRE(isNearlyEqual(2.0, 10.0, 0.75, 1.0));
    STATIC_REQUIRE(isNearlyEqual(-2.0, -10.0, 0.75, 1.0));
  }
}

}
