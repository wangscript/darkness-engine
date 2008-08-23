/*
 *  Graphics_Model.cpp
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#include "precompiled.h"

#include "Graphics_Model.h"

namespace Dark
{
namespace Graphics
{

  Model::Model( int model_ )
  {
    model = model_;

    anim.type       = -1;
    anim.currTime   = 0.0;
    anim.oldTime    = 0.0;
    setAnim( 0 );
  }

  void Model::setAnim( int type )
  {
    if( anim.type != type ) {
      anim.startFrame = MD2::animList[type].firstFrame;
      anim.endFrame   = MD2::animList[type].lastFrame;
      anim.currFrame  = anim.startFrame;
      anim.nextFrame  = anim.startFrame + 1;
      anim.fps        = MD2::animList[type].fps;
      anim.frameTime  = 1.0 / anim.fps;
      anim.type       = type;
    }
  }

}
}
