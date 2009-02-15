INCLUDE_DIRECTORIES( ../matrix ../nirvana )
LINK_DIRECTORIES( ../base ../matrix ../nirvana )
LINK_LIBRARIES( base matrix nirvana )

ADD_EXECUTABLE( dark
  BSP_Dual.cpp
  BSP_Dual.h
  Camera.cpp
  Camera.h
  Client.cpp
  Client.h
  Context.cpp
  Context.h
  Font.cpp
  Font.h
  Frustum.cpp
  Frustum.h
  MD2.cpp
  MD2.h
  MD3.cpp
  MD3.h
  Main.cpp
  Main.h
  Model.cpp
  Model.h
  OBJ.cpp
  OBJ.h
  Particles.cpp
  Particles.h
  Render.cpp
  Render.h
  Shape.cpp
  Shape.h
  SimpleObjectDual.cpp
  SimpleObjectDual.h
  Sky_Dual.cpp
  Sky_Dual.h
  Skybox.cpp
  Skybox.h
  SoundManager.cpp
  SoundManager.h
  SparkGenRender.cpp
  SparkGenRender.h
  Terrain_Dual.cpp
  Terrain_Dual.h
  Water_Dual.cpp
  Water_Dual.h )

ADD_DEPENDENCIES( dark precompile )
