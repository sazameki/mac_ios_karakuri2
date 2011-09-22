//
//  GMDebug.h
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_DEBUG_H__
#define __GM_DEBUG_H__

#include <TargetConditionals.h>

#include <string>

#if TARGET_OS_IPHONE
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#else
#include <OpenGL/OpenGL.h>
#endif

#include "GMTypes.h"


class GMDebug {
    
public:
    static void     output(const GMVector2D& vec, const std::string& title = "");
    static void     output(const GMVector3D& vec, const std::string& title = "");
    static void     output(const GMVector4D& vec, const std::string& title = "");
    static void     output(const GMMatrix& mat, const std::string& title = "");
    static void     output(const GMQuat& quat, const std::string& title = "");
    static void     output(const GMRect2D& rect, const std::string& title = "");
    
    static void     outputGLMatrix(GLenum matrixType, const std::string& title = "");
    static void     outputGLMatrix(const GLfloat* m, const std::string& title = "");

#if !TARGET_OS_IPHONE
    static void     outputGLMatrix(const GLdouble* m, const std::string& title = "");
#endif

};


#endif  //#ifndef __GM_DEBUG_H__


