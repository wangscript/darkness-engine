/*
 *  Graphics_Terrain.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Graphics_Terrain_h_
#define _Graphics_Terrain_h_

#include "Terrain.h"
#include "Graphics_Context.h"
#include "Graphics_Frustum.h"

#define TERRA_DEPTH            2
#define TERRA_DETAILTEX_SCALE  4
#define TERRA_GROUNDTEX_SCALE  1

namespace Dark
{
namespace Graphics
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

#endif // _Graphics_Terrain_h_