target_sources(Mathpp
  PUBLIC
    FILE_SET public_cxx_modules TYPE CXX_MODULES
    FILES  
      basic.cppm
      modules/factorial.cppm
      modules/pow.cppm
      modules/abs.cppm
      modules/compare.cppm
      modules/fma.cppm
      modules/trunc.cppm
      modules/ceil.cppm
      modules/floor.cppm
      modules/bit.cppm
      modules/ilogb.cppm
      modules/ldexp.cppm
)
