//
//  GMDrawSys.cpp
//  Karakuri2 Mac
//
//  Created by Numata Satoshi on 11/09/06.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMDrawSys.h"
#include "GMGlobals.h"

#include <iostream>

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#else
#include <OpenGL/glu.h>
#endif


static GMBlendMode  sGMBlendMode = GMBlendModeAlpha;
static GMIndexBuffer*   sGMIndexBuffer = NULL;
static GMVertexBuffer*  sGMVertexBuffer = NULL;


#pragma mark -
#pragma mark <<<< GMIndexBuffer クラスの実装 >>>>

GMIndexBuffer::GMIndexBuffer()
{
    glGenBuffers(1, &mIndexBuffer);
}

GMIndexBuffer::~GMIndexBuffer()
{
    glDeleteBuffers(1, &mIndexBuffer);
}

void GMIndexBuffer::setData(unsigned short* data, int startIndex, int elementCount)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * elementCount, data + startIndex, GL_STATIC_DRAW);
}


#pragma mark -
#pragma mark <<<< GMVertexBuffer クラスの実装 >>>>

GMVertexBuffer::GMVertexBuffer()
{
    glGenBuffers(1, &mVertexBuffer);
}

GMVertexBuffer::~GMVertexBuffer()
{
    glDeleteBuffers(1, &mVertexBuffer);
}

void GMVertexBuffer::setData(GMVertexDataVC* data, int startIndex, int elementCount)
{
    mDataType = __GMVertexDataTypeVC;
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GMVertexDataVC) * elementCount, data + startIndex, GL_DYNAMIC_DRAW);
}

void GMVertexBuffer::setData(GMVertexDataVT* data, int startIndex, int elementCount)
{
    mDataType = __GMVertexDataTypeVT;
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GMVertexDataVT) * elementCount, data + startIndex, GL_DYNAMIC_DRAW);
}

void GMVertexBuffer::setData(GMVertexDataVCT* data, int startIndex, int elementCount)
{
    mDataType = __GMVertexDataTypeVCT;
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GMVertexDataVCT) * elementCount, data + startIndex, GL_DYNAMIC_DRAW);
}

void GMVertexBuffer::setData(GMVertexDataVNT* data, int startIndex, int elementCount)
{
    mDataType = __GMVertexDataTypeVNT;
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GMVertexDataVNT) * elementCount, data + startIndex, GL_DYNAMIC_DRAW);
}


#pragma mark -
#pragma mark <<<< GMDrawSys クラスの実装 >>>>

void GMDrawSys::DrawPrimitives(GMPrimitiveType type, int startIndex, int primitiveCount)
{
    // TODO: GMDrawSys::DrawPrimitives() の実装
    std::cerr << "GMDrawSys::DrawPrimitives() is not implemented!!" << std::endl;
}

void GMDrawSys::SetVertexBuffer(GMVertexBuffer* vertexBuffer)
{
    sGMVertexBuffer = vertexBuffer;
}

void GMDrawSys::DrawPrimitivesIndexed(GMPrimitiveType type, int startIndex, int primitiveCount)
{
    // TODO: GMDrawSys::DrawPrimitivesIndexed() の実装
    std::cerr << "GMDrawSys::DrawPrimitivesIndexed() is not implemented!!" << std::endl;
}

void GMDrawSys::SetIndexBuffer(GMIndexBuffer* indexBuffer)
{
    sGMIndexBuffer = indexBuffer;
}

void GMDrawSys::DrawPrimitivesUser(GMPrimitiveType type, GMVertexDataVC* data, int startIndex, int primitiveCount)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    // 頂点の座標
    unsigned char* p = (unsigned char*)data;
    glVertexPointer(3, GL_FLOAT, sizeof(GMVertexDataVC), p);
    p = (unsigned char*)(((GLfloat*)p) + 3);
    
    // 頂点のカラー
    glColorPointer(4, GL_FLOAT, sizeof(GMVertexDataVC), p);
    p = (unsigned char*)(((GLfloat*)p) + 4);
    
    // 描画の実行
    if (type == GMPrimitiveTypePointList) {
        glPointSize((GLfloat)gGMPointSize);
        glDrawArrays(GL_POINTS, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeLineList) {
        glLineWidth((GLfloat)gGMLineWidth);
        glDrawArrays(GL_LINES, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeLineStrip) {
        glLineWidth((GLfloat)gGMLineWidth);
        glDrawArrays(GL_LINE_STRIP, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeTriangleList) {
        glDrawArrays(GL_TRIANGLES, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeTriangleStrip) {
        glDrawArrays(GL_TRIANGLE_STRIP, 0, primitiveCount);
    }
    
    gGMPointSize = 0.0;
    gGMLineWidth = 0.0;
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void GMDrawSys::DrawPrimitivesUser(GMPrimitiveType type, GMVertexDataVT* data, int startIndex, int primitiveCount)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    // 頂点の座標
    unsigned char* p = (unsigned char*)data;
    glVertexPointer(3, GL_FLOAT, sizeof(GMVertexDataVT), p);
    p = (unsigned char*)(((GLfloat*)p) + 3);
    
    // 頂点のテクスチャ座標
    glTexCoordPointer(2, GL_FLOAT, sizeof(GMVertexDataVT), p);
    
    // 描画の実行
    if (type == GMPrimitiveTypePointList) {
        glPointSize((GLfloat)gGMPointSize);
        glDrawArrays(GL_POINTS, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeLineList) {
        glLineWidth((GLfloat)gGMLineWidth);
        glDrawArrays(GL_LINES, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeLineStrip) {
        glLineWidth((GLfloat)gGMLineWidth);
        glDrawArrays(GL_LINE_STRIP, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeTriangleList) {
        glDrawArrays(GL_TRIANGLES, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeTriangleStrip) {
        glDrawArrays(GL_TRIANGLE_STRIP, 0, primitiveCount);
    }
    
    gGMPointSize = 0.0;
    gGMLineWidth = 0.0;

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void GMDrawSys::DrawPrimitivesUser(GMPrimitiveType type, GMVertexDataVCT* data, int startIndex, int primitiveCount)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    // 頂点の座標
    unsigned char* p = (unsigned char*)data;
    glVertexPointer(3, GL_FLOAT, sizeof(GMVertexDataVCT), p);
    p = (unsigned char*)(((GLfloat*)p) + 3);
    
    // 頂点のカラー
    glColorPointer(4, GL_FLOAT, sizeof(GMVertexDataVCT), p);
    p = (unsigned char*)(((GLfloat*)p) + 4);
    
    // 頂点のテクスチャ座標
    glTexCoordPointer(2, GL_FLOAT, sizeof(GMVertexDataVCT), p);
    
    // 描画の実行
    if (type == GMPrimitiveTypePointList) {
        glPointSize((GLfloat)gGMPointSize);
        glDrawArrays(GL_POINTS, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeLineList) {
        glLineWidth((GLfloat)gGMLineWidth);
        glDrawArrays(GL_LINES, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeLineStrip) {
        glLineWidth((GLfloat)gGMLineWidth);
        glDrawArrays(GL_LINE_STRIP, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeTriangleList) {
        glDrawArrays(GL_TRIANGLES, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeTriangleStrip) {
        glDrawArrays(GL_TRIANGLE_STRIP, 0, primitiveCount);
    }
    
    gGMPointSize = 0.0;
    gGMLineWidth = 0.0;

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void GMDrawSys::DrawPrimitivesUser(GMPrimitiveType type, GMVertexDataVNT* data, int startIndex, int primitiveCount)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    // 頂点の座標
    unsigned char* p = (unsigned char*)data;
    glVertexPointer(3, GL_FLOAT, sizeof(GMVertexDataVNT), p);
    p = (unsigned char*)(((GLfloat*)p) + 3);
    
    // 頂点の法線ベクトル
    glNormalPointer(GL_FLOAT, sizeof(GMVertexDataVNT), p);
    p = (unsigned char*)(((GLfloat*)p) + 3);
    
    // 頂点のテクスチャ座標
    glTexCoordPointer(2, GL_FLOAT, sizeof(GMVertexDataVNT), p);
    
    // 描画の実行
    if (type == GMPrimitiveTypePointList) {
        glPointSize((GLfloat)gGMPointSize);
        glDrawArrays(GL_POINTS, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeLineList) {
        glLineWidth((GLfloat)gGMLineWidth);
        glDrawArrays(GL_LINES, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeLineStrip) {
        glLineWidth((GLfloat)gGMLineWidth);
        glDrawArrays(GL_LINE_STRIP, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeTriangleList) {
        glDrawArrays(GL_TRIANGLES, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeTriangleStrip) {
        glDrawArrays(GL_TRIANGLE_STRIP, 0, primitiveCount);
    }
    
    gGMPointSize = 0.0;
    gGMLineWidth = 0.0;

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void GMDrawSys::__DrawPrimitivesUser(GMPrimitiveType type, __GMVertexDataVCNT* data, int startIndex, int primitiveCount)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    // 頂点の座標
    unsigned char* p = (unsigned char*)data;
    glVertexPointer(3, GL_FLOAT, sizeof(__GMVertexDataVCNT), p);
    p = (unsigned char*)(((GLfloat*)p) + 3);
    
    // 頂点のカラー
    glColorPointer(4, GL_FLOAT, sizeof(__GMVertexDataVCNT), p);
    p = (unsigned char*)(((GLfloat*)p) + 4);
    
    // 頂点の法線ベクトル
    glNormalPointer(GL_FLOAT, sizeof(__GMVertexDataVCNT), p);
    p = (unsigned char*)(((GLfloat*)p) + 3);
    
    // 頂点のテクスチャ座標
    glTexCoordPointer(2, GL_FLOAT, sizeof(__GMVertexDataVCNT), p);
    
    // 描画の実行
    if (type == GMPrimitiveTypePointList) {
        glPointSize((GLfloat)gGMPointSize);
        glDrawArrays(GL_POINTS, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeLineList) {
        glLineWidth((GLfloat)gGMLineWidth);
        glDrawArrays(GL_LINES, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeLineStrip) {
        glLineWidth((GLfloat)gGMLineWidth);
        glDrawArrays(GL_LINE_STRIP, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeTriangleList) {
        glDrawArrays(GL_TRIANGLES, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeTriangleStrip) {
        glDrawArrays(GL_TRIANGLE_STRIP, 0, primitiveCount);
    }
    
    gGMPointSize = 0.0;
    gGMLineWidth = 0.0;

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

GMBlendMode GMDrawSys::GetBlendMode()
{
    return sGMBlendMode;
}

void GMDrawSys::SetBlendMode(GMBlendMode mode)
{
    if (sGMBlendMode == mode) {
        return;
    }
    
    // アルファブレンディングの設定の反映
    sGMBlendMode = mode;
    switch (sGMBlendMode) {
        case GMBlendModeCopy:
            // コピー合成（単純な上書き）
            glBlendFunc(GL_ONE, GL_ZERO);
            break;
            
        case GMBlendModeInvert:
            // 反転合成
            glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
            break;
            
        case GMBlendModeXOR:
            // XOR合成
            glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_COLOR);
            break;
            
        case GMBlendModeMultiply:
            // 乗算合成
            glBlendFunc(GL_ZERO, GL_SRC_COLOR);
            break;
            
        case GMBlendModeScreen:
            // スクリーン合成
            glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE);
            break;
            
        case GMBlendModeAdd:
            // 加算合成（覆い焼き（リニア））
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            break;
            
        case GMBlendModeClear:
            // クリア
            glBlendFunc(GL_ZERO, GL_ZERO);
            break;
            
        case GMBlendModeAlpha:
        default:
            // アルファ合成
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;
    }
}



