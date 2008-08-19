/*
 *  Bounds.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Bounds_h_
#define _Bounds_h_

namespace Dark
{

  struct AABB;

  struct Bounds
  {
    Vec3 mins;
    Vec3 maxs;

    Bounds()
    {
    }

    Bounds( const Vec3 &mins_, const Vec3 &maxs_ ) : mins( mins_ ), maxs( maxs_ )
    {
    }

    Bounds &fromPointMove( const Vec3 &p, const Vec3 &move, scalar eps = 0.0 )
    {
      if( move.x < 0.0 ) {
        mins.x = p.x - 2.0 * eps + move.x;
        maxs.x = p.x + 2.0 * eps;
      }
      else {
        mins.x = p.x - 2.0 * eps;
        maxs.x = p.x + 2.0 * eps + move.x;
      }
      if( move.y < 0.0 ) {
        mins.y = p.y - 2.0 * eps + move.y;
        maxs.y = p.y + 2.0 * eps;
      }
      else {
        mins.y = p.y - 2.0 * eps;
        maxs.y = p.y + 2.0 * eps + move.y;
      }
      if( move.z < 0.0 ) {
        mins.z = p.z - 2.0 * eps + move.z;
        maxs.z = p.z + 2.0 * eps;
      }
      else {
        mins.z = p.z - 2.0 * eps;
        maxs.z = p.z + 2.0 * eps + move.z;
      }
      return *this;
    }

    Bounds operator + ( const Vec3 &v ) const
    {
      return Bounds( mins + v, maxs + v );
    }

    Bounds operator - ( const Vec3 &v ) const
    {
      return Bounds( mins - v, maxs - v );
    }

    Bounds &operator += ( const Vec3 &v )
    {
      mins += v;
      maxs += v;
      return *this;
    }

    Bounds &operator -= ( const Vec3 &v )
    {
      mins -= v;
      maxs -= v;
      return *this;
    }

    bool includes( const Vec3 &v, scalar eps = 0.0 ) const
    {
      return
          mins.x - eps <= v.x && v.x <= maxs.x + eps &&
          mins.y - eps <= v.y && v.y <= maxs.y + eps &&
          mins.z - eps <= v.z && v.z <= maxs.z + eps;
    }

    bool isInside( const Bounds &b, scalar eps = 0.0 ) const
    {
      return
          b.mins.x - eps <= mins.x && maxs.x <= b.maxs.x + eps &&
          b.mins.y - eps <= mins.y && maxs.y <= b.maxs.y + eps &&
          b.mins.z - eps <= mins.z && maxs.z <= b.maxs.z + eps;
    }

    bool includes( const Bounds &b, scalar eps = 0.0 ) const
    {
      return b.isInside( *this, eps );
    }

    bool overlaps( const Bounds &b, scalar eps = 0.0 ) const
    {
      return
          b.mins.x - eps <= maxs.x && mins.x <= b.maxs.x + eps &&
          b.mins.y - eps <= maxs.y && mins.y <= b.maxs.y + eps &&
          b.mins.z - eps <= maxs.z && mins.z <= b.maxs.z + eps;
    }

    // implemented in AABB.h
    bool isInside( const AABB &a, scalar eps = 0.0 ) const;
    bool includes( const AABB &a, scalar eps = 0.0 ) const;
    bool overlaps( const AABB &a, scalar eps = 0.0 ) const;

  };

}

#endif // _Bounds_h_
