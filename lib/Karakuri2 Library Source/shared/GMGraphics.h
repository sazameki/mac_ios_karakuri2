//
//  GMGraphics.h
//  Game Framework
//
//  Created by numata on Dec 26, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_GRAPHICS_H__
#define __GM_GRAPHICS_H__


#include "GMObject.h"
#include "GMColor.h"
#include "GMTypes.h"
#include "GMViewport.h"
#include "GMRenderTarget2D.h"


/*!
    @class      GMGraphics
    @group      Graphics
    @abstract   ビューの大きさ、ポイントスプライトの設定、デプステストの設定などを管理するためのクラスです。
    このクラスのインスタンスには、クラス変数 GMGraphics::Graphics1 または GMGraphics::Graphics2 を使ってアクセスできます。
 */
class GMGraphics : public GMObject {

    GMVector2D  mOpenGLViewFrameSize;
    
    bool        mUsesWireframe;
    bool        mIsDepthTestEnabled;
    bool        mIsScissorTestEnabled;
    
    GMViewport  mViewport;
    
    bool        mIsShaderEnabled;
    bool        mIsPointSpriteEnabled;
    
    GLuint              mCurrentMainFramebuffer;
    GMRenderTarget2D*   mRenderTarget;

public:
    /*!
        @var        CurrentGraphics
        @abstract   現在の描画のために選択されているインスタンスです。
     */
    static GMGraphics*     CurrentGraphics;
    
    /*!
        @var        Graphics1
        @abstract   メインディスプレイのためのインスタンスです。
     */
    static GMGraphics*     Graphics1;

    /*!
        @var        Graphics2
        @abstract   サブディスプレイのためのインスタンスです。
     */
    static GMGraphics*     Graphics2;
    
public:
    GMGraphics();
    
public:
    /*!
        @task   画面のクリア
     */
    /*!
        @method     clear
     */
    void    clear(const GMColor& color);

    /*!
        @task   ビューポートの操作
     */
    /*!
        @method     getScreenSize
     */
    GMVector2D  getScreenSize() const;
    
    /*!
        @method     getViewport
     */
    GMViewport  getViewport() const;
    
    /*!
        @method     setViewport
     */
    void        setViewport(const GMViewport& viewport);
    
    
    /*!
        @task   レンダリング・ターゲットの操作（未実装）
     */
    /*!
        @method     getRenderTarget
     */
    GMRenderTarget2D*   getRenderTarget() const;

    /*!
        @method     setRenderTarget
        @abstract   レンダリングターゲットを設定します。NULL を指定すると、デフォルトのレンダリングターゲットが選択されます。
     */
    void    setRenderTarget(GMRenderTarget2D* target);

    
    /*!
        @task   各種設定
     */
    
    /*!
        @method     enableDepthTest
     */
    void        enableDepthTest(bool flag);
    
    /*!
        @method     enablePointSprite
     */
    void        enablePointSprite(bool flag);
    
    /*!
        @method     enableScissorTest
     */
    void        enableScissorTest(bool flag);

    /*!
        @method     enableWireframeMode
     */
    void        enableWireframeMode(bool flag);
    
    /*!
        @method     isDepthTestEnabled
     */
    bool        isDepthTestEnabled() const;

    /*!
        @method     isPointSpriteEnabled
     */
    bool        isPointSpriteEnabled() const;
    
    /*!
        @method     isScissorTestEnabled
     */
    bool        isScissorTestEnabled() const;
    
    /*!
        @method     isShaderEnabled
     */
    bool        isShaderEnabled() const;
    
    /*!
        @method     isWireframeModeEnabled
     */
    bool        isWireframeModeEnabled() const;
    
    
public:
    void        __setOpenGLViewFrameSize(const GMVector2D& size);
    void        __setShaderEnabled(bool flag);
    void        __setCurrentMainFramebuffer(GLuint framebuffer);
    
};


#endif  //#ifndef __GM_GRAPHICS_H__


