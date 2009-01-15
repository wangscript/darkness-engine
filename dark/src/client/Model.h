/*
 *  Model.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#pragma once

#include "MD2.h"

namespace Dark
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
