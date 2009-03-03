link_libraries( base )

add_executable( test
  pool.cpp )

add_dependencies( test precompile )
