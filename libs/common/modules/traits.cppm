module;

#include <concepts>
#include <cstdint>

#include <Mathpp/macros.hpp>

export module Mathpp.common:traits;

namespace mathpp {

namespace {

template<class T>
concept HasAdditiveIdentity = requires {
  { T(0) } -> std::same_as<T>;
};

template<class T>
concept HasMultiplicativeIdentity = requires {
  { T(1) } -> std::same_as<T>;
};

}

}

export namespace mathpp {

template<class T>
struct MatchUnsignedWidth {
  using type = 
    std::conditional_t<sizeof(T) == sizeof(std::uint64_t), std::uint64_t,
    std::conditional_t<sizeof(T) == sizeof(std::uint32_t), std::uint32_t,
    std::conditional_t<sizeof(T) == sizeof(std::uint16_t), std::uint16_t,
    std::conditional_t<sizeof(T) == sizeof(std::uint8_t),  std::uint8_t, 
    void>>>>; // Fallback to void if no matching size exists
};

template<class T>
struct MatchSignedWidth {
  using type = 
    std::conditional_t<sizeof(T) == sizeof(std::int64_t), std::int64_t,
    std::conditional_t<sizeof(T) == sizeof(std::int32_t), std::int32_t,
    std::conditional_t<sizeof(T) == sizeof(std::int16_t), std::int16_t,
    std::conditional_t<sizeof(T) == sizeof(std::int8_t),  std::int8_t, 
    void>>>>; // Fallback to void if no matching size exists
};

template<class T>
using MatchUnsignedWidth_t = MatchUnsignedWidth<T>::type;

template<class T>
using MatchSignedWidth_t = MatchSignedWidth<T>::type;

template<class T>
concept Addible = std::regular<T> &&
requires(T a, T b) {
  { a + b } -> std::convertible_to<T>;
  { a += b } -> std::same_as<T&>;
};

template<class T>
concept Subtractible = std::regular<T> &&
requires(T a, T b) {
  { a - b } -> std::convertible_to<T>;
  { a -= b } -> std::same_as<T&>;
};

template<class T>
concept Negatable = std::regular<T> &&
requires(T a) {
  { -a } -> std::convertible_to<T>;
};

template<class T>
concept Additive = Addible<T> &&
Subtractible<T> &&
Negatable<T> &&
HasAdditiveIdentity<T>;

template<class T, class T_other>
concept MultipliableBy = std::regular<T> &&
requires(T val, T_other val_other) {
  { val * val_other } -> std::convertible_to<T>;
  { val_other * val } -> std::convertible_to<T>;
  { val *= val_other} -> std::same_as<T&>;
};

template<class T> 
concept SelfMultipliable = MultipliableBy<T, T>;

template<class T, class... T_others>
concept MultipliableByAll = (MultipliableBy<T, T_others> && ...);

template<class T, class T_den>
concept DivisibleBy = std::regular<T> &&
requires(T num, T_den den) {
  { num / den } -> std::convertible_to<T>;
  { num /= den } -> std::same_as<T&>;
};

template<class T>
concept SelfDivisible = DivisibleBy<T, T>;

template<class T, class... T_others>
concept DivisibleByAll = (DivisibleBy<T, T_others> && ...);

template<class T>
concept Multiplicative = SelfMultipliable<T> &&
SelfDivisible<T> &&
HasMultiplicativeIdentity<T>;

template<class T>
concept Scalar = Additive<T> &&
Multiplicative<T> &&
std::totally_ordered<T>;

template<class T, class T_scalar>
concept MultipliableByScalar = MultipliableBy<T, T_scalar> &&
Scalar<T_scalar>;

template<class T, class... T_scalars>
concept MultipliableByAllScalars = (MultipliableByScalar<T, T_scalars> && ...);

template<class T, class T_scalar>
concept DivisibleByScalar = DivisibleBy<T, T_scalar> &&
Scalar<T_scalar>;

template<class T, class... T_scalars>
concept DivisibleByAllScalars = (DivisibleByScalar<T, T_scalars> && ...);

}
