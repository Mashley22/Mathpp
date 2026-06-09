#include <catch2/catch_all.hpp>

#include <Mathpp/macros.hpp>

import Mathpp;

namespace mathpp {

using namespace mathpp::literals;

TEST_CASE( "signbit", "[common][signbit]" ) {

  SECTION( "float32" ) {
    STATIC_REQUIRE(signbit(-0.0_f32));
    STATIC_REQUIRE(!signbit(0.0_f32));

    STATIC_REQUIRE(!signbit(1.0_f32));
    STATIC_REQUIRE(signbit(-100.0_f32));
  }

  SECTION( "float64" ) {
    STATIC_REQUIRE(signbit(-0.0_f64));
    STATIC_REQUIRE(!signbit(0.0_f64));

    STATIC_REQUIRE(!signbit(1.0_f64));
    STATIC_REQUIRE(signbit(-100.0_f64));
  }

}

TEST_CASE( "copysign", "[common][copysign]" ) {

  SECTION( "float32" ) {
    STATIC_REQUIRE(0.0_f32 == copysign(0.0_f32, 0.0_f32));
    STATIC_REQUIRE(-0.0_f32 == copysign(0.0_f32, -0.0_f32));
    STATIC_REQUIRE(-0.0_f32 == copysign(-0.0_f32, -0.0_f32));
    STATIC_REQUIRE(-0.0_f32 == copysign(-0.0_f32, 0.0_f32));
  }

  SECTION( "float64" ) {
    STATIC_REQUIRE(0.0_f64 == copysign(0.0_f64, 0.0_f64));
    STATIC_REQUIRE(-0.0_f64 == copysign(0.0_f64, -0.0_f64));
    STATIC_REQUIRE(-0.0_f64 == copysign(-0.0_f64, -0.0_f64));
    STATIC_REQUIRE(-0.0_f64 == copysign(-0.0_f64, 0.0_f64));
  }

}

}
