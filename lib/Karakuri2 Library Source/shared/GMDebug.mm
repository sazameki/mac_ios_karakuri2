//
//  GMDebug.cpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMDebug.h"
//#import "GMTestCase.h"


void GMDebug::output(const GMVector2D& vec, const std::string& title)
{
    printf("\n");
    if (title.length() > 0) {
        printf("[%s] ", title.c_str());
    }
    
    printf("%4.3f, %4.3f (vec2)\n", vec.x, vec.y);
}

void GMDebug::output(const GMVector3D& vec, const std::string& title)
{
    printf("\n");
    if (title.length() > 0) {
        printf("[%s] ", title.c_str());
    }
    
    printf("%4.3f, %4.3f, %4.3f (vec3)\n", vec.x, vec.y, vec.z);    
}

void GMDebug::output(const GMVector4D& vec, const std::string& title)
{
    printf("\n");
    if (title.length() > 0) {
        printf("[%s] ", title.c_str());
    }
    
    printf("%4.3f, %4.3f, %4.3f, %4.3f (vec4)\n", vec.x, vec.y, vec.z, vec.w);    
}

void GMDebug::output(const GMMatrix& mat, const std::string& title)
{
    outputGLMatrix(mat.mat, title);
}

void GMDebug::output(const GMQuat& quat, const std::string& title)
{
    printf("\n");
    if (title.length() > 0) {
        printf("[%s] ", title.c_str());
    }
    
    printf("%4.3f, %4.3f, %4.3f, %4.3f (quat)\n", quat.x, quat.y, quat.z, quat.w);    
}

void GMDebug::output(const GMRect2D& rect, const std::string& title)
{
    printf("\n");
    if (title.length() > 0) {
        printf("[%s] ", title.c_str());
    }
    
    printf("%4.3f, %4.3f, %4.3f, %4.3f (quat)\n", rect.x, rect.y, rect.width, rect.height);    
}

void GMDebug::outputGLMatrix(GLenum matrixType, const std::string& title)
{
    GLfloat m[16];
    glGetFloatv(matrixType, m);
    outputGLMatrix(m, title);
}

void GMDebug::outputGLMatrix(const GLfloat* m, const std::string& title)
{
    /*
    if (title.length() > 0) {
        GMTestLog("[%s]", title.c_str());
    }
    
    GMTestLog("    %+4.3f   %+4.3f   %+4.3f   %+4.3f : 0-3", m[0], m[1], m[2],  m[3]);
    GMTestLog("    %+4.3f   %+4.3f   %+4.3f   %+4.3f : 4-7", m[4], m[5], m[6],  m[7]);
    GMTestLog("    %+4.3f   %+4.3f   %+4.3f   %+4.3f : 8-11", m[8], m[9], m[10], m[11]);
    GMTestLog("    %+4.3f   %+4.3f   %+4.3f   %+4.3f : 12-15", m[12], m[13], m[14], m[15]);
    GMTestLog("    (matrix)");
     */
}


#if !TARGET_OS_IPHONE

void GMDebug::outputGLMatrix(const GLdouble* m, const std::string& title)
{
    /*
    if (title.length() > 0) {
        GMTestLog("[%s]", title.c_str());
    }
    
    GMTestLog("    %+4.3f   %+4.3f   %+4.3f   %+4.3f : 0-3", m[0], m[1], m[2],  m[3]);
    GMTestLog("    %+4.3f   %+4.3f   %+4.3f   %+4.3f : 4-7", m[4], m[5], m[6],  m[7]);
    GMTestLog("    %+4.3f   %+4.3f   %+4.3f   %+4.3f : 8-11", m[8], m[9], m[10], m[11]);
    GMTestLog("    %+4.3f   %+4.3f   %+4.3f   %+4.3f : 12-15", m[12], m[13], m[14], m[15]);
    GMTestLog("    (matrix)");
     */
}

#endif
