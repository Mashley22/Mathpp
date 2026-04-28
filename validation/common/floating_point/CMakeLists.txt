add_unit_test(test_floating_point)

target_sources(test_floating_point
  PRIVATE
    test_isnan.cpp
    test_isinf.cpp
)
