LINK_DIRECTORIES( ../base ../matrix ../nirvana )
LINK_LIBRARIES( base matrix nirvana )

ADD_EXECUTABLE( dark
  BSP.cpp
  BSP.h
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
  Model.h
  OBJ.cpp
  OBJ.h
  Particles.cpp
  Particles.h
  Render.cpp
  Render.h
  ResourceManager.h
  ResourceManager.cpp
  Shape.cpp
  Shape.h
  SimpleObject.cpp
  SimpleObject.h
  Sky.cpp
  Sky.h
  Skybox.cpp
  Skybox.h
  SoundManager.cpp
  SoundManager.h
  SparkGenRender.cpp
  SparkGenRender.h
  Terrain.cpp
  Terrain.h
  Water.cpp
  Water.h )

ADD_DEPENDENCIES( dark precompile )
