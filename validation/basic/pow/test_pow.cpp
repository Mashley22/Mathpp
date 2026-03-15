#include <numeric>

#include <catch2/catch_all.hpp>

import Mathpp.basic;
import Mathpp.common;

#define TEST_POW(base, exponent, expected)  \
  STATIC_REQUIRE(isNearlyEqualRel(pow(base, exponent), expected, std::numeric_limits<double>::epsilon()));

namespace mathpp {

TEST_CASE( "pow with integer exponent", "[pow][basic]" ) {

  SECTION( "integral type" ) {
    STATIC_REQUIRE(pow(0, 5) == 0);
    STATIC_REQUIRE(pow(1, 43123) == 1); // not too high for the constexpr step lim
    STATIC_REQUIRE(pow(-1, 3) == -1);

    STATIC_REQUIRE(pow(1231412343465, 0) == 1);
  }

  SECTION( "floating point type" ) {
    TEST_POW(0.0, 5, 0.0);
    TEST_POW(1.0, 43123, 1.0); // not too high for the constexpr step lim
    TEST_POW(-1.0, 3, -1.0);

    TEST_POW(1231412343465.12341354, 0, 1.0);
  }

  
}

}
