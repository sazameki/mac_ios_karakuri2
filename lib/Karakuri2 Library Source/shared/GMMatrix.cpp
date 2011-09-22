//
//  GMMatrix.cpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "Globals.h"

#include "GMMatrix.h"

#include "GMTypes.h"
#include "GMMathHelper.h"
#include "GMQuat.h"
#include "GMVector3D.h"
#include "GMException.h"

#include <cmath>
#include <iostream>
#include <TargetConditionals.h>


const GMMatrix& GMMatrix::Identity = GMMatrix(1.0, 0.0, 0.0, 0.0,
                                              0.0, 1.0, 0.0, 0.0,
                                              0.0, 0.0, 1.0, 0.0,
                                              0.0, 0.0, 0.0, 1.0);

GMMatrix GMMatrix::CreateBillboard(const GMVector3D& objectPos, const GMVector3D& cameraPos,
                                   const GMVector3D& cameraUpVec, const GMVector3D cameraForwardVec)
{
    GMVector3D translation = objectPos - cameraPos;
    GMVector3D backwards = translation.normal();
    GMVector3D up = cameraUpVec.normal();
    GMVector3D right = backwards.cross(up);
    up = backwards.cross(right);

    GMMatrix ret(GMMatrix::Identity);
    ret.setBackward(backwards);
    ret.setRight(right);
    ret.setUp(up);
    ret.setTranslation(translation);
    
    return ret;
}

GMMatrix GMMatrix::CreateConstrainedBillboard(const GMVector3D& objectPos, const GMVector3D& cameraPos, const GMVector3D& rotateAxis,
                                              const GMVector3D& cameraForwardVec, const GMVector3D& objectForwardVec)
{
    GMMatrix ret;

    // TODO: GMMatrix::CreateConstrainedBillboard() の実装
    
    return ret;
}

GMMatrix GMMatrix::CreateFromAxisAngle(const GMVector3D& axis, double rad)
{
    GMVector3D n(axis);
    n.normalize();

    double c = cos(rad);
    double ic = 1.0 - c;
    double s = sin(rad);

    return GMMatrix(n.x*n.x*ic+c,     n.x*n.y*ic+n.z*s, n.x*n.z*ic-n.y*s, 0.0,
                    n.x*n.y*ic-n.z*s, n.y*n.y*ic+c    , n.y*n.z*ic+n.x*s, 0.0,
                    n.x*n.z*ic+n.y*s, n.y*n.z*ic-n.x*s, n.z*n.z*ic+c,     0.0,
                    0.0,              0.0,              0.0,              1.0);
}

GMMatrix GMMatrix::CreateFromYawPitchRoll(double yaw, double pitch, double roll)
{
    double cx = cos(pitch);
    double cy = cos(yaw);
    double cz = cos(roll);
    double sx = sin(pitch);
    double sy = sin(yaw);
    double sz = sin(roll);
    
    return GMMatrix(sx*sy*sz+cy*cz, cx*sz, sx*cy*sz-sy*cz, 0.0,
                    sx*sy*cz-cy*sz, cx*cz, sx*cy*cz+sy*sz, 0.0,
                    cx*sy         , -sx  , cx*cy         , 0.0,
                    0.0           , 0.0  , 0.0           , 1.0);
}

// cf. http://msdn.microsoft.com/en-us/library/bb205343(v=VS.85).aspx
GMMatrix GMMatrix::CreateLookAt(const GMVector3D& eye, const GMVector3D& center, const GMVector3D& up)
{
    GMVector3D f = (eye - center).normal();
    GMVector3D s = up.cross(f).normal();
    GMVector3D u = f.cross(s);
    
    return GMMatrix(s.x, u.x, f.x, 0.0,
                    s.y, u.y, f.y, 0.0,
                    s.z, u.z, f.z, 0.0,
                    -s.dot(eye), -u.dot(eye), -f.dot(eye), 1.0);
}

// cf. http://msdn.microsoft.com/en-us/library/bb205349(v=VS.85).aspx
GMMatrix GMMatrix::CreateOrthographic(double width, double height, double zNear, double zFar)
{
    return GMMatrix(2 / width, 0.0       , 0.0                   , 0.0,
                    0.0      , 2 / height, 0.0                   , 0.0,
                    0.0      , 0.0       , 1 / (zNear - zFar)    , 0.0,
                    0.0      , 0.0       , zNear / (zNear - zFar), 1.0);
}

// cf. http://msdn.microsoft.com/en-us/library/bb205348(v=VS.85).aspx
GMMatrix GMMatrix::CreateOrthographicOffCenter(double left, double right, double bottom, double top, double zNear, double zFar)
{
    return GMMatrix(2 / (right - left), 0.0               , 0.0               , 0.0,
                    0.0               , 2 / (top - bottom), 0.0               , 0.0,
                    0.0               , 0.0               , 1 / (zNear - zFar), 0.0,
                    (left + right) / (left - right), (top + bottom) / (bottom - top) , zNear / (zNear - zFar) , 1.0);
}

// cf. http://msdn.microsoft.com/en-us/library/bb205355(v=vs.85).aspx
GMMatrix GMMatrix::CreatePerspective(double width, double height, double zNear, double zFar)
{
    return GMMatrix(2 * (zNear / width), 0.0                 , 0.0                  , 0.0,
                    0.0                , 2 * (zNear / height), 0.0                  , 0.0,
                    0.0                , 0.0                 , zFar / (zNear - zFar), -1.0,
                    0.0                , 0.0                 , zNear * zFar / (zNear - zFar) , 0.0);
}

// cf. http://msdn.microsoft.com/en-us/library/bb205351(v=vs.85).aspx
// cf. http://msdn.microsoft.com/en-us/library/bb147302(v=vs.85).aspx
GMMatrix GMMatrix::CreatePerspectiveFieldOfView(double fieldOfView, double aspect, double nearDist, double farDist)
{
    double yScale = 1.0 / tan(fieldOfView / 2);
    double xScale = yScale / aspect;
    
    return GMMatrix(xScale, 0.0   , 0.0 , 0.0,
                    0.0   , yScale, 0.0 , 0.0,
                    0.0   , 0.0   , farDist / (nearDist - farDist) , -1.0,
                    0.0   , 0.0   , nearDist * farDist / (nearDist - farDist), 0.0);
}

// cf. http://msdn.microsoft.com/en-us/library/bb205354(v=vs.85).aspx
GMMatrix GMMatrix::CreatePerspectiveOffCenter(double left, double right, double bottom, double top, double nearDist, double farDist)
{
    double x = (2.0 * nearDist) / (right - left);
    double y = (2.0 * nearDist) / (top - bottom);
    double a = (left + right) / (right - left);
    double b = (top + bottom) / (top - bottom);
    double zDist = nearDist - farDist;
    double c = farDist / zDist;
    double d = nearDist * farDist / zDist;
    
    return GMMatrix(x  , 0.0,  0.0,  0.0,
                    0.0, y  ,  0.0,  0.0,
                    a  , b  ,  c  , -1.0,
                    0.0, 0.0,  d  ,  0.0);
}

GMMatrix GMMatrix::CreateReflection(const GMPlane& plane)
{
    GMPlane p = plane.normal();

    return GMMatrix(-2 * p.normalVec.x * p.normalVec.x + 1,
                    -2 * p.normalVec.x * p.normalVec.y,
                    -2 * p.normalVec.x * p.normalVec.z,
                    0.0,
                    -2 * p.normalVec.y * p.normalVec.x,
                    -2 * p.normalVec.y * p.normalVec.y + 1,
                    -2 * p.normalVec.y * p.normalVec.z,
                    0.0,
                    -2 * p.normalVec.z * p.normalVec.x,
                    -2 * p.normalVec.z * p.normalVec.y,
                    -2 * p.normalVec.z * p.normalVec.z + 1,
                    0.0,
                    -2 * p.distance * p.normalVec.x,
                    -2 * p.distance * p.normalVec.y,
                    -2 * p.distance * p.normalVec.z,
                    1.0);
}

GMMatrix GMMatrix::CreateRotationX(double rad)
{
    double c = cos(rad);
    double s = sin(rad);
    
    return GMMatrix(1.0, 0.0, 0.0, 0.0,
                    0.0,   c,   s, 0.0,
                    0.0,  -s,   c, 0.0,
                    0.0, 0.0, 0.0, 1.0);
}

GMMatrix GMMatrix::CreateRotationY(double rad)
{
    double c = cos(rad);
    double s = sin(rad);
    
    return GMMatrix(  c, 0.0,  -s, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                      s, 0.0,   c, 0.0,
                    0.0, 0.0, 0.0, 1.0);
}

GMMatrix GMMatrix::CreateRotationZ(double rad)
{
    double c = cos(rad);
    double s = sin(rad);
    
    return GMMatrix(  c,   s, 0.0, 0.0,
                     -s,   c, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0);
}

GMMatrix GMMatrix::CreateScale(double scale)
{
    return GMMatrix(scale,   0.0,   0.0,   0.0,
                      0.0, scale,   0.0,   0.0,
                      0.0,   0.0, scale,   0.0,
                      0.0,   0.0,   0.0,   1.0);
}

GMMatrix GMMatrix::CreateScale(double x, double y, double z)
{
    return GMMatrix(  x, 0.0, 0.0, 0.0,
                    0.0,   y, 0.0, 0.0,
                    0.0, 0.0,   z, 0.0,
                    0.0, 0.0, 0.0, 1.0);
}

GMMatrix GMMatrix::CreateScale(const GMVector3D& vec)
{
    return GMMatrix(vec.x,   0.0,   0.0,   0.0,
                      0.0, vec.y,   0.0,   0.0,
                      0.0,   0.0, vec.z,   0.0,
                      0.0,   0.0,   0.0,   1.0);
}

// http://msdn.microsoft.com/en-us/library/bb205364(v=VS.85).aspx
GMMatrix GMMatrix::CreateShadow(const GMVector3D& lightDir, const GMPlane& plane)
{
    GMPlane p = plane.normal();
    double d = p.normalVec.dot(lightDir);

    return GMMatrix(-1 * p.normalVec.x * lightDir.x + d,
                    -1 * p.normalVec.x * lightDir.y,
                    -1 * p.normalVec.x * lightDir.z,
                    0.0,
                    -1 * p.normalVec.y * lightDir.x,
                    -1 * p.normalVec.y * lightDir.y + d,
                    -1 * p.normalVec.y * lightDir.z,
                    0.0,
                    -1 * p.normalVec.z * lightDir.x,
                    -1 * p.normalVec.z * lightDir.y,
                    -1 * p.normalVec.z * lightDir.z + d,
                    0.0,
                    -1 * p.distance * lightDir.x,
                    -1 * p.distance * lightDir.y,
                    -1 * p.distance * lightDir.z,
                    d);                    
}

GMMatrix GMMatrix::CreateTranslation(double x, double y, double z)
{
    return GMMatrix(1.0, 0.0, 0.0, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                      x,   y,   z, 1.0);
}

GMMatrix GMMatrix::CreateTranslation(const GMVector3D& vec)
{
    return GMMatrix(  1.0,   0.0,   0.0,   0.0,
                      0.0,   1.0,   0.0,   0.0,
                      0.0,   0.0,   1.0,   0.0,
                    vec.x, vec.y, vec.z,   1.0);
}

GMMatrix GMMatrix::CreateWorld(const GMVector3D& pos, const GMVector3D& forward, const GMVector3D& up)
{
    GMVector3D z = forward.normal();
    GMVector3D x = forward.cross(up);
    GMVector3D y = x.cross(forward);
    x.normalize();
    y.normalize();
    
    return GMMatrix(  x.x,   x.y,   x.z, 0.0,
                      y.x,   y.y,   y.z, 0.0,
                     -z.x,  -z.y,  -z.z, 0.0,
                    pos.x, pos.y, pos.z, 1.0);
}

GMMatrix GMMatrix::EaseIn(const GMMatrix& mat1, const GMMatrix& mat2, double t)
{
    return mat1 + (mat2 - mat1) * (t * t);
}

GMMatrix GMMatrix::EaseInOut(const GMMatrix& mat1, const GMMatrix& mat2, double t)
{
    GMMatrix middle = (mat1 + mat2) / 2;
    
    t *= 2;
    if (t <= 1.0) {
        return mat1 + (middle - mat1) * (t * t);
    }
    t -= 1;
    return middle + (mat2 - middle) * (t * t);
}

GMMatrix GMMatrix::EaseOut(const GMMatrix& mat1, const GMMatrix& mat2, double t)
{
    return (mat1 - (mat2 - mat1) * (t * (t - 2)));
}

GMMatrix GMMatrix::Lerp(const GMMatrix& mat1, const GMMatrix& mat2, double t)
{
    return mat1 + (mat2 - mat1) * t;
}

GMMatrix::GMMatrix()
{
    m11 = 0.0;
    m12 = 0.0;
    m13 = 0.0;
    m14 = 0.0;

    m21 = 0.0;
    m22 = 0.0;
    m23 = 0.0;
    m24 = 0.0;

    m31 = 0.0;
    m32 = 0.0;
    m33 = 0.0;
    m34 = 0.0;

    m41 = 0.0;
    m42 = 0.0;
    m43 = 0.0;
    m44 = 0.0;
}

GMMatrix::GMMatrix(double m11, double m12, double m13, double m14,
                   double m21, double m22, double m23, double m24,
                   double m31, double m32, double m33, double m34,
                   double m41, double m42, double m43, double m44)
{
    this->m11 = m11;
    this->m12 = m12;
    this->m13 = m13;
    this->m14 = m14;
    
    this->m21 = m21;
    this->m22 = m22;
    this->m23 = m23;
    this->m24 = m24;
    
    this->m31 = m31;
    this->m32 = m32;
    this->m33 = m33;
    this->m34 = m34;
    
    this->m41 = m41;
    this->m42 = m42;
    this->m43 = m43;
    this->m44 = m44;
}

GMMatrix::GMMatrix(const GMQuat& quat)
{
    double x2 = quat.x + quat.x;
    double y2 = quat.y + quat.y;
    double z2 = quat.z + quat.z;

    double xx = quat.x * x2;
    double xy = quat.x * y2;
    double xz = quat.x * z2;
    
    double yy = quat.y * y2;
    double yz = quat.y * z2;

    double zz = quat.z * z2;
    
    double wx = quat.w * x2;
    double wy = quat.w * y2;
    double wz = quat.w * z2;
    
    m11 = 1.0 - (yy + zz);
    m12 = xy + wz;
    m13 = xz - wy;
    m14 = 0.0;
    m21 = xy - wz;
    m22 = 1.0 - (xx + zz);
    m23 = yz + wx;
    m24 = 0.0;
    m31 = xz + wy;
    m32 = yz - wx;
    m33 = 1.0 - (xx + yy);
    m34 = 0.0;
    m41 = 0.0;
    m42 = 0.0;
    m43 = 0.0;
    m44 = 1.0;
}

GMMatrix& GMMatrix::operator=(const GMMatrix& matrix)
{
    m11 = matrix.m11;
    m12 = matrix.m12;
    m13 = matrix.m13;
    m14 = matrix.m14;

    m21 = matrix.m21;
    m22 = matrix.m22;
    m23 = matrix.m23;
    m24 = matrix.m24;

    m31 = matrix.m31;
    m32 = matrix.m32;
    m33 = matrix.m33;
    m34 = matrix.m34;

    m41 = matrix.m41;
    m42 = matrix.m42;
    m43 = matrix.m43;
    m44 = matrix.m44;

    return *this;
}

GMMatrix GMMatrix::operator-() const
{
    return (*this) * -1;
}

GMMatrix GMMatrix::operator+(const GMMatrix& matrix) const
{
    GMMatrix ret(*this);

    ret.m11 += matrix.m11;
    ret.m12 += matrix.m12;
    ret.m13 += matrix.m13;
    ret.m14 += matrix.m14;
    
    ret.m21 += matrix.m21;
    ret.m22 += matrix.m22;
    ret.m23 += matrix.m23;
    ret.m24 += matrix.m24;
    
    ret.m31 += matrix.m31;
    ret.m32 += matrix.m32;
    ret.m33 += matrix.m33;
    ret.m34 += matrix.m34;
    
    ret.m41 += matrix.m41;
    ret.m42 += matrix.m42;
    ret.m43 += matrix.m43;
    ret.m44 += matrix.m44;
    
    return ret;
}

GMMatrix GMMatrix::operator-(const GMMatrix& matrix) const
{
    GMMatrix ret(*this);

    ret.m11 -= matrix.m11;
    ret.m12 -= matrix.m12;
    ret.m13 -= matrix.m13;
    ret.m14 -= matrix.m14;
    
    ret.m21 -= matrix.m21;
    ret.m22 -= matrix.m22;
    ret.m23 -= matrix.m23;
    ret.m24 -= matrix.m24;
    
    ret.m31 -= matrix.m31;
    ret.m32 -= matrix.m32;
    ret.m33 -= matrix.m33;
    ret.m34 -= matrix.m34;
    
    ret.m41 -= matrix.m41;
    ret.m42 -= matrix.m42;
    ret.m43 -= matrix.m43;
    ret.m44 -= matrix.m44;
    
    return ret;
}

GMMatrix GMMatrix::operator*(const GMMatrix& matrix) const
{
    GMMatrix& a = const_cast<GMMatrix&>(matrix);
    GMMatrix& b = const_cast<GMMatrix&>(*this);
    
    GMMatrix ret;

    ret.m11 = a.m11 * b.m11 + a.m21 * b.m12 + a.m31 * b.m13 + a.m41 * b.m14;
    ret.m12 = a.m12 * b.m11 + a.m22 * b.m12 + a.m32 * b.m13 + a.m42 * b.m14;
    ret.m13 = a.m13 * b.m11 + a.m23 * b.m12 + a.m33 * b.m13 + a.m43 * b.m14;
    ret.m14 = a.m14 * b.m11 + a.m24 * b.m12 + a.m34 * b.m13 + a.m44 * b.m14;
    
    ret.m21 = a.m11 * b.m21 + a.m21 * b.m22 + a.m31 * b.m23 + a.m41 * b.m24;
    ret.m22 = a.m12 * b.m21 + a.m22 * b.m22 + a.m32 * b.m23 + a.m42 * b.m24;
    ret.m23 = a.m13 * b.m21 + a.m23 * b.m22 + a.m33 * b.m23 + a.m43 * b.m24;
    ret.m24 = a.m14 * b.m21 + a.m24 * b.m22 + a.m34 * b.m23 + a.m44 * b.m24;
    
    ret.m31 = a.m11 * b.m31 + a.m21 * b.m32 + a.m31 * b.m33 + a.m41 * b.m34;
    ret.m32 = a.m12 * b.m31 + a.m22 * b.m32 + a.m32 * b.m33 + a.m42 * b.m34;
    ret.m33 = a.m13 * b.m31 + a.m23 * b.m32 + a.m33 * b.m33 + a.m43 * b.m34;
    ret.m34 = a.m14 * b.m31 + a.m24 * b.m32 + a.m34 * b.m33 + a.m44 * b.m34;
    
    ret.m41 = a.m11 * b.m41 + a.m21 * b.m42 + a.m31 * b.m43 + a.m41 * b.m44;
    ret.m42 = a.m12 * b.m41 + a.m22 * b.m42 + a.m32 * b.m43 + a.m42 * b.m44;
    ret.m43 = a.m13 * b.m41 + a.m23 * b.m42 + a.m33 * b.m43 + a.m43 * b.m44;
    ret.m44 = a.m14 * b.m41 + a.m24 * b.m42 + a.m34 * b.m43 + a.m44 * b.m44;
    
    return ret;
}

GMMatrix GMMatrix::operator/(const GMMatrix& matrix) const
{
    GMMatrix ret(*this);

    ret.m11 /= matrix.m11;
    ret.m12 /= matrix.m12;
    ret.m13 /= matrix.m13;
    ret.m14 /= matrix.m14;
    
    ret.m21 /= matrix.m21;
    ret.m22 /= matrix.m22;
    ret.m23 /= matrix.m23;
    ret.m24 /= matrix.m24;
    
    ret.m31 /= matrix.m31;
    ret.m32 /= matrix.m32;
    ret.m33 /= matrix.m33;
    ret.m34 /= matrix.m34;
    
    ret.m41 /= matrix.m41;
    ret.m42 /= matrix.m42;
    ret.m43 /= matrix.m43;
    ret.m44 /= matrix.m44;
    
    return ret;    
}

GMMatrix GMMatrix::operator*(double value) const
{
    GMMatrix ret(*this);

    ret.m11 *= value;
    ret.m12 *= value;
    ret.m13 *= value;
    ret.m14 *= value;
    
    ret.m21 *= value;
    ret.m22 *= value;
    ret.m23 *= value;
    ret.m24 *= value;
    
    ret.m31 *= value;
    ret.m32 *= value;
    ret.m33 *= value;
    ret.m34 *= value;
    
    ret.m41 *= value;
    ret.m42 *= value;
    ret.m43 *= value;
    ret.m44 *= value;
    
    return ret;
}

GMMatrix GMMatrix::operator/(double value) const
{
    GMMatrix ret(*this);

    ret.m11 /= value;
    ret.m12 /= value;
    ret.m13 /= value;
    ret.m14 /= value;
    
    ret.m21 /= value;
    ret.m22 /= value;
    ret.m23 /= value;
    ret.m24 /= value;
    
    ret.m31 /= value;
    ret.m32 /= value;
    ret.m33 /= value;
    ret.m34 /= value;
    
    ret.m41 /= value;
    ret.m42 /= value;
    ret.m43 /= value;
    ret.m44 /= value;
    
    return ret;
}

GMMatrix operator*(double value, const GMMatrix& matrix)
{
    GMMatrix ret(matrix);

    ret.m11 *= value;
    ret.m12 *= value;
    ret.m13 *= value;
    ret.m14 *= value;
    
    ret.m21 *= value;
    ret.m22 *= value;
    ret.m23 *= value;
    ret.m24 *= value;
    
    ret.m31 *= value;
    ret.m32 *= value;
    ret.m33 *= value;
    ret.m34 *= value;
    
    ret.m41 *= value;
    ret.m42 *= value;
    ret.m43 *= value;
    ret.m44 *= value;
    
    return ret;
}

GMMatrix& GMMatrix::operator+=(const GMMatrix& matrix)
{
    m11 += matrix.m11;
    m12 += matrix.m12;
    m13 += matrix.m13;
    m14 += matrix.m14;
    
    m21 += matrix.m21;
    m22 += matrix.m22;
    m23 += matrix.m23;
    m24 += matrix.m24;
    
    m31 += matrix.m31;
    m32 += matrix.m32;
    m33 += matrix.m33;
    m34 += matrix.m34;
    
    m41 += matrix.m41;
    m42 += matrix.m42;
    m43 += matrix.m43;
    m44 += matrix.m44;

    return *this;
}

GMMatrix& GMMatrix::operator-=(const GMMatrix& matrix)
{
    m11 -= matrix.m11;
    m12 -= matrix.m12;
    m13 -= matrix.m13;
    m14 -= matrix.m14;
    
    m21 -= matrix.m21;
    m22 -= matrix.m22;
    m23 -= matrix.m23;
    m24 -= matrix.m24;
    
    m31 -= matrix.m31;
    m32 -= matrix.m32;
    m33 -= matrix.m33;
    m34 -= matrix.m34;
    
    m41 -= matrix.m41;
    m42 -= matrix.m42;
    m43 -= matrix.m43;
    m44 -= matrix.m44;

    return *this;
}

GMMatrix& GMMatrix::operator*=(const GMMatrix& matrix)
{
    *this = (*this) * matrix;
    return *this;
}

GMMatrix& GMMatrix::operator/=(const GMMatrix& matrix)
{
    m11 /= matrix.m11;
    m12 /= matrix.m12;
    m13 /= matrix.m13;
    m14 /= matrix.m14;

    m21 /= matrix.m21;
    m22 /= matrix.m22;
    m23 /= matrix.m23;
    m24 /= matrix.m24;

    m31 /= matrix.m31;
    m32 /= matrix.m32;
    m33 /= matrix.m33;
    m34 /= matrix.m34;
    
    m41 /= matrix.m41;
    m42 /= matrix.m42;
    m43 /= matrix.m43;
    m44 /= matrix.m44;

    return *this;
}

GMMatrix& GMMatrix::operator*=(double value)
{
    m11 *= value;
    m12 *= value;
    m13 *= value;
    m14 *= value;
    
    m21 *= value;
    m22 *= value;
    m23 *= value;
    m24 *= value;
    
    m31 *= value;
    m32 *= value;
    m33 *= value;
    m34 *= value;
    
    m41 *= value;
    m42 *= value;
    m43 *= value;
    m44 *= value;

    return *this;
}

GMMatrix& GMMatrix::operator/=(double value)
{
    m11 /= value;
    m12 /= value;
    m13 /= value;
    m14 /= value;
    
    m21 /= value;
    m22 /= value;
    m23 /= value;
    m24 /= value;
    
    m31 /= value;
    m32 /= value;
    m33 /= value;
    m34 /= value;
    
    m41 /= value;
    m42 /= value;
    m43 /= value;
    m44 /= value;

    return *this;
}

bool GMMatrix::operator==(const GMMatrix& matrix) const
{
    return equals(matrix, GMMathHelper::DoubleEqThreshold);
}

bool GMMatrix::operator!=(const GMMatrix& matrix) const
{
    return !equals(matrix, GMMathHelper::DoubleEqThreshold);
}

bool GMMatrix::equals(const GMMatrix& matrix, double accuracy) const
{
    if (fabs(m11 - matrix.m11) >= accuracy) return false;
    if (fabs(m12 - matrix.m12) >= accuracy) return false;
    if (fabs(m13 - matrix.m13) >= accuracy) return false;
    if (fabs(m14 - matrix.m14) >= accuracy) return false;

    if (fabs(m21 - matrix.m21) >= accuracy) return false;
    if (fabs(m22 - matrix.m22) >= accuracy) return false;
    if (fabs(m23 - matrix.m23) >= accuracy) return false;
    if (fabs(m24 - matrix.m24) >= accuracy) return false;

    if (fabs(m31 - matrix.m31) >= accuracy) return false;
    if (fabs(m32 - matrix.m32) >= accuracy) return false;
    if (fabs(m33 - matrix.m33) >= accuracy) return false;
    if (fabs(m34 - matrix.m34) >= accuracy) return false;

    if (fabs(m41 - matrix.m41) >= accuracy) return false;
    if (fabs(m42 - matrix.m42) >= accuracy) return false;
    if (fabs(m43 - matrix.m43) >= accuracy) return false;
    if (fabs(m44 - matrix.m44) >= accuracy) return false;
    
    return true;
}

bool GMMatrix::decompose(GMVector3D& scale, GMQuat& rotation, GMVector3D& translation) const
{
    translation.x = m41;
    translation.y = m42;
    translation.z = m43;
    
    scale.x = GMVector3D(m11, m12, m13).length();
    scale.y = GMVector3D(m21, m22, m23).length();
    scale.z = GMVector3D(m31, m32, m33).length();
    
    if (fabs(scale.x) < GMMathHelper::DoubleEqThreshold ||
        fabs(scale.y) < GMMathHelper::DoubleEqThreshold ||
        fabs(scale.z) < GMMathHelper::DoubleEqThreshold)
    {
        return false;
    }
    
    GMMatrix rm(m11/scale.x, m12/scale.x, m13/scale.x, 0.0,
                m21/scale.y, m22/scale.y, m23/scale.y, 0.0,
                m31/scale.z, m32/scale.z, m33/scale.z, 0.0,
                0.0        , 0.0        , 0.0        , 1.0);
    rotation = rm.toQuat();
    
    return true;
}

double GMMatrix::determinant() const
{
    double ret = 0.0;
    
    ret += m11 * m22 * m33 * m44 + m11 * m32 * m43 * m24 + m11 * m42 * m23 * m34;
    ret += m21 * m12 * m43 * m34 + m21 * m32 * m13 * m44 + m21 * m42 * m33 * m14;
    ret += m31 * m12 * m23 * m44 + m31 * m22 * m43 * m14 + m31 * m42 * m13 * m24;
    ret += m41 * m12 * m33 * m24 + m41 * m22 * m13 * m34 + m41 * m32 * m23 * m14;
    
    ret += -m11 * m22 * m43 * m34 - m11 * m32 * m23 * m44 - m11 * m42 * m33 * m24;
    ret += -m21 * m12 * m33 * m44 - m21 * m32 * m43 * m14 - m21 * m42 * m13 * m34;
    ret += -m31 * m12 * m43 * m24 - m31 * m22 * m13 * m44 - m31 * m42 * m23 * m14;
    ret += -m41 * m12 * m23 * m34 - m41 * m22 * m33 * m14 - m41 * m32 * m13 * m24;
    
    return ret;
}

GMMatrix GMMatrix::invert() const
{
    double det = determinant();
    if (det == 0.0) {
        throw GMArithmeticException();
    }
    
    GMMatrix ret;
    
    ret.m11 = (m22*m33*m44 + m23*m34*m42 + m24*m32*m43 - m22*m34*m43 - m23*m32*m44 - m24*m33*m42) / det;
    ret.m12 = (m12*m34*m43 + m13*m32*m44 + m14*m33*m42 - m12*m33*m44 - m13*m34*m42 - m14*m32*m43) / det;
    ret.m13 = (m12*m23*m44 + m13*m24*m42 + m14*m22*m43 - m12*m24*m43 - m13*m22*m44 - m14*m23*m42) / det;
    ret.m14 = (m12*m24*m33 + m13*m22*m34 + m14*m23*m32 - m12*m23*m34 - m13*m24*m32 - m14*m22*m33) / det;
    
    ret.m21 = (m21*m34*m43 + m23*m31*m44 + m24*m33*m41 - m21*m33*m44 - m23*m34*m41 - m24*m31*m43) / det;
    ret.m22 = (m11*m33*m44 + m13*m34*m41 + m14*m31*m43 - m11*m34*m43 - m13*m31*m44 - m14*m33*m41) / det;
    ret.m23 = (m11*m24*m43 + m13*m21*m44 + m14*m23*m41 - m11*m23*m44 - m13*m24*m41 - m14*m21*m43) / det;
    ret.m24 = (m11*m23*m34 + m13*m24*m31 + m14*m21*m33 - m11*m24*m33 - m13*m21*m34 - m14*m23*m31) / det;
    
    ret.m31 = (m21*m32*m44 + m22*m34*m41 + m24*m31*m42 - m21*m34*m42 - m22*m31*m44 - m24*m32*m41) / det;
    ret.m32 = (m11*m34*m42 + m12*m31*m44 + m14*m32*m41 - m11*m32*m44 - m12*m34*m41 - m14*m31*m42) / det;
    ret.m33 = (m11*m22*m44 + m12*m24*m41 + m14*m21*m42 - m11*m24*m42 - m12*m21*m44 - m14*m22*m41) / det;
    ret.m34 = (m11*m24*m32 + m12*m21*m34 + m14*m22*m31 - m11*m22*m34 - m12*m24*m31 - m14*m21*m32) / det;
    
    ret.m41 = (m21*m33*m42 + m22*m31*m43 + m23*m32*m41 - m21*m32*m43 - m22*m33*m41 - m23*m31*m42) / det;
    ret.m42 = (m11*m32*m43 + m12*m33*m41 + m13*m31*m42 - m11*m33*m42 - m12*m31*m43 - m13*m32*m41) / det;
    ret.m43 = (m11*m23*m42 + m12*m21*m43 + m13*m22*m41 - m11*m22*m43 - m12*m23*m41 - m13*m21*m42) / det;
    ret.m44 = (m11*m22*m33 + m12*m23*m31 + m13*m21*m32 - m11*m23*m32 - m12*m21*m33 - m13*m22*m31) / det;
    
    return ret;
}

GMQuat GMMatrix::toQuat() const
{
    return GMQuat(*this);
}

GMMatrix GMMatrix::transform(const GMQuat& quat) const
{
    return GMMatrix(quat) * (*this);
}

GMMatrix GMMatrix::transpose() const
{
    GMMatrix ret;
    
    ret.m11 = m11;
    ret.m12 = m21;
    ret.m13 = m31;
    ret.m14 = m41;
    
    ret.m21 = m12;
    ret.m22 = m22;
    ret.m23 = m32;
    ret.m24 = m42;
    
    ret.m31 = m13;
    ret.m32 = m23;
    ret.m33 = m33;
    ret.m34 = m43;
    
    ret.m41 = m14;
    ret.m42 = m24;
    ret.m43 = m34;
    ret.m44 = m44;
    
    return ret;
}

void GMMatrix::setBackward(const GMVector3D& vec)
{
    m31 = vec.x;
    m32 = vec.y;
    m33 = vec.z;
}

void GMMatrix::setDown(const GMVector3D& vec)
{
    m21 = -vec.x;
    m22 = -vec.y;
    m23 = -vec.z;
}

void GMMatrix::setForward(const GMVector3D& vec)
{
    m31 = -vec.x;
    m32 = -vec.y;
    m33 = -vec.z;
}

void GMMatrix::setLeft(const GMVector3D& vec)
{
    m11 = -vec.x;
    m12 = -vec.y;
    m13 = -vec.z;
}

void GMMatrix::setRight(const GMVector3D& vec)
{
    m11 = vec.x;
    m12 = vec.y;
    m13 = vec.z;
}

void GMMatrix::setTranslation(const GMVector3D& vec)
{
    m41 = vec.x;
    m42 = vec.y;
    m43 = vec.z;
}

void GMMatrix::setUp(const GMVector3D& vec)
{
    m21 = vec.x;
    m22 = vec.y;
    m23 = vec.z;
}


