#include <catch2/catch_all.hpp>

import Mathpp.basic;
import Mathpp.common;

namespace mathpp {

using namespace mathpp::literals;

TEST_CASE( "", "[trunc][basic]" ) {

  SECTION( "float64" ) {
    STATIC_REQUIRE(ilogb(0_f64) == 0);
    STATIC_REQUIRE(ilogb(1e100_f64) == 332);
    STATIC_REQUIRE(ilogb(1e-100_f64) == -333);
    STATIC_REQUIRE(ilogb(1_f64) == 0);
    STATIC_REQUIRE(ilogb(2_f64) == 1);
  }

  SECTION( "float32" ) {
    STATIC_REQUIRE(ilogb(0_f32) == 0);
    STATIC_REQUIRE(ilogb(1e50_f32) == 128);
    STATIC_REQUIRE(ilogb(1e-20_f32) == -67);
    STATIC_REQUIRE(ilogb(1_f32) == 0);
    STATIC_REQUIRE(ilogb(2_f32) == 1);
  }

}

}
