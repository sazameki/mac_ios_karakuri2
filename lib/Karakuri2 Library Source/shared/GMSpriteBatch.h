//
//  GMSpriteBatch.h
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_SPRITE_BATCH_H__
#define __GM_SPRITE_BATCH_H__


#include "GMObject.h"
#include "GMTexture2D.h"
#include "GMTypes.h"
#include "GMDraw.h"
#include "GMGraphics.h"
#include "GMBasicEffect.h"

#include <list>


enum GMSpriteFlip {
    GMSpriteFlipNone,
    GMSpriteFlipHorizontally,
    GMSpriteFlipVertically,
};

/*!
    @enum       GMSpriteSortMode
    @group      Graphics
    @abstract   スプライト描画のソート方法を指定する定数です。
    @constant   GMSpriteSortModeImmediate       バッチ処理を行わず、即座に描画が行われます。
    @constant   GMSpriteSortModeDeferred        描画命令を発行した順に描画が行われます。（デフォルト）
    @constant   GMSpriteSortModeTexture         テクスチャによって描画順をソートします。
    @constant   GMSpriteSortModeBackToFront     layerDepth指定による深さで逆順にソートします。
    @constant   GMSpriteSortModeFrontToBack     layerDepth指定による深さでソートします。
 */
enum GMSpriteSortMode {
    GMSpriteSortModeImmediate,
    GMSpriteSortModeDeferred,
    GMSpriteSortModeTexture,
    GMSpriteSortModeBackToFront,
    GMSpriteSortModeFrontToBack,
};


struct GMSprite : public GMObject {
    
    GMTexture2D*    tex;
    GMRect2D        destRect;
    GMRect2D        srcRect;
    GMColor         color;
    double          rotation;
    GMVector2D      origin;
    GMSpriteFlip    flip;
    double          layerDepth;
    unsigned        count;
    
public:
    GMSprite(GMTexture2D* tex, const GMRect2D& destRect, const GMRect2D& srcRect, const GMColor& color,
             double rotation, const GMVector2D& origin, GMSpriteFlip flip, double layerDepth, unsigned count);
    
};


/*!
    @class  GMSpriteBatch
    @group  Graphics
    <p><strong>GMSpriteBatch クラスのオブジェクトを使用した描画は、GMBasicEffect クラスのオブジェクトの begin()〜end() の呼び出し内で行う必要があります。</strong></p>
    <p>このクラスのインスタンスは、GMScene クラスのサブクラスの willAppear() メソッドが呼ばれたときに new して作成してください。</p>
    <p>実際の OpenGL / OpenGL ES の描画命令の発行は、GMDraw クラスを介して、GMDrawSys クラスによって行われます。</p>
 */
class GMSpriteBatch : public GMObject {
    
    GMSpriteSortMode        mSortMode;
    std::list<GMSprite*>    mSpriteList;
    int                     mDrawCount;
    GMMatrix                mTransformMatrix;
    
    bool    mHasBegun;

public:
    /*!
        @task   コンストラクタ
     */
    
    /*!
        @method     GMSpriteBatch
     */
    GMSpriteBatch();
    
public:
    /*!
        @task   描画の開始と終了
     */
    
    /*!
        @method     begin
     */
    void    begin(GMSpriteSortMode sortMode = GMSpriteSortModeDeferred, const GMMatrix& transform = GMMatrix::Identity);

    /*!
        @method     end
     */
    void    end();
    
    /*!
        @task   矩形を指定する描画
     */

    /*!
        @method     draw
     */
    void    draw(GMTexture2D* tex, const GMRect2D& destRect, const GMColor& color = GMColor::White, double layerDepth = 0.0);
    
    /*!
        @method     draw
     */
    void    draw(GMTexture2D* tex, const GMRect2D& destRect, const GMRect2D& srcRect, const GMColor& color = GMColor::White, double layerDepth = 0.0);
    
    /*!
        @method     draw
     */
    void    draw(GMTexture2D* tex, const GMRect2D& destRect, const GMRect2D& srcRect, const GMColor& color, double rotation, const GMVector2D& origin, GMSpriteFlip flip, double layerDepth);

    /*!
        @task   位置を指定する描画
     */
    
    /*!
        @method     draw
     */
    void    draw(GMTexture2D* tex, const GMVector2D& pos, const GMColor& color = GMColor::White, double layerDepth = 0.0);
    
    /*!
        @method     draw
     */
    void    draw(GMTexture2D* tex, const GMVector2D& pos, const GMRect2D& srcRect, const GMColor& color = GMColor::White, double layerDepth = 0.0);
    
    /*!
        @method     draw
     */
    void    draw(GMTexture2D* tex, const GMVector2D& pos, const GMRect2D& srcRect, const GMColor& color, double rotation, const GMVector2D& origin, const GMVector2D& scale, GMSpriteFlip flip, double layerDepth);
    
private:
    void    __applyGraphicsSettings();
    void    __flushBatchDraws();
    
};


#endif  //#ifndef __GM_SPRITE_BATCH_H__


