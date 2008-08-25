/*
 *  Graphics_BSP.h
 *
 *  BSP level rendering class
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Graphics_BSP_h_
#define _Graphics_BSP_h_

#include "BSP.h"
#include "Graphics_Context.h"

#define BSP_GAMMA_CORR        0.5

namespace Dark
{
namespace Graphics
{

  class BSP
  {
    protected:

      Dark::BSP *bsp;

      uint   baseList;
      uint   *textures;
      uint   *lightMaps;

      Bitset drawnFaces;
      Bitset visibleLeafs;
      Bitset hiddenFaces;

      int  getLeafIndex( const Vec3 &p ) const;
      void compileFace( int faceIndex ) const;
      void drawFace( int faceIndex ) const;
      void drawNode( int index );

    public:

      BSP();
      ~BSP();

      explicit BSP( Dark::BSP *bsp );

      void init( Dark::BSP *bsp );
      void draw( const Vec3 &p );
      uint genList();

      static void beginRender();
      static void endRender();

      void free();
  };

}
}

#endif // _Graphics_BSP_h_
