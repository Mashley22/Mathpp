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

function(add_perf_val TEST_NAME)

  add_executable(${TEST_NAME})

  target_compile_definitions(${TEST_NAME}
    PRIVATE
      TOLERANCE=${TOLERANCE}
      RUNTIME_SCALE=${RUNTIME_SCALE}
  )

  target_link_libraries(${TEST_NAME}
    PRIVATE
      Mathpp
      Mathpp_pv_utils
      Catch2::Catch2WithMain
  )

  target_compile_options(${TEST_NAME}
    PRIVATE
      ${PEDANTIC_COMPILE_OPTIONS}
      ${MATHPP_SAFE_FAST_MATH}
  )

  catch_discover_tests(${TEST_NAME})

endfunction()

add_subdirectory(mathpp_pv_utils)

add_subdirectory(basic)
