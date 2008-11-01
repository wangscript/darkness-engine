INCLUDE_DIRECTORIES( .. )
LINK_DIRECTORIES( ../base ../matrix ../nirvana )
LINK_LIBRARIES( base matrix nirvana )

ADD_EXECUTABLE( dark Camera.cpp SoundManager.cpp Client.cpp
                     Font.cpp Context.cpp Frustum Shape.cpp
                     Sky.cpp Water.cpp Skybox.cpp Terrain.cpp
                     BSP.cpp MD2.cpp Model.cpp SparkGenRender.cpp
                     Render.cpp
                     Main.cpp )
