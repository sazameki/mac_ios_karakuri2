//
//  GMBoundingFrustum.cpp
//  Game Framework
//
//  Created by numata on Jan 09, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMBoundingFrustum.h"

#include "GMBoundingBox.h"
#include "GMMathHelper.h"


const int GMBoundingFrustum::CornerCount = 8;


GMBoundingFrustum::GMBoundingFrustum()
{
    setMatrix(GMMatrix::Identity);
}

GMBoundingFrustum::GMBoundingFrustum(const GMMatrix& mat)
{
    setMatrix(mat);
}

GMContainmentType GMBoundingFrustum::contains(const GMBoundingBox& box) const
{
    // TODO: GMBoundingFrustum::contains(const GMBoundingBox& box) の実装
    return GMContainmentTypeContains;
}

GMContainmentType GMBoundingFrustum::contains(const GMBoundingFrustum& frustum) const
{
    // TODO: GMBoundingFrustum::contains(const GMBoundingFrustum& frustum) の実装
    return GMContainmentTypeContains;
}

GMContainmentType GMBoundingFrustum::contains(const GMBoundingSphere& sphere) const
{
    // TODO: GMBoundingFrustum::contains(const GMBoundingSphere& sphere) の実装
    return GMContainmentTypeContains;
}

static double classifyPoint(const GMVector3D& point, const GMPlane& plane)
{
    return point.x * plane.normalVec.x + point.y * plane.normalVec.y + point.z * plane.normalVec.z + plane.distance;
}

GMContainmentType GMBoundingFrustum::contains(const GMVector3D& point) const
{
    // Check the top
    if (classifyPoint(point, top) > 0) {
        return GMContainmentTypeDisjoint;
    }
    
    // Check the bottom
    if (classifyPoint(point, bottom) > 0) {
        return GMContainmentTypeDisjoint;
    }
    
    // Check the left
    if (classifyPoint(point, left) > 0) {
        return GMContainmentTypeDisjoint;
    }
    
    // Check the right
    if (classifyPoint(point, right) > 0) {
        return GMContainmentTypeDisjoint;
    }
    
    // Check the near
    if (classifyPoint(point, near) > 0) {
        return GMContainmentTypeDisjoint;
    }
    
    // Check the far
    if (classifyPoint(point, far) > 0) {
        return GMContainmentTypeDisjoint;
    }
    
    return GMContainmentTypeContains;
}

void GMBoundingFrustum::getCorners(GMVector3D* vecs) const
{
    // TODO: GMBoundingFrustum::getCorners(GMVector3D* vecs) の実装
}

bool GMBoundingFrustum::intersects(const GMBoundingBox& box) const
{
    // TODO: GMBoundingFrustum::intersects(const GMBoundingBox& box) の実装
    return false;
}

bool GMBoundingFrustum::intersects(const GMBoundingFrustum& frustum) const
{
    // TODO: GMBoundingFrustum::intersects(const GMBoundingFrustum& frustum) の実装
    return false;
}

bool GMBoundingFrustum::intersects(const GMBoundingSphere& sphere) const
{
    // TODO: GMBoundingFrustum::intersects(const GMBoundingSphere& sphere) の実装
    return false;
}

GMPlaneIntersectionType GMBoundingFrustum::intersects(const GMPlane& plane) const
{
    // TODO: GMBoundingFrustum::intersects(const GMPlane& plane) の実装
    return GMPlaneIntersectionTypeIntersecting;
}

double GMBoundingFrustum::intersects(const GMRay& ray) const
{
    // TODO: GMBoundingFrustum::intersects(const GMRay& ray) の実装
    return 0.0;
}

bool GMBoundingFrustum::operator==(const GMBoundingFrustum& frustum) const
{
    return equals(frustum, GMMathHelper::DoubleEqThreshold);
}

bool GMBoundingFrustum::operator!=(const GMBoundingFrustum& frustum) const
{
    return !equals(frustum, GMMathHelper::DoubleEqThreshold);
}

bool GMBoundingFrustum::equals(const GMBoundingFrustum& frustum, double accuracy) const
{
    return matrix.equals(frustum.matrix, accuracy);
}

GMMatrix GMBoundingFrustum::getMatrix() const
{
    return matrix;
}

void GMBoundingFrustum::setMatrix(const GMMatrix& mat)
{
    matrix = mat;
    createPlanes();
    createCorners();
}

void GMBoundingFrustum::createPlanes()
{
    left = GMPlane(-matrix.m14 - matrix.m11, -matrix.m24 - matrix.m21,
                   -matrix.m34 - matrix.m31, -matrix.m44 - matrix.m41);
    
    right = GMPlane(matrix.m11 - matrix.m14, matrix.m21 - matrix.m24,
                    matrix.m31 - matrix.m34, matrix.m41 - matrix.m44);
    
    top = GMPlane(matrix.m12 - matrix.m14, matrix.m22 - matrix.m24,
                  matrix.m32 - matrix.m34, matrix.m42 - matrix.m44);
    
    bottom = GMPlane(-matrix.m14 - matrix.m12, -matrix.m24 - matrix.m22,
                     -matrix.m34 - matrix.m32, -matrix.m44 - matrix.m42);
    
    near = GMPlane(-matrix.m13, -matrix.m23, -matrix.m33, -matrix.m43);
    
    far = GMPlane(matrix.m13 - matrix.m14, matrix.m23 - matrix.m24,
                  matrix.m33 - matrix.m34, matrix.m43 - matrix.m44);
    
    left.normalize();
    right.normalize();
    top.normalize();
    bottom.normalize();
    near.normalize();
    far.normalize();
}

static GMVector3D intersectionPoint(const GMPlane& a, const GMPlane& b, const GMPlane& c)
{
    double f = -a.normalVec.dot(b.normalVec.cross(c.normalVec));
    
    GMVector3D v1 = a.distance * b.normalVec.cross(c.normalVec);
    GMVector3D v2 = b.distance * c.normalVec.cross(a.normalVec);
    GMVector3D v3 = c.distance * a.normalVec.cross(b.normalVec);
    
    return GMVector3D(v1.x + v2.x + v3.x, v1.y + v2.y + v3.y, v1.z + v2.z + v3.z) / f;
}

void GMBoundingFrustum::createCorners()
{
    corners[0] = intersectionPoint(near, left, top);
    corners[1] = intersectionPoint(near, right, top);
    corners[2] = intersectionPoint(near, right, bottom);
    corners[3] = intersectionPoint(near, left, bottom);
    corners[4] = intersectionPoint(far, left, top);
    corners[5] = intersectionPoint(far, right, top);
    corners[6] = intersectionPoint(far, right, bottom);
    corners[7] = intersectionPoint(far, left, bottom);
}


