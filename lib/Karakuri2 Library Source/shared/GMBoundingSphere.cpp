//
//  GMBoundingSphere.cpp
//  Game Framework
//
//  Created by numata on Jan 09, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMBoundingSphere.h"

#include <algorithm>
#include <cmath>
#include "GMMatrix.h"
#include "GMBoundingBox.h"
#include "GMBoundingFrustum.h"
#include "GMPlane.h"
#include "GMMathHelper.h"
#include "GMRay.h"


GMBoundingSphere GMBoundingSphere::CreateFromBoundingBox(const GMBoundingBox& box)
{
    GMVector3D center((box.min.x + box.max.x) / 2.0,
                      (box.min.y + box.max.y) / 2.0,
                      (box.min.z + box.max.z) / 2.0);
    return GMBoundingSphere(center, center.distance(box.max));
}

GMBoundingSphere GMBoundingSphere::CreateFromFrustum(const GMBoundingFrustum& frustum)
{
    GMVector3D corners[8];
    frustum.getCorners(corners);
    return CreateFromPoints(corners, 8);
}

GMBoundingSphere GMBoundingSphere::CreateFromPoints(const GMVector3D* vecs, size_t count)
{
    GMVector3D center;
    for (int i = 0; i < count; i++) {
        center += vecs[i];
    }    
    center /= count;
    
    double radius = 0.0;
    for (int i = 0; i < count; i++) {
        double distance = (vecs[i] - center).length();
        if (distance > radius) {
            radius = distance;
        }
    }

    return GMBoundingSphere(center, radius);    
}

GMBoundingSphere GMBoundingSphere::CreateMerged(const GMBoundingSphere& original, const GMBoundingSphere& additional)
{
    GMVector3D ocenterToaCenter = additional.center - original.center;
    double distance = ocenterToaCenter.length();
    if (distance <= original.radius + additional.radius) {
        if (distance <= original.radius - additional.radius) {
            return original;
        }
        if (distance <= additional.radius - original.radius) {
            return additional;
        }
    }
    
    double leftRadius = std::max(original.radius - distance, additional.radius);
    double Rightradius = std::max(original.radius + distance, additional.radius);
    ocenterToaCenter = ocenterToaCenter + ((leftRadius - Rightradius) / (2 * ocenterToaCenter.length())) * ocenterToaCenter;
    
    return GMBoundingSphere(original.center + ocenterToaCenter, (leftRadius + Rightradius) / 2);
}

GMBoundingSphere::GMBoundingSphere()
    : center(GMVector3D::Zero), radius(0.0)
{
    // Do nothing
}

GMBoundingSphere::GMBoundingSphere(const GMVector3D& center_, double radius_)
    : center(center_), radius(radius_)
{
    // Do nothing
}

GMContainmentType GMBoundingSphere::contains(const GMBoundingBox& box) const
{
    bool inside = true;
    GMVector3D corners[8];
    box.getCorners(corners);
    for (int i = 0; i < 8; i++) {
        if (contains(corners[i]) == GMContainmentTypeDisjoint) {
            inside = false;
            break;
        }
    }
    if (inside) {
        return GMContainmentTypeContains;
    }
    
    double dmin = 0;
    
    if (center.x < box.min.x) {
        dmin += (center.x - box.min.x) * (center.x - box.min.x);
    } else if (center.x > box.max.x) {
        dmin += (center.x - box.max.x) * (center.x - box.max.x);
    }
    
    if (center.y < box.min.y) {
        dmin += (center.y - box.min.y) * (center.y - box.min.y);
    } else if (center.y > box.max.y) {
        dmin += (center.y - box.max.y) * (center.y - box.max.y);
    }
    
    if (center.z < box.min.z) {
        dmin += (center.z - box.min.z) * (center.z - box.min.z);
    } else if (center.z > box.max.z) {
        dmin += (center.z - box.max.z) * (center.z - box.max.z);
    }
    
    return (dmin <= radius * radius)? GMContainmentTypeIntersects: GMContainmentTypeDisjoint;
}

GMContainmentType GMBoundingSphere::contains(const GMBoundingFrustum& frustum) const
{
    // TODO: GMBoundingSphere::contains(const GMBoundingFrustum& frustum) の実装
    return GMContainmentTypeIntersects;
}

GMContainmentType GMBoundingSphere::contains(const GMBoundingSphere& sphere) const
{
    double val = sphere.center.distance(center);
    
    if (val > sphere.radius + radius) {
        return GMContainmentTypeDisjoint;
    } else if (val <= radius - sphere.radius) {
        return GMContainmentTypeContains;
    } else {
        return GMContainmentTypeIntersects;
    }
}

GMContainmentType GMBoundingSphere::contains(const GMVector3D& point) const
{
    double distance = point.distance(center);
    
    if (distance > radius) {
        return GMContainmentTypeDisjoint;
    } else if (distance < radius) {
        return GMContainmentTypeContains;
    } else {
        return GMContainmentTypeIntersects;
    }
}

bool GMBoundingSphere::intersects(const GMBoundingBox& box) const
{
    return box.intersects(*this);
}

bool GMBoundingSphere::intersects(const GMBoundingFrustum& frustum) const
{
    // TODO: GMBoundingSphere::intersects(const GMBoundingFrustum& frustum) の実装
    return false;
}

bool GMBoundingSphere::intersects(const GMBoundingSphere& sphere) const
{
    return (center.distance(sphere.center) <= radius + sphere.radius)? true: false;
}

GMPlaneIntersectionType GMBoundingSphere::intersects(const GMPlane& plane) const
{
    double distance = plane.normalVec.dot(center) + plane.distance;
    if (distance > radius) {
        return GMPlaneIntersectionTypeFront;
    } else if (distance < -radius) {
        return GMPlaneIntersectionTypeBack;
    }
    return GMPlaneIntersectionTypeIntersecting;
}

double GMBoundingSphere::intersects(const GMRay& ray) const
{
    return ray.intersects(*this);
}

bool GMBoundingSphere::operator==(const GMBoundingSphere& sphere) const
{
    return equals(sphere, GMMathHelper::DoubleEqThreshold);
}

bool GMBoundingSphere::operator!=(const GMBoundingSphere& sphere) const
{
    return !equals(sphere, GMMathHelper::DoubleEqThreshold);
}

bool GMBoundingSphere::equals(const GMBoundingSphere& sphere, double accuracy) const
{
    return (center.equals(sphere.center, accuracy) && fabs(radius - sphere.radius) < accuracy)? true: false;
}

GMBoundingSphere GMBoundingSphere::transform(const GMMatrix& matrix) const
{
    GMBoundingSphere ret;
    ret.center = center.transform(matrix);
    ret.radius = radius * sqrt(std::max(matrix.m11 * matrix.m11 + matrix.m12 * matrix.m12 + matrix.m13 * matrix.m13,
                                        std::max(matrix.m21 * matrix.m21 + matrix.m22 * matrix.m22 + matrix.m23 * matrix.m23,
                                                 matrix.m31 * matrix.m31 + matrix.m32 * matrix.m32 + matrix.m33 * matrix.m33)));
    return ret;
}


