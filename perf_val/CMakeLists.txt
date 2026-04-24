set(TOLERANCE
  5
  CACHE
  STRING
  "The tolerance multiplier for the difference between the means 
  compared to the combined standard deviation of the means of 
  cmath implementations and mathpp"
)

set(RUNTIME_SCALE
  10
  CACHE
  STRING
  "Run length multiplier, the default length should make the
  performance validations take not a huge amount of time 
  (~100ms per), but still be fairly good representations"
)

if(MATHPP_PERF_VAL_AS_BENCHMARK)
  add_executable(Benchmarks)

  set_target_properties(Benchmarks
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  )

  file(TOUCH ${CMAKE_CURRENT_BINARY_DIR}/dummy.cpp)

  target_sources(Benchmarks
    PRIVATE
      ${CMAKE_CURRENT_BINARY_DIR}/dummy.cpp
  )
endif()

function(add_perf_val TEST_NAME)
  
  if(MATHPP_PERF_VAL_AS_BENCHMARK)
    add_library(${TEST_NAME} OBJECT)
  else()
    add_executable(${TEST_NAME})
  endif()

  target_compile_definitions(${TEST_NAME}
    PRIVATE
      TOLERANCE=${TOLERANCE}
      RUNTIME_SCALE=${RUNTIME_SCALE}
  )

  target_link_libraries(${TEST_NAME}
    PRIVATE
      Mathpp
      Mathpp_pv_utils
  )

  target_compile_options(${TEST_NAME}
    PRIVATE
      ${PEDANTIC_COMPILE_OPTIONS}
      ${MATHPP_SAFE_FAST_MATH}
      -Wno-c2y-extensions
      -Wno-double-promotion # since some catch2 issues 
  )

  if(MATHPP_PERF_VAL_AS_BENCHMARK)
    target_link_libraries(Benchmarks
      PRIVATE
        ${TEST_NAME}
    )
  else()
    catch_discover_tests(${TEST_NAME})
    target_link_libraries(${TEST_NAME}
      PRIVATE
        Catch2::Catch2WithMain
    )
  endif()
endfunction()

add_subdirectory(mathpp_pv_utils)

add_subdirectory(basic)
