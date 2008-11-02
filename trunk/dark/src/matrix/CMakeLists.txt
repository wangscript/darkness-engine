INCLUDE_DIRECTORIES( .. )

ADD_LIBRARY( matrix STATIC AABB.cpp
                           Timer.cpp Translator.cpp
                           BSP.cpp Structure.cpp Sky.cpp Terrain.cpp SparkGen.cpp
                           Particle.cpp Object.cpp DynObject.cpp
                           World.cpp Collider.cpp Physics.cpp
                           Ladder.cpp Water.cpp Weapon.cpp Item.cpp Vehicle.cpp
                           O_Tree1.cpp O_Tree2.cpp
                           D_SmallCrate.cpp D_BigCrate.cpp D_WoodBarrel.cpp D_MetalBarrel.cpp
                           B_Spirit.cpp B_Human.cpp B_Goblin.cpp
                           ObjectFactory.cpp Matrix.cpp )
