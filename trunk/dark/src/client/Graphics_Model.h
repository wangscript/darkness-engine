/*
 *  Graphics_Model.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Graphics_Model.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Graphics_Model_h_
#define _Graphics_Model_h_

#include "Graphics_MD2.h"

namespace Dark
{
namespace Graphics
{

  struct Model
  {
    enum State
    {
      NOT_UPDATED,
      UPDATED
    };

    State        state;
    int          model;
    MD2AnimState anim;

    explicit Model( int model );

    void setAnim( int type );
  };

}
}

#endif // _Graphics_Model_h_
