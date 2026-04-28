#include <numeric>

#include <catch2/catch_test_macros.hpp>

#include <Mathpp/macros.hpp>

import Mathpp.common;

namespace mathpp {

namespace {

TEST_CASE( "isnan" , "[common][floating_point][isnan]") {

  SECTION( "nan is nan(lol)" ) {
    STATIC_REQUIRE(isnan(std::numeric_limits<float32>::quiet_NaN()));
    STATIC_REQUIRE(isnan(std::numeric_limits<float32>::signaling_NaN()));

    STATIC_REQUIRE(isnan(std::numeric_limits<float64>::quiet_NaN()));
    STATIC_REQUIRE(isnan(std::numeric_limits<float64>::signaling_NaN()));
  }

  SECTION( "inf is not nan" ) {
    STATIC_REQUIRE(!isnan(std::numeric_limits<float32>::infinity()));
    STATIC_REQUIRE(!isnan(-std::numeric_limits<float32>::infinity()));

    STATIC_REQUIRE(!isnan(std::numeric_limits<float64>::infinity()));
    STATIC_REQUIRE(!isnan(-std::numeric_limits<float64>::infinity()));
  }

  SECTION("zero is not nan") {
    STATIC_REQUIRE(!isnan(float32{0.0f}));
    STATIC_REQUIRE(!isnan(float32{-0.0f}));

    STATIC_REQUIRE(!isnan(float64{0.0}));
    STATIC_REQUIRE(!isnan(float64{-0.0}));
  }

  SECTION("normal finite values are not nan") {
    STATIC_REQUIRE(!isnan(float32{1.0f}));
    STATIC_REQUIRE(!isnan(float32{-1.0f}));
    STATIC_REQUIRE(!isnan(float32{123.456f}));

    STATIC_REQUIRE(!isnan(float64{1.0}));
    STATIC_REQUIRE(!isnan(float64{-1.0}));
    STATIC_REQUIRE(!isnan(float64{123.456}));
  }

  SECTION("extreme finite values are not nan") {
    STATIC_REQUIRE(!isnan(std::numeric_limits<float32>::max()));
    STATIC_REQUIRE(!isnan(std::numeric_limits<float32>::lowest()));
    STATIC_REQUIRE(!isnan(std::numeric_limits<float32>::min())); 

    STATIC_REQUIRE(!isnan(std::numeric_limits<float64>::max()));
    STATIC_REQUIRE(!isnan(std::numeric_limits<float64>::lowest()));
    STATIC_REQUIRE(!isnan(std::numeric_limits<float64>::min()));
  }

  SECTION("subnormal values are not nan") {
    STATIC_REQUIRE(!isnan(std::numeric_limits<float32>::denorm_min()));
    STATIC_REQUIRE(!isnan(std::numeric_limits<float64>::denorm_min()));
  }

}

}

}
