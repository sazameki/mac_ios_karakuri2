//
//  GMRect2D.cpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMRect2D.h"

#include "GMMathHelper.h"
#include "GMVector2D.h"

#include <algorithm>
#include <cmath>


const GMRect2D& GMRect2D::Empty     = GMRect2D(0.0, 0.0, 0.0, 0.0);


GMRect2D::GMRect2D()
    : x(0.0), y(0.0), width(0.0), height(0.0)
{
    // Do nothing
}

GMRect2D::GMRect2D(double x_, double y_, double width_, double height_)
    : x(x_), y(y_), width(width_), height(height_)
{
    // Do nothing
}

GMRect2D::GMRect2D(const GMVector2D& pos, const GMVector2D& size)
    : x(pos.x), y(pos.y), width(size.x), height(size.y)
{
    // Do nothing
}

GMRect2D::GMRect2D(const GMRect2D& rect)
    : x(rect.x), y(rect.y), width(rect.width), height(rect.height)
{
    // Do nothing
}

GMRect2D& GMRect2D::operator=(const GMRect2D& rect)
{
    x = rect.x;
    y = rect.y;
    width = rect.width;
    height = rect.height;
    return *this;
}

bool GMRect2D::operator==(const GMRect2D& rect) const
{
    return equals(rect, GMMathHelper::DoubleEqThreshold);
}

bool GMRect2D::operator!=(const GMRect2D& rect) const
{
    return !equals(rect, GMMathHelper::DoubleEqThreshold);
}

bool GMRect2D::equals(const GMRect2D& rect, double accuracy) const
{
    return (fabs(x - rect.x) < accuracy &&
            fabs(y - rect.y) < accuracy &&
            fabs(width - rect.width) < accuracy &&
            fabs(height - rect.height) < accuracy)? true: false;    
}

bool GMRect2D::contains(const GMVector2D& pos) const
{
    double theMinX = minX();
    double theMinY = minY();
    double theMaxX = maxX();
    double theMaxY = maxY();
    
    return (pos.x >= theMinX && pos.y >= theMinY &&
            pos.x <= theMaxX && pos.y <= theMaxY);
}

bool GMRect2D::contains(const GMRect2D& rect) const
{
    double theMinX = minX();
    double theMinY = minY();
    double theMaxX = maxX();
    double theMaxY = maxY();

    double targetMinX = rect.minX();
    double targetMinY = rect.minY();
    double targetMaxX = rect.maxX();
    double targetMaxY = rect.maxY();
    
    return (targetMinX >= theMinX && targetMinY >= theMinY &&
            targetMaxX <= theMaxX && targetMaxY <= theMaxY);
}

GMRect2D& GMRect2D::inflate(double h, double v)
{
    x -= h;
    y -= v;
    width += h * 2;
    height += v * 2;
    return *this;
}

GMRect2D GMRect2D::intersect(const GMRect2D& rect) const
{
    double x1 = std::max(minX(), rect.minX());
    double y1 = std::max(minY(), rect.minY());
    double x2 = std::min(maxX(), rect.maxX());
    double y2 = std::min(maxY(), rect.maxY());
    
    return GMRect2D(x1, y1, x2 - x1, y2 - y1);
}

bool GMRect2D::intersects(const GMRect2D& rect) const
{
    double minX1 = minX();
    double minY1 = minY();
    double maxX1 = maxX();
    double maxY1 = maxY();

    double minX2 = rect.minX();
    double minY2 = rect.minY();
    double maxX2 = rect.maxX();
    double maxY2 = rect.maxY();
    
    return (minX1 < maxX2 && maxX1 > minX2 &&
            minY1 < maxY2 && maxY1 > minY2);
}

double GMRect2D::maxX() const
{
    return std::max(x, x + width);
}

double GMRect2D::maxY() const
{
    return std::max(y, y + height);
}

double GMRect2D::minX() const
{
    return std::min(x, x + width);
}

double GMRect2D::minY() const
{
    return std::min(y, y + height);
}

GMRect2D& GMRect2D::offset(const GMVector2D& pos)
{
    x = pos.x;
    y = pos.y;
    return *this;
}

GMRect2D GMRect2D::unionRect(const GMRect2D& rect) const
{
    double theMinX = std::min(minX(), rect.minX());
    double theMaxX = std::max(maxX(), rect.maxX());
    double theMinY = std::min(minY(), rect.minY());
    double theMaxY = std::max(maxY(), rect.maxY());
    
    return GMRect2D(theMinX, theMinY, theMaxX - theMinX, theMaxY - theMinY);
}

