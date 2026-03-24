#include <catch2/catch_all.hpp>

#include <Mathpp/macros.hpp>

import Mathpp.common;

namespace mathpp {

TEST_CASE( "signbit", "[common][signbit]" ) {

  SECTION( "float" ) {
    STATIC_REQUIRE(signbit(-0.0f));
    STATIC_REQUIRE(!signbit(0.0f));

    STATIC_REQUIRE(!signbit(1.0f));
    STATIC_REQUIRE(signbit(-100.0f));
  }

  SECTION( "double" ) {
    STATIC_REQUIRE(signbit(-0.0));
    STATIC_REQUIRE(!signbit(0.0));

    STATIC_REQUIRE(!signbit(1.0));
    STATIC_REQUIRE(signbit(-100.0));
  }

  SECTION( "long double" ) {
    STATIC_REQUIRE(signbit(-0.0l));
    STATIC_REQUIRE(!signbit(0.0l));

    STATIC_REQUIRE(!signbit(1.0l));
    STATIC_REQUIRE(signbit(-100.0l));
  }
}

}
