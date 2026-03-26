target_sources(Mathpp
  PUBLIC
    FILE_SET public_cxx_modules TYPE CXX_MODULES
    BASE_DIRS ${CMAKE_CURRENT_LIST_DIR}/..
    FILES  
      modules/check.cppm
      modules/traits.cppm
      modules/floating_point.cppm
      common.cppm
)

target_include_directories(Mathpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)
