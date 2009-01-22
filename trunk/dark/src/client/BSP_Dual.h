/*
 *  BSP_Dual.h
 *
 *  BSP level rendering class
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

#include "matrix/BSP.h"
#include "Context.h"

#define BSP_GAMMA_CORR        0.5

namespace Dark
{

  class BSP_Dual
  {
    protected:

      BSP  *bsp;

      int  contextId;

      uint baseList;
      uint *textures;
      uint *lightMaps;

      Bitset drawnFaces;
      Bitset visibleLeafs;
      Bitset hiddenFaces;

      int  getLeafIndex( const Vec3 &p ) const;
      void compileFace( int faceIndex ) const;
      void drawFace( int faceIndex ) const;
      void drawNode( int index );

    public:

      BSP_Dual();
      ~BSP_Dual();

      explicit BSP_Dual( BSP *bsp );

      void init( BSP *bsp );
      void draw( const Vec3 &p );
      uint genList();

      static void beginRender();
      static void endRender();

      void free();
  };

}
