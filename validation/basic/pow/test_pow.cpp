#include <numeric>

#include <catch2/catch_all.hpp>

import Mathpp.basic;
import Mathpp.common;

#define TEST_POW(base, exponent, expected)  \
  STATIC_REQUIRE(isNearlyEqualRel(pow(base, exponent), expected, std::numeric_limits<double>::epsilon()));

namespace mathpp {

using namespace mathpp::literals;

TEST_CASE( "pow with integer exponent", "[pow][basic]" ) {

  SECTION( "integral type" ) {
    STATIC_REQUIRE(pow(0, 5) == 0);
    STATIC_REQUIRE(pow(1, 43123) == 1); // not too high for the constexpr step lim
    STATIC_REQUIRE(pow(-1, 3) == -1);

    STATIC_REQUIRE(pow(1231412343465, 0) == 1);
  }

  SECTION( "floating point type" ) {
    TEST_POW(0.0_f32, 5, 0.0_f32);
    TEST_POW(1.0_f32, 43123, 1.0_f32); // not too high for the constexpr step lim
    TEST_POW(-1.0_f32, 3, -1.0_f32);

    TEST_POW(1231412343465.12341354_f32, 0, 1.0_f32);
  }

  
}

}
