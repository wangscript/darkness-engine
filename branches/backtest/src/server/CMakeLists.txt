link_libraries( base matrix nirvana )

add_executable( server
  Main.cpp
  Main.h
  Server.cpp
  Server.h )

add_dependencies( server precompile )
