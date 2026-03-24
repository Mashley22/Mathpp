function(add_perf_val TEST_NAME)

  add_executable(${TEST_NAME})

  target_link_libraries(${TEST_NAME}
    PRIVATE
      Mathpp
      Mathpp_pv_utils
      Catch2::Catch2WithMain
  )

  target_compile_options(${TEST_NAME}
    PRIVATE
      ${PEDANTIC_COMPILE_OPTIONS}
  )

  catch_discover_tests(${TEST_NAME})

endfunction()

add_subdirectory(mathpp_pv_utils)

add_subdirectory(basic)
