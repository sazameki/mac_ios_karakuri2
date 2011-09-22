//
//  GMVector3D.cpp
//  Game Framework
//
//  Created by numata on Jan 10, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMVector2D.h"
#include "GMVector3D.h"
#include "GMVector4D.h"
#include "GMMathHelper.h"

#include <cmath>


const GMVector3D& GMVector3D::Backward  = GMVector3D(0.0, 0.0, 1.0);
const GMVector3D& GMVector3D::Down      = GMVector3D(0.0, -1.0, 0.0);
const GMVector3D& GMVector3D::Forward   = GMVector3D(0.0, 0.0, -1.0);
const GMVector3D& GMVector3D::Left      = GMVector3D(-1.0, 0.0, 0.0);
const GMVector3D& GMVector3D::One       = GMVector3D(1.0, 1.0, 1.0);
const GMVector3D& GMVector3D::Right     = GMVector3D(1.0, 0.0, 0.0);
const GMVector3D& GMVector3D::UnitX     = GMVector3D(1.0, 0.0, 0.0);
const GMVector3D& GMVector3D::UnitY     = GMVector3D(0.0, 1.0, 0.0);
const GMVector3D& GMVector3D::UnitZ     = GMVector3D(0.0, 0.0, 1.0);
const GMVector3D& GMVector3D::Up        = GMVector3D(0.0, 1.0, 0.0);
const GMVector3D& GMVector3D::Zero      = GMVector3D(0.0, 0.0, 0.0);


GMVector3D GMVector3D::Barycentric(const GMVector3D& v1, const GMVector3D& v2, const GMVector3D& v3, double t1, double t2)
{
    return ((1.0 - t1 - t2) * v1) + (t1 * v2) + (t2 * v3);
}

GMVector3D GMVector3D::CatmullRom(const GMVector3D& v1, const GMVector3D& v2, const GMVector3D& v3, const GMVector3D& v4, double t)
{
    double t2 = t * t;
    double t3 = t2 * t;
    
    GMVector3D temp1 = (v3 - v1) / 2;
    GMVector3D temp2 = (v4 - v2) / 2;
    
    return (2 * v2 - 2 * v3 + temp1 + temp2) * t3 + (-3 * v2 + 3 * v3 - 2 * temp1 - temp2) * t2 + temp1 * t + v2;
}

GMVector3D GMVector3D::EaseIn(const GMVector3D& vec1, const GMVector3D& vec2, double t)
{
    return vec1 + (vec2 - vec1) * (t * t);
}

GMVector3D GMVector3D::EaseInOut(const GMVector3D& vec1, const GMVector3D& vec2, double t)
{
    GMVector3D middle = (vec1 + vec2) / 2;
    
    t *= 2;
    if (t <= 1.0) {
        return vec1 + (middle - vec1) * (t * t);
    }
    t -= 1;
    return middle + (vec2 - middle) * (t * t);
}

GMVector3D GMVector3D::EaseOut(const GMVector3D& vec1, const GMVector3D& vec2, double t)
{
    return (vec1 - (vec2 - vec1) * (t * (t - 2)));
}

GMVector3D GMVector3D::Hermite(const GMVector3D& vec1, const GMVector3D& tan1, const GMVector3D& vec2, const GMVector3D& tan2, double t)
{
    double t3 = t * t * t;
    double t2 = t * t;
    
    double h1 = 2.0 * t3 - 3.0 * t2 + 1.0;
    double h2 = -2.0 * t3 + 3.0 * t2;
    double h3 = t3 - 2.0 * t2 + t;
    double h4 = t3 - t2;
    
    return h1 * vec1 + h2 * vec2 + h3 * tan1 + h4 * tan2;
}

GMVector3D GMVector3D::Lerp(const GMVector3D& vec1, const GMVector3D& vec2, double t)
{
    return vec1 + (vec2 - vec1) * t;
}

GMVector3D GMVector3D::Max(const GMVector3D& vec1, const GMVector3D& vec2)
{
    GMVector3D ret = vec1;
    if (vec2.x > ret.x) {
        ret.x = vec2.x;
    }
    if (vec2.y > ret.y) {
        ret.y = vec2.y;
    }
    if (vec2.z > ret.z) {
        ret.z = vec2.z;
    }
    return ret;
}

GMVector3D GMVector3D::Min(const GMVector3D& vec1, const GMVector3D& vec2)
{
    GMVector3D ret = vec1;
    if (vec2.x < ret.x) {
        ret.x = vec2.x;
    }
    if (vec2.y < ret.y) {
        ret.y = vec2.y;
    }
    if (vec2.z < ret.z) {
        ret.z = vec2.z;
    }
    return ret;    
}

GMVector3D GMVector3D::SmoothStep(const GMVector3D& vec1, const GMVector3D& vec2, double t)
{
    return GMVector3D(GMMathHelper::SmoothStep(vec1.x, vec2.x, t),
                      GMMathHelper::SmoothStep(vec1.y, vec2.y, t),
                      GMMathHelper::SmoothStep(vec1.z, vec2.z, t));
}

GMVector3D::GMVector3D()
: x(0.0), y(0.0), z(0.0)
{
    // Do nothing
}

GMVector3D::GMVector3D(double value)
: x(value), y(value), z(value)
{
    // Do nothing
}

GMVector3D::GMVector3D(double x_, double y_, double z_)
: x(x_), y(y_), z(z_)
{
    // Do nothing
}

GMVector3D::GMVector3D(const GMVector2D& vec, double z_)
: x(vec.x), y(vec.y), z(z_)
{
    // Do nothing
}

GMVector3D::GMVector3D(const GMVector3D& vec)
: x(vec.x), y(vec.y), z(vec.z)
{
    // Do nothing
}

GMVector3D& GMVector3D::operator=(const GMVector3D& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
    return *this;
}

GMVector3D GMVector3D::operator-() const
{
    return GMVector3D(-x, -y, -z);
}

GMVector3D GMVector3D::operator+(const GMVector3D& vec) const
{
    return GMVector3D(x + vec.x, y + vec.y, z + vec.z);
}

GMVector3D GMVector3D::operator-(const GMVector3D& vec) const
{
    return GMVector3D(x - vec.x, y - vec.y, z - vec.z);
}

GMVector3D GMVector3D::operator*(const GMVector3D& vec) const
{
    return GMVector3D(x * vec.x, y * vec.y, z * vec.z);
}

GMVector3D GMVector3D::operator/(const GMVector3D& vec) const
{
    return GMVector3D(x / vec.x, y / vec.y, z / vec.z);
}

GMVector3D GMVector3D::operator*(double value) const
{
    return GMVector3D(x * value, y * value, z * value);
}

GMVector3D GMVector3D::operator/(double value) const
{
    return GMVector3D(x / value, y / value, z / value);
}

GMVector3D operator*(double value, const GMVector3D& vec)
{
    return GMVector3D(vec.x * value, vec.y * value, vec.z * value);
}

GMVector3D& GMVector3D::operator+=(const GMVector3D& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

GMVector3D& GMVector3D::operator-=(const GMVector3D& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

GMVector3D& GMVector3D::operator*=(const GMVector3D& vec)
{
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    return *this;
}

GMVector3D& GMVector3D::operator/=(const GMVector3D& vec)
{
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
    return *this;
}

GMVector3D& GMVector3D::operator*=(double value)
{
    x *= value;
    y *= value;
    z *= value;
    return *this;
}

GMVector3D& GMVector3D::operator/=(double value)
{
    x /= value;
    y /= value;
    z /= value;
    return *this;
}

bool GMVector3D::operator==(const GMVector3D& vec) const
{
    return equals(vec, GMMathHelper::DoubleEqThreshold);
}

bool GMVector3D::operator!=(const GMVector3D& vec) const
{
    return !equals(vec, GMMathHelper::DoubleEqThreshold);
}

bool GMVector3D::equals(const GMVector3D& vec, double accuracy) const
{
    return (fabs(x - vec.x) < accuracy &&
            fabs(y - vec.y) < accuracy &&
            fabs(z - vec.z) < accuracy)? true: false;
}

GMVector3D GMVector3D::clamp(const GMVector3D& minVal, const GMVector3D& maxVal) const
{
    return Min(Max(*this, minVal), maxVal);
}

GMVector3D GMVector3D::cross(const GMVector3D& vec) const
{
    return GMVector3D(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}

double GMVector3D::distance(const GMVector3D& vec) const
{
    return (*this - vec).length();
}

double GMVector3D::distanceSq(const GMVector3D& vec) const
{
    return (*this - vec).lengthSq();
}

double GMVector3D::dot(const GMVector3D& vec) const
{
    return (x * vec.x + y * vec.y + z * vec.z);
}

double GMVector3D::length() const
{
    return sqrt(x * x + y * y + z * z);
}

double GMVector3D::lengthSq() const
{
    return (x * x + y * y + z * z);
}

GMVector3D GMVector3D::normal() const
{
    return GMVector3D(*this).normalize();
}

GMVector3D& GMVector3D::normalize()
{
    *this /= length();
    return *this;
}

GMVector3D GMVector3D::reflect(const GMVector3D& normal) const
{
    GMVector3D theNormal(normal);
    theNormal.normalize();
    return *this - 2.0 * dot(theNormal) * theNormal;
}

GMVector3D GMVector3D::transform(const GMMatrix& matrix) const
{
    GMVector4D v4(*this, 1.0);
    v4 = v4.transform(matrix);
    return GMVector3D(v4.x, v4.y, v4.z);
}

GMVector3D GMVector3D::transform(const GMQuat& quat) const
{
    GMVector4D v4(*this, 1.0);
    v4 = v4.transform(quat);
    return GMVector3D(v4.x, v4.y, v4.z);    
}



