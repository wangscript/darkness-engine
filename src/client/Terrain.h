/*
 *  Terrain.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Client_Terrain_h_
#define _Client_Terrain_h_

#include "matrix/Terrain.h"
#include "Context.h"
#include "Frustum.h"

#define TERRA_DEPTH            2
#define TERRA_DETAILTEX_SCALE  4
#define TERRA_GROUNDTEX_SCALE  1

namespace Dark
{
namespace Client
{

  struct Quadtree : Sphere
  {
    union
    {
      Quadtree *next[4];
      uint     list;
    };

    ~Quadtree();
  };

  class Terrain
  {
    protected:

      uint tTerraDetail;
      uint tTerraMap;

      Quadtree *qTerra;

      uint makeQuad( int minX, int minY, int maxX, int maxY, float *minHeight, float *maxHeight );
      void buildQuadtree( Quadtree *qTree, int minX, int minY, int maxX, int maxY,
                          float *minHeight, float *maxHeight );
      void drawQuadtree( const Quadtree *qTree );

    public:

      ~Terrain();

      void init( uint terraMap, uint terraDetail );
      void free();

      void draw();
  };

}
}

#endif // _Client_Terrain_h_
