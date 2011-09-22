//
//  GMVector4D.cpp
//  Game Framework
//
//  Created by numata on Jan 10, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMVector4D.h"

#include "GMMathHelper.h"
#include "GMMatrix.h"
#include "GMQuat.h"
#include "GMVector2D.h"
#include "GMVector3D.h"

#include <cmath>


const GMVector4D& GMVector4D::One   = GMVector4D(1.0, 1.0, 1.0, 1.0);
const GMVector4D& GMVector4D::UnitX = GMVector4D(1.0, 0.0, 0.0, 0.0);
const GMVector4D& GMVector4D::UnitY = GMVector4D(0.0, 1.0, 0.0, 0.0);
const GMVector4D& GMVector4D::UnitZ = GMVector4D(0.0, 0.0, 1.0, 0.0);
const GMVector4D& GMVector4D::UnitW = GMVector4D(0.0, 0.0, 0.0, 1.0);
const GMVector4D& GMVector4D::Zero  = GMVector4D(0.0, 0.0, 0.0, 0.0);


GMVector4D GMVector4D::Barycentric(const GMVector4D& v1, const GMVector4D& v2, const GMVector4D& v3, double t1, double t2)
{
    return ((1.0 - t1 - t2) * v1) + (t1 * v2) + (t2 * v3);
}

GMVector4D GMVector4D::CatmullRom(const GMVector4D& v1, const GMVector4D& v2, const GMVector4D& v3, const GMVector4D& v4, double t)
{
    double t2 = t * t;
    double t3 = t2 * t;
    
    GMVector4D temp1 = (v3 - v1) / 2;
    GMVector4D temp2 = (v4 - v2) / 2;
    
    return (2 * v2 - 2 * v3 + temp1 + temp2) * t3 + (-3 * v2 + 3 * v3 - 2 * temp1 - temp2) * t2 + temp1 * t + v2;
}

GMVector4D GMVector4D::EaseIn(const GMVector4D& vec1, const GMVector4D& vec2, double t)
{
    return vec1 + (vec2 - vec1) * (t * t);
}

GMVector4D GMVector4D::EaseInOut(const GMVector4D& vec1, const GMVector4D& vec2, double t)
{
    GMVector4D middle = (vec1 + vec2) / 2;
    
    t *= 2;
    if (t <= 1.0) {
        return vec1 + (middle - vec1) * (t * t);
    }
    t -= 1;
    return middle + (vec2 - middle) * (t * t);
}

GMVector4D GMVector4D::EaseOut(const GMVector4D& vec1, const GMVector4D& vec2, double t)
{
    return (vec1 - (vec2 - vec1) * (t * (t - 2)));
}

GMVector4D GMVector4D::Hermite(const GMVector4D& vec1, const GMVector4D& tan1, const GMVector4D& vec2, const GMVector4D& tan2, double t)
{
    double t3 = t * t * t;
    double t2 = t * t;
    
    double h1 = 2.0 * t3 - 3.0 * t2 + 1.0;
    double h2 = -2.0 * t3 + 3.0 * t2;
    double h3 = t3 - 2.0 * t2 + t;
    double h4 = t3 - t2;
    
    return h1 * vec1 + h2 * vec2 + h3 * tan1 + h4 * tan2;
}

GMVector4D GMVector4D::Lerp(const GMVector4D& vec1, const GMVector4D& vec2, double t)
{
    return vec1 + (vec2 - vec1) * t;
}

GMVector4D GMVector4D::Max(const GMVector4D& vec1, const GMVector4D& vec2)
{
    GMVector4D ret = vec1;
    if (vec2.x > ret.x) {
        ret.x = vec2.x;
    }
    if (vec2.y > ret.y) {
        ret.y = vec2.y;
    }
    if (vec2.z > ret.z) {
        ret.z = vec2.z;
    }
    if (vec2.w > ret.w) {
        ret.w = vec2.w;
    }
    return ret;
}

GMVector4D GMVector4D::Min(const GMVector4D& vec1, const GMVector4D& vec2)
{
    GMVector4D ret = vec1;
    if (vec2.x < ret.x) {
        ret.x = vec2.x;
    }
    if (vec2.y < ret.y) {
        ret.y = vec2.y;
    }
    if (vec2.z < ret.z) {
        ret.z = vec2.z;
    }
    if (vec2.w < ret.w) {
        ret.w = vec2.w;
    }
    return ret;    
}

GMVector4D GMVector4D::SmoothStep(const GMVector4D& vec1, const GMVector4D& vec2, double t)
{
    return GMVector4D(GMMathHelper::SmoothStep(vec1.x, vec2.x, t),
                      GMMathHelper::SmoothStep(vec1.y, vec2.y, t),
                      GMMathHelper::SmoothStep(vec1.z, vec2.z, t),
                      GMMathHelper::SmoothStep(vec1.w, vec2.w, t));
}

GMVector4D GMVector4D::Transform(const GMVector2D& position, const GMMatrix& matrix)
{
    return GMVector4D((position.x * matrix.m11) + (position.y * matrix.m21) + matrix.m41,
                      (position.x * matrix.m12) + (position.y * matrix.m22) + matrix.m42,
                      (position.x * matrix.m13) + (position.y * matrix.m23) + matrix.m43,
                      (position.x * matrix.m14) + (position.y * matrix.m24) + matrix.m44);
}

GMVector4D GMVector4D::Transform(const GMVector3D& position, const GMMatrix& matrix)
{
    return GMVector4D((position.x * matrix.m11) + (position.y * matrix.m21) + (position.z * matrix.m31) + matrix.m41,
                      (position.x * matrix.m12) + (position.y * matrix.m22) + (position.z * matrix.m32) + matrix.m42,
                      (position.x * matrix.m13) + (position.y * matrix.m23) + (position.z * matrix.m33) + matrix.m43,
                      (position.x * matrix.m14) + (position.y * matrix.m24) + (position.z * matrix.m34) + matrix.m44);
}

GMVector4D GMVector4D::Transform(const GMVector4D& vector, const GMMatrix& matrix)
{
    return GMVector4D((vector.x * matrix.m11) + (vector.y * matrix.m21) + (vector.z * matrix.m31) + (vector.w * matrix.m41),
                      (vector.x * matrix.m12) + (vector.y * matrix.m22) + (vector.z * matrix.m32) + (vector.w * matrix.m42),
                      (vector.x * matrix.m13) + (vector.y * matrix.m23) + (vector.z * matrix.m33) + (vector.w * matrix.m43),
                      (vector.x * matrix.m14) + (vector.y * matrix.m24) + (vector.z * matrix.m34) + (vector.w * matrix.m44));
}

GMVector4D::GMVector4D()
: x(0.0), y(0.0), z(0.0), w(0.0)
{
    // Do nothing
}

GMVector4D::GMVector4D(double value)
: x(value), y(value), z(value), w(value)
{
    // Do nothing
}

GMVector4D::GMVector4D(double x_, double y_, double z_, double w_)
: x(x_), y(y_), z(z_), w(w_)
{
    // Do nothing
}

GMVector4D::GMVector4D(const GMVector2D& vec, double z_, double w_)
: x(vec.x), y(vec.y), z(z_), w(w_)
{
    // Do nothing
}

GMVector4D::GMVector4D(const GMVector3D& vec, double w_)
: x(vec.x), y(vec.y), z(vec.z), w(w_)
{
    // Do nothing
}

GMVector4D::GMVector4D(const GMVector4D& vec)
: x(vec.x), y(vec.y), z(vec.z), w(vec.w)
{
    // Do nothing
}

GMVector4D& GMVector4D::operator=(const GMVector4D& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
    w = vec.w;
    return *this;
}

GMVector4D GMVector4D::operator-() const
{
    return GMVector4D(-x, -y, -z, -w);
}

GMVector4D GMVector4D::operator+(const GMVector4D& vec) const
{
    return GMVector4D(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
}

GMVector4D GMVector4D::operator-(const GMVector4D& vec) const
{
    return GMVector4D(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
}

GMVector4D GMVector4D::operator*(const GMVector4D& vec) const
{
    return GMVector4D(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
}

GMVector4D GMVector4D::operator/(const GMVector4D& vec) const
{
    return GMVector4D(x / vec.x, y / vec.y, z / vec.z, w / vec.w);
}

GMVector4D GMVector4D::operator*(double value) const
{
    return GMVector4D(x * value, y * value, z * value, w * value);
}

GMVector4D GMVector4D::operator/(double value) const
{
    double d = 1.0 / value;
    return GMVector4D(x * d, y * d, z * d, w * d);
}

GMVector4D operator*(double value, const GMVector4D& vec)
{
    return GMVector4D(vec.x * value, vec.y * value, vec.z * value, vec.w * value);
}

GMVector4D& GMVector4D::operator+=(const GMVector4D& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
    w += vec.w;
    return *this;
}

GMVector4D& GMVector4D::operator-=(const GMVector4D& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    w -= vec.w;
    return *this;
}

GMVector4D& GMVector4D::operator*=(const GMVector4D& vec)
{
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    w *= vec.w;
    return *this;
}

GMVector4D& GMVector4D::operator/=(const GMVector4D& vec)
{
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
    w /= vec.w;
    return *this;
}

GMVector4D& GMVector4D::operator*=(double value)
{
    x *= value;
    y *= value;
    z *= value;
    w *= value;
    return *this;
}

GMVector4D& GMVector4D::operator/=(double value)
{
    double d = 1.0 / value;
    x *= d;
    y *= d;
    z *= d;
    w *= d;
    return *this;
}

bool GMVector4D::operator==(const GMVector4D& vec) const
{
    return equals(vec, GMMathHelper::DoubleEqThreshold);
}

bool GMVector4D::operator!=(const GMVector4D& vec) const
{
    return !equals(vec, GMMathHelper::DoubleEqThreshold);
}

bool GMVector4D::equals(const GMVector4D& vec, double accuracy) const
{
    return (fabs(x - vec.x) < accuracy &&
            fabs(y - vec.y) < accuracy &&
            fabs(z - vec.z) < accuracy &&
            fabs(w - vec.w) < accuracy)? true: false;
}

GMVector4D GMVector4D::clamp(const GMVector4D& minVal, const GMVector4D& maxVal) const
{
    return Min(Max(*this, minVal), maxVal);
}

double GMVector4D::distance(const GMVector4D& vec) const
{
    return (*this - vec).length();
}

double GMVector4D::distanceSq(const GMVector4D& vec) const
{
    return (*this - vec).lengthSq();
}

double GMVector4D::dot(const GMVector4D& vec) const
{
    return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
}

double GMVector4D::length() const
{
    return sqrt(x * x + y * y + z * z + w * w);
}

double GMVector4D::lengthSq() const
{
    return (x * x + y * y + z * z + w * w);
}

GMVector4D GMVector4D::normal() const
{
    return GMVector4D(*this).normalize();
}

GMVector4D& GMVector4D::normalize()
{
    *this /= length();
    return *this;
}

GMVector4D GMVector4D::transform(const GMMatrix& matrix) const
{
    GMVector4D ret;
    
    ret.x = x * matrix.m11 + y * matrix.m21 + z * matrix.m31 + w * matrix.m41;
    ret.y = x * matrix.m12 + y * matrix.m22 + z * matrix.m32 + w * matrix.m42;
    ret.z = x * matrix.m13 + y * matrix.m23 + z * matrix.m33 + w * matrix.m43;
    ret.w = x * matrix.m14 + y * matrix.m24 + z * matrix.m34 + w * matrix.m44;
    
    return ret;
}

GMVector4D GMVector4D::transform(const GMQuat& quat) const
{
    GMQuat conj(quat);
    conj.conjugate();
    
    GMQuat p(x, y, z, w);    
    p = quat * p;
    p = p * conj;
    
    return GMVector4D(p.x, p.y, p.z, p.w);
}



