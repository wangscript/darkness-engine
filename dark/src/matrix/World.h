/*
 *  World.h
 *
 *  Matrix data structure for world (terrain, all structures and objects in the world)
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _World_h_
#define _World_h_

#include "Timer.h"
#include "Translator.h"

#include "BSP.h"
#include "Sky.h"
#include "Terrain.h"

#include "Structure.h"
#include "Sound.h"
#include "Object.h"
#include "SparkGen.h"
#include "Particle.h"

#include "Sector.h"

namespace Dark
{

  class World : public Bounds
  {
    protected:

      // List of free indices. Indices can be reused after one full world update pass, so that all
      // references to those indices are removed (object update functions should remove all invalid
      // references).
      Vector<int> strFreeQueue[3];
      Vector<int> objFreeQueue[3];
      Vector<int> sparkGenFreeQueue[3];
      Vector<int> partFreeQueue[3];

      int addingQueue;
      int standbyQueue;
      int freedQueue;

    public:

      static const int MAX = 64;
      static const scalar DIM;

      Sky     sky;
      Terrain terrain;
      Sector  sectors[World::MAX][World::MAX];

      Vector<Structure*>  structures;
      Vector<SparkGen*>   sparkGens;
      Vector<Object*>     objects;
      Vector<Particle*>   particles;

      // bsp list (should not change during world existance)
      Vector<BSP*>        bsps;

      int minSectX, minSectY;
      int maxSectX, maxSectY;

      World();

      // get pointer to the sector the point is in
      Sector* getSector( float x, float y );
      Sector* getSector( const Vec3 &p );

      // get indices of the sector the point is in
      void getInters( float x, float y, float epsilon = 0.0 );
      void getInters( const Vec3 &p, float epsilon = 0.0 );

      // get indices of min and max sectors which the AABB intersects
      void getInters( const AABB &bb, float epsilon = 0.0 );

      // get indices of min and max sectors which the bounds intersects
      void getInters( const Bounds &bounds, float epsilon = 0.0 );

      void put( Object *obj );
      void cut( Object *obj );

      int add( Structure *str );
      int add( Object *obj, bool doPut = true );
      int add( SparkGen *sparkGen );
      int add( Particle *part );

      void remove( Structure *str );
      void remove( Object *obj );
      void remove( SparkGen *sparkGen );
      void remove( Particle *part );

      void genParticles( int number, const Vec3 &p,
                         const Vec3 &velocity, float velocitySpread,
                         float rejection, float mass, float lifeTime,
                         int model, const Vec3 &color, float colorSpread );

      void beginUpdate();
      void endUpdate();
      // trim vectors to optimize memory usage
      void trim();

      void add( BSP *bsp );

      void free();
  };

  extern World world;

  inline Sector *World::getSector( float x, float y )
  {
    int ix = (int)( ( x + World::DIM ) / Sector::DIM );
    int iy = (int)( ( y + World::DIM ) / Sector::DIM );

    ix = bound( ix, 0, World::MAX - 1 );
    iy = bound( iy, 0, World::MAX - 1 );

    return &sectors[ix][iy];
  }

  inline Sector *World::getSector( const Vec3 &p )
  {
    int ix = (int)( ( p.x + World::DIM ) / Sector::DIM );
    int iy = (int)( ( p.y + World::DIM ) / Sector::DIM );

    ix = bound( ix, 0, World::MAX - 1 );
    iy = bound( iy, 0, World::MAX - 1 );

    return &sectors[ix][iy];
  }

  inline void World::getInters( float x, float y, float epsilon )
  {
    minSectX = (int)( ( x - epsilon + World::DIM ) / Sector::DIM );
    minSectY = (int)( ( y - epsilon + World::DIM ) / Sector::DIM );

    maxSectX = (int)( ( x + epsilon + World::DIM ) + 1 / Sector::DIM );
    maxSectY = (int)( ( y + epsilon + World::DIM ) + 1 / Sector::DIM );

    minSectX = bound( minSectX, 0, World::MAX - 1 );
    minSectY = bound( minSectY, 0, World::MAX - 1 );
    maxSectX = bound( maxSectX, 0, World::MAX - 1 );
    maxSectY = bound( maxSectY, 0, World::MAX - 1 );
  }

  inline void World::getInters( const Vec3 &p, float epsilon )
  {
    minSectX = (int)( ( p.x - epsilon + World::DIM ) / Sector::DIM );
    minSectY = (int)( ( p.y - epsilon + World::DIM ) / Sector::DIM );

    maxSectX = (int)( ( p.x + epsilon + World::DIM ) / Sector::DIM );
    maxSectY = (int)( ( p.y + epsilon + World::DIM ) / Sector::DIM );

    minSectX = bound( minSectX, 0, World::MAX - 1 );
    minSectY = bound( minSectY, 0, World::MAX - 1 );
    maxSectX = bound( maxSectX, 0, World::MAX - 1 );
    maxSectY = bound( maxSectY, 0, World::MAX - 1 );
  }

  inline void World::getInters( const AABB &bb, float epsilon )
  {
    minSectX = (int)( ( bb.p.x - bb.dim.x - epsilon + World::DIM ) / Sector::DIM );
    minSectY = (int)( ( bb.p.y - bb.dim.y - epsilon + World::DIM ) / Sector::DIM );

    maxSectX = (int)( ( bb.p.x + bb.dim.x + epsilon + World::DIM ) / Sector::DIM );
    maxSectY = (int)( ( bb.p.y + bb.dim.y + epsilon + World::DIM ) / Sector::DIM );

    minSectX = bound( minSectX, 0, World::MAX - 1 );
    minSectY = bound( minSectY, 0, World::MAX - 1 );
    maxSectX = bound( maxSectX, 0, World::MAX - 1 );
    maxSectY = bound( maxSectY, 0, World::MAX - 1 );
  }

  inline void World::getInters( const Bounds &bounds, float epsilon )
  {
    minSectX = (int)( ( bounds.mins.x - epsilon + World::DIM ) / Sector::DIM );
    minSectY = (int)( ( bounds.mins.y - epsilon + World::DIM ) / Sector::DIM );

    maxSectX = (int)( ( bounds.maxs.x + epsilon + World::DIM ) / Sector::DIM );
    maxSectY = (int)( ( bounds.maxs.y + epsilon + World::DIM ) / Sector::DIM );

    minSectX = bound( minSectX, 0, World::MAX - 1 );
    minSectY = bound( minSectY, 0, World::MAX - 1 );
    maxSectX = bound( maxSectX, 0, World::MAX - 1 );
    maxSectY = bound( maxSectY, 0, World::MAX - 1 );
  }

}

#endif // _World_h_
