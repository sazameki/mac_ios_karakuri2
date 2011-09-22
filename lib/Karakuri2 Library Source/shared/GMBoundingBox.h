//
//  GMBoundingBox.h
//  Game Framework
//
//  Created by numata on Jan 09, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_BOUNDING_BOX_H__
#define __GM_BOUNDING_BOX_H__


#include "GMObject.h"
#include <cstdio>
#include "GMVector3D.h"
#include "GMEnums.h"

struct GMBoundingFrustum;
struct GMBoundingSphere;
struct GMMatrix;
struct GMPlane;
struct GMRay;


/*!
    @class  GMBoundingBox
    @group  Math
 */
struct GMBoundingBox : public GMObject {
    
    /*!
        @const      CornerCount
     */
    static const int    CornerCount;
    
    /*!
        @var    max
     */
    GMVector3D  max;

    /*!
        @var    min
     */
    GMVector3D  min;
    
public:
    /*!
        @task   生成メソッド
     */
    
    /*!
        @method     CreateFromPoints
     */
    static GMBoundingBox    CreateFromPoints(const GMVector3D* vecs, size_t count);
    
    /*!
        @method     CreateFromSphere
     */
    static GMBoundingBox    CreateFromSphere(const GMBoundingSphere& sphere);
    
    /*!
        @method     CreateMerged
     */
    static GMBoundingBox    CreateMerged(const GMBoundingBox& original, const GMBoundingBox& additional);
    
public:
    /*!
        @task   コンストラクタ
     */
    
    /*!
        @method     GMBoundingBox
     */
    GMBoundingBox();

    /*!
        @method     GMBoundingBox
     */
    GMBoundingBox(const GMVector3D& min, const GMVector3D& max);
    
public:
    /*!
        @task   メインの操作
     */
    
    /*!
        @method     contains
     */
    GMContainmentType   contains(const GMBoundingBox& box) const;
    
    /*!
        @method     contains
     */
    GMContainmentType   contains(const GMBoundingFrustum& frustum) const;
    
    /*!
        @method     contains
     */
    GMContainmentType   contains(const GMBoundingSphere& sphere) const;
    
    /*!
        @method     contains
     */
    GMContainmentType   contains(const GMVector3D& point) const;
    
    /*!
        @method     equals
     */
    bool    equals(const GMBoundingBox& box, double accuracy) const;
    
    /*!
        @method     getCorners
     */
    void    getCorners(GMVector3D* vecs) const;
    
    /*!
        @method     intersects
     */
    bool                    intersects(const GMBoundingBox& box) const;
    
    /*!
        @method     intersects
     */
    bool                    intersects(const GMBoundingFrustum& frustum) const;
    
    /*!
        @method     intersects
     */
    bool                    intersects(const GMBoundingSphere& sphere) const;
    
    /*!
        @method     intersects
     */
    GMPlaneIntersectionType intersects(const GMPlane& plane) const;
    
    /*!
        @method     intersects
     */
    double                  intersects(const GMRay& ray) const;
    
    /*!
        @task   演算子のオーバーロード
     */
    
    /*!
        @method     operator==
     */
    bool    operator==(const GMBoundingBox& box) const;
    
    /*!
        @method     operator!=
     */
    bool    operator!=(const GMBoundingBox& box) const;

};


#endif  //#ifndef __GM_BOUNDING_BOX_H__
