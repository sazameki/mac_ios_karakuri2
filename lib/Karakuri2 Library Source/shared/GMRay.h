//
//  GMRay.h
//  Game Framework
//
//  Created by numata on Jan 09, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_RAY_H__
#define __GM_RAY_H__


#include "GMObject.h"
#include "GMVector3D.h"

struct GMBoundingBox;
struct GMBoundingSphere;
struct GMPlane;


/*!
    @class  GMRay
    @group  Math
 */
struct GMRay : public GMObject {

    /*!
        @var    direction
     */
    GMVector3D  direction;
    
    /*!
        @var    position
     */
    GMVector3D  position;
    
public:
    /*!
        @task   コンストラクタ
     */
    
    /*!
        @method GMRay
     */
    GMRay();
    
    /*!
        @method GMRay
     */
    GMRay(const GMVector3D& position, const GMVector3D& direction);

    
    /*!
        @task   メインの処理
     */
    
    /*!
        @method     equals
     */
    bool        equals(const GMRay& ray, double accuracy) const;    

    /*!
        @method     intersects
     */
    double      intersects(const GMBoundingBox& box) const;
    
    /*!
        @method     intersects
     */
    double      intersects(const GMBoundingSphere& sphere) const;
    
    /*!
        @method     intersects
     */
    double      intersects(const GMPlane& plane) const;

    /*!
        @task   演算子のオーバーロード
     */
    
    /*!
        @method     operator==
     */
    bool        operator==(const GMRay& ray) const;
    
    /*!
        @method     operator!=
     */
    bool        operator!=(const GMRay& ray) const;

};


#endif  //#ifndef __GM_RAY_H__


