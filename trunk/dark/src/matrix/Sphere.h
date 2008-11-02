/*
 *  Sphere.h
 *
 *  [description]
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Sphere_h_
#define _Sphere_h_

namespace Dark
{

  struct Sphere
  {
    Vec3   p;
    float r;

    Sphere()
    {
    }

    Sphere( const Vec3 &p_, float r_ ) : p( p_ ), r( r_ )
    {
    }

    Sphere operator + ( const Vec3 &v ) const
    {
      return Sphere( p + v, r );
    }

    Sphere operator - ( const Vec3 &v ) const
    {
      return Sphere( p - v, r );
    }

    Sphere &operator += ( const Vec3 &v )
    {
      p += v;
      return *this;
    }

    Sphere &operator -= ( const Vec3 &v )
    {
      p -= v;
      return *this;
    }

  };

}

#endif // _Sphere_h_