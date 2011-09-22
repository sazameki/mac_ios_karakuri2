//
//  GMRect2D.h
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_RECT2D_H__
#define __GM_RECT2D_H__


#include "GMObject.h"

struct GMRect2D;
struct GMVector2D;


/*!
    @class  GMRect2D
    @group  Math
 */
struct GMRect2D : public GMObject {
    
public:
    /*!
        @const  Empty
     */    
    static const GMRect2D&  Empty;

public:
    /*!
        @var    x
     */
    double  x;

    /*!
        @var    y
     */
    double  y;

    /*!
        @var    width
     */
    double  width;

    /*!
        @var    height
     */
    double  height;
    
public:
    /*!
        @task   コンストラクタ
     */
    
    /*!
        @method     GMRect2D
     */
    GMRect2D();
    
    /*!
        @method     GMRect2D
     */
    GMRect2D(double x, double y, double width, double height);

    /*!
        @method     GMRect2D
     */
    GMRect2D(const GMVector2D& pos, const GMVector2D& size);

    /*!
        @method     GMRect2D
     */
    GMRect2D(const GMRect2D& rect);
    
    /*!
        @task   メインの操作
     */
    
    /*!
        @method     contains
     */
    bool        contains(const GMVector2D& pos) const;
    
    /*!
        @method     contains
     */
    bool        contains(const GMRect2D& rect) const;
    
    /*!
        @method     equals
     */
    bool        equals(const GMRect2D& rect, double accuracy) const;
    
    /*!
        @method     inflate
     */
    GMRect2D&   inflate(double h, double v);
    
    /*!
        @method     intersect
     */
    GMRect2D    intersect(const GMRect2D& rect) const;
    
    /*!
        @method     intersects
     */
    bool        intersects(const GMRect2D& rect) const;
    
    /*!
        @method     maxX
     */
    double      maxX() const;
    
    /*!
        @method     maxY
     */
    double      maxY() const;
    
    /*!
        @method     minX
     */
    double      minX() const;
    
    /*!
        @method     minY
     */
    double      minY() const;
    
    /*!
        @method     offset
     */
    GMRect2D&   offset(const GMVector2D& pos);
    
    /*!
        @method     unionRect
     */
    GMRect2D    unionRect(const GMRect2D& rect) const;

    /*!
        @task   演算子のオーバーロード
     */
    
    /*!
        @method     operator=
     */
    GMRect2D&   operator=(const GMRect2D& rect);
    
    /*!
        @method     operator==
     */
    bool        operator==(const GMRect2D& rect) const;
    
    /*!
        @method     operator!=
     */
    bool        operator!=(const GMRect2D& rect) const;
    
};


#endif  //#ifndef __GM_RECT2D_H__

