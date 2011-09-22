//
//  GMRenderTarget2D.h
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/09/01.
//  Copyright (c) 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_RENDER_TARGET_2D_H__
#define __GM_RENDER_TARGET_2D_H__


#include "GMTexture2D.h"
#include "GMException.h"


/*!
    @class  GMRenderTarget2D
    @group  Graphics
    @abstract レンダリングのターゲットとして使用できる2次元テクスチャを表すためのクラスです。
    GMGraphics クラスの setRenderTarget() メソッドで、このテクスチャをレンダリングの対象として設定することができます。
 */
class GMRenderTarget2D : public GMTexture2D {
    
    GLuint  mFramebuffer;
    
public:
    /*!
        @task コンストラクタ
     */
    /*!
        @method     GMRenderTarget2D
        @abstract   幅と高さを指定して、32bit RGBA のレンダリングターゲットを作成します。
     */
    GMRenderTarget2D(int width, int height) throw(GMInvalidOperationException, GMOutOfMemoryException);

    /*!
        @method     GMRenderTarget2D
        @abstract   幅と高さとフォーマットを指定して、レンダリングターゲットを作成します。
     */
    GMRenderTarget2D(int width, int height, GMTextureFormat format) throw(GMInvalidOperationException, GMOutOfMemoryException);
    
    virtual ~GMRenderTarget2D();
    
public:
    GLuint  __getFramebuffer() const;
    
};


#endif  //#ifndef __GM_RENDER_TARGET_2D_H__

