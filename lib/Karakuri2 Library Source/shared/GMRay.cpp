//
//  GMRay.cpp
//  Game Framework
//
//  Created by numata on Jan 09, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMRay.h"
#include <cfloat>
#include <cmath>
#include "GMBoundingSphere.h"


GMRay::GMRay()
    : position(GMVector3D::Zero), direction(GMVector3D::Zero)
{
    // Do nothing
}

GMRay::GMRay(const GMVector3D& position_, const GMVector3D& direction_)
    : position(position_), direction(direction_)
{
    // Do nothing
}

bool GMRay::operator==(const GMRay& ray) const
{
    return (position == ray.position && direction == ray.direction);
}

bool GMRay::operator!=(const GMRay& ray) const
{
    return (position != ray.position || direction != ray.direction);
}

bool GMRay::equals(const GMRay& ray, double accuracy) const
{
    return (position.equals(ray.position, accuracy) && direction.equals(ray.direction, accuracy));
}

double GMRay::intersects(const GMBoundingBox& box) const
{
    // TODO: GMRay::intersects(const GMBoundingBox& box) の実装
    return 0.0;
}

double GMRay::intersects(const GMBoundingSphere& sphere) const
{
    GMVector3D diff = sphere.center - position;
    
    double diffLengthSq = diff.lengthSq();
    double sphereRadiusSq = sphere.radius * sphere.radius;    
    if (diffLengthSq < sphereRadiusSq) {
        return DBL_MAX;
    }
    
    double distAlongRay = direction.dot(diff);
    if (distAlongRay < 0) {
        return DBL_MAX;
    }
    
    double dist = sphereRadiusSq + distAlongRay * distAlongRay - diffLengthSq;
    if (dist >= 0.0) {
        return distAlongRay - sqrt(dist);
    }
    return DBL_MAX;
}

double GMRay::intersects(const GMPlane& plane) const
{
    // TODO: GMRay::intersects(const GMPlane& plane) の実装
    return 0.0;
}

