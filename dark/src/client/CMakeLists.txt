INCLUDE_DIRECTORIES( .. )
LINK_DIRECTORIES( ../base ../matrix ../nirvana )
LINK_LIBRARIES( base matrix nirvana )

ADD_EXECUTABLE( dark Camera.cpp SoundManager.cpp Client.cpp
                     Graphics_Font.cpp Graphics_Context.cpp Graphics_Frustum Graphics_Shape.cpp
                     Graphics_Sky.cpp Graphics_Water.cpp Graphics_Skybox.cpp Graphics_Terrain.cpp
                     Graphics_BSP.cpp Graphics_MD2.cpp Graphics_Model.cpp Graphics_SparkGenRender.cpp
                     Graphics_Render.cpp
                     Main.cpp )
