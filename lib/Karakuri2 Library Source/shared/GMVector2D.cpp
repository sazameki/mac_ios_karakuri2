//
//  GMVector2D.cpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMVector2D.h"

#include "GMMathHelper.h"
#include "GMMatrix.h"
#include "GMQuat.h"
#include "GMVector4D.h"

#include <cmath>


#pragma mark ==== GMVector2D ====

const GMVector2D& GMVector2D::One   = GMVector2D(1.0, 1.0);
const GMVector2D& GMVector2D::UnitX = GMVector2D(1.0, 0.0);
const GMVector2D& GMVector2D::UnitY = GMVector2D(0.0, 1.0);
const GMVector2D& GMVector2D::Zero  = GMVector2D(0.0, 0.0);

GMVector2D GMVector2D::Barycentric(const GMVector2D& v1, const GMVector2D& v2, const GMVector2D& v3, double t1, double t2)
{
    return ((1.0 - t1 - t2) * v1) + (t1 * v2) + (t2 * v3);
}

GMVector2D GMVector2D::CatmullRom(const GMVector2D& v1, const GMVector2D& v2, const GMVector2D& v3, const GMVector2D& v4, double t)
{
    double t2 = t * t;
    double t3 = t2 * t;
    
    GMVector2D temp1 = (v3 - v1) / 2;
    GMVector2D temp2 = (v4 - v2) / 2;
    
    return (2 * v2 - 2 * v3 + temp1 + temp2) * t3 + (-3 * v2 + 3 * v3 - 2 * temp1 - temp2) * t2 + temp1 * t + v2;
}

GMVector2D GMVector2D::EaseIn(const GMVector2D& vec1, const GMVector2D& vec2, double t)
{
    return vec1 + (vec2 - vec1) * (t * t);
}

GMVector2D GMVector2D::EaseInOut(const GMVector2D& vec1, const GMVector2D& vec2, double t)
{
    GMVector2D middle = (vec1 + vec2) / 2;
    
    t *= 2;
    if (t <= 1.0) {
        return vec1 + (middle - vec1) * (t * t);
    }
    t -= 1;
    return middle + (vec2 - middle) * (t * t);
}

GMVector2D GMVector2D::EaseOut(const GMVector2D& vec1, const GMVector2D& vec2, double t)
{
    return (vec1 - (vec2 - vec1) * (t * (t - 2)));
}

GMVector2D GMVector2D::Hermite(const GMVector2D& vec1, const GMVector2D& tan1, const GMVector2D& vec2, const GMVector2D& tan2, double t)
{
    double t3 = t * t * t;
    double t2 = t * t;
    
    double h1 = 2.0 * t3 - 3.0 * t2 + 1.0;
    double h2 = -2.0 * t3 + 3.0 * t2;
    double h3 = t3 - 2.0 * t2 + t;
    double h4 = t3 - t2;
    
    return h1 * vec1 + h2 * vec2 + h3 * tan1 + h4 * tan2;
}

GMVector2D GMVector2D::Lerp(const GMVector2D& vec1, const GMVector2D& vec2, double t)
{
    return vec1 + (vec2 - vec1) * t;
}

GMVector2D GMVector2D::Max(const GMVector2D& vec1, const GMVector2D& vec2)
{
    GMVector2D ret = vec1;
    if (vec2.x > ret.x) {
        ret.x = vec2.x;
    }
    if (vec2.y > ret.y) {
        ret.y = vec2.y;
    }
    return ret;
}

GMVector2D GMVector2D::Min(const GMVector2D& vec1, const GMVector2D& vec2)
{
    GMVector2D ret = vec1;
    if (vec2.x < ret.x) {
        ret.x = vec2.x;
    }
    if (vec2.y < ret.y) {
        ret.y = vec2.y;
    }
    return ret;    
}

GMVector2D GMVector2D::SmoothStep(const GMVector2D& vec1, const GMVector2D& vec2, double t)
{
    return GMVector2D(GMMathHelper::SmoothStep(vec1.x, vec2.x, t), GMMathHelper::SmoothStep(vec1.y, vec2.y, t));
}

GMVector2D::GMVector2D()
    : x(0.0), y(0.0)
{
    // Do nothing
}

GMVector2D::GMVector2D(double value)
    : x(value), y(value)
{
    // Do nothing
}

GMVector2D::GMVector2D(double x_, double y_)
    : x(x_), y(y_)
{
    // Do nothing
}

GMVector2D::GMVector2D(const GMVector2D& vec)
    : x(vec.x), y(vec.y)
{
    // Do nothing
}

GMVector2D& GMVector2D::operator=(const GMVector2D& vec)
{
    x = vec.x;
    y = vec.y;
    return *this;
}

GMVector2D GMVector2D::operator-() const
{
    return GMVector2D(-x, -y);
}

GMVector2D GMVector2D::operator+(const GMVector2D& vec) const
{
    return GMVector2D(x + vec.x, y + vec.y);
}

GMVector2D GMVector2D::operator-(const GMVector2D& vec) const
{
    return GMVector2D(x - vec.x, y - vec.y);
}

GMVector2D GMVector2D::operator*(const GMVector2D& vec) const
{
    return GMVector2D(x * vec.x, y * vec.y);
}

GMVector2D GMVector2D::operator/(const GMVector2D& vec) const
{
    return GMVector2D(x / vec.x, y / vec.y);
}

GMVector2D GMVector2D::operator*(double value) const
{
    return GMVector2D(x * value, y * value);
}

GMVector2D GMVector2D::operator/(double value) const
{
    double d = 1.0 / value;
    return GMVector2D(x * d, y * d);
}

GMVector2D operator*(double value, const GMVector2D& vec)
{
    return GMVector2D(vec.x * value, vec.y * value);
}

GMVector2D& GMVector2D::operator+=(const GMVector2D& vec)
{
    x += vec.x;
    y += vec.y;
    return *this;
}

GMVector2D& GMVector2D::operator-=(const GMVector2D& vec)
{
    x -= vec.x;
    y -= vec.y;
    return *this;
}

GMVector2D& GMVector2D::operator*=(const GMVector2D& vec)
{
    x *= vec.x;
    y *= vec.y;
    return *this;    
}

GMVector2D& GMVector2D::operator/=(const GMVector2D& vec)
{
    x /= vec.x;
    y /= vec.y;
    return *this;    
}

GMVector2D& GMVector2D::operator*=(double value)
{
    x *= value;
    y *= value;
    return *this;    
}

GMVector2D& GMVector2D::operator/=(double value)
{
    x /= value;
    y /= value;
    return *this;    
}

bool GMVector2D::operator==(const GMVector2D& vec) const
{
    return equals(vec, GMMathHelper::DoubleEqThreshold);
}

bool GMVector2D::operator!=(const GMVector2D& vec) const
{
    return !equals(vec, GMMathHelper::DoubleEqThreshold);
}

bool GMVector2D::equals(const GMVector2D& vec, double accuracy) const
{
    return (fabs(x - vec.x) < accuracy &&
            fabs(y - vec.y) < accuracy)? true: false;
}

GMVector2D GMVector2D::clamp(const GMVector2D& minVal, const GMVector2D& maxVal) const
{
    return Min(Max(*this, minVal), maxVal);
}

double GMVector2D::cross(const GMVector2D& vec) const
{
    return x * vec.y - y * vec.x;
}

double GMVector2D::distance(const GMVector2D& vec) const
{
    return (*this - vec).length();
}

double GMVector2D::distanceSq(const GMVector2D& vec) const
{
    return (*this - vec).lengthSq();
}

double GMVector2D::dot(const GMVector2D& vec) const
{
    return x * vec.x + y * vec.y;
}

double GMVector2D::length() const
{
    return sqrt(x * x + y * y);
}

double GMVector2D::lengthSq() const
{
    return (x * x + y * y);
}

GMVector2D GMVector2D::normal() const
{
    return GMVector2D(*this).normalize();
}

GMVector2D& GMVector2D::normalize()
{
    *this /= length();
    return *this;
}

GMVector2D GMVector2D::reflect(const GMVector2D& normal) const
{
    GMVector2D theNormal(normal);
    theNormal.normalize();
    return *this - 2.0 * dot(theNormal) * theNormal;    
}

GMVector2D GMVector2D::transform(const GMMatrix& matrix) const
{
    GMVector4D v4(*this, 0.0, 1.0);
    v4 = v4.transform(matrix);
    return GMVector2D(v4.x, v4.y);
}

GMVector2D GMVector2D::transform(const GMQuat& quat) const
{
    GMVector4D v4(*this, 0.0, 1.0);
    v4 = v4.transform(quat);
    return GMVector2D(v4.x, v4.y);    
}



