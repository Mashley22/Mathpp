function(add_unit_test TEST_NAME)

  add_executable(${TEST_NAME})

  target_link_libraries(${TEST_NAME}
    PRIVATE
      Mathpp
      Catch2::Catch2WithMain
  )

  target_compile_options(${TEST_NAME}
    PRIVATE
      ${PEDANTIC_COMPILE_OPTIONS}
      -Wno-double-promotion # since some catch2 issues 
      -Wno-c2y-extensions
  )

  catch_discover_tests(${TEST_NAME})

endfunction()

add_subdirectory(common)
add_subdirectory(basic)
