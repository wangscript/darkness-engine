/*
 *  Mat33.h
 *
 *  Column-major 3x3 matrix
 *
 *  Copyright (C) 2002-2007, Davorin Učakar <davorin.ucakar@gmail.com>
 *
 *  $Id$
 */

#ifndef _Dark_Mat33_h_
#define _Dark_Mat33_h_

namespace Dark
{

  struct Mat33
  {
    // WARNING: first index is column, second is line
    scalar _00;
    scalar _01;
    scalar _02;
    scalar _10;
    scalar _11;
    scalar _12;
    scalar _20;
    scalar _21;
    scalar _22;

    Mat33()
    {}

    Mat33( scalar m00, scalar m01, scalar m02,
           scalar m10, scalar m11, scalar m12,
           scalar m20, scalar m21, scalar m22 ) :
        _00( m00 ), _01( m01 ), _02( m02 ),
        _10( m10 ), _11( m11 ), _12( m12 ),
        _20( m20 ), _21( m21 ), _22( m22 )
    {}

    explicit Mat33( const scalar *v )
    {
      *this = *(Mat33*) v;
    }

    // implemented in Mat44.h
    explicit Mat33( const Mat44 &m );

    Mat33( const Vec3 &a, const Vec3 &b, const Vec3 &c )
    {
      *(Vec3*) &_00 = a;
      *(Vec3*) &_10 = b;
      *(Vec3*) &_20 = c;
    }

    static Mat33 zero()
    {
      return Mat33( 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0 );
    }

    static Mat33 id()
    {
      return Mat33( 1.0, 0.0, 0.0,
                    0.0, 1.0, 0.0,
                    0.0, 0.0, 1.0 );
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
      return ( (scalar* ) this )[i];
    }

    const scalar &operator [] ( int i ) const
    {
      return ( (const scalar*) this )[i];
    }

    // i-th column
    Vec3 &col( int i )
    {
      return ( (Vec3*) this )[i];
    }

    // i-th column
    const Vec3 &col( int i ) const
    {
      return ( (Vec3*) this )[i];
    }

    bool operator == ( const Mat33 &a ) const
    {
      return
          _00 == a._00 &&
          _01 == a._01 &&
          _02 == a._02 &&
          _10 == a._10 &&
          _11 == a._11 &&
          _12 == a._12 &&
          _20 == a._20 &&
          _21 == a._21 &&
          _22 == a._22;
    }

    bool operator != ( const Mat33 &a ) const
    {
      return
          _00 != a._00 ||
          _01 != a._01 ||
          _02 != a._02 ||
          _10 != a._10 ||
          _11 != a._11 ||
          _12 != a._12 ||
          _20 != a._20 ||
          _21 != a._21 ||
          _22 != a._22;
    }

    Mat33 operator + () const
    {
      return *this;
    }

    Mat33 operator - () const
    {
      return Mat33( -_00, -_01, -_02,
                    -_10, -_11, -_12,
                    -_20, -_21, -_22 );
    }

    // determinant
    scalar det() const
    {
      return
          _00 * ( _11*_22 - _12*_21 ) -
          _10 * ( _01*_22 - _02*_21 ) +
          _20 * ( _01*_12 - _02*_11 );
    }

    // return transposed matrix
    Mat33 operator ~ ()
    {
      return Mat33( _00, _10, _20,
                    _01, _11, _21,
                    _02, _12, _22 );
    }

    // transpose
    Mat33 &trans()
    {
      swap( _01, _10 );
      swap( _02, _20 );
      swap( _12, _21 );
      return *this;
    }

    bool isZero() const
    {
      return
          0.f == _00 &&
          _00 == _01 &&
          _01 == _02 &&
          _02 == _10 &&
          _10 == _11 &&
          _11 == _12 &&
          _12 == _20 &&
          _20 == _21 &&
          _21 == _22;
    }

    Mat33 &setZero()
    {
      _22 = _21 = _20 = _12 = _11 = _10 = _02 = _01 = _00 = 0.0;
      return *this;
    }

    bool isId() const
    {
      return
          0.f == _01 && _01 == _02 && _02 == _10 &&
          _10 == _12 && _12 == _20 && _20 == _21 &&
          1.f == _00 && _00 == _11 && _11 == _22;
    }

    Mat33 &setId()
    {
      _21 = _20 = _12 = _10 = _02 = _01 = 0.0;
      _22 = _11 = _00 = 1.0;
      return *this;
    }

    // assignment operators
    Mat33 &operator += ( const Mat33 &a )
    {
      _00 += a._00;
      _01 += a._01;
      _02 += a._02;
      _10 += a._10;
      _11 += a._11;
      _12 += a._12;
      _20 += a._20;
      _21 += a._21;
      _22 += a._22;
      return *this;
    }

    Mat33 &operator -= ( const Mat33 &a )
    {
      _00 -= a._00;
      _01 -= a._01;
      _02 -= a._02;
      _10 -= a._10;
      _11 -= a._11;
      _12 -= a._12;
      _20 -= a._20;
      _21 -= a._21;
      _22 -= a._22;
      return *this;
    }

    Mat33 &operator *= ( scalar k )
    {
      _00 *= k;
      _01 *= k;
      _02 *= k;
      _10 *= k;
      _11 *= k;
      _12 *= k;
      _20 *= k;
      _21 *= k;
      _22 *= k;
      return *this;
    }

    Mat33 &operator /= ( scalar k )
    {
      k = 1.0 / k;
      _00 *= k;
      _01 *= k;
      _02 *= k;
      _10 *= k;
      _11 *= k;
      _12 *= k;
      _20 *= k;
      _21 *= k;
      _22 *= k;
      return *this;
    }

    // binary operators
    Mat33 operator + ( const Mat33 &a ) const
    {
      return Mat33( _00 + a._00, _01 + a._01, _02 + a._02,
                    _10 + a._10, _11 + a._11, _12 + a._12,
                    _20 + a._20, _21 + a._21, _22 + a._22 );
    }

    Mat33 operator - ( const Mat33 &a ) const
    {
      return Mat33( _00 - a._00, _01 - a._01, _02 - a._02,
                    _10 - a._10, _11 - a._11, _12 - a._12,
                    _20 - a._20, _21 - a._21, _22 - a._22 );
    }

    Mat33 operator * ( scalar k ) const
    {
      return Mat33( _00 * k, _01 * k, _02 * k,
                    _10 * k, _11 * k, _12 * k,
                    _20 * k, _21 * k, _22 * k );
    }

    Mat33 operator / ( scalar k ) const
    {
      k = 1.0 / k;
      return Mat33( _00 * k, _01 * k, _02 * k,
                    _10 * k, _11 * k, _12 * k,
                    _20 * k, _21 * k, _22 * k );
    }

    Mat33 operator * ( const Mat33 &a ) const
    {
      return Mat33( _00 * a._00 + _10 * a._01 + _20 * a._02,
                    _01 * a._00 + _11 * a._01 + _21 * a._02,
                    _02 * a._00 + _12 * a._01 + _22 * a._02,

                    _00 * a._10 + _10 * a._11 + _20 * a._12,
                    _01 * a._10 + _11 * a._11 + _21 * a._12,
                    _02 * a._10 + _12 * a._11 + _22 * a._12,

                    _00 * a._20 + _10 * a._21 + _20 * a._22,
                    _01 * a._20 + _11 * a._21 + _21 * a._22,
                    _02 * a._20 + _12 * a._21 + _22 * a._22 );
    }

    Vec3 operator * ( const Vec3 &v ) const
    {
      return Vec3( v.x * _00 + v.y * _10 + v.z * _20,
                   v.x * _01 + v.y * _11 + v.z * _21,
                   v.x * _02 + v.y * _12 + v.z * _22 );
    }

    Vec3 invMultiply( const Vec3 &v ) const
    {
      return Vec3( v.x * _00 + v.y * _01 + v.z * _02,
                   v.x * _10 + v.y * _11 + v.z * _12,
                   v.x * _20 + v.y * _21 + v.z * _22 );
    }

    friend Mat33 operator * ( scalar k, const Mat33 &a )
    {
      return Mat33( a._00 * k, a._01 * k, a._02 * k,
                    a._10 * k, a._11 * k, a._12 * k,
                    a._20 * k, a._21 * k, a._22 * k );
    }

    // make matrix for rotation around x-axis
    static Mat33 rotX( scalar theta )
    {
      scalar s, c;

      Math::sincos( theta, &s, &c );

      return Mat33( 1.0, 0.0, 0.0,
                    0.0,   c,   s,
                    0.0,  -s,   c );
    }

    // make matrix for rotation around y-axis
    static Mat33 rotY( scalar theta )
    {
      scalar s, c;

      Math::sincos( theta, &s, &c );

      return Mat33(   c, 0.0,  -s,
                    0.0, 1.0, 0.0,
                      s, 0.0,   c );
    }

    // make matrix for rotation around z-axis
    static Mat33 rotZ( scalar theta )
    {
      scalar s, c;

      Math::sincos( theta, &s, &c );

      return Mat33(   c,   s, 0.0,
                     -s,   c, 0.0,
                    0.0, 0.0, 1.0 );
    }

  };

  // declared in Quat.h
  inline Mat33 Quat::rotMat33() const
  {
    // this matrix is in column major format in implementation
    //
    // [ 1 - 2yy - 2zz    2xy - 2wz      2xz + 2wy   ]
    // [   2xy + 2wz    1 - 2xx - 2zz    2yz - 2wx   ]
    // [   2xz - 2wy      2yz + 2wx    1 - 2xx - 2yy ]
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

    return Mat33( 1.0 - yy - zz, xy + zw,  xz - yw,
                  xy - zw,       xx1 - zz, yz + xw,
                  xz + yw,       yz - xw,  xx1 - yy );
  }

  // declared in Quat.h
  inline Mat33 Quat::invRotMat33() const
  {
    // this matrix is in column major format in implementation
    //
    // [ 1 - 2yy - 2zz    2xy + 2wz      2xz - 2wy   ]
    // [   2xy - 2wz    1 - 2xx - 2zz    2yz + 2wx   ]
    // [   2xz + 2wy      2yz - 2wx    1 - 2xx - 2yy ]
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

    return Mat33( 1.0 - yy - zz, xy - zw,  xz + yw,
                  xy + zw,       xx1 - zz, yz - xw,
                  xz - yw,       yz + xw,  xx1 - yy );
  }

}

#endif // _Dark_Mat33_h_
