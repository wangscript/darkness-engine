INCLUDE_DIRECTORIES( .. )

ADD_LIBRARY( matrix STATIC
    bv.h
    Bounds.h
    AABB.h AABB.cpp
    Sphere.h
    Timer.h Timer.cpp
    BSP.h BSP.cpp
    Structure.h Structure.cpp
    Sky.h Sky.cpp
    Terrain.h Terrain.cpp
    SparkGen.h SparkGen.cpp
    Particle.h Particle.cpp
    Object.h Object.cpp
    DynObject.h DynObject.cpp
    World.h World.cpp
    Collider.h Collider.cpp
    Physics.h Physics.cpp
    Ladder.h Ladder.cpp
    Water.h Water.cpp
    Weapon.h Weapon.cpp
    Item.h Item.cpp
    Vehicle.h Vehicle.cpp
    O_Tree1.h O_Tree1.cpp
    O_Tree2.h O_Tree2.cpp
    D_SmallCrate.h D_SmallCrate.cpp
    D_BigCrate.h D_BigCrate.cpp
    D_WoodBarrel.h D_WoodBarrel.cpp
    D_MetalBarrel.h D_MetalBarrel.cpp
    B_Spirit.h B_Spirit.cpp
    B_Human.h B_Human.cpp
    B_Goblin.h B_Goblin.cpp
    Matrix.h Matrix.cpp )
