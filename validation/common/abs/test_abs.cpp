#include <numeric>

#include <catch2/catch_test_macros.hpp>

#include <Mathpp/macros.hpp>

import Mathpp.common;

// two's complement correction here
#define testAbsLimitValsInt(T) \
  std::numeric_limits<T>::max() == abs(std::numeric_limits<T>::max()) && \
  std::numeric_limits<T>::max() == abs(std::numeric_limits<T>::min() + 1) 

#define testAbsLimitValsFloat(T) \
  std::numeric_limits<T>::max() == abs(std::numeric_limits<T>::max()) && \
  std::numeric_limits<T>::max() == abs(-std::numeric_limits<T>::max()) && \
  std::numeric_limits<T>::min() == abs(std::numeric_limits<T>::min()) && \
  std::numeric_limits<T>::min() == abs(-std::numeric_limits<T>::min())

#define BIG_FP_TEST_VAL 1.9e

namespace mathpp {

TEST_CASE( "abs" , "[abs][common]" ) {

  SECTION( "integral types" ) {
    STATIC_REQUIRE(abs(3) == 3);
    STATIC_REQUIRE(abs(-3) == 3);

    STATIC_REQUIRE(abs(0) == 0);
    STATIC_REQUIRE(abs(-0) == 0);
    STATIC_REQUIRE(abs(0) == -0);

    STATIC_REQUIRE(testAbsLimitValsInt(std::int64_t));
    STATIC_REQUIRE(testAbsLimitValsInt(std::int32_t));
    STATIC_REQUIRE(testAbsLimitValsInt(std::int16_t));
    STATIC_REQUIRE(testAbsLimitValsInt(std::int8_t));
    STATIC_REQUIRE(testAbsLimitValsInt(int));
    STATIC_REQUIRE(testAbsLimitValsInt(signed char));
  }

  SECTION( "floating point types" ) {
    STATIC_REQUIRE(abs(3.0) == 3.0);
    STATIC_REQUIRE(abs(-3.0) == 3.0);

    STATIC_REQUIRE(abs(0.0) == 0.0);
    STATIC_REQUIRE(abs(-0.0) == 0.0);
    STATIC_REQUIRE(abs(0.0) == -0.0);

    STATIC_REQUIRE(testAbsLimitValsFloat(float));
    STATIC_REQUIRE(testAbsLimitValsFloat(double));
    STATIC_REQUIRE(testAbsLimitValsFloat(long double));
  }

}

}
