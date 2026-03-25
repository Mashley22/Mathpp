#include <numeric>
#include <iostream>

#include <catch2/catch_all.hpp>

import Mathpp.basic;
import Mathpp.common;

namespace mathpp {

TEST_CASE( "floating point ceil", "[trunc][basic]" ) {

  SECTION( "double" ) {
    STATIC_REQUIRE(isNearlyEqual(ceil(3.7), 4.0));
    STATIC_REQUIRE(isNearlyEqual(ceil(-3.7), -3.0));

    STATIC_REQUIRE(isNearlyEqual(ceil(0.0), 0.0));
    STATIC_REQUIRE(isNearlyEqual(ceil(-0.0), 0.0));
  }

  SECTION( "float" ) {
    STATIC_REQUIRE(isNearlyEqual(ceil(3.7f), 4.0f));
    STATIC_REQUIRE(isNearlyEqual(ceil(-3.7f), -3.0f));

    STATIC_REQUIRE(isNearlyEqual(ceil(0.0f), 0.0f));
    STATIC_REQUIRE(isNearlyEqual(ceil(-0.0f), 0.0f));
  }

  SECTION( "long double" ) {
    STATIC_REQUIRE(isNearlyEqual(ceil(3.7l), 4.0l));
    STATIC_REQUIRE(isNearlyEqual(ceil(-3.7l), -3.0l));

    STATIC_REQUIRE(isNearlyEqual(ceil(0.0l), 0.0l));
    STATIC_REQUIRE(isNearlyEqual(ceil(-0.0l), 0.0l));
  }

  SECTION( "very big numbers (bigger than intmax)" ) {
    STATIC_REQUIRE(isNearlyEqual(ceil(1e74), 1e74));
    STATIC_REQUIRE(isNearlyEqual(ceil(-1e74), -1e74));

    STATIC_REQUIRE(isNearlyEqual(ceil(1e74l), 1e74l));
    STATIC_REQUIRE(isNearlyEqual(ceil(-1e74l), -1e74l));

    STATIC_REQUIRE(isNearlyEqual(ceil(1e24f), 1e24f));
    STATIC_REQUIRE(isNearlyEqual(ceil(-1e24f), -1e24f));
  }
}

}
