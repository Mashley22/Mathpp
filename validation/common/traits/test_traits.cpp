#include <catch2/catch_test_macros.hpp>

#include <Mathpp/macros.hpp>

import Mathpp.common;

namespace mathpp {

namespace {

template<class... T>
concept AllAddible = (Addible<T> && ...);

template<class... T>
concept AllSubtractible = (Subtractible<T> && ...);

template<class... T>
concept AllAdditive = (Additive<T> && ...);

template<class... T>
concept AllMultipliable = (MultipliableByAll<T, MATHPP_ALL_ARITHMETIC_TYPES> && ...);

template<class... T>
concept AllDivisible = (DivisibleByAll<T, MATHPP_ALL_ARITHMETIC_TYPES> && ...);

template<class... T>
concept AllMultiplicative = (Multiplicative<T> && ...);

template<class... T>
concept AllScalar = (Scalar<T> && ...);

}

TEST_CASE( "Test the standard arithmetic types work!" , "[common][traits]") {

  SECTION( "Addible" ) {
    STATIC_REQUIRE(AllAddible<MATHPP_ALL_ARITHMETIC_TYPES>);
  }

  SECTION( "Subtractible" ) {
    STATIC_REQUIRE(AllSubtractible<MATHPP_ALL_ARITHMETIC_TYPES>);
  }

  SECTION( "Additive" ) {
    STATIC_REQUIRE(AllAdditive<MATHPP_ALL_ARITHMETIC_TYPES>);
  }

  SECTION( "Multipliable" ) {
    STATIC_REQUIRE(AllMultipliable<MATHPP_ALL_ARITHMETIC_TYPES>);
  }

  SECTION( "Divisible" ) {
    STATIC_REQUIRE(AllDivisible<MATHPP_ALL_ARITHMETIC_TYPES>);
  }

  SECTION( "Multiplicative" ) {
    STATIC_REQUIRE(AllMultiplicative<MATHPP_ALL_ARITHMETIC_TYPES>);
  }

  SECTION( "Scalar" ) {
    STATIC_REQUIRE(AllScalar<MATHPP_ALL_ARITHMETIC_TYPES>);
  }

}

namespace {

struct Addible_t {
  Addible_t operator+(const Addible_t& other) {
    return other;
  }

  Addible_t& operator+=(const Addible_t& other) {
    (void)other;
    return *this;
  }
  
  bool operator==(const Addible_t& other) const = default;
};

struct Subtractible_t {
  Subtractible_t operator-(const Subtractible_t& other) {
    return other;
  }

  Subtractible_t& operator-=(const Subtractible_t& other) {
    (void)other;
    return *this;
  }

  bool operator==(const Subtractible_t& other) const = default;
};

struct Additive_t {
  Additive_t() {}
  Additive_t(double) {}

  Additive_t operator-(const Additive_t& other) {
    return other;
  }

  Additive_t& operator-=(const Additive_t& other) {
    (void)other;
    return *this;
  }

  Additive_t operator+(const Additive_t& other) {
    return other;
  }

  Additive_t& operator+=(const Additive_t& other) {
    (void)other;
    return *this;
  }

  Additive_t operator-() {
    return *this;
  }

  bool operator==(const Additive_t& other) const = default;
};

struct AdditiveNonNegatable_t {
  AdditiveNonNegatable_t operator-(const AdditiveNonNegatable_t& other) {
    return other;
  }

  AdditiveNonNegatable_t& operator-=(const AdditiveNonNegatable_t& other) {
    (void)other;
    return *this;
  }

  AdditiveNonNegatable_t operator+(const AdditiveNonNegatable_t& other) {
    return other;
  }

  AdditiveNonNegatable_t& operator+=(const AdditiveNonNegatable_t& other) {
    (void)other;
    return *this;
  }

  bool operator==(const AdditiveNonNegatable_t& other) const = default;
};

}

TEST_CASE( "Additive with custom types!", "[common][traits]" ) {
  
  SECTION( "Addible" ) {
    STATIC_REQUIRE(Addible<Addible_t>);
    STATIC_REQUIRE(!Addible<Subtractible_t>);
    STATIC_REQUIRE(Addible<Additive_t>);
    STATIC_REQUIRE(Addible<AdditiveNonNegatable_t>);
  }

  SECTION( "Subtractible" ) {
    STATIC_REQUIRE(!Subtractible<Addible_t>);
    STATIC_REQUIRE(Subtractible<Subtractible_t>);
    STATIC_REQUIRE(Subtractible<Additive_t>);
    STATIC_REQUIRE(Subtractible<AdditiveNonNegatable_t>);
  }

  SECTION( "Additive" ) {
    STATIC_REQUIRE(!Additive<Addible_t>);
    STATIC_REQUIRE(!Additive<Subtractible_t>);
    STATIC_REQUIRE(!Additive<AdditiveNonNegatable_t>);
    STATIC_REQUIRE(Additive<Additive_t>);
  }

}

namespace {
  
struct MultipliableByInt_t {
  bool operator==(const MultipliableByInt_t& other) const = default;

  MultipliableByInt_t operator*(int) { return *this; }
  MultipliableByInt_t& operator*=(int) { return *this; }

};

[[maybe_unused]] MultipliableByInt_t operator*(int, MultipliableByInt_t) { return MultipliableByInt_t{}; }

struct SelfMultipliable_t {
  bool operator==(const SelfMultipliable_t& other) const = default;

  SelfMultipliable_t operator*(const SelfMultipliable_t& other) { return other; }

  SelfMultipliable_t& operator*=(const SelfMultipliable_t& other) { (void)other; return *this; }
};

struct DivisibleByInt_t {
  bool operator==(const DivisibleByInt_t& other) const = default;

  DivisibleByInt_t operator/(int) { return *this; }
  DivisibleByInt_t& operator/=(int) { return *this; }

};

struct SelfDivisible_t {
  bool operator==(const SelfDivisible_t& other) const = default;

  SelfDivisible_t operator/(const SelfDivisible_t& other) { return other; }

  SelfDivisible_t& operator/=(const SelfDivisible_t& other) { (void)other; return *this; }
};

struct Multiplicative_t {
  Multiplicative_t() {}
  Multiplicative_t(int) {}

  bool operator==(const Multiplicative_t& other) const = default;

  Multiplicative_t operator/(const Multiplicative_t& other) { return other; }

  Multiplicative_t& operator/=(const Multiplicative_t& other) { (void)other; return *this; }

  Multiplicative_t operator*(const Multiplicative_t& other) { return other; }

  Multiplicative_t& operator*=(const Multiplicative_t& other) { (void)other; return *this; }
};

}

TEST_CASE( "Multiplicative with custom types!", "[common][traits]" ) {
  
  SECTION( "Multipliable" ) {
    STATIC_REQUIRE(MultipliableBy<MultipliableByInt_t, int>);
    STATIC_REQUIRE(!MultipliableBy<MultipliableByInt_t, Addible_t>);
    STATIC_REQUIRE(!SelfMultipliable<MultipliableByInt_t>);

    STATIC_REQUIRE(!MultipliableBy<SelfMultipliable_t, int>);
    STATIC_REQUIRE(SelfMultipliable<SelfMultipliable_t>);

    STATIC_REQUIRE(SelfMultipliable<Multiplicative_t>);
  }

  SECTION( "Divisible" ) {
    STATIC_REQUIRE(DivisibleBy<DivisibleByInt_t, int>);
    STATIC_REQUIRE(!DivisibleBy<DivisibleByInt_t, Addible_t>);
    STATIC_REQUIRE(!SelfDivisible<DivisibleByInt_t>);

    STATIC_REQUIRE(!DivisibleBy<SelfDivisible_t, int>);
    STATIC_REQUIRE(SelfDivisible<SelfDivisible_t>);

    STATIC_REQUIRE(SelfDivisible<Multiplicative_t>);
  }

  SECTION( "Multiplicative" ) {
    STATIC_REQUIRE(Multiplicative<Multiplicative_t>);
    STATIC_REQUIRE(!Multiplicative<DivisibleByInt_t>);
    STATIC_REQUIRE(!Multiplicative<MultipliableByInt_t>);
  }

}

namespace {

struct Scalar_t {
  
  Scalar_t() = default;
  Scalar_t(unsigned int) {}

  bool operator==(const Scalar_t& other) const = default;
  bool operator<=(const Scalar_t& other) const { (void)other; return true; } 
  bool operator>=(const Scalar_t& other) const { (void)other; return true; }
  bool operator<(const Scalar_t& other) const { (void)other; return true; } 
  bool operator>(const Scalar_t& other) const { (void)other; return true; }

  Scalar_t operator/(const Scalar_t& other) { return other; }

  Scalar_t& operator/=(const Scalar_t& other) { (void)other; return *this; }

  Scalar_t operator*(const Scalar_t& other) { return other; }

  Scalar_t& operator*=(const Scalar_t& other) { (void)other; return *this; }

  Scalar_t operator+(const Scalar_t& other) { return other; }

  Scalar_t& operator+=(const Scalar_t& other) { (void)other; return *this; }

  Scalar_t operator-(const Scalar_t& other) { return other; }

  Scalar_t& operator-=(const Scalar_t& other) { (void)other; return *this; }

  Scalar_t operator-() { return *this; }
};

struct ScalarNonOrdered_t {
  bool operator==(const ScalarNonOrdered_t& other) const = default;
  ScalarNonOrdered_t operator/(const ScalarNonOrdered_t& other) { return other; }

  ScalarNonOrdered_t& operator/=(const ScalarNonOrdered_t& other) { (void)other; return *this; }

  ScalarNonOrdered_t operator*(const ScalarNonOrdered_t& other) { return other; }

  ScalarNonOrdered_t& operator*=(const ScalarNonOrdered_t& other) { (void)other; return *this; }

  ScalarNonOrdered_t operator+(const ScalarNonOrdered_t& other) { return other; }

  ScalarNonOrdered_t& operator+=(const ScalarNonOrdered_t& other) { (void)other; return *this; }

  ScalarNonOrdered_t operator-(const ScalarNonOrdered_t& other) { return other; }

  ScalarNonOrdered_t& operator-=(const ScalarNonOrdered_t& other) { (void)other; return *this; }

  ScalarNonOrdered_t operator-() { return *this; }
};

}

TEST_CASE( "Scalar with custom types", "[common][traits]" ) {
  STATIC_REQUIRE(Scalar<Scalar_t>);
  STATIC_REQUIRE(!Scalar<ScalarNonOrdered_t>);
}

}
