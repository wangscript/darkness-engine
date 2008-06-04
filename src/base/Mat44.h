/*
 *  Mat44.h
 *
 *  Column-major 4x4 matrix
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id: Mat44.h 11 2007-08-31 12:03:10Z davorin $
 */

#ifndef _Dark_Mat44_h_
#define _Dark_Mat44_h_

namespace Dark
{

  struct Mat44
  {
    // WARNING: first index is column, second is line
    scalar _00;
    scalar _01;
    scalar _02;
    scalar _03;
    scalar _10;
    scalar _11;
    scalar _12;
    scalar _13;
    scalar _20;
    scalar _21;
    scalar _22;
    scalar _23;
    scalar _30;
    scalar _31;
    scalar _32;
    scalar _33;

    Mat44()
    {}

    Mat44( scalar m00, scalar m01, scalar m02, scalar m03,
           scalar m10, scalar m11, scalar m12, scalar m13,
           scalar m20, scalar m21, scalar m22, scalar m23,
           scalar m30, scalar m31, scalar m32, scalar m33 ) :
        _00( m00 ), _01( m01 ), _02( m02 ), _03( m03 ),
        _10( m10 ), _11( m11 ), _12( m12 ), _13( m13 ),
        _20( m20 ), _21( m21 ), _22( m22 ), _23( m23 ),
        _30( m30 ), _31( m31 ), _32( m32 ), _33( m33 )
    {}

    explicit Mat44( const scalar *v )
    {
      *this = *(Mat44*) v;
    }

    explicit Mat44( const Mat33 &m ) :
        _00( m._00 ), _01( m._01 ), _02( m._02 ), _03( 0.0 ),
        _10( m._10 ), _11( m._11 ), _12( m._12 ), _13( 0.0 ),
        _20( m._20 ), _21( m._21 ), _22( m._22 ), _23( 0.0 ),
        _30( 0.0 ), _31( 0.0 ), _32( 0.0 ), _33( 1.0 )
    {}


    Mat44( const Vec3 &a, const Vec3 &b, const Vec3 &c, const Vec3 &d )
    {
      *( Vec3* )&_00 = a;
      *( Vec3* )&_10 = b;
      *( Vec3* )&_20 = c;
      *( Vec3* )&_30 = d;
      _03 = 0.0;
      _13 = 0.0;
      _23 = 0.0;
      _33 = 1.0;
    }

    Mat44( const Quat &a, const Quat &b, const Quat &c, const Quat &d )
    {
      *(Quat*) &_00 = a;
      *(Quat*) &_10 = b;
      *(Quat*) &_20 = c;
      *(Quat*) &_30 = d;
    }

    static Mat44 zero()
    {
      return Mat44( 0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0 );
    }

    static Mat44 id()
    {
      return Mat44( 1.0, 0.0, 0.0, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0 );
    }

    operator scalar* () const
    {
      return (scalar*) this;
    }

    operator const scalar* () const
    {
      return (scalar*) this;
    }

    scalar &operator [] ( int i )
    {
      return ( (scalar*) this )[i];
    }

    const scalar &operator [] ( int i ) const
    {
      return ( (const scalar*) this )[i];
    }

    // get i-th column
    Vec3 &col( int i )
    {
      return *(Vec3*) ( (scalar*) this + i * 4 );
    }

    // get i-th column
    const Vec3 &col( int i ) const
    {
      return *(Vec3*) ( (scalar*) this + i * 4 );
    }

    bool operator == ( const Mat44 &a ) const
    {
      return
          _00 == a._00 &&
          _01 == a._01 &&
          _02 == a._02 &&
          _03 == a._03 &&
          _10 == a._10 &&
          _11 == a._11 &&
          _12 == a._12 &&
          _13 == a._13 &&
          _20 == a._20 &&
          _21 == a._21 &&
          _22 == a._22 &&
          _23 == a._23 &&
          _30 == a._30 &&
          _31 == a._31 &&
          _32 == a._32 &&
          _33 == a._33;
    }

    bool operator != ( const Mat44 &a ) const
    {
      return
          _00 != a._00 ||
          _01 != a._01 ||
          _02 != a._02 ||
          _03 != a._03 ||
          _10 != a._10 ||
          _11 != a._11 ||
          _12 != a._12 ||
          _13 != a._13 ||
          _20 != a._20 ||
          _21 != a._21 ||
          _22 != a._22 ||
          _23 != a._23 ||
          _30 != a._30 ||
          _31 != a._31 ||
          _32 != a._32 ||
          _33 != a._33;
    }

    Mat44 operator + () const
    {
      return *this;
    }

    Mat44 operator - () const
    {
      return Mat44( -_00, -_01, -_02, -_03,
                    -_10, -_11, -_12, -_13,
                    -_20, -_21, -_22, -_23,
                    -_30, -_31, -_32, -_33 );
    }

    scalar det() const
    {
      scalar klop = _22 * _33 - _32 * _23;
      scalar jlnp = _12 * _33 - _32 * _13;
      scalar jkno = _12 * _23 - _22 * _13;
      scalar ilmp = _02 * _33 - _32 * _03;
      scalar ikmo = _02 * _23 - _22 * _03;
      scalar ijmn = _02 * _13 - _12 * _03;
      return
          _00 * _11 * klop -
          _00 * _21 * jlnp +
          _00 * _31 * jkno -
          _10 * _01 * klop +
          _10 * _21 * ilmp -
          _10 * _31 * ikmo +
          _20 * _01 * jlnp -
          _20 * _11 * ilmp +
          _20 * _31 * ijmn -
          _30 * _01 * jkno +
          _30 * _11 * ikmo -
          _30 * _21 * ijmn;
    }

    Mat44 operator ~ () const
    {
      return Mat44( _00, _10, _20, _30,
                    _01, _11, _21, _31,
                    _02, _12, _22, _32,
                    _03, _13, _23, _33 );
    }

    Mat44 &trans()
    {
      swap( _01, _10 );
      swap( _02, _20 );
      swap( _03, _30 );
      swap( _12, _21 );
      swap( _13, _31 );
      swap( _23, _32 );
      return *this;
    }

    bool isZero() const
    {
      return
          0.f == _00 &&
          _00 == _01 &&
          _01 == _02 &&
          _02 == _03 &&
          _03 == _10 &&
          _10 == _11 &&
          _11 == _12 &&
          _12 == _13 &&
          _13 == _20 &&
          _20 == _21 &&
          _21 == _22 &&
          _22 == _23 &&
          _23 == _30 &&
          _30 == _31 &&
          _31 == _32 &&
          _32 == _33;
    }

    Mat44 &setZero()
    {
      _33 = _32 = _31 = _30 = _23 = _22 = _21 = _20 = _13 = _12 = _11 = _10 =
          _03 = _02 = _01 = _00 = 0.0;
      return *this;
    }

    bool isId() const
    {
      return
          0.f == _01 && _01 == _02 && _02 == _03 && _03 == _10 &&
          _10 == _12 && _12 == _13 && _13 == _20 && _20 == _21 &&
          _21 == _23 && _23 == _30 && _30 == _31 && _31 == _32 &&
          1.f == _00 && _00 == _11 && _11 == _22 && _22 == _33;
    }

    Mat44 &setId()
    {
      _32 = _31 = _30 = _23 = _21 = _20 = _13 = _12 = _10 = _03 = _02 = _01 = 0.0;
      _33 = _22 = _11 = _00 = 1.0;
      return *this;
    }

    Mat44 &operator += ( const Mat44 &a )
    {
      _00 += a._00;
      _01 += a._01;
      _02 += a._02;
      _03 += a._03;
      _10 += a._10;
      _11 += a._11;
      _12 += a._12;
      _13 += a._13;
      _20 += a._20;
      _21 += a._21;
      _22 += a._22;
      _23 += a._23;
      _30 += a._30;
      _31 += a._31;
      _32 += a._32;
      _33 += a._33;
      return *this;
    }

    Mat44 &operator -= ( const Mat44 &a )
    {
      _00 -= a._00;
      _01 -= a._01;
      _02 -= a._02;
      _03 -= a._03;
      _10 -= a._10;
      _11 -= a._11;
      _12 -= a._12;
      _13 -= a._13;
      _20 -= a._20;
      _21 -= a._21;
      _22 -= a._22;
      _23 -= a._23;
      _30 -= a._30;
      _31 -= a._31;
      _32 -= a._32;
      _33 -= a._33;
      return *this;
    }

    Mat44 &operator *= ( scalar k )
    {
      _00 *= k;
      _01 *= k;
      _02 *= k;
      _03 *= k;
      _10 *= k;
      _11 *= k;
      _12 *= k;
      _13 *= k;
      _20 *= k;
      _21 *= k;
      _22 *= k;
      _23 *= k;
      _30 *= k;
      _31 *= k;
      _32 *= k;
      _33 *= k;
      return *this;
    }

    Mat44 &operator /= ( scalar k )
    {
      k = 1.0 / k;
      _00 *= k;
      _01 *= k;
      _02 *= k;
      _03 *= k;
      _10 *= k;
      _11 *= k;
      _12 *= k;
      _13 *= k;
      _20 *= k;
      _21 *= k;
      _22 *= k;
      _23 *= k;
      _30 *= k;
      _31 *= k;
      _32 *= k;
      _33 *= k;
      return *this;
    }

    Mat44 operator + ( const Mat44 &a ) const
    {
      return Mat44( _00 + a._00, _01 + a._01, _02 + a._02, _03 + a._03,
                    _10 + a._10, _11 + a._11, _12 + a._12, _13 + a._13,
                    _20 + a._20, _21 + a._21, _22 + a._22, _23 + a._23,
                    _30 + a._30, _31 + a._31, _32 + a._32, _33 + a._33 );
    }

    Mat44 operator - ( const Mat44 &a ) const
    {
      return Mat44( _00 - a._00, _01 - a._01, _02 - a._02, _03 - a._03,
                    _10 - a._10, _11 - a._11, _12 - a._12, _13 - a._13,
                    _20 - a._20, _21 - a._21, _22 - a._22, _23 - a._23,
                    _30 - a._30, _31 - a._31, _32 - a._32, _33 - a._33 );
    }

    Mat44 operator * ( scalar k ) const
    {
      return Mat44( _00 * k, _01 * k, _02 * k, _03 * k,
                    _10 * k, _11 * k, _12 * k, _13 * k,
                    _20 * k, _21 * k, _22 * k, _23 * k,
                    _30 * k, _31 * k, _32 * k, _33 * k );
    }

    Mat44 operator / ( scalar k ) const
    {
      k = 1.0 / k;
      return Mat44( _00 * k, _01 * k, _02 * k, _03 * k,
                    _10 * k, _11 * k, _12 * k, _13 * k,
                    _20 * k, _21 * k, _22 * k, _23 * k,
                    _30 * k, _31 * k, _32 * k, _33 * k );
    }

    Mat44 operator * ( const Mat44 &a ) const
    {
      return Mat44( _00 * a._00 + _10 * a._01 + _20 * a._02 + _30 * a._03,
                    _01 * a._00 + _11 * a._01 + _21 * a._02 + _31 * a._03,
                    _02 * a._00 + _12 * a._01 + _22 * a._02 + _32 * a._03,
                    _03 * a._00 + _13 * a._01 + _23 * a._02 + _33 * a._03,

                    _00 * a._10 + _10 * a._11 + _20 * a._12 + _30 * a._13,
                    _01 * a._10 + _11 * a._11 + _21 * a._12 + _31 * a._13,
                    _02 * a._10 + _12 * a._11 + _22 * a._12 + _32 * a._13,
                    _03 * a._10 + _13 * a._11 + _23 * a._12 + _33 * a._13,

                    _00 * a._20 + _10 * a._21 + _20 * a._22 + _30 * a._23,
                    _01 * a._20 + _11 * a._21 + _21 * a._22 + _31 * a._23,
                    _02 * a._20 + _12 * a._21 + _22 * a._22 + _32 * a._23,
                    _03 * a._20 + _13 * a._21 + _23 * a._22 + _33 * a._23,

                    _00 * a._30 + _10 * a._31 + _20 * a._32 + _30 * a._33,
                    _01 * a._30 + _11 * a._31 + _21 * a._32 + _31 * a._33,
                    _02 * a._30 + _12 * a._31 + _22 * a._32 + _32 * a._33,
                    _03 * a._30 + _13 * a._31 + _23 * a._32 + _33 * a._33 );
    }

    Vec3 operator * ( const Vec3 &v ) const
    {
      return Vec3( v.x * _00 + v.y * _10 + v.z * _20 + _30,
                   v.x * _01 + v.y * _11 + v.z * _21 + _31,
                   v.x * _02 + v.y * _12 + v.z * _22 + _32 );
    }

    Vec3 invMultiply( const Vec3 &v ) const
    {
      return Vec3( v.x * _00 + v.y * _01 + v.z * _02 + _03,
                   v.x * _10 + v.y * _11 + v.z * _12 + _13,
                   v.x * _20 + v.y * _21 + v.z * _22 + _23 );
    }

    friend Mat44 operator * ( scalar k, const Mat44 &a )
    {
      return Mat44( a._00 * k, a._01 * k, a._02 * k, a._03 * k,
                    a._10 * k, a._11 * k, a._12 * k, a._13 * k,
                    a._20 * k, a._21 * k, a._22 * k, a._23 * k,
                    a._30 * k, a._31 * k, a._32 * k, a._33 * k );
    }

    // transformation matrices
    static Mat44 transl( scalar dx, scalar dy, scalar dz )
    {
      return Mat44( 1.0, 0.0, 0.0, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    dx,   dy,  dz, 1.0 );
    }

    static Mat44 transl( const Vec3 &v )
    {
      return Mat44( 1.0, 0.0, 0.0, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    v.x, v.y, v.z, 1.0 );
    }

    static Mat44 rotX( scalar theta )
    {
      scalar s, c;

      Math::sincos( theta, &s, &c );

      return Mat44( 1.0, 0.0, 0.0, 0.0,
                    0.0,   c,   s, 0.0,
                    0.0,  -s,   c, 0.0,
                    0.0, 0.0, 0.0, 1.0 );
    }

    static Mat44 rotY( scalar theta )
    {
      scalar s, c;

      Math::sincos( theta, &s, &c );

      return Mat44(   c, 0.0,  -s, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                      s, 0.0,   c, 0.0,
                    0.0, 0.0, 0.0, 1.0 );
    }

    static Mat44 rotZ( scalar theta )
    {
      scalar s, c;

      Math::sincos( theta, &s, &c );

      return Mat44( c,     s, 0.0, 0.0,
                    -s,    c, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0 );
    }

  };

  // declared in Quat.h
  inline Mat44 Quat::rotMat44() const
  {
    // this matrix is in column major format in implementation
    //
    // [ 1 - 2yy - 2zz    2xy - 2wz      2xz + 2wy    0 ]
    // [   2xy + 2wz    1 - 2xx - 2zz    2yz - 2wx    0 ]
    // [   2xz - 2wy      2yz + 2wx    1 - 2xx - 2yy  0 ]
    // [       0              0              0        1 ]
    //

    scalar x2 = x + x;
    scalar y2 = y + y;
    scalar z2 = z + z;
    scalar xx1 = 1.0 - x2 * x;
    scalar yy = y2 * y;
    scalar zz = z2 * z;
    scalar xy = x2 * y;
    scalar xz = x2 * z;
    scalar xw = x2 * w;
    scalar yz = y2 * z;
    scalar yw = y2 * w;
    scalar zw = z2 * w;

    return Mat44( 1.0 - yy - zz, xy + zw,  xz - yw,  0.0,
                  xy - zw,       xx1 - zz, yz + xw,  0.0,
                  xz + yw,       yz - xw,  xx1 - yy, 0.0,
                  0.0,           0.0,      0.0,      1.0 );
  }

  // declared in Quat.h
  inline Mat44 Quat::invRotMat44() const
  {
    // this matrix is in column major format in implementation
    //
    // [ 1 - 2yy - 2zz    2xy + 2wz      2xz - 2wy    0 ]
    // [   2xy - 2wz    1 - 2xx - 2zz    2yz + 2wx    0 ]
    // [   2xz + 2wy      2yz - 2wx    1 - 2xx - 2yy  0 ]
    // [       0              0              0        1 ]
    //

    scalar x2 = x + x;
    scalar y2 = y + y;
    scalar z2 = z + z;
    scalar xx1 = 1.0 - x2 * x;
    scalar yy = y2 * y;
    scalar zz = z2 * z;
    scalar xy = x2 * y;
    scalar xz = x2 * z;
    scalar xw = x2 * w;
    scalar yz = y2 * z;
    scalar yw = y2 * w;
    scalar zw = z2 * w;

    return Mat44( 1.0 - yy - zz, xy - zw,  xz + yw,  0.0,
                  xy + zw,       xx1 - zz, yz - xw,  0.0,
                  xz - yw,       yz + xw,  xx1 - yy, 0.0,
                  0.0,           0.0,      0.0,      1.0 );
  }

  // declared in Quat.h
  inline Mat33::Mat33( const Mat44 &m ) :
      _00( m._00 ), _01( m._01 ), _02( m._02 ),
      _10( m._10 ), _11( m._11 ), _12( m._12 ),
      _20( m._20 ), _21( m._21 ), _22( m._22 )
  {}

}

#endif // _Dark_Mat44_h_
