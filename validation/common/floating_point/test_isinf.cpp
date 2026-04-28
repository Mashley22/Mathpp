#include <numeric>

#include <catch2/catch_test_macros.hpp>

#include <Mathpp/macros.hpp>

import Mathpp.common;

namespace mathpp {

namespace {

TEST_CASE( "isinf" , "[common][floating_point][isinf]" ) {

  SECTION( "inf is inf" ) {
    STATIC_REQUIRE(isinf(std::numeric_limits<float32>::infinity()));
    STATIC_REQUIRE(isinf(-std::numeric_limits<float32>::infinity()));

    STATIC_REQUIRE(isinf(std::numeric_limits<float64>::infinity()));
    STATIC_REQUIRE(isinf(-std::numeric_limits<float64>::infinity()));
  }

  SECTION( "nan is not inf" ) {
    STATIC_REQUIRE(!isinf(std::numeric_limits<float32>::quiet_NaN()));
    STATIC_REQUIRE(!isinf(std::numeric_limits<float32>::signaling_NaN()));

    STATIC_REQUIRE(!isinf(std::numeric_limits<float64>::quiet_NaN()));
    STATIC_REQUIRE(!isinf(std::numeric_limits<float64>::signaling_NaN()));
  }

  SECTION("zero is not inf") {
    STATIC_REQUIRE(!isinf(float32{0.0f}));
    STATIC_REQUIRE(!isinf(float32{-0.0f}));

    STATIC_REQUIRE(!isinf(float64{0.0}));
    STATIC_REQUIRE(!isinf(float64{-0.0}));
  }

  SECTION("normal finite values are not inf") {
    STATIC_REQUIRE(!isinf(float32{1.0f}));
    STATIC_REQUIRE(!isinf(float32{-1.0f}));
    STATIC_REQUIRE(!isinf(float32{123.456f}));

    STATIC_REQUIRE(!isinf(float64{1.0}));
    STATIC_REQUIRE(!isinf(float64{-1.0}));
    STATIC_REQUIRE(!isinf(float64{123.456}));
  }

  SECTION("extreme finite values are not inf") {
    STATIC_REQUIRE(!isinf(std::numeric_limits<float32>::max()));
    STATIC_REQUIRE(!isinf(std::numeric_limits<float32>::lowest()));
    STATIC_REQUIRE(!isinf(std::numeric_limits<float32>::min())); 

    STATIC_REQUIRE(!isinf(std::numeric_limits<float64>::max()));
    STATIC_REQUIRE(!isinf(std::numeric_limits<float64>::lowest()));
    STATIC_REQUIRE(!isinf(std::numeric_limits<float64>::min()));
  }

  SECTION("subnormal values are not inf") {
    STATIC_REQUIRE(!isinf(std::numeric_limits<float32>::denorm_min()));
    STATIC_REQUIRE(!isinf(std::numeric_limits<float64>::denorm_min()));
  }

}

}

}
