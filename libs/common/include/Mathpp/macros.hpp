#ifndef MATHPP_MACROS_HPP
#define MATHPP_MACROS_HPP

#define MATHPP_IMPL_CHECK_DISPATCHER(_1, _2, NAME, ...) NAME

#define MATHPP_IMPL_CHECK_ASSUME_DISPATCHER(_1, _2, NAME, ...) NAME

#define MATHPP_ASSUME(expr) \
  do{ bool mathpp_impl_assume_temp_variable = (expr); [[assume(mathpp_impl_assume_temp_variable)]]; }while(0)

#define MATHPP_CHECK_EXPR_ONLY(expr) \
  mathpp::check(expr)

#define MATHPP_CHECK_WITH_MSG(expr, msg) \
  mathpp::check(expr, msg)

#define MATHPP_CHECK_ASSUME_EXPR_ONLY(expr) \
  mathpp::check(expr); \
  MATHPP_ASSUME(expr)

#define MATHPP_CHECK_ASSUME_WITH_MSG(expr, msg) \
  mathpp::check(expr, msg); \
  MATHPP_ASSUME(expr)

#define MATHPP_CHECK(...) \
  MATHPP_IMPL_CHECK_DISPATCHER(__VA_ARGS__, MATHPP_CHECK_WITH_MSG, MATHPP_CHECK_EXPR_ONLY)(__VA_ARGS__)

#define MATHPP_CHECK_ASSUME(...) \
  MATHPP_IMPL_CHECK_ASSUME_DISPATCHER(__VA_ARGS__, MATHPP_CHECK_ASSUME_WITH_MSG, MATHPP_CHECK_ASSUME_EXPR_ONLY)(__VA_ARGS__)

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
