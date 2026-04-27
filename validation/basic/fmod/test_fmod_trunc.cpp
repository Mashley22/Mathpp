#include <catch2/catch_all.hpp>

#define FMOD_EPSILON_F32 1e-5f
#define FMOD_EPSILON_F64 1e-10

import Mathpp.basic;
import Mathpp.common;

namespace mathpp {

using namespace mathpp::literals;

TEST_CASE("fmodTrunc - basic modulo operations", "[fmodTrunc][basic]") {
  
  SECTION("float64") {
    REQUIRE_THAT(fmodTrunc(5.3_f64, 2.0_f64), 
                 Catch::Matchers::WithinRel(1.3_f64, FMOD_EPSILON_F64));
    REQUIRE_THAT(fmodTrunc(7.5_f64, 3.0_f64), 
                 Catch::Matchers::WithinRel(1.5_f64, FMOD_EPSILON_F64));
    REQUIRE_THAT(fmodTrunc(10.7_f64, 4.0_f64), 
                 Catch::Matchers::WithinRel(2.7_f64, FMOD_EPSILON_F64));
  }

  SECTION("float32") {
    REQUIRE_THAT(fmodTrunc(5.3_f32, 2.0_f32), 
                 Catch::Matchers::WithinRel(1.3_f32, FMOD_EPSILON_F32));
    REQUIRE_THAT(fmodTrunc(7.5_f32, 3.0_f32), 
                 Catch::Matchers::WithinRel(1.5_f32, FMOD_EPSILON_F32));
    REQUIRE_THAT(fmodTrunc(10.7_f32, 4.0_f32), 
                 Catch::Matchers::WithinRel(2.7_f32, FMOD_EPSILON_F32));
  }
}

TEST_CASE("fmodTrunc - negative values", "[fmodTrunc][basic]") {
  
  SECTION("float64") {
    // Result takes sign of dividend
    REQUIRE_THAT(fmodTrunc(-5.3_f64, 2.0_f64), 
                 Catch::Matchers::WithinRel(-1.3_f64, FMOD_EPSILON_F64));
    REQUIRE_THAT(fmodTrunc(5.3_f64, -2.0_f64), 
                 Catch::Matchers::WithinRel(1.3_f64, FMOD_EPSILON_F64));
    REQUIRE_THAT(fmodTrunc(-5.3_f64, -2.0_f64), 
                 Catch::Matchers::WithinRel(-1.3_f64, FMOD_EPSILON_F64));
  }

  SECTION("float32") {
    REQUIRE_THAT(fmodTrunc(-5.3_f32, 2.0_f32), 
                 Catch::Matchers::WithinRel(-1.3_f32, FMOD_EPSILON_F32));
    REQUIRE_THAT(fmodTrunc(5.3_f32, -2.0_f32), 
                 Catch::Matchers::WithinRel(1.3_f32, FMOD_EPSILON_F32));
    REQUIRE_THAT(fmodTrunc(-5.3_f32, -2.0_f32), 
                 Catch::Matchers::WithinRel(-1.3_f32, FMOD_EPSILON_F32));
  }
}

TEST_CASE("fmodTrunc - zero dividend", "[fmodTrunc][basic]") {
  
  SECTION("float64") {
    REQUIRE_THAT(fmodTrunc(0.0_f64, 5.0_f64), 
                 Catch::Matchers::WithinRel(0.0_f64, FMOD_EPSILON_F64));
    REQUIRE_THAT(fmodTrunc(-0.0_f64, 5.0_f64), 
                 Catch::Matchers::WithinRel(0.0_f64, FMOD_EPSILON_F64));
  }

  SECTION("float32") {
    REQUIRE_THAT(fmodTrunc(0.0_f32, 5.0_f32), 
                 Catch::Matchers::WithinRel(0.0_f32, FMOD_EPSILON_F32));
    REQUIRE_THAT(fmodTrunc(-0.0_f32, 5.0_f32), 
                 Catch::Matchers::WithinRel(0.0_f32, FMOD_EPSILON_F32));
  }
}

TEST_CASE("fmodTrunc - dividend smaller than divisor", "[fmodTrunc][basic]") {
  
  SECTION("float64") {
    REQUIRE_THAT(fmodTrunc(1.5_f64, 3.0_f64), 
                 Catch::Matchers::WithinRel(1.5_f64, FMOD_EPSILON_F64));
    REQUIRE_THAT(fmodTrunc(2.7_f64, 5.0_f64), 
                 Catch::Matchers::WithinRel(2.7_f64, FMOD_EPSILON_F64));
    REQUIRE_THAT(fmodTrunc(-1.5_f64, 3.0_f64), 
                 Catch::Matchers::WithinRel(-1.5_f64, FMOD_EPSILON_F64));
  }

  SECTION("float32") {
    REQUIRE_THAT(fmodTrunc(1.5_f32, 3.0_f32), 
                 Catch::Matchers::WithinRel(1.5_f32, FMOD_EPSILON_F32));
    REQUIRE_THAT(fmodTrunc(2.7_f32, 5.0_f32), 
                 Catch::Matchers::WithinRel(2.7_f32, FMOD_EPSILON_F32));
    REQUIRE_THAT(fmodTrunc(-1.5_f32, 3.0_f32), 
                 Catch::Matchers::WithinRel(-1.5_f32, FMOD_EPSILON_F32));
  }
}

TEST_CASE("fmodTrunc - exact multiples", "[fmodTrunc][basic]") {
  
  SECTION("float64") {
    REQUIRE_THAT(fmodTrunc(6.0_f64, 3.0_f64), 
                 Catch::Matchers::WithinRel(0.0_f64, FMOD_EPSILON_F64));
    REQUIRE_THAT(fmodTrunc(10.0_f64, 5.0_f64), 
                 Catch::Matchers::WithinRel(0.0_f64, FMOD_EPSILON_F64));
    REQUIRE_THAT(fmodTrunc(-12.0_f64, 4.0_f64), 
                 Catch::Matchers::WithinRel(0.0_f64, FMOD_EPSILON_F64));
  }

  SECTION("float32") {
    REQUIRE_THAT(fmodTrunc(6.0_f32, 3.0_f32), 
                 Catch::Matchers::WithinRel(0.0_f32, FMOD_EPSILON_F32));
    REQUIRE_THAT(fmodTrunc(10.0_f32, 5.0_f32), 
                 Catch::Matchers::WithinRel(0.0_f32, FMOD_EPSILON_F32));
    REQUIRE_THAT(fmodTrunc(-12.0_f32, 4.0_f32), 
                 Catch::Matchers::WithinRel(0.0_f32, FMOD_EPSILON_F32));
  }
}

TEST_CASE("fmodTrunc - fractional divisor", "[fmodTrunc][basic]") {
  
  SECTION("float64") {
    REQUIRE_THAT(fmodTrunc(5.5_f64, 1.5_f64), 
                 Catch::Matchers::WithinRel(1.0_f64, FMOD_EPSILON_F64));
    REQUIRE_THAT(fmodTrunc(7.2_f64, 2.5_f64), 
                 Catch::Matchers::WithinRel(2.2_f64, FMOD_EPSILON_F64));
  }

  SECTION("float32") {
    REQUIRE_THAT(fmodTrunc(5.5_f32, 1.5_f32), 
                 Catch::Matchers::WithinRel(1.0_f32, FMOD_EPSILON_F32));
    REQUIRE_THAT(fmodTrunc(7.2_f32, 2.5_f32), 
                 Catch::Matchers::WithinRel(2.2_f32, FMOD_EPSILON_F32));
  }
}

TEST_CASE("fmodTrunc - small values", "[fmodTrunc][basic]") {
  
  SECTION("float64") {
    REQUIRE_THAT(fmodTrunc(0.0005_f64, 0.0002_f64), 
                 Catch::Matchers::WithinRel(0.0001_f64, FMOD_EPSILON_F64));
    REQUIRE_THAT(fmodTrunc(0.00035_f64, 0.0001_f64), 
                 Catch::Matchers::WithinRel(0.00005_f64, FMOD_EPSILON_F64));
  }

  SECTION("float32") {
    REQUIRE_THAT(fmodTrunc(0.0005_f32, 0.0002_f32), 
                 Catch::Matchers::WithinRel(0.0001_f32, FMOD_EPSILON_F32));
    REQUIRE_THAT(fmodTrunc(0.00035_f32, 0.0001_f32), 
                 Catch::Matchers::WithinRel(0.00005_f32, FMOD_EPSILON_F32));
  }
}

TEST_CASE("fmodTrunc - large values", "[fmodTrunc][basic]") {
  
  SECTION("float64") {
    REQUIRE_THAT(fmodTrunc(1234.56_f64, 100.0_f64), 
                 Catch::Matchers::WithinRel(34.56_f64, FMOD_EPSILON_F64));
    REQUIRE_THAT(fmodTrunc(5678.9_f64, 1000.0_f64), 
                 Catch::Matchers::WithinRel(678.9_f64, FMOD_EPSILON_F64));
  }

  SECTION("float32") {
    REQUIRE_THAT(fmodTrunc(1234.56_f32, 100.0_f32), 
                 Catch::Matchers::WithinRel(34.56_f32, FMOD_EPSILON_F32));
    REQUIRE_THAT(fmodTrunc(5678.9_f32, 1000.0_f32), 
                 Catch::Matchers::WithinRel(678.9_f32, FMOD_EPSILON_F32));
  }
}

}
