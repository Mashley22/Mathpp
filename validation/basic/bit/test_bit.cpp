#include <catch2/catch_all.hpp>

#include <Mathpp/macros.hpp>

import Mathpp;

namespace mathpp {

using namespace mathpp::literals;

TEST_CASE( "signbit", "[common][signbit]" ) {

  SECTION( "float32_t (_f32)" ) {
    STATIC_REQUIRE(signbit(-0.0_f32));
    STATIC_REQUIRE(!signbit(0.0_f32));

    STATIC_REQUIRE(!signbit(1.0_f32));
    STATIC_REQUIRE(signbit(-100.0_f32));
  }

  SECTION( "float64_t (_f64)" ) {
    STATIC_REQUIRE(signbit(-0.0_f64));
    STATIC_REQUIRE(!signbit(0.0_f64));

    STATIC_REQUIRE(!signbit(1.0_f64));
    STATIC_REQUIRE(signbit(-100.0_f64));
  }

  SECTION( "long double" ) {
    STATIC_REQUIRE(signbit(-0.0l));
    STATIC_REQUIRE(!signbit(0.0l));

    STATIC_REQUIRE(!signbit(1.0l));
    STATIC_REQUIRE(signbit(-100.0l));
  }
}

}
