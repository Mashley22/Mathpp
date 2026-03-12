module;

#include <concepts>

#include <Mathpp/macros.hpp>

export module Mathpp.common:traits;

export namespace mathpp {

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
Negatable<T>;

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
SelfDivisible<T>;

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
