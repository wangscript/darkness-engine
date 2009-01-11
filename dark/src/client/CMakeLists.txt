INCLUDE_DIRECTORIES( .. )
LINK_DIRECTORIES( ../base ../matrix ../nirvana )
LINK_LIBRARIES( base matrix nirvana )

ADD_EXECUTABLE( dark
    Camera.h Camera.cpp
    Sky.h Sky.cpp
    Frustum.h Frustum.cpp
    Font.h Font.cpp
    Context.h Context.cpp
    Skybox.h Skybox.cpp
    Terrain.h Terrain.cpp
    SparkGenRender.h SparkGenRender.cpp
    Shape.h Shape.cpp
    Water.h Water.cpp
    BSP.h BSP.cpp
#OBJ.h OBJ.cpp
    MD2.h MD2.cpp
    MD3.h MD3.cpp
    Model.h Model.cpp
    Render.h Render.cpp
    SoundManager.h SoundManager.cpp
    Client.h Client.cpp
    Main.h Main.cpp )
