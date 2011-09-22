//
//  GMTexture2DLoader.h
//  Game Framework
//
//  Created by numata on Dec 31, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_TEXTURE_2D_LOADER_H__
#define __GM_TEXTURE_2D_LOADER_H__


#include <OpenGL/OpenGL.h>
#include <string>
#include "GMTypes.h"


enum GMTexture2DScaleMode {
    GMTexture2DScaleModeLinear,
    GMTexture2DScaleModeNearest,
};


GLuint __GMTexture2DLoad(const std::string& imageNameCpp, GMTexture2DScaleMode scaleMode, GMVector2D* imageSize, GLushort* resizedWidth, GLushort* resizedHeight);
GLuint __GMTexture2DCreateFromString(const std::string& str, void* nsFont, GMVector2D* imageSize, GLushort* resizedWidth, GLushort* resizedHeight);


#endif  //#ifndef __GM_TEXTURE_2D_LOADER_H__


