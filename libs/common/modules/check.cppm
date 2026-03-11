module;

#include<source_location>
#include <string>
#include <exception>

export module Mathpp.common:check;

export namespace mathpp {

struct CheckFail {
  std::string msg;
  std::source_location loc;
};

constexpr void
check(bool expr,
      std::string&& msg = {},
      std::source_location loc = std::source_location::current()) {
#ifdef NDEBUG
  (void)expr;
  (void)msg;
  (void)loc;
#else 
  if (!expr) {
#ifndef MATHPP_UNIT_TEST
    (void)msg;
    (void)loc;
    std::terminate();
#else 
    throw CheckFail{.msg = msg, .loc = loc};
#endif 
  }
#endif
}

}
