/*
 *  Model.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Client_Model_h_
#define _Client_Model_h_

#include "MD2.h"

namespace oz
{
namespace Client
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

#endif // _Client_Model_h_
