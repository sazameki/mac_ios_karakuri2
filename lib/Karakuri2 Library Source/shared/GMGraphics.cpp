//
//  GMGraphics.cpp
//  Game Framework
//
//  Created by numata on Dec 26, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "Globals.h"

#include "GMGraphics.h"
#include "GMTexture2D.h"
#include "GMDraw.h"
#include "GMGlobals.h"
#include "GMMathHelper.h"

#include <cmath>
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


GMGraphics* GMGraphics::CurrentGraphics = NULL;
GMGraphics* GMGraphics::Graphics1 = NULL;
GMGraphics* GMGraphics::Graphics2 = NULL;


GMGraphics::GMGraphics()
{
    if (GMGraphics::Graphics1 == NULL) {
        GMGraphics::Graphics1 = this;
    } else {
        GMGraphics::Graphics2 = this;
    }
    
    mUsesWireframe = false;
    mIsDepthTestEnabled = false;
    mIsPointSpriteEnabled = false;
    mIsScissorTestEnabled = false;
    mIsShaderEnabled = false;
    
    mRenderTarget = NULL;
}



#pragma mark -
#pragma mark <<<< 画面のクリア >>>>

void GMGraphics::clear(const GMColor& color)
{
    glClearColor((float)color.r, (float)color.g, (float)color.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


#pragma mark -
#pragma mark <<<< ビューポートの操作 >>>>

GMVector2D GMGraphics::getScreenSize() const
{
#if TARGET_OS_IPHONE
    if (!GMScreenIsVertical && this == Graphics1) {
        GMVector2D ret;
        ret.x = mOpenGLViewFrameSize.y;
        ret.y = mOpenGLViewFrameSize.x;
        return ret;
    }
#endif
    return mOpenGLViewFrameSize;
}

GMViewport GMGraphics::getViewport() const
{
    return mViewport;
}

void GMGraphics::setViewport(const GMViewport& value)
{
    mViewport = value;
    glViewport(mViewport.x, mViewport.y, mViewport.width, mViewport.height);
    if (mIsScissorTestEnabled) {
        glScissor(mViewport.x, mViewport.y, mViewport.width, mViewport.height);
    }
}


#pragma mark -
#pragma mark <<<< レンダリング・ターゲットの操作 >>>>

GMRenderTarget2D* GMGraphics::getRenderTarget() const
{
    return mRenderTarget;
}

void GMGraphics::setRenderTarget(GMRenderTarget2D* target)
{
    mRenderTarget = target;
    
    if (mRenderTarget == NULL) {
        glBindFramebuffer(GL_FRAMEBUFFER, mCurrentMainFramebuffer);
    } else {
        glBindFramebuffer(GL_FRAMEBUFFER, mRenderTarget->__getFramebuffer());
    }
}

void GMGraphics::__setCurrentMainFramebuffer(GLuint framebuffer)
{
    mCurrentMainFramebuffer = framebuffer;
}


#pragma mark -
#pragma mark <<<< 各種設定 >>>>

void GMGraphics::enableDepthTest(bool flag)
{
    if (!(mIsDepthTestEnabled ^ flag)) {
        return;
    }
    mIsDepthTestEnabled = flag;
    
    if (mIsDepthTestEnabled) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

void GMGraphics::enablePointSprite(bool flag)
{
    mIsPointSpriteEnabled = flag;
}

void GMGraphics::enableScissorTest(bool flag)
{
    if (!(mIsScissorTestEnabled ^ flag)) {
        return;
    }
    mIsScissorTestEnabled = flag;
    
    if (mIsScissorTestEnabled) {
        glEnable(GL_SCISSOR_TEST);
    } else {
        glDisable(GL_SCISSOR_TEST);
    }
}

void GMGraphics::enableWireframeMode(bool flag)
{
#if TARGET_OS_IPHONE
    printf("Karakuri2-Warning: iOS does not support wireframe mode!!\n");
#else
    mUsesWireframe = flag;
    if (mUsesWireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
#endif
}

bool GMGraphics::isDepthTestEnabled() const
{
    return mIsDepthTestEnabled;
}

bool GMGraphics::isPointSpriteEnabled() const
{
    return mIsPointSpriteEnabled;
}

bool GMGraphics::isScissorTestEnabled() const
{
    return mIsScissorTestEnabled;
}

bool GMGraphics::isShaderEnabled() const
{
    return mIsShaderEnabled;
}

bool GMGraphics::isWireframeModeEnabled() const
{
    return mUsesWireframe;
}

void GMGraphics::__setOpenGLViewFrameSize(const GMVector2D& size)
{
    mOpenGLViewFrameSize = size;
    mViewport.x = 0;
    mViewport.y = 0;
    mViewport.width = (int)mOpenGLViewFrameSize.x;
    mViewport.height = (int)mOpenGLViewFrameSize.y;
}

void GMGraphics::__setShaderEnabled(bool flag)
{
    mIsShaderEnabled = flag;
}

