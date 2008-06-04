/*
 *  Quat.h
 *
 *  Quaternion library
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Quat.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Dark_Quat_h_
#define _Dark_Quat_h_

namespace Dark
{

  struct Mat33;
  struct Mat44;

  struct Quat
  {
    scalar x;
    scalar y;
    scalar z;
    scalar w;

    Quat()
    {}

    Quat( scalar x_, scalar y_, scalar z_, scalar w_ ) : x( x_ ), y( y_ ), z( z_ ), w( w_ )
    {}

    explicit Quat( scalar *q )
    {
      *this = *(Quat*) q;
    }

    explicit Quat( const Vec3 &v ) : x( v.x ), y( v.y ), z( v.z ), w( 0.0 )
    {
    }

    static Quat zero()
    {
      return Quat( 0.0, 0.0, 0.0, 0.0 );
    }

    static Quat id()
    {
      return Quat( 0.0, 0.0, 0.0, 1.0 );
    }

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
      return ( (const scalar*) this )[i];
    }

    bool operator == ( const Quat &a ) const
    {
      return x == a.x && y == a.y && z == a.y && w == a.w;
    }

    bool operator != ( const Quat &a ) const
    {
      return x != a.x || y != a.y || z != a.y || w != a.w;
    }

    Vec3 &vec3()
    {
      return *(Vec3*) this;
    }

    const Vec3 &vec3() const
    {
      return *(Vec3*) this;
    }

    Quat operator + () const
    {
      return *this;
    }

    Quat operator - () const
    {
      return Quat( -x, -y, -z, -w );
    }

    scalar operator ! () const
    {
      return Math::sqrt( x*x + y*y + z*z + w*w );
    }

    scalar sqL() const
    {
      return x*x + y*y + z*z + w*w;
    }

    Quat operator * () const
    {
      return Quat( -x, -y, -z, -w );
    }

    Quat &conj()
    {
      x = -x;
      y = -y;
      z = -z;
      return *this;
    }

    bool isZero() const
    {
      return 0.0 == x && x == y && y == z && z == w;
    }

    Quat &setZero()
    {
      w = z = y = x = 0.0;
      return *this;
    }

    bool isId() const
    {
      return 0.0 == x && x == y && y == z && w == 1.0;
    }

    Quat &setId()
    {
      z = y = x = 0.0;
      w = 1.0;
      return *this;
    }

    bool isUnit() const
    {
      return x*x + y*y + z*z + w*w == 1.0;
    }

    Quat operator ~ () const
    {
      assert( x*x + y*y + z*z + w*w > 0.0 );

      scalar r = 1.0 / Math::sqrt( x*x + y*y + z*z + w*w );
      return Quat( x * r, y * r, z * r, w * r );
    }

    Quat &norm()
    {
      assert( x*x + y*y + z*z + w*w > 0.0 );

      scalar r = 1.0 / Math::sqrt( x*x + y*y + z*z + w*w );
      x *= r;
      z *= r;
      z *= r;
      w *= r;
      return *this;
    }

    Quat &operator += ( const Quat &a )
    {
      x += a.x;
      y += a.y;
      z += a.z;
      w += a.w;
      return *this;
    }

    Quat &operator -= ( const Quat &a )
    {
      x -= a.x;
      y -= a.y;
      z -= a.z;
      w -= a.w;
      return *this;
    }

    Quat &operator *= ( scalar k )
    {
      x *= k;
      y *= k;
      z *= k;
      w *= k;
      return *this;
    }

    Quat &operator /= ( scalar k )
    {
      k = 1.0 / k;
      x *= k;
      y *= k;
      z *= k;
      w *= k;
      return *this;
    }

    // quaternion multiplication
    Quat &operator ^= ( const Quat &a )
    {
      scalar tx = x, ty = y, tz = z;

      x = w*a.x + tx*a.w + ty*a.z - tz*a.y;
      y = w*a.y + ty*a.w + tz*a.x - tx*a.z;
      z = w*a.z + tz*a.w + tx*a.y - ty*a.x;
      w = w*a.w - tx*a.x - ty*a.y - tz*a.z;

      return *this;
    }

    Quat operator + ( const Quat &a ) const
    {
      return Quat( x + a.x, y + a.y, z + a.z, w + a.w );
    }

    Quat operator - ( const Quat &a ) const
    {
      return Quat( x - a.x, y - a.y, z - a.z, w - a.w );
    }

    Quat operator * ( scalar k ) const
    {
      return Quat( x * k, y * k, z * k, w * k );
    }

    Quat operator / ( scalar k ) const
    {
      k = 1.0 / k;
      return Quat( x * k, y * k, z * k, w * k );
    }

    // dot product
    scalar operator * ( const Quat &a )
    {
      return x*a.x + y*a.y + z*a.z + w*a.w;
    }

    // product of quaternions
    Quat operator ^ ( const Quat &a ) const
    {

      return Quat( w*a.x + x*a.w + y*a.z - z*a.y,
                   w*a.y + y*a.w + z*a.x - x*a.z,
                   w*a.z + z*a.w + x*a.y - y*a.x,
                   w*a.w - x*a.x - y*a.y - z*a.z );
    }

    friend Quat operator * ( scalar k, const Quat &a )
    {
      return Quat( a.x * k, a.y * k, a.z * k, a.w * k );
    }

    // make rotation matrix (implemented in Mat33.h)
    Mat33 rotMat33() const;

    // make transposed (inverse) rotation matrix (implemented in Mat33.h)
    Mat33 invRotMat33() const;

    // make rotation matrix (implemented in Mat44.h)
    Mat44 rotMat44() const;

    // make transposed (inverse) rotation matrix (implemented in Mat44.h)
    Mat44 invRotMat44() const;

    // make quaternion for rotation around given axis
    static Quat rotAxis( const Vec3 &axis, scalar theta )
    {
      scalar s, c;
      Math::sincos( theta * 0.5, &s, &c );
      Vec3 qv = s * axis;
      return Quat( qv.x, qv.y, qv.z, c );
    }

    // make quaternion for rotation around x axis
    static Quat rotX( scalar theta )
    {
      scalar s, c;
      Math::sincos( theta * 0.5, &s, &c );
      return Quat( s, 0, 0, c );
    }

    // make quaternion for rotation around y axis
    static Quat rotY( scalar theta )
    {
      scalar s, c;
      Math::sincos( theta * 0.5, &s, &c );
      return Quat( 0, s, 0, c );
    }

    // make quaternion for rotation around z axis
    static Quat rotZ( scalar theta )
    {
      scalar s, c;
      Math::sincos( theta * 0.5, &s, &c );
      return Quat( 0, 0, s, c );
    }

    // rotZ ^ rotX ^ rotY
    static Quat rotZXY( scalar x, scalar y, scalar z )
    {
      scalar sx, cx, sy, cy, sz, cz;

      Math::sincos( x * 0.5, &sx, &cx );
      Math::sincos( y * 0.5, &sy, &cy );
      Math::sincos( z * 0.5, &sz, &cz );

      scalar cxcy = cx * cy;
      scalar cxsy = cx * sy;
      scalar sxcy = sx * cy;
      scalar sxsy = sx * sy;

      return Quat( sxcy * cz - cxsy * sz,
                   cxsy * cz + sxcy * sz,
                   cxcy * sz + sxsy * cz,
                   cxcy * cz - sxsy * sz );
    }

    Vec3 rotate( const Vec3 &v ) const
    {
      scalar a11 = x*x;
      scalar a22 = y*y;
      scalar a33 = z*z;
      scalar a44 = w*w;

      scalar a12 =  2.0 * x*y;
      scalar a13 =  2.0 * x*z;
      scalar a14 =  2.0 * x*w;
      scalar a23 =  2.0 * y*z;
      scalar a24 =  2.0 * y*w;
      scalar a34 =  2.0 * z*w;

      scalar a4433 = a44 - a33;

      return Vec3( ( a4433 - a22 + a11 ) * v.x + ( a12 - a34 ) * v.y + ( a24 + a13 ) * v.z,
                   ( a34 + a12 ) * v.x + ( a4433 + a22 - a11 ) * v.y + ( a23 - a14 ) * v.z,
                   ( a13 - a24 ) * v.x + ( a14 + a23 ) * v.y + ( a44 + a33 - a22 - a11 ) * v.z );
    }

    Vec3 rotateInv( const Vec3 &v ) const
    {
      scalar a11 = x*x;
      scalar a22 = y*y;
      scalar a33 = z*z;
      scalar a44 = w*w;

      scalar a12 =  2.0 * x*y;
      scalar a13 =  2.0 * x*z;
      scalar a14 = -2.0 * x*w;
      scalar a23 =  2.0 * y*z;
      scalar a24 = -2.0 * y*w;
      scalar a34 = -2.0 * z*w;

      scalar a4433 = a44 - a33;

      return Vec3( ( a4433 - a22 + a11 ) * v.x + ( a12 - a34 ) * v.y + ( a24 + a13 ) * v.z,
                   ( a34 + a12 ) * v.x + ( a4433 + a22 - a11 ) * v.y + ( a23 - a14 ) * v.z,
                   ( a13 - a24 ) * v.x + ( a14 + a23 ) * v.y + ( a44 + a33 - a22 - a11 ) * v.z );
    }
  };

  // declared in Vec3.h
  inline Vec3::Vec3( const Quat &q )
  {
    *this = *(Vec3*) &q;
  }

}

#endif // _Dark_Quat_h_
