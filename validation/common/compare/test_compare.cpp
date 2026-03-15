#include <catch2/catch_test_macros.hpp>

#include <Mathpp/macros.hpp>

import Mathpp.common;

namespace mathpp {

TEST_CASE( "compare" , "[compare][common]" ) {

  SECTION( "integral type" ) {
    STATIC_REQUIRE(!isNearlyEqualAbs(0, 5, 3));
    STATIC_REQUIRE(!isNearlyEqualAbs(0, -5, 3));
    STATIC_REQUIRE(isNearlyEqualAbs(2, 5, 3));
    STATIC_REQUIRE(isNearlyEqualAbs(-2, -5, 3));

    STATIC_REQUIRE(isNearlyEqualAbs(2, -1, 3));
    STATIC_REQUIRE(isNearlyEqualAbs(-2, 1, 3));

    STATIC_REQUIRE(!isNearlyEqualRel<int, double>(2, 5, 0.3));
    STATIC_REQUIRE(isNearlyEqualRel<int, double>(2, 5, 0.8));
    STATIC_REQUIRE(!isNearlyEqualRel<int, double>(-2, -5, 0.3));
    STATIC_REQUIRE(isNearlyEqualRel<int, double>(-2, -5, 0.8));
    
    STATIC_REQUIRE(isNearlyEqual<int, double>(2, 10, 0.75, 1));
    STATIC_REQUIRE(isNearlyEqual<int, double>(-2, -10, 0.75, 1));
  }

  SECTION( "floating point type" ) {
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
