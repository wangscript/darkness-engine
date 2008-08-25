/*
 *  Graphics_Render.h
 *
 *  Graphics render engine
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Graphics_Render_h_
#define _Graphics_Render_h_

#include "World.h"

#include "Graphics_Font.h"
#include "Graphics_BSP.h"
#include "Graphics_Terrain.h"
#include "Graphics_MD2.h"
#include "Graphics_Model.h"
#include "Graphics_SparkGenRender.h"

namespace Dark
{
namespace Graphics
{

  class Render
  {
    protected:

      static const int MODEL_HT_SIZE = 4096;
      static const int SPARKGENRENDER_HT_SIZE = 4096;

      static const float RELEASED_CULL_FACTOR;
      static const float INCH;

      static const float BLACK[];
      static const float WHITE[];

      static const float GLOBAL_AMBIENT[];

      static const float NIGHT_FOG_COEFF;
      static const float NIGHT_FOG_DIST;

      Font          font;

      Terrain       terra;

      Vector<BSP*>  bsps;
      Bitset        drawnStructures;

      Vector<uint>  lists;

      Vector<MD2*>  md2s;

      HashIndex<Model, MODEL_HT_SIZE> models;
      HashIndex<SparkGenRender, SPARKGENRENDER_HT_SIZE> sparkGenRenders;

      Vector<Structure*> structures;
      Vector<Object*>    objects;
      Vector<Object*>    blendedObjects;
      Vector<Object*>    waterObjects;
      Vector<Particle*>  particles;
      Vector<SparkGen*>  sparkGens;

      float perspectiveAngle;
      float perspectiveAspect;
      float perspectiveMin;
      float perspectiveMax;

      float particleRadius;

      bool  drawAABBs;
      bool  blendHeaven;
      bool  showAim;

      bool isSpirit;
      bool isUnderWater;

      void drawObject( Object *obj );
      void drawSparkGen( SparkGen *sparkGen );
      void scheduleSector( int sectorX, int sectorY );

    public:

      void init();
      void load();
      void free();

      void draw();
  };

  extern Render render;

}
}

#endif // _Render_h_
