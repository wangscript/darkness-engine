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

    State state;
    Model *prev[1];
    Model *next[1];

    virtual void load() = 0;
    virtual void draw() = 0;
  };

}
}
