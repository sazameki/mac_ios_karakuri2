//
//  GMBoundingSphere.h
//  Game Framework
//
//  Created by numata on Jan 09, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_BOUNDING_SPHERE_H__
#define __GM_BOUNDING_SPHERE_H__


#include "GMObject.h"
#include <cstdio>
#include "GMVector3D.h"
#include "GMEnums.h"


struct GMBoundingBox;
struct GMBoundingFrustum;
struct GMBoundingSphere;
struct GMPlane;
struct GMRay;


/*!
    @class  GMBoundingSphere
    @group  Math
 */
struct GMBoundingSphere : public GMObject {

    GMVector3D      center;
    double          radius;
    
public:
    static GMBoundingSphere CreateFromBoundingBox(const GMBoundingBox& box);
 	static GMBoundingSphere CreateFromFrustum(const GMBoundingFrustum& frustum);
 	static GMBoundingSphere CreateFromPoints(const GMVector3D* vecs, size_t count);
 	static GMBoundingSphere CreateMerged(const GMBoundingSphere& original, const GMBoundingSphere& additional);
    
public:
    GMBoundingSphere();
    GMBoundingSphere(const GMVector3D& center, double radius);
    
public:
    GMContainmentType   contains(const GMBoundingBox& box) const;
    GMContainmentType   contains(const GMBoundingFrustum& frustum) const;
    GMContainmentType   contains(const GMBoundingSphere& sphere) const;
    GMContainmentType   contains(const GMVector3D& point) const;
    
    bool                    intersects(const GMBoundingBox& box) const;
    bool                    intersects(const GMBoundingFrustum& frustum) const;
    bool                    intersects(const GMBoundingSphere& sphere) const;
    GMPlaneIntersectionType intersects(const GMPlane& plane) const;
    double                  intersects(const GMRay& ray) const;
    
    bool    operator==(const GMBoundingSphere& sphere) const;
    bool    operator!=(const GMBoundingSphere& sphere) const;
    bool    equals(const GMBoundingSphere& sphere, double accuracy) const;

    GMBoundingSphere    transform(const GMMatrix& matrix) const;

};


#endif  //#ifndef __GM_BOUNDING_SPHERE_H__



