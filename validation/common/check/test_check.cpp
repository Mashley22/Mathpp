#include <source_location>
#include <string>

#include <catch2/catch_all.hpp>

#include <Mathpp/macros.hpp>

import Mathpp.common;

namespace mathpp {

TEST_CASE( "common_check", "[common][check]" ) {
  SECTION( "Basic" ) {
    REQUIRE_THROWS_AS(check(false), CheckFail);
    REQUIRE_NOTHROW(check(true));

    REQUIRE_THROWS_AS(MATHPP_CHECK(false), CheckFail);
    REQUIRE_NOTHROW(MATHPP_CHECK(true));
  }

  SECTION( "Error is correct place" ) {
    constexpr std::source_location src_loc = std::source_location::current();
    std::string msg = "Hello";

    try {
      check(false, std::string{msg}, src_loc);
      REQUIRE_FALSE(true);
    } catch(CheckFail& fail) {
      REQUIRE_THAT(fail.msg, Catch::Matchers::Equals(msg, Catch::CaseSensitive::Yes));
      REQUIRE(fail.loc.column() == src_loc.column());
      REQUIRE(fail.loc.file_name() == src_loc.file_name());
      REQUIRE(fail.loc.function_name() == src_loc.function_name());
      REQUIRE(fail.loc.line() == src_loc.line());
    }
  }
}

}
