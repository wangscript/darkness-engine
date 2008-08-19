/*
 *  Graphics_MD2.h
 *
 *  MD2 model class
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Graphics_MD2_h_
#define _Graphics_MD2_h_

#include "Timer.h"
#include "Graphics_Context.h"

namespace Dark
{
namespace Graphics
{

  struct MD2Anim
  {
    int firstFrame;
    int lastFrame;
    int fps;
  };

  struct MD2AnimState
  {
    int   startFrame;
    int   endFrame;

    int   fps;
    float frameTime;
    float currTime;
    float oldTime;

    int   type;

    int   currFrame;
    int   nextFrame;
  };

  class MD2
  {
    protected:

      static float anorms[][3];

      int   nFrames;
      int   nVerts;
      int   nGlCmds;

      Vec3  *verts;
      int   *glCmds;
      int   *lightNormals;

      uint  texId;

      float animInterpol;

      void animate( MD2AnimState *anim, float time );
      void interpolate( MD2AnimState *anim, Vec3 *vertList );
      void renderFrame();

    public:

      static MD2Anim animList[];

      MD2();
      ~MD2();

      bool load( const char *path );

      void drawFrame( int frame );
      void draw( MD2AnimState *anim );

      void scale( float scale );
      void translate( const Vec3 &t );
      void translate( int animType, const Vec3 &t );

      static uint genList( const char *path, float scale, const Vec3 &translate );

      void free();
  };

}
}

#endif // _Graphics_MD2_h_
