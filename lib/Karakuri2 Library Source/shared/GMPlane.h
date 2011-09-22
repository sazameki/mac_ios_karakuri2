//
//  GMPlane.h
//  Game Framework
//
//  Created by numata on Jan 09, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_PLANE_H__
#define __GM_PLANE_H__


#include "GMObject.h"
#include "GMVector3D.h"
#include "GMVector4D.h"
#include "GMEnums.h"


struct GMBoundingBox;
struct GMBoundingFrustum;
struct GMBoundingSphere;


/*!
    @class  GMPlane
    @group  Math
 */
struct GMPlane : public GMObject {
    
    /*!
        @var    distance
     */
    double      distance;
    
    /*!
        @var    normalVec
     */
    GMVector3D  normalVec;
    
public:
    /*!
        @task   コンストラクタ
     */
    
    /*!
        @method     GMPlane
     */
    GMPlane();
    
    /*!
        @method     GMPlane
     */
    GMPlane(double a, double b, double c, double d);
    
    /*!
        @method     GMPlane
     */
    GMPlane(const GMVector3D& normal, double d);
    
    /*!
        @method     GMPlane
     */
    GMPlane(const GMVector3D& p1, const GMVector3D& p2, const GMVector3D& p3);
    
    /*!
        @method     GMPlane
     */
    GMPlane(const GMVector4D& vec);

    /*!
        @task   メインの操作
     */
    
    /*!
        @method     dot
     */
    double      dot(const GMVector4D& vec) const;

    /*!
        @method     dotCoordinate
     */
    double      dotCoordinate(const GMVector3D& vec) const;
    
    /*!
        @method     dotNormal
     */
    double      dotNormal(const GMVector3D& vec) const;
    
    /*!
        @method     equals
     */
    bool        equals(const GMPlane& plane, double accuracy) const;
    
    
    /*!
        @method     intersects
     */
    GMPlaneIntersectionType intersects(const GMBoundingBox& box) const;
    
    /*!
        @method     intersects
     */
    GMPlaneIntersectionType intersects(const GMBoundingFrustum& frustum) const;
    
    /*!
        @method     intersects
     */
    GMPlaneIntersectionType intersects(const GMBoundingSphere& sphere) const;
    
    
    /*!
        @method     normal
     */
    GMPlane     normal() const;
    
    /*!
        @method     normalize
     */
    void        normalize();
    
    /*!
        @method     transform
     */
    GMPlane     transform(const GMMatrix& matrix) const;
    
    /*!
        @method     transform
     */
    GMPlane     transform(const GMQuat& quat) const;
    
    
    /*!
        @task   演算子のオーバーロード
     */    
    
    /*!
        @method     operator==
     */
    bool        operator==(const GMPlane& plane) const;
    
    /*!
        @method     operator!=
     */
    bool        operator!=(const GMPlane& plane) const;

};


#endif  //#ifndef __GM_PLANE_H__


