Simple 3D engine written in C++ and based on open-source cross-platform libraries suitable for FPS shooters and RPGs.

# Introduction #

I'm developing a 3D engine as a hobby since the end of high school in 2002. Since then many attempts were made, many rewrites and refractories of the code. Since I have many other things to do the development is slow and unregular last years.

# Details #

It is meant to support huge levels (at most 20x20 km). Terrain is specified as height map, buildings and character use Quake3 BSP and Quake2 MD2 formats respectively. As it is strictly layered it should ease integration of networking code and split for client-server model (maybe suitable for MMORPG?) which is planned in near future.

The engine is meant to be cross-platform, running at least on GNU/Linux, FreeBSD and Windows. However, the development occurs on GNU/Linux, so the development version may not compile on other platforms.

**Features**
  * quite advanced AABB collision detection/physics. It's still AABB (the physical representation of object cannot rotate) like in old 5+ years old games, but it's still better (you can push a whole pile of boxes at once!)
  * water
  * particles
  * exchanging day and night (lighting, sky and visual distance adjust to time of day)
  * use of Quake2 MD2 models for objects
  * use of Quake3 BSP levels for buildings
  * playing of Ogg Vorbis, WAVE and AU sounds

# Design #

**Base library**

  * utility functions (min, max, array manipulation functions, quicksort ...)
  * containers, including iterators (List, DList, Vector, SVector, HashIndex, HashString)
  * some useful data types (String, Bitset)
  * basic math and linear algebra classes (Math, Vec3, Quat, Mat33, Mat44)
  * utilities (LogFile, Config)
  * memory management (Reuser)

**Matrix layer**

It holds and handles logical representation of the world. It strictly avoids any code or data that would handle, contain or reference anything in higher layers. Roughly it contains following things:
  * data structures for world representation
  * loaders for BSP levels, terrain ...
  * collision detection
  * physics
  * object logic
  * scheduling sounds
  * character logic and movement

**Nirvana layer**

It's an AI layer. It launches in separate thread. It provides _brain_ for computer-controlled characters in Matrix layer.

**Client layer**

The front-end. It renders world to the screen, plays sounds, read player input ...
  * graphics rendering
  * playing sounds
  * initialization of game
  * loading of sounds, textures, models, etc.
  * reading input

# How to make it work #

Required tools:
  * cmake
  * KDevelop (optional)

Required libraries:
  * SDL
  * SDL\_image
  * SDL\_net
  * SDL\_mixer
  * MesaGL
  * MesaGLU
  * OpenAL
  * freealut
  * libvorbis
  * libxml2

Data files:

> Since data files might violate some copyrights they cannot be publicly distributed.

**Unix instructions**:

Go to project root and run
```
cmake .
make
```
to compile project. Then run the engine with `src/client/dark`. First time it will  crash, since it won't find data files, but it will create default settings in `~/.dark/config.xml`. Edit that file to your preference and don't forget to set `data` to where you have data files installed. Run it again and that time it should work.

**Windows instructions**:

  * Use Dev-C++: install devpaks for all libraries and create a project (if you are familiar with Dev-C++ you should probably know what to do).

  * [Visual C++ 2008](BuildVC2008.md)

# TODO #

Short-term:
  * ladder
  * Quake3 MD3 models
  * vehicles
  * incremental tree growth
  * XML files to describe world
  * loading/saving world state

Medium-term:
  * networking
  * scripting

Long-term:
  * shadows, shaders and other advanced graphics effects
  * integration of Bullet physics engine