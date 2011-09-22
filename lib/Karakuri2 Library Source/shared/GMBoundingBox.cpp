//
//  GMBoundingBox.cpp
//  Game Framework
//
//  Created by numata on Jan 09, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMBoundingBox.h"

#include <cfloat>
#include <cmath>

#include "GMBoundingFrustum.h"
#include "GMBoundingSphere.h"
#include "GMMathHelper.h"
#include "GMPlane.h"
#include "GMRay.h"


const int GMBoundingBox::CornerCount = 8;


GMBoundingBox GMBoundingBox::CreateFromPoints(const GMVector3D* vecs, size_t count)
{
    GMVector3D vector2(DBL_MAX);
    GMVector3D vector1(DBL_MIN);
    for (int i = 0; i < count; i++) {
        vector2 = GMVector3D::Min(vector2, vecs[i]);
        vector1 = GMVector3D::Max(vector1, vecs[i]);
    }
    return GMBoundingBox(vector2, vector1);
}

GMBoundingBox GMBoundingBox::CreateFromSphere(const GMBoundingSphere& sphere)
{
    GMVector3D vector1(sphere.radius);
    return GMBoundingBox(sphere.center - vector1, sphere.center + vector1);
}

GMBoundingBox GMBoundingBox::CreateMerged(const GMBoundingBox& original, const GMBoundingBox& additional)
{
    return GMBoundingBox(GMVector3D::Min(original.min, additional.min), GMVector3D::Max(original.max, additional.max));
}

GMBoundingBox::GMBoundingBox()
    : min(GMVector3D::Zero), max(GMVector3D::Zero)
{
    // Do nothing
}

GMBoundingBox::GMBoundingBox(const GMVector3D& min_, const GMVector3D& max_)
    : min(min_), max(max_)
{
    // Do nothing
}

GMContainmentType GMBoundingBox::contains(const GMBoundingBox& box) const
{
    if (box.max.x < min.x || box.min.x > max.x ||
        box.max.y < min.y || box.min.y > max.y ||
        box.max.z < min.z || box.min.z > max.z)
    {
        return GMContainmentTypeDisjoint;
    }
    
    if (box.min.x >= min.x && box.max.x <= max.x &&
        box.min.y >= min.y && box.max.y <= max.y &&
        box.min.z >= min.z && box.max.z <= max.z)
    {
        return GMContainmentTypeContains;
    }
    
    return GMContainmentTypeIntersects;    
}

GMContainmentType GMBoundingBox::contains(const GMBoundingFrustum& frustum) const
{
    // TODO: GMBoundingBox::contains(const GMBoundingFrustum& frustum) の実装
    return GMContainmentTypeContains;
}

GMContainmentType GMBoundingBox::contains(const GMBoundingSphere& sphere) const
{
    if (sphere.center.x - min.x > sphere.radius &&
        sphere.center.y - min.y > sphere.radius &&
        sphere.center.z - min.z > sphere.radius &&
        max.x - sphere.center.x > sphere.radius &&
        max.y - sphere.center.y > sphere.radius &&
        max.z - sphere.center.z > sphere.radius)
    {
        return GMContainmentTypeContains;
    }
    
    double dmin = 0;
    
    if (sphere.center.x - min.x <= sphere.radius) {
        dmin += (sphere.center.x - min.x) * (sphere.center.x - min.x);
    } else if (max.x - sphere.center.x <= sphere.radius) {
        dmin += (sphere.center.x - max.x) * (sphere.center.x - max.x);
    }
    if (sphere.center.y - min.y <= sphere.radius) {
        dmin += (sphere.center.y - min.y) * (sphere.center.y - min.y);
    } else if (max.y - sphere.center.y <= sphere.radius) {
        dmin += (sphere.center.y - max.y) * (sphere.center.y - max.y);
    }
    if (sphere.center.z - min.z <= sphere.radius) {
        dmin += (sphere.center.z - min.z) * (sphere.center.z - min.z);
    } else if (max.z - sphere.center.z <= sphere.radius) {
        dmin += (sphere.center.z - max.z) * (sphere.center.z - max.z);
    }
    
    return (dmin <= sphere.radius * sphere.radius)? GMContainmentTypeIntersects: GMContainmentTypeDisjoint;
}

GMContainmentType GMBoundingBox::contains(const GMVector3D& point) const
{
    if (point.x < min.x || point.x > max.x ||
        point.y < min.y || point.y > max.y ||
        point.z < min.z || point.z > max.z)
    {
        return GMContainmentTypeDisjoint;
    } else if (fabs(point.x - min.x) < GMMathHelper::DoubleEqThreshold ||
               fabs(point.x - max.x) < GMMathHelper::DoubleEqThreshold ||
               fabs(point.y - min.y) < GMMathHelper::DoubleEqThreshold ||
               fabs(point.y - max.y) < GMMathHelper::DoubleEqThreshold ||
               fabs(point.z - min.z) < GMMathHelper::DoubleEqThreshold ||
               fabs(point.z - max.z) < GMMathHelper::DoubleEqThreshold)
    {
        return GMContainmentTypeIntersects;
    } else {
        return GMContainmentTypeContains;
    }
}

void GMBoundingBox::getCorners(GMVector3D* corners) const
{
    corners[0].x = min.x;
    corners[0].y = max.y;
    corners[0].z = max.z;
    corners[1].x = max.x;
    corners[1].y = max.y;
    corners[1].z = max.z;
    corners[2].x = max.x;
    corners[2].y = min.y;
    corners[2].z = max.z;
    corners[3].x = min.x;
    corners[3].y = min.y;
    corners[3].z = max.z;
    corners[4].x = min.x;
    corners[4].y = max.y;
    corners[4].z = min.z;
    corners[5].x = max.x;
    corners[5].y = max.y;
    corners[5].z = min.z;
    corners[6].x = max.x;
    corners[6].y = min.y;
    corners[6].z = min.z;
    corners[7].x = min.x;
    corners[7].y = min.y;
    corners[7].z = min.z;
}

bool GMBoundingBox::intersects(const GMBoundingBox& box) const
{
    if (max.x >= box.min.x && min.x <= box.max.x) {
        if (max.y < box.min.y || min.y > box.max.y) {
            return false;
        }

        return (max.z >= box.min.z && min.z <= box.max.z);
    }
    
    return false;
}

bool GMBoundingBox::intersects(const GMBoundingFrustum& frustum) const
{
    return frustum.intersects(*this);
}

bool GMBoundingBox::intersects(const GMBoundingSphere& sphere) const
{
    if (sphere.center.x - min.x > sphere.radius &&
        sphere.center.y - min.y > sphere.radius &&
        sphere.center.z - min.z > sphere.radius &&
        max.x - sphere.center.x > sphere.radius &&
        max.y - sphere.center.y > sphere.radius &&
        max.z - sphere.center.z > sphere.radius)
    {
        return true;
    }
    
    double dmin = 0;
    
    if (sphere.center.x - min.x <= sphere.radius) {
        dmin += (sphere.center.x - min.x) * (sphere.center.x - min.x);
    } else if (max.x - sphere.center.x <= sphere.radius) {
        dmin += (sphere.center.x - max.x) * (sphere.center.x - max.x);
    }
    
    if (sphere.center.y - min.y <= sphere.radius) {
        dmin += (sphere.center.y - min.y) * (sphere.center.y - min.y);
    } else if (max.y - sphere.center.y <= sphere.radius) {
        dmin += (sphere.center.y - max.y) * (sphere.center.y - max.y);
    }
    
    if (sphere.center.z - min.z <= sphere.radius) {
        dmin += (sphere.center.z - min.z) * (sphere.center.z - min.z);
    } else if (max.z - sphere.center.z <= sphere.radius) {
        dmin += (sphere.center.z - max.z) * (sphere.center.z - max.z);
    }
    
    return (dmin <= sphere.radius * sphere.radius)? true: false;
}

GMPlaneIntersectionType GMBoundingBox::intersects(const GMPlane& plane) const
{
    GMVector3D corners[8];
    getCorners(corners);
    double lastdistance = plane.normalVec.dot(corners[0]) + plane.distance;
    
    for (int i = 1; i < 8; i++) {
        double distance = plane.normalVec.dot(corners[i]) + plane.distance;
        if ((distance <= 0.0 && lastdistance > 0.0) || (distance >= 0.0 && lastdistance < 0.0)) {
            return GMPlaneIntersectionTypeIntersecting;
        }
        lastdistance = distance;
    }
    
    return (lastdistance > 0.0f)? GMPlaneIntersectionTypeFront: GMPlaneIntersectionTypeBack;
}

double GMBoundingBox::intersects(const GMRay& ray) const
{
    return ray.intersects(*this);
}

bool GMBoundingBox::operator==(const GMBoundingBox& box) const
{
    return equals(box, GMMathHelper::DoubleEqThreshold);
}

bool GMBoundingBox::operator!=(const GMBoundingBox& box) const
{
    return !equals(box, GMMathHelper::DoubleEqThreshold);
}

bool GMBoundingBox::equals(const GMBoundingBox& box, double accuracy) const
{
    return (min.equals(box.min, accuracy) && max.equals(box.max, accuracy))? true: false;
}



