//
//  GMQuat.cpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMQuat.h"

#include "GMTypes.h"
#include "GMMathHelper.h"
#include "GMVector3D.h"

#include <cmath>


const GMQuat& GMQuat::Identity  = GMQuat(0.0, 0.0, 0.0, 1.0);


GMQuat::GMQuat()
    : x(0.0), y(0.0), z(0.0), w(0.0)
{
    // Do nothing
}

GMQuat::GMQuat(double x_, double y_, double z_, double w_)
    : x(x_), y(y_), z(z_), w(w_)
{
    // Do nothing
}

GMQuat::GMQuat(const GMQuat& quat)
    : x(quat.x), y(quat.y), z(quat.z), w(quat.w)
{
    // Do nothing
}

GMQuat::GMQuat(const GMMatrix& m)
{
    double m11 = m.m11;
    double m22 = m.m22;
    double m33 = m.m33;
    
    double tr = m11 + m22 + m33;
    
    if (tr > 0.0) {
        double t = sqrt(tr + 1.0) * 2;
        x = (m.m23 - m.m32) / t;
        y = (m.m31 - m.m13) / t; 
        z = (m.m12 - m.m21) / t;
        w = t / 4;
    } else if (m11 >= m22 && m11 >= m33) {
        double t = sqrt(m11 - m22 - m33 + 1.0) * 2;
        x = t / 4;
        y = (m.m21 + m.m12) / t;
        z = (m.m31 + m.m13) / t;
        w = (m.m23 - m.m32) / t;
    } else if (m22 > m33) {
        double t = sqrt(m22 - m11 - m33 + 1.0) * 2;
        x = (m.m21 + m.m12) / t;
        y = t / 4;
        z = (m.m32 + m.m23) / t;
        w = (m.m31 - m.m13) / t;
    } else {
        double t = sqrt(m33 - m11 - m22 + 1.0) * 2;
        x = (m.m31 + m.m13) / t;
        y = (m.m32 + m.m23) / t;
        z = t / 4;
        w = (m.m12 - m.m21) / t;
    }
}

GMQuat GMQuat::CreateFromAxisAngle(const GMVector3D& axis, double angle)
{
    GMQuat ret;

    double s = sin(angle / 2);
    ret.x = axis.x * s;
    ret.y = axis.y * s;
    ret.z = axis.z * s;
    ret.w = cos(angle / 2);
    
    return ret;
}

GMQuat GMQuat::CreateFromYawPitchRoll(double yaw, double pitch, double roll)
{
    double cx = cos(pitch / 2);
    double cy = cos(yaw / 2);
    double cz = cos(roll / 2);
    double sx = sin(pitch / 2);
    double sy = sin(yaw / 2);
    double sz = sin(roll / 2);

    return GMQuat(sx*cy*cz + cx*sy*sz,
                  cx*sy*cz - sx*cy*sz,
                  cx*cy*sz - sx*sy*cz,
                  cx*cy*cz + sx*sy*sz);
}

GMQuat GMQuat::EaseIn(const GMQuat& q1, const GMQuat& q2, double t)
{
    return q1 + (q2 - q1) * (t * t);
}

GMQuat GMQuat::EaseInOut(const GMQuat& q1, const GMQuat& q2, double t)
{
    GMQuat middle = (q1 + q2) / 2;
    
    t *= 2;
    if (t <= 1.0) {
        return q1 + (middle - q1) * (t * t);
    }
    t -= 1;
    return middle + (q2 - middle) * (t * t);
}

GMQuat GMQuat::EaseOut(const GMQuat& q1, const GMQuat& q2, double t)
{
    return (q1 - (q2 - q1) * (t * (t - 2)));
}

GMQuat GMQuat::Lerp(const GMQuat& q1, const GMQuat& q2, double t)
{
    //return (q1 + (q2 - q1) * t).normal();
    return q1 * (1.0 - t) + q2 * t;
}

GMQuat GMQuat::Slerp(const GMQuat& q1, const GMQuat& q2, double t)
{
    double dot = q1.dot(q2);
    
    GMQuat q3 = q2;
    if (dot < 0) {
        q3 *= -1;
        dot = -dot;
    }
    
    if (dot < 0.95) {
        double angle = acos(dot);
        return (q1 * sin(angle * (1 - t)) + q3 * sin(angle * t)) / sin(angle);
    } else {
        return Lerp(q1, q3, t);
    }
}

GMQuat& GMQuat::operator=(const GMQuat& quat)
{
    x = quat.x;
    y = quat.y;
    z = quat.z;
    w = quat.w;
    return *this;
}

GMQuat GMQuat::operator-() const
{
    GMQuat ret(*this);
    ret *= -1;
    return ret;
}

GMQuat GMQuat::operator+(const GMQuat& quat) const
{
    GMQuat ret(*this);
    ret += quat;
    return ret;
}

GMQuat GMQuat::operator-(const GMQuat& quat) const
{
    GMQuat ret(*this);
    ret -= quat;
    return ret;
}

GMQuat GMQuat::operator*(const GMQuat& quat) const
{
    GMQuat ret(*this);
    ret *= quat;
    return ret;
}

GMQuat GMQuat::operator*(double scale) const
{
    GMQuat ret(*this);
    ret.x *= scale;
    ret.y *= scale;
    ret.z *= scale;
    ret.w *= scale;
    return ret;    
}

GMQuat GMQuat::operator/(const GMQuat& quat) const
{
    GMQuat ret(*this);
    ret /= quat;
    return ret;
}

GMQuat GMQuat::operator/(double value) const
{
    GMQuat ret(*this);
    ret.x /= value;
    ret.y /= value;
    ret.z /= value;
    ret.w /= value;
    return ret;
}

GMQuat& GMQuat::operator+=(const GMQuat& quat)
{
    x += quat.x;
    y += quat.y;
    z += quat.z;
    w += quat.w;
    return *this;
}

GMQuat& GMQuat::operator-=(const GMQuat& quat)
{
    x -= quat.x;
    y -= quat.y;
    z -= quat.z;
    w -= quat.w;
    return *this;
}

GMQuat& GMQuat::operator*=(const GMQuat& quat)
{
    double tx = x;
    double ty = y;
    double tz = z;
    double tw = w;
    
    x = tw * quat.x + tx * quat.w + ty * quat.z - tz * quat.y;
    y = tw * quat.y - tx * quat.z + ty * quat.w + tz * quat.x;
    z = tw * quat.z + tx * quat.y - ty * quat.x + tz * quat.w;
    w = tw * quat.w - tx * quat.x - ty * quat.y - tz * quat.z;
    
    return *this;
}

GMQuat& GMQuat::operator*=(double scale)
{
    x *= scale;
    y *= scale;
    z *= scale;
    w *= scale;
    return *this;
}

GMQuat& GMQuat::operator/=(const GMQuat& quat)
{
    double tx = x;
    double ty = y;
    double tz = z;
    double tw = w;
    
    double len = length();

    x = (-tw * quat.x + tx * quat.w - ty * quat.z + tz * quat.y) / len;
    y = (-tw * quat.y + tx * quat.z + ty * quat.w - tz * quat.x) / len;
    z = (-tw * quat.z - tx * quat.y + ty * quat.x + tz * quat.w) / len;
    w = ( tw * quat.w + tx * quat.x + ty * quat.y + tz * quat.z) / len;

    return *this;
}

GMQuat& GMQuat::operator/=(double value)
{
    x /= value;
    y /= value;
    z /= value;
    w /= value;
    return *this;
}

bool GMQuat::operator==(const GMQuat& quat) const
{
    return equals(quat, GMMathHelper::DoubleEqThreshold);
}

bool GMQuat::operator!=(const GMQuat& quat) const
{
    return !equals(quat, GMMathHelper::DoubleEqThreshold);
}

bool GMQuat::equals(const GMQuat& quat, double accuracy) const
{
    return (fabs(x - quat.x) < accuracy &&
            fabs(y - quat.y) < accuracy &&
            fabs(z - quat.z) < accuracy &&
            fabs(w - quat.w) < accuracy)? true: false;    
}

GMQuat GMQuat::concat(const GMQuat& quat) const
{
    return quat * (*this);
}

GMQuat& GMQuat::conjugate()
{
    x *= -1;
    y *= -1;
    z *= -1;
    return *this;
}

double GMQuat::dot(const GMQuat& quat) const
{
    return x * quat.x + y * quat.y + z * quat.z + w * quat.w;
}

GMQuat GMQuat::inverse() const
{
    GMQuat ret(*this);
    ret.conjugate();
    ret /= lengthSq();
    return ret;
}

double GMQuat::length() const
{
    return sqrt(x * x + y * y + z * z + w * w);
}

double GMQuat::lengthSq() const
{
    return x * x + y * y + z * z + w * w;
}

GMQuat GMQuat::normal() const
{
    return *this / length();
}

GMQuat& GMQuat::normalize()
{
    *this /= length();
    return *this;
}

GMMatrix GMQuat::toMatrix() const
{
    return GMMatrix(*this);
}


