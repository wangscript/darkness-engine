/*
 *  Vec3.h
 *
 *  3D vector library
 *
 *  Copyright (C) 2002-2008, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Dark_Vec3_h_
#define _Dark_Vec3_h_

namespace Dark
{

  struct Quat;

  struct Vec3
  {
    scalar x;
    scalar y;
    scalar z;

    Vec3()
    {}

    Vec3( scalar x_, scalar y_, scalar z_ ) : x( x_ ), y( y_ ), z( z_ )
    {}

    explicit Vec3( scalar *v )
    {
      *this = *(Vec3*) v;
    }

    // implemented in Quat.h
    explicit Vec3( const Quat &q );

    static Vec3 zero()
    {
      return Vec3( 0.0, 0.0, 0.0 );
    }

    // casting
    operator scalar* () const
    {
      return (scalar*) this;
    }

    operator const scalar* () const
    {
      return (const scalar*) this;
    }

    scalar &operator [] ( int i )
    {
      return ( (scalar*) this )[i];
    }

    const scalar &operator [] ( int i ) const
    {
      return ( (scalar*) this )[i];
    }

    bool operator == ( const Vec3 &a ) const
    {
      return x == a.x && y == a.y && z == a.z;
    }

    bool operator != ( const Vec3 &a ) const
    {
      return x != a.x || y != a.y || z != a.z;
    }

    bool isEqual( const Vec3 &a, scalar epsilon ) const
    {
      return
          Math::abs( x - a.x ) <= epsilon &&
          Math::abs( y - a.y ) <= epsilon &&
          Math::abs( z - a.z ) <= epsilon;
    }

    Vec3 operator + () const
    {
      return *this;
    }

    Vec3 operator - () const
    {
      return Vec3( -x, -y, -z );
    }

    // length
    scalar operator ! () const
    {
      return Math::sqrt( x*x + y*y + z*z );
    }

    // square length
    scalar sqL() const
    {
      return x*x + y*y + z*z;
    }

    bool isZero() const
    {
      return 0.0 == x && x == y && y == z;
    }

    Vec3 &setZero()
    {
      z = y = x = 0.0;
      return *this;
    }

    bool isUnit() const
    {
      return x*x + y*y + z*z == 1.0;
    }

    Vec3 operator ~ () const
    {
      assert( x*x + y*y + z*z > 0.0 );

      scalar r = 1.0 / Math::sqrt( x*x + y*y + z*z );
      return Vec3( x * r, y * r, z * r );
    }

    // normize
    Vec3 &norm()
    {
      assert( x*x + y*y + z*z > 0.0 );

      scalar r = 1.0 / Math::sqrt( x*x + y*y + z*z );
      x *= r;
      y *= r;
      z *= r;
      return *this;
    }

    bool isColinear( const Vec3 &v ) const
    {
      scalar p1 = v.x * y * z;
      scalar p2 = v.y * x * z;
      scalar p3 = v.z * x * y;

      return p1 == p2 && p1 == p3;
    }

    bool isColinear( const Vec3 &v, scalar epsilon ) const
    {
      scalar p1 = v.x * y * z;
      scalar p2 = v.y * x * z;
      scalar p3 = v.z * x * y;

      return Math::abs( p1 - p2 ) <= epsilon && Math::abs( p1 - p3 ) <= epsilon;
    }

    Vec3 &operator += ( const Vec3 &a )
    {
      x += a.x;
      y += a.y;
      z += a.z;
      return *this;
    }

    Vec3 &operator -= ( const Vec3 &a )
    {
      x -= a.x;
      y -= a.y;
      z -= a.z;
      return *this;
    }

    Vec3 &operator *= ( scalar k )
    {
      x *= k;
      y *= k;
      z *= k;
      return *this;
    }

    Vec3 &operator /= ( scalar k )
    {
      k = 1.0 / k;
      x *= k;
      y *= k;
      z *= k;
      return *this;
    }

    Vec3 operator + ( const Vec3 &a ) const
    {
      return Vec3( x + a.x, y + a.y, z + a.z );
    }

    Vec3 operator - ( const Vec3 &a ) const
    {
      return Vec3( x - a.x, y - a.y, z - a.z );
    }

    Vec3 operator * ( scalar k ) const
    {
      return Vec3( x * k, y * k, z * k );
    }

    Vec3 operator / ( scalar k ) const
    {
      k = 1.0 / k;
      return Vec3( x * k, y * k, z * k );
    }

    // dot product
    scalar operator * ( const Vec3 &a ) const
    {
      return x*a.x + y*a.y + z*a.z;
    }

    // cross product
    Vec3 operator ^ ( const Vec3 &a ) const
    {
      return Vec3( y*a.z - z*a.y, z*a.x - x*a.z, x*a.y - y*a.x );
    }

    // vector which lies in plane defined by given vectors and is perpendicular to first one
    Vec3 operator % ( const Vec3 &a ) const
    {
      // this is actually -( u x v ) x u, where u is *this vector
      // This equals to:
      // ( u . u )v - ( u . v )u = |u|^2 * ( v - ( u . v )/( |u|^2 ) * u )
      // ( the length doesn't matter )

      // |u|^2, assume it's not 0
      scalar k = x*x + y*y + z*z;

      assert( k != 0.0 );

      k = ( x * a.x + y * a.y + z * a.z ) / k;
      return a - k * ( *this );
    }

    friend Vec3 operator * ( scalar k, const Vec3 &a )
    {
      return Vec3( a.x * k, a.y * k, a.z * k );
    }

    // mixed product
    friend scalar mix( const Vec3 &a, const Vec3 &b, const Vec3 &c )
    {
      // 3x3 determinant
      return
          a.x * ( b.y * c.z - b.z * c.y ) -
          a.y * ( b.x * c.z - b.z * c.x ) +
          a.z * ( b.x * c.y - b.y * c.x );
    }

  };

}

#endif // _Dark_Vec3_h_
