//
//  GMPlane.cpp
//  Game Framework
//
//  Created by numata on Jan 09, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMPlane.h"

#include "GMMathHelper.h"
#include "GMBoundingBox.h"
#include "GMBoundingFrustum.h"
#include "GMBoundingSphere.h"

#include <cmath>


GMPlane::GMPlane()
    : normalVec(GMVector3D::Zero), distance(0.0)
{
    // Do nothing
}

GMPlane::GMPlane(double a, double b, double c, double d)
    : normalVec(GMVector3D(a, b, c)), distance(d)
{
    // Do nothing
}

GMPlane::GMPlane(const GMVector3D& n, double d)
    : normalVec(n), distance(d)
{
    // Do nothing
}

GMPlane::GMPlane(const GMVector3D& a, const GMVector3D& b, const GMVector3D& c)
{
    GMVector3D ab = b - a;
    GMVector3D ac = c - a;
    
    GMVector3D cross = ab.cross(ac);

    normalVec = cross.normal();
    distance = -cross.dot(a);
}

GMPlane::GMPlane(const GMVector4D& vec)
    : normalVec(GMVector3D(vec.x, vec.y, vec.z)), distance(vec.w)
{
    // Do nothing
}

bool GMPlane::operator==(const GMPlane& plane) const
{
    return equals(plane, GMMathHelper::DoubleEqThreshold);
}

bool GMPlane::operator!=(const GMPlane& plane) const
{
    return !equals(plane, GMMathHelper::DoubleEqThreshold);
}

bool GMPlane::equals(const GMPlane& plane, double accuracy) const
{
    return (normalVec.equals(plane.normalVec, accuracy) && fabs(distance - plane.distance) < accuracy)? true: false;
}

double GMPlane::dot(const GMVector4D& vec) const
{
    return (normalVec.x * vec.x + normalVec.y * vec.y + normalVec.z * vec.z + distance * vec.w);
}

double GMPlane::dotCoordinate(const GMVector3D& vec) const
{
    return (normalVec.x * vec.x + normalVec.y * vec.y + normalVec.z * vec.z + distance);
}

double GMPlane::dotNormal(const GMVector3D& vec) const
{
    return (normalVec.x * vec.x + normalVec.y * vec.y + normalVec.z * vec.z);
}

GMPlaneIntersectionType GMPlane::intersects(const GMBoundingBox& box) const
{
    return box.intersects(*this);
}

GMPlaneIntersectionType GMPlane::intersects(const GMBoundingFrustum& frustum) const
{
    return frustum.intersects(*this);
}

GMPlaneIntersectionType GMPlane::intersects(const GMBoundingSphere& sphere) const
{
    return sphere.intersects(*this);
}

GMPlane GMPlane::normal() const
{
    GMPlane ret(*this);
    ret.normalize();
    return ret;
}

void GMPlane::normalize()
{
    double factor = 1.0 / normalVec.length();
    normalVec *= factor;
    distance *= factor;
}

GMPlane GMPlane::transform(const GMMatrix& matrix) const
{
    GMPlane ret;
    // TODO: GMPlane::transform(const GMMatrix& matrix) の実装
    return ret;
}

GMPlane GMPlane::transform(const GMQuat& quat) const
{
    GMPlane ret;
    // TODO: GMPlane::transform(const GMQuat& quat) の実装
    return ret;
}




