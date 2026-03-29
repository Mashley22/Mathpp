#ifndef MATHPP_MACROS_HPP
#define MATHPP_MACROS_HPP

#define MATHPP_CHECK(expr) \
  mathpp::check(expr)

#define MATHPP_CHECK_ASSUME(expr) \
  mathpp::check(expr); \
  [[assume(expr)]]

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
#define MATHPP_NOEXCEPT noexcept
#define MATHPP_NOEXCEPT_COND(...) noexcept(__VA_ARGS__)
#else
#define MATHPP_NOEXCEPT
#define MATHPP_NOEXCEPT_COND(...)
#endif

#ifndef _MSCV_VER
#define MATHPP_PURE_FUNC __attribute__((pure))
#define MATHPP_CONST_FUNC __attribute__((const))
#else 
#define MATHPP_PURE_FUNC
#define MATHPP_CONST_FUNC __declspec(noalias)
#endif

#define MATHPP_IS_CONSTEXPR(...) requires { typename std::bool_constant<(__VA_ARGS__)>; }

#ifdef __has_builtin
#define MATHPP_HAS_BUILTIN(x) __has_builtin(x)
#else
#define MATHPP_HAS_BUILTIN(x) 0
#endif

#ifdef __has_constexpr_builtin
#define MATHPP_HAS_CONSTEXPR_BUILTIN(x) __has_constexpr_builtin(x)
#else
#define MATHPP_HAS_CONSTEXPR_BUILTIN(x) 0
#endif

#endif /* MATHPP_MACROS_HPP */
