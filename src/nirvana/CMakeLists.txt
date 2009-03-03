add_library( nirvana STATIC
  M_Walker.cpp
  M_Walker.h
  Mind.cpp
  Mind.h
  Nirvana.cpp
  Nirvana.h
  Soul.cpp
  Soul.h )

add_dependencies( nirvana precompile )
