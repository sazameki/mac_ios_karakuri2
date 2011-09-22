//
//  GMTexture2D.h
//  Game Framework
//
//  Created by numata on Dec 26, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_TEXTURE_2D_H__
#define __GM_TEXTURE_2D_H__


#include <TargetConditionals.h>

#if TARGET_OS_IPHONE
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#else
#include <OpenGL/OpenGL.h>
#endif

#include "GMObject.h"
#include "GMColor.h"
#include "GMTypes.h"
#include "GMTexture2DLoader.h"
#include "GMLabel.h"
#include "GMException.h"

#include <string>


/*!
    @enum   GMTextureFormat
    @group  Graphics
 
    @constant   GMTextureFormat_RGBA8       各チャンネルに 8bit ずつ使用する、32bit RGBA ピクセルフォーマットです (unsigned byte)。
    @constant   GMTextureFormat_A8          8bit のアルファチャンネルのみのピクセルフォーマットです (unsigned byte)。
 */
enum GMTextureFormat {
    GMTextureFormat_RGBA8,
    GMTextureFormat_A8,
};


/*!
    @class  GMTexture2D
    @group  Graphics
    <p>2次元のテクスチャを表現するためのクラスです。</p>
    <p>このクラスは、テクスチャの描画はサポートしません。テクスチャの描画には、GMDraw クラスか GMSpriteBatch クラスを利用します。</p>
 */
class GMTexture2D : public GMObject {

    GLuint      mTexName;
    GMVector2D  mImageSize;
    GMVector2D  mImageScale;    // 2の乗数に揃えるためのスケーリング

public:
    /*!
        @task   コンストラクタ
     */
    
    /*!
        @method     GMTexture2D
        @abstract   幅と高さを指定して、32bit ARGB フォーマットのテクスチャを作成します。
        幅と高さには、2の乗数しか指定できません。
     */
    GMTexture2D(int width, int height) throw(GMInvalidOperationException, GMOutOfMemoryException);

    /*!
        @method     GMTexture2D
        @abstract   幅と高さを指定して、指定されたフォーマットのテクスチャを作成します。
        幅と高さには、2の乗数しか指定できません。
     */
    GMTexture2D(int width, int height, GMTextureFormat format) throw(GMInvalidOperationException, GMOutOfMemoryException);

    /*!
        @method     GMTexture2D
        @abstract   画像ファイルの名前を指定してテクスチャを作成します。
        第2引数に GMTexture2DScaleModeLinear か GMTexture2DScaleModeNearest を指定することで、拡大・縮小時の補完方法を指定することができます。
     */
    GMTexture2D(const std::string& imageName, GMTexture2DScaleMode mode = GMTexture2DScaleModeLinear);

    GMTexture2D(const std::string& str, const __GMFont* font);
    virtual ~GMTexture2D();

public:
    /*!
        @task   サイズ関係のメソッド
     */
    /*!
        @method     getSize
        @abstract   テクスチャのサイズをピクセル単位で取得します。
     */
    GMVector2D  getSize() const;

public:
    /*!
        @task   スケーリング関係のメソッド
     */
    /*!
        @method     getScale
        @abstract   縦横ともに、1.0を基準として何パーセントを実際のテクスチャ領域としているかを取得します（テクスチャのサイズには2の乗数しか指定できないため）
     */
    GMVector2D  getScale() const;
    
    /*!
        @method     setScale
        @abstract   縦横ともに、1.0を基準として何パーセントを実際のテクスチャ領域としているかを設定します（テクスチャのサイズには2の乗数しか指定できないため）
     */
    void    setScale(const GMVector2D& scale);
    

public:
    GLuint      __getName() const;

};


#endif  //#ifndef __GM_TEXTURE_2D_H__


