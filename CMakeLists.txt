cmake_minimum_required(VERSION 3.28)

project(Mathpp VERSION 0.0.1 LANGUAGES CXX)

set(MINIMUM_CXX_STANDARD 23)
if(NOT DEFINED CMAKE_CXX_STANDARD)
  message(STATUS "No c++ standard found, defaulting to ${MINIMUM_CXX_STANDARD}")
  set(CMAKE_CXX_STANDARD ${MINIMUM_CXX_STANDARD})
elseif(CMAKE_CXX_STANDARD LESS ${MINIMUM_CXX_STANDARD})
  message(FATAL_ERROR "c++ standard set too low: ${CMAKE_CXX_STANDARD}. Need ${MINIMUM_CXX_STANDARD} atleast!")
endif()

add_library(Mathpp)

option(MATHPP_UNIT_TEST "build the unit tests" OFF)
option(MATHPP_PERF_VAL "build the performance validations" OFF) 
option(MATHPP_PERF_VAL_AS_BENCHMARK "build the performance validations as a set of benchmarks" OFF)

if(MSVC)
  set(MATHPP_SAFE_FAST_MATH
    /fp:precise  
    /fp:except-  
  )
else()
  set(MATHPP_SAFE_FAST_MATH
    -fno-trapping-math
    -fno-rounding-math
  )
endif()

set(PEDANTIC_COMPILE_OPTIONS
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
    -Wall -Wextra -Wpedantic -Werror
    -Wshadow -Wconversion -Wsign-conversion
    -Wcast-align -Wcast-qual -Wformat=2
    -Wundef -Wnull-dereference -Wdouble-promotion
    -Wimplicit-fallthrough -Wmissing-declarations
    -Wredundant-decls -Wstrict-overflow=5
    -Wswitch-enum -Wunreachable-code
  >

  $<$<CXX_COMPILER_ID:MSVC>:
    /W4          
    /WX          
    /w14242      
    /w14254      
    /w14263      
    /w14265      
    /w14287      
    /we4289      
    /w14296      
    /w14311      
    /w14826      
    /w14905      
    /w14906      
    /w14928      
    /permissive-
  >
)

target_compile_options(Mathpp
  PRIVATE
    ${MATHPP_SAFE_FAST_MATH}
)

if(MATHPP_UNIT_TEST)
  add_compile_definitions(MATHPP_UNIT_TEST)
  set(CMAKE_BUILD_TYPE "Debug")
  target_compile_options(Mathpp
    PRIVATE 
      ${PEDANTIC_COMPILE_OPTIONS}
  )
endif()

if(MATHPP_PERF_VAL)
  add_compile_definitions(MATHPP_PERF_VAL)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT supported OUTPUT error)

  if(supported)
    message(STATUS "IPO / LTO enabled")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
  else()
    message(STATUS "IPO / LTO not supported: <${error}>")
  endif()

  if(MSVC)
    add_compile_options("/Ox")
  else()
    add_compile_options("-O3")
  endif()

  if(MATHPP_PERF_VAL_AS_BENCHMARK)
    add_compile_definitions(MATHPP_PERF_VAL_AS_BENCHMARK)
  endif()
endif()

add_subdirectory(libs)

if(MATHPP_UNIT_TEST)
  enable_testing()
  include(CTest)

  add_subdirectory(extern/catch2)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/extern/catch2/extras")
  include(Catch)

  add_subdirectory(validation)
endif()

if(MATHPP_PERF_VAL)

  if(NOT MATHPP_PERF_VAL_AS_BENCHMARK)
    enable_testing()
    include(CTest)
    add_subdirectory(extern/catch2)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/extern/catch2/extras")
    include(Catch)
  endif()

  add_subdirectory(extern/benchpp)

  add_subdirectory(perf_val)
endif()
