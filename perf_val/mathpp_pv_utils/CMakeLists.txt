add_library(Mathpp_pv_utils)

target_link_libraries(Mathpp_pv_utils
  PUBLIC
    benchpp
)

target_sources(Mathpp_pv_utils
  PUBLIC
    FILE_SET public_cxx_modules TYPE CXX_MODULES
    FILES  
      mathpp_pv_utils.cppm
)
