module;

#include <source_location>
#include <string>

#ifdef NDEBUG
#ifndef MATHPP_UNIT_TEST
#include <iostream>
#include <cstdlib>
#endif
#endif

export module Mathpp.common:check;

export namespace mathpp {

struct CheckFail {
  std::string msg;
  std::source_location loc;
};

constexpr void
check([[maybe_unused]] bool expr,
      [[maybe_unused]] std::string&& msg = {},
      [[maybe_unused]] std::source_location loc = std::source_location::current()) {
#ifndef NDEBUG
  if (!expr) {
#ifndef MATHPP_UNIT_TEST
    std::cerr << "ASSERTION FAILED: " << message << "\n"
              << "File: " << location.file_name() << "\n"
              << "Line: " << location.line() << ":" << location.column() << "\n"
              << "Function: " << location.function_name() << std::endl;
    std::abort();
#else 
    throw CheckFail{.msg = msg, .loc = loc};
#endif 
  }
#endif
}

}
