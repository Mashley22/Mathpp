#include <catch2/catch_all.hpp>

import Mathpp;

namespace mathpp {

using namespace mathpp::literals;

TEST_CASE( "floating point ldexp", "[ldexp][basic]" ) {

  SECTION( "float64" ) {
    STATIC_REQUIRE(isNearlyEqual(ldexp(1.0_f64, 0), 1.0_f64));
    
    STATIC_REQUIRE(isNearlyEqual(ldexp(1.0_f64, 1), 2.0_f64));
    STATIC_REQUIRE(isNearlyEqual(ldexp(1.0_f64, 2), 4.0_f64));
    STATIC_REQUIRE(isNearlyEqual(ldexp(1.0_f64, 3), 8.0_f64));
    
    STATIC_REQUIRE(isNearlyEqual(ldexp(1.0_f64, -1), 0.5_f64));
    STATIC_REQUIRE(isNearlyEqual(ldexp(1.0_f64, -2), 0.25_f64));
    STATIC_REQUIRE(isNearlyEqual(ldexp(1.0_f64, -3), 0.125_f64));
    
    STATIC_REQUIRE(isNearlyEqual(ldexp(3.5_f64, 0), 3.5_f64));
    STATIC_REQUIRE(isNearlyEqual(ldexp(2.5_f64, 2), 10.0_f64));
    STATIC_REQUIRE(isNearlyEqual(ldexp(1.5_f64, 3), 12.0_f64));
    STATIC_REQUIRE(isNearlyEqual(ldexp(0.75_f64, -2), 0.1875_f64));
    
    STATIC_REQUIRE(isNearlyEqual(ldexp(-1.0_f64, 1), -2.0_f64));
    STATIC_REQUIRE(isNearlyEqual(ldexp(-1.0_f64, -1), -0.5_f64));
    STATIC_REQUIRE(isNearlyEqual(ldexp(-3.5_f64, 2), -14.0_f64));
    
    STATIC_REQUIRE(isNearlyEqual(ldexp(0.0_f64, 0), 0.0_f64));
    STATIC_REQUIRE(isNearlyEqual(ldexp(0.0_f64, 100), 0.0_f64));
    STATIC_REQUIRE(isNearlyEqual(ldexp(0.0_f64, -100), 0.0_f64));
  }

  SECTION( "float32" ) {
    STATIC_REQUIRE(isNearlyEqual(ldexp(1.0_f32, 0), 1.0_f32));
    
    STATIC_REQUIRE(isNearlyEqual(ldexp(1.0_f32, 1), 2.0_f32));
    STATIC_REQUIRE(isNearlyEqual(ldexp(1.0_f32, 2), 4.0_f32));
    
    STATIC_REQUIRE(isNearlyEqual(ldexp(1.0_f32, -1), 0.5_f32));
    STATIC_REQUIRE(isNearlyEqual(ldexp(1.0_f32, -2), 0.25_f32));
    
    STATIC_REQUIRE(isNearlyEqual(ldexp(2.5_f32, 2), 10.0_f32));
    STATIC_REQUIRE(isNearlyEqual(ldexp(1.5_f32, 3), 12.0_f32));
    
    STATIC_REQUIRE(isNearlyEqual(ldexp(-1.0_f32, 1), -2.0_f32));
    STATIC_REQUIRE(isNearlyEqual(ldexp(-3.5_f32, 2), -14.0_f32));
    
    STATIC_REQUIRE(isNearlyEqual(ldexp(0.0_f32, 0), 0.0_f32));
    STATIC_REQUIRE(isNearlyEqual(ldexp(0.0_f32, 50), 0.0_f32));
  }

  SECTION( "large exponents" ) {
    STATIC_REQUIRE(isNearlyEqual(ldexp(1.0_f64, 50), ldexp(1.0_f64, 50)));
    
    STATIC_REQUIRE(isNearlyEqual(ldexp(1.0_f64, -50), ldexp(1.0_f64, -50)));
    
    STATIC_REQUIRE(isNearlyEqual(ldexp(1.0_f32, 20), ldexp(1.0_f32, 20)));
    STATIC_REQUIRE(isNearlyEqual(ldexp(1.0_f32, -20), ldexp(1.0_f32, -20)));
  }

}

}
