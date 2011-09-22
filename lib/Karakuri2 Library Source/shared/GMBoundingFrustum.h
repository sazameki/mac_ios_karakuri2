//
//  GMBoundingFrustum.h
//  Game Framework
//
//  Created by numata on Jan 09, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_BOUNDING_FRUSTUM_H__
#define __GM_BOUNDING_FRUSTUM_H__


#include "GMObject.h"
#include "GMEnums.h"
#include "GMPlane.h"
#include "GMMatrix.h"

struct GMBoundingBox;
struct GMBoundingSphere;
struct GMRay;
struct GMVector3D;


/*!
    @class  GMBoundingFrustum
    @group  Math
 */
struct GMBoundingFrustum : public GMObject {
    
    static const int    CornerCount;

    GMPlane     left;
    GMPlane     right;
    GMPlane     bottom;
    GMPlane     top;
    GMPlane     near;
    GMPlane     far;    
    
private:
    GMVector3D  corners[8];
    GMMatrix    matrix;

public:
    /*!
        @task   コンストラクタ
     */
    
    /*!
        @method     GMBoundingFrustum
     */
    GMBoundingFrustum();

    /*!
        @method     GMBoundingFrustum
     */
    GMBoundingFrustum(const GMMatrix& matrix);

public:
    GMContainmentType   contains(const GMBoundingBox& box) const;
    GMContainmentType   contains(const GMBoundingFrustum& frustum) const;
    GMContainmentType   contains(const GMBoundingSphere& sphere) const;
    GMContainmentType   contains(const GMVector3D& point) const;
    
    void    getCorners(GMVector3D* vecs) const;

    bool                    intersects(const GMBoundingBox& box) const;
    bool                    intersects(const GMBoundingFrustum& frustum) const;
    bool                    intersects(const GMBoundingSphere& sphere) const;
    GMPlaneIntersectionType intersects(const GMPlane& plane) const;
    double                  intersects(const GMRay& ray) const;
    
    bool    operator==(const GMBoundingFrustum& frustum) const;
    bool    operator!=(const GMBoundingFrustum& frustum) const;
    bool    equals(const GMBoundingFrustum& frustum, double accuracy) const;

public:
    GMMatrix    getMatrix() const;
    void        setMatrix(const GMMatrix& matrix);
    
private:
    void        createPlanes();
    void        createCorners();
    
};


#endif  //#ifndef __GM_BOUNDING_FRUSTUM_H__

