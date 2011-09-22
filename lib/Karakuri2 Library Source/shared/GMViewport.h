//
//  GMViewport.h
//  Game Framework
//
//  Created by numata on Jan 10, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_VIEWPORT_H__
#define __GM_VIEWPORT_H__


#include "GMObject.h"
#include "GMTypes.h"


/*!
    @class  GMViewport
    @group  Math
 */
struct GMViewport : public GMObject {
    
    /*!
        @var    x
     */
    int x;

    /*!
        @var    y
     */
    int y;

    /*!
        @var    width
     */
    int width;

    /*!
        @var    height
     */
    int height;

    /*!
        @var    maxDepth
     */
    double maxDepth;

    /*!
        @var    minDepth
     */
    double minDepth;
    
public:
    /*!
        @task   コンストラクタ
     */
    
    /*!
        @method     GMViewport
     */
    GMViewport();
    
    /*!
        @method     GMViewport
     */
    GMViewport(int x, int y, int width, int height);
    
    /*!
        @method     GMViewport
     */
    GMViewport(const GMViewport& viewport);
    
    /*!
        @method     GMViewport
     */
    GMViewport(const GMRect2D& bounds);

public:
    /*!
        @task   メインの操作
     */
    /*!
        @method     getAspectRatio
     */
    double      getAspectRatio() const;

    /*!
        @method     getBounds
     */
    GMRect2D    getBounds() const;

    /*!
        @method     project
     */
    GMVector3D  project(const GMVector3D& source, const GMMatrix& projection, const GMMatrix& view, const GMMatrix& world);

    /*!
        @method     setBounds
     */
    void        setBounds(const GMRect2D& bounds);

    /*!
        @method     unproject
     */
    GMVector3D  unproject(const GMVector3D& source, const GMMatrix& projection, const GMMatrix& view, const GMMatrix& world);

};


#endif  //#ifndef __GM_VIEWPORT_H__


