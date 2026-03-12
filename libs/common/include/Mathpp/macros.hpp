#ifndef MATHPP_MACROS_HPP
#define MATHPP_MACROS_HPP

#define MATHPP_CHECK(expr) \
  mathpp::check(expr)

#define MATHPP_ALL_ARITHMETIC_TYPES \
  float, double, long double, \
  int, unsigned int, \
  short, unsigned short, \
  long, unsigned long, \
  long long, unsigned long long, \
  char, unsigned char, signed char

#define MATHPP_ALL_SCALAR_TYPES \
  MATHPP_ALL_ARITHMETIC_TYPES

#ifndef MATHPP_UNIT_TEST
#define MATHPP_NOEXCEPT(...) noexcept(...)
#else
#define MATHPP_NOEXCEPT(...)
#endif

#endif /* MATHPP_MACROS_HPP */
