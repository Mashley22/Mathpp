add_library(Mathpp_pv_utils)

if(MATHPP_PERF_VAL_AS_BENCHMARK)
  target_link_libraries(Mathpp_pv_utils
    PUBLIC
      benchpp_with_main
  )
else()
  target_link_libraries(Mathpp_pv_utils
    PUBLIC
      benchpp
  )
endif()

target_sources(Mathpp_pv_utils
  PUBLIC
    FILE_SET public_cxx_modules TYPE CXX_MODULES
    FILES  
      mathpp_pv_utils.cppm
)
