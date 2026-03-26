#include <array>
#include <cstdint>

#include <catch2/catch_all.hpp>

import Mathpp.basic;
import Mathpp.common;

#define TEST_NUM 20

namespace mathpp {

namespace {

constexpr std::array<std::uint64_t, TEST_NUM> factorial_vals = {
    1,                
    1,                
    2,                
    6,                
    24,               
    120,              
    720,              
    5040,             
    40320,            
    362880,           
    3628800,          
    39916800,         
    479001600,        
    6227020800,       
    87178291200,      
    1307674368000,    
    20922789888000,   
    355687428096000,  
    6402373705728000, 
    121645100408832000,
};

template<Scalar T>
constexpr bool
test_factorial_int(void) {
  bool retVal = true;
  for (std::size_t i = 0; i < TEST_NUM; i++) {
    retVal = retVal && (factorial<T>(i) == static_cast<T>(factorial_vals[i]));
  }
  return retVal;
}

template<Scalar T>
constexpr bool
test_factorial_float(void) {
  bool retVal = true;
  for (std::size_t i = 0; i < TEST_NUM; i++) {
    retVal = retVal && isNearlyEqualRel(factorial<T>(i), static_cast<T>(factorial_vals[i]), std::numeric_limits<double>::epsilon());
  }
  return retVal;
}

}

TEST_CASE( "Factorial" , "[basic][factorial]" ) {

  SECTION( "integral type" ) {
    STATIC_REQUIRE(test_factorial_int<std::size_t>());
  }

  SECTION( "floating point type" ) {
    STATIC_REQUIRE(test_factorial_float<double>());
    STATIC_REQUIRE(test_factorial_float<float64>());
  }

}

}
