**Renamed to `OpenZone` and moved to http://code.google.com/p/openzone/**

Simple 3D engine that uses OpenGL for graphics, OpenAL or SDL for sound and SDL for other comunication with OS (threads, input, initialization).

It is meant to support huge levels (at most 20x20 km). Terrain is specified as heightmap, buildings and character use Quake3 BSP and Quake2 MD2 formats respectively.
As it is strictly layered it should ease integration of networking code and split for client-server model (maybe suitable for MMORPG?) which is planned in near future.

The engine is meant to be cross-platform, running at least on GNU/Linux, FreeBSD and Windows. However, the development occurs on GNU/Linux, so the development version may not compile on other platforms.