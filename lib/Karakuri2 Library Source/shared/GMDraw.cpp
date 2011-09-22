//
//  GMDraw.cpp
//  Game Framework
//
//  Created by numata on Dec 26, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMDraw.h"
#include "GMDrawSys.h"
#include "GMColor.h"
#include "GMGlobals.h"
#include "GMTexture2D.h"
#include "GMGraphics.h"
#include "GMException.h"
#include "GMBasicEffect.h"

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



static __GMVertexDataVCNT   sGMBatchDrawVertexes[GM_DRAW_BATCH_SIZE * 6];
static GMPrimitiveType      sGMBatchPrimitiveType = __GMPrimitiveTypeNone;
static int                  sGMBatchPrimitiveCount = 0;


void GMDraw::Begin()
{
    if (gGMIsDrawing) {
        throw GMInvalidOperationException("GMDraw::begin() should not be invoked before GMDraw::end() is called.");
    }
    gGMIsDrawing = true;
}

void GMDraw::End()
{
    if (!gGMIsDrawing) {
        throw GMInvalidOperationException("GMDraw::end() should not be invoked after GMDraw::begin().");
    }

    __FlushBatchDraws();
    
    gGMIsDrawing = false;
}

void GMDraw::__FlushBatchDraws()
{
    // バッチ処理の存在をチェックしておく
    if (sGMBatchPrimitiveCount == 0) {
        return;
    }
    
    // ポイントスプライト使用の確認
    bool doPointSprite = false;
    if (sGMBatchPrimitiveType == GMPrimitiveTypePointList) {
        bool pointSpriteEnabled = GMGraphics::CurrentGraphics->isPointSpriteEnabled();
        GMBasicEffect* effect = (GMBasicEffect*)GMEffect::CurrentEffect;
        bool textureEnabled = effect->isTextureEnabled();
        if (pointSpriteEnabled & textureEnabled) {
            doPointSprite = true;
        }
    }
    
    // ポイントスプライトの有効化
    if (doPointSprite) {
#if TARGET_OS_IPHONE
        glEnable(GL_POINT_SPRITE_OES);
        glTexEnvi(GL_POINT_SPRITE_OES, GL_COORD_REPLACE_OES, GL_TRUE);
#else
        glEnable(GL_POINT_SPRITE);
        glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
#endif
    }

    // 頂点配列による描画の実行
    GMDrawSys::__DrawPrimitivesUser(sGMBatchPrimitiveType, sGMBatchDrawVertexes, 0, sGMBatchPrimitiveCount);
    
    // ポイントスプライトの無効化
    if (doPointSprite) {
#if TARGET_OS_IPHONE
        glDisable(GL_POINT_SPRITE_OES);
#else
        glDisable(GL_POINT_SPRITE);
#endif
    }

    // バッチ処理の終了
    sGMBatchPrimitiveType = __GMPrimitiveTypeNone;
    sGMBatchPrimitiveCount = 0;
}

void GMDraw::DrawPoint(const GMVector2D& pos, const GMColor& color, double size)
{
    DrawPoint(GMVector3D(pos, 0.0), color, size);
}

void GMDraw::DrawPoint(const GMVector3D& pos, const GMColor& color, double size)
{
    if (!gGMIsDrawing) {
        throw GMInvalidOperationException("GMDraw::begin() should be invoked before calling drawing methods.");
    }
    
    // 色と点の大きさの決定
    GMColor theColor = color;
    if (GMGraphics::CurrentGraphics->isWireframeModeEnabled()) {
        size = 1.0;
        theColor = GMColor::White;
    }
    
    // 異なる設定のプリミティブを描画する場合には、前のプリミティブ描画を掃き出しておく
    if (sGMBatchPrimitiveType != GMPrimitiveTypePointList) {
        __FlushBatchDraws();
        sGMBatchPrimitiveType = GMPrimitiveTypePointList;
        if (gGMPointSize != size) {
            gGMPointSize = size;
        }
    } else if (gGMPointSize != size) {
        __FlushBatchDraws();
        gGMPointSize = size;
    }
    
    // 頂点配列データの格納
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vx = (GLfloat)pos.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vy = (GLfloat)pos.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vz = (GLfloat)pos.z;

    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cr = theColor.r;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cg = theColor.g;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cb = theColor.b;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ca = theColor.a;
    
    // 次のバッチ処理へ
    sGMBatchPrimitiveCount++;
}

void GMDraw::DrawLine(const GMVector2D& p1, const GMVector2D& p2, const GMColor& color, double width)
{
    DrawLine(GMVector3D(p1, 0), GMVector3D(p2, 0), color, color, width);
}

void GMDraw::DrawLine(const GMVector2D& p1, const GMVector2D& p2, const GMColor& c1, const GMColor& c2, double width)
{
    DrawLine(GMVector3D(p1, 0), GMVector3D(p2, 0), c1, c2, width);
}

void GMDraw::DrawLine(const GMVector3D& p1, const GMVector3D& p2, const GMColor& color, double width)
{
    DrawLine(p1, p2, color, color, width);
}

void GMDraw::FillTriangle(const GMVector2D& p1, const GMVector2D& p2, const GMVector2D& p3,
                          const GMColor& color,
                          const GMVector2D& t1, const GMVector2D& t2, const GMVector2D& t3)
{
    __FillTriangle(GMVector3D(p1, 0), GMVector3D(p2, 0), GMVector3D(p3, 0),
                   GMVector3D(0, 0, 1), GMVector3D(0, 0, 1), GMVector3D(0, 0, 1),
                   color, color, color,
                   t1, t2, t3);
}

void GMDraw::FillTriangle(const GMVector2D& p1, const GMVector2D& p2, const GMVector2D& p3,
                          const GMColor& c1, const GMColor& c2, const GMColor& c3,
                          const GMVector2D& t1, const GMVector2D& t2, const GMVector2D& t3)
{
    __FillTriangle(GMVector3D(p1, 0), GMVector3D(p2, 0), GMVector3D(p3, 0),
                   GMVector3D(0, 0, 1), GMVector3D(0, 0, 1), GMVector3D(0, 0, 1),
                   c1, c2, c3,
                   t1, t2, t3);
}

void GMDraw::FillTriangle(const GMVector3D& p1, const GMVector3D& p2, const GMVector3D& p3,
                          const GMVector3D& n1, const GMVector3D& n2, const GMVector3D& n3,
                          const GMVector2D& t1, const GMVector2D& t2, const GMVector2D& t3)
{
    GMColor color = GMColor::White;
    __FillTriangle(p1, p2, p3, n1, n2, n3, color, color, color, t1, t2, t3);
}

void GMDraw::FillQuad(const GMVector2D& p1, const GMVector2D& p2, const GMVector2D& p3, const GMVector2D& p4,
                      const GMColor& color,
                      const GMVector2D& t1, const GMVector2D& t2, const GMVector2D& t3, const GMVector2D& t4)
{
    __FillQuad(GMVector3D(p1, 0), GMVector3D(p2, 0), GMVector3D(p3, 0), GMVector3D(p4, 0),
               GMVector3D(0, 0, 1), GMVector3D(0, 0, 1), GMVector3D(0, 0, 1), GMVector3D(0, 0, 1),
               color, color, color, color,
               t1, t2, t3, t4);
}

void GMDraw::FillQuad(const GMVector2D& p1, const GMVector2D& p2, const GMVector2D& p3, const GMVector2D& p4,
                      const GMColor& c1, const GMColor& c2, const GMColor& c3, const GMColor& c4,
                      const GMVector2D& t1, const GMVector2D& t2, const GMVector2D& t3, const GMVector2D& t4)
{
    __FillQuad(GMVector3D(p1, 0), GMVector3D(p2, 0), GMVector3D(p3, 0), GMVector3D(p4, 0),
               GMVector3D(0, 0, 1), GMVector3D(0, 0, 1), GMVector3D(0, 0, 1), GMVector3D(0, 0, 1),
               c1, c2, c3, c4,
               t1, t2, t3, t4);
}

void GMDraw::FillQuad(const GMVector3D& p1, const GMVector3D& p2, const GMVector3D& p3, const GMVector3D& p4,
                      const GMVector3D& n1, const GMVector3D& n2, const GMVector3D& n3, const GMVector3D& n4,
                      const GMVector2D& t1, const GMVector2D& t2, const GMVector2D& t3, const GMVector2D& t4)
{
    GMColor color = GMColor::White;
    __FillQuad(p1, p2, p3, p4,
               n1, n2, n3, n4,
               color, color, color, color,
               t1, t2, t3, t4);
}

void GMDraw::DrawLine(const GMVector3D& p1, const GMVector3D& p2, const GMColor& c1, const GMColor& c2, double width)
{
    if (!gGMIsDrawing) {
        throw GMInvalidOperationException("GMDraw::begin() should be invoked before calling drawing methods.");
    }
    
    // 色と線幅の決定
    GMColor theC1 = c1;
    GMColor theC2 = c2;
    if (GMGraphics::CurrentGraphics->isWireframeModeEnabled()) {
        width = 1.0;
        theC1 = GMColor::White;
        theC2 = GMColor::White;
    }
    
    // 異なる設定のプリミティブを描画する場合には、前のプリミティブ描画を掃き出しておく
    if (sGMBatchPrimitiveType != GMPrimitiveTypeLineList) {
        __FlushBatchDraws();
        sGMBatchPrimitiveType = GMPrimitiveTypeLineList;
        if (gGMLineWidth != width) {
            gGMLineWidth = width;
        }
    } else if (gGMLineWidth != width) {
        __FlushBatchDraws();
        gGMLineWidth = width;
    }

    // 頂点配列データの格納 1
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vx = (GLfloat)p1.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vy = (GLfloat)p1.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vz = (GLfloat)p1.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cr = (GLfloat)theC1.r;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cg = (GLfloat)theC1.g;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cb = (GLfloat)theC1.b;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ca = (GLfloat)theC1.a;
    sGMBatchPrimitiveCount++;

    // 頂点配列データの格納 2
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vx = (GLfloat)p2.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vy = (GLfloat)p2.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vz = (GLfloat)p2.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cr = (GLfloat)theC2.r;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cg = (GLfloat)theC2.g;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cb = (GLfloat)theC2.b;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ca = (GLfloat)theC2.a;
    sGMBatchPrimitiveCount++;
}

void GMDraw::__FillTriangle(const GMVector3D& p1, const GMVector3D& p2, const GMVector3D& p3,
                          const GMVector3D& n1, const GMVector3D& n2, const GMVector3D& n3,
                          const GMColor& c1, const GMColor& c2, const GMColor& c3,
                          const GMVector2D& t1, const GMVector2D& t2, const GMVector2D& t3)
{
    if (!gGMIsDrawing) {
        throw GMInvalidOperationException("GMDraw::begin() should be invoked before calling drawing methods.");
    }
    
    
    // 異なる設定のプリミティブを描画する場合には、前のプリミティブ描画を掃き出しておく
    if (sGMBatchPrimitiveType != GMPrimitiveTypeTriangleList) {
        __FlushBatchDraws();
        sGMBatchPrimitiveType = GMPrimitiveTypeTriangleList;
    }

    // 色の決定
    GMColor theC1 = c1;
    GMColor theC2 = c2;
    GMColor theC3 = c3;
    if (GMGraphics::CurrentGraphics->isWireframeModeEnabled()) {
        theC1 = GMColor::White;
        theC2 = GMColor::White;
        theC3 = GMColor::White;
    }
    
    // 頂点配列データの格納 1
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vx = (GLfloat)p1.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vy = (GLfloat)p1.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vz = (GLfloat)p1.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cr = (GLfloat)theC1.r;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cg = (GLfloat)theC1.g;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cb = (GLfloat)theC1.b;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ca = (GLfloat)theC1.a;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nx = (GLfloat)n1.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ny = (GLfloat)n1.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nz = (GLfloat)n1.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].tx = (GLfloat)t1.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ty = (GLfloat)(1.0 - t1.y);
    sGMBatchPrimitiveCount++;
    
    // 頂点配列データの格納 2
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vx = (GLfloat)p2.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vy = (GLfloat)p2.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vz = (GLfloat)p2.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cr = (GLfloat)theC2.r;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cg = (GLfloat)theC2.g;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cb = (GLfloat)theC2.b;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ca = (GLfloat)theC2.a;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nx = (GLfloat)n2.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ny = (GLfloat)n2.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nz = (GLfloat)n2.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].tx = (GLfloat)t2.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ty = (GLfloat)(1.0 - t2.y);
    sGMBatchPrimitiveCount++;

    // 頂点配列データの格納 3
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vx = (GLfloat)p3.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vy = (GLfloat)p3.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vz = (GLfloat)p3.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cr = (GLfloat)theC3.r;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cg = (GLfloat)theC3.g;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cb = (GLfloat)theC3.b;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ca = (GLfloat)theC3.a;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nx = (GLfloat)n3.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ny = (GLfloat)n3.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nz = (GLfloat)n3.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].tx = (GLfloat)t3.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ty = (GLfloat)(1.0 - t3.y);
    sGMBatchPrimitiveCount++;
}

void GMDraw::__FillQuad(const GMVector3D& p1, const GMVector3D& p2, const GMVector3D& p3, const GMVector3D& p4,
                      const GMVector3D& n1, const GMVector3D& n2, const GMVector3D& n3, const GMVector3D& n4,
                      const GMColor& c1, const GMColor& c2, const GMColor& c3, const GMColor& c4,
                      const GMVector2D& t1, const GMVector2D& t2, const GMVector2D& t3, const GMVector2D& t4)
{
    if (!gGMIsDrawing) {
        throw GMInvalidOperationException("GMDraw::begin() should be invoked before calling drawing methods.");
    }
    
    // 異なる設定のプリミティブを描画する場合には、前のプリミティブ描画を掃き出しておく
    if (sGMBatchPrimitiveType != GMPrimitiveTypeTriangleList) {
        __FlushBatchDraws();
        sGMBatchPrimitiveType = GMPrimitiveTypeTriangleList;
    }

    // 色の決定
    GMColor theC1 = c1;
    GMColor theC2 = c2;
    GMColor theC3 = c3;
    GMColor theC4 = c4;
    if (GMGraphics::CurrentGraphics->isWireframeModeEnabled()) {
        theC1 = GMColor::White;
        theC2 = GMColor::White;
        theC3 = GMColor::White;
        theC4 = GMColor::White;
    }
    
    // 頂点配列データの格納 1
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vx = (GLfloat)p1.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vy = (GLfloat)p1.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vz = (GLfloat)p1.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cr = (GLfloat)theC1.r;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cg = (GLfloat)theC1.g;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cb = (GLfloat)theC1.b;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ca = (GLfloat)theC1.a;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nx = (GLfloat)n1.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ny = (GLfloat)n1.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nz = (GLfloat)n1.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].tx = (GLfloat)t1.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ty = (GLfloat)(1.0 - t1.y);
    sGMBatchPrimitiveCount++;

    // 頂点配列データの格納 2
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vx = (GLfloat)p2.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vy = (GLfloat)p2.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vz = (GLfloat)p2.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cr = (GLfloat)theC2.r;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cg = (GLfloat)theC2.g;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cb = (GLfloat)theC2.b;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ca = (GLfloat)theC2.a;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nx = (GLfloat)n2.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ny = (GLfloat)n2.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nz = (GLfloat)n2.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].tx = (GLfloat)t2.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ty = (GLfloat)(1.0 - t2.y);
    sGMBatchPrimitiveCount++;

    // 頂点配列データの格納 3
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vx = (GLfloat)p4.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vy = (GLfloat)p4.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vz = (GLfloat)p4.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cr = (GLfloat)theC4.r;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cg = (GLfloat)theC4.g;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cb = (GLfloat)theC4.b;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ca = (GLfloat)theC4.a;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nx = (GLfloat)n4.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ny = (GLfloat)n4.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nz = (GLfloat)n4.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].tx = (GLfloat)t4.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ty = (GLfloat)(1.0 - t4.y);
    sGMBatchPrimitiveCount++;

    // 頂点配列データの格納 4
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount] = sGMBatchDrawVertexes[sGMBatchPrimitiveCount-1];
    sGMBatchPrimitiveCount++;
    
    // 頂点配列データの格納 5
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount] = sGMBatchDrawVertexes[sGMBatchPrimitiveCount-3];
    sGMBatchPrimitiveCount++;

    // 頂点配列データの格納 6
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vx = (GLfloat)p3.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vy = (GLfloat)p3.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vz = (GLfloat)p3.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cr = (GLfloat)theC3.r;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cg = (GLfloat)theC3.g;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cb = (GLfloat)theC3.b;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ca = (GLfloat)theC3.a;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nx = (GLfloat)n3.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ny = (GLfloat)n3.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nz = (GLfloat)n3.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].tx = (GLfloat)t3.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ty = (GLfloat)(1.0 - t3.y);
    sGMBatchPrimitiveCount++;
}

