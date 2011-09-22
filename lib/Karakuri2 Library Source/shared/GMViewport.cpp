//
//  GMViewport.cpp
//  Game Framework
//
//  Created by numata on Jan 10, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMViewport.h"

#include "GMMathHelper.h"
#include <cmath>


GMViewport::GMViewport()
    : x(0), y(0), width(0), height(0), minDepth(0.0), maxDepth(0.0)
{
    // Do nothing
}

GMViewport::GMViewport(int x_, int y_, int width_, int height_)
    : x(x_), y(y_), width(width_), height(height_), minDepth(0.0), maxDepth(0.0)
{
    // Do nothing
}

GMViewport::GMViewport(const GMViewport& viewport)
    : x(viewport.x), y(viewport.y), width(viewport.width), height(viewport.height),
      minDepth(viewport.minDepth), maxDepth(viewport.maxDepth)
{
    // Do nothing
}

GMViewport::GMViewport(const GMRect2D& bounds)
    : x(bounds.x), y(bounds.y), width(bounds.width), height(bounds.height), minDepth(0.0), maxDepth(0.0)
{
    // Do nothing
}

double GMViewport::getAspectRatio() const
{
    return (double)width / height;
}

GMRect2D GMViewport::getBounds() const
{
    return GMRect2D(x, y, width, height);
}

void GMViewport::setBounds(const GMRect2D& bounds)
{
    x = bounds.x;
    y = bounds.y;
    width = bounds.width;
    height = bounds.height;
}

GMVector3D GMViewport::project(const GMVector3D& source, const GMMatrix& projection, const GMMatrix& view, const GMMatrix& world)
{
    GMVector4D result = GMVector4D::Transform(source, world);
    result = result.transform(view);
    result = result.transform(projection);
    result.z = result.z * (maxDepth - minDepth);
    result /=  result.w;
    
    GMVector3D finalResult(result.x, result.y, result.z);    
    finalResult.x = x + (1 + finalResult.x) * width / 2;
    finalResult.y = y + (1 - finalResult.y) * height / 2;
    finalResult.z = finalResult.z + minDepth;
    return finalResult;    
}

GMVector3D GMViewport::unproject(const GMVector3D& source, const GMMatrix& projection, const GMMatrix& view, const GMMatrix& world)
{
    GMVector4D result;
    result.x = ((source.x - x) * 2 / width) - 1;
    result.y = 1 - ((source.y - y) * 2 / height);
    result.z = source.z - minDepth;
    if (fabs(maxDepth - minDepth) < GMMathHelper::DoubleEqThreshold) {
        result.z = 0.0;
    } else {
        result.z /= (maxDepth - minDepth);
    }
    result.w = 1.0;
    result = result.transform(projection.invert());
    result = result.transform(view.invert());
    result = result.transform(world.invert());
    result /= result.w;
    return GMVector3D(result.x, result.y, result.z);
    
}


