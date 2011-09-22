//
//  GMSpriteBatch.cpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMSpriteBatch.h"

#include "GMException.h"
#include "GMTexture2D.h"
#include "GMDraw.h"
#include "GMDebug.h"
#include <cmath>


GMSprite::GMSprite(GMTexture2D* tex_, const GMRect2D& destRect_, const GMRect2D& srcRect_, const GMColor& color_,
                   double rotation_, const GMVector2D& origin_, GMSpriteFlip flip_, double layerDepth_, unsigned count_)
    : tex(tex_), destRect(destRect_), srcRect(srcRect_), color(color_),
      rotation(rotation_), origin(origin_), flip(flip_), layerDepth(layerDepth_), count(count_)
{
    // Do nothing
}


GMSpriteBatch::GMSpriteBatch()
    : mDrawCount(0), mHasBegun(false)
{
    // Do nothing
}


#pragma mark ==== バッチ処理の基本 ====

void GMSpriteBatch::begin(GMSpriteSortMode sortMode, const GMMatrix& transform)
{
    mSortMode = sortMode;
    mTransformMatrix = transform;

    mSpriteList.clear();
    mDrawCount = 0;
    
    if (mSortMode == GMSpriteSortModeImmediate) {
        __applyGraphicsSettings();
    }
    
    mHasBegun = true;
}

void GMSpriteBatch::end()
{
    if (!mHasBegun) {
        throw new GMException("GMSpriteBach::end() was called without begin().");
    }

    if (mSortMode != GMSpriteSortModeImmediate) {
        __applyGraphicsSettings();
        __flushBatchDraws();
    }
}


#pragma mark ==== 描画対象の矩形を指定する関数 ====

void GMSpriteBatch::draw(GMTexture2D* tex, const GMRect2D& destRect, const GMColor& color, double layerDepth)
{
    draw(tex, destRect, GMRect2D::Empty, color, layerDepth);
}

void GMSpriteBatch::draw(GMTexture2D* tex, const GMRect2D& destRect, const GMRect2D& srcRect, const GMColor& color, double layerDepth)
{
    draw(tex, destRect, srcRect, color, 0.0, GMVector2D::Zero, GMSpriteFlipNone, layerDepth);
}

// すべての描画がこの draw() メソッドに集約されるようにする。
void GMSpriteBatch::draw(GMTexture2D* tex, const GMRect2D& destRect, const GMRect2D& srcRect, const GMColor& color,
                         double rotation, const GMVector2D& origin, GMSpriteFlip flip, double layerDepth)
{
    GMSprite* sprite = new GMSprite(tex, destRect, srcRect, color, rotation, origin, flip, layerDepth, mDrawCount++);
    mSpriteList.push_back(sprite);
    
    if (mSortMode == GMSpriteSortModeImmediate) {
        __flushBatchDraws();
    }
}


#pragma mark ==== 描画位置を指定する関数 ====

void GMSpriteBatch::draw(GMTexture2D* tex, const GMVector2D& pos, const GMColor& color, double layerDepth)
{
    draw(tex, pos, GMRect2D::Empty, color, layerDepth);
}

void GMSpriteBatch::draw(GMTexture2D* tex, const GMVector2D& pos, const GMRect2D& srcRect, const GMColor& color, double layerDepth)
{
    draw(tex, pos, srcRect, color, 0.0, GMVector2D::Zero, 1.0, GMSpriteFlipNone, layerDepth);
}

void GMSpriteBatch::draw(GMTexture2D* tex, const GMVector2D& pos, const GMRect2D& srcRect, const GMColor& color,
                         double rotation, const GMVector2D& origin, const GMVector2D& scale, GMSpriteFlip flip, double layerDepth)
{
    GMRect2D destRect;
    destRect.x = pos.x;
    destRect.y = pos.y;
    if (srcRect.width == 0.0 || srcRect.height == 0.0) {
        GMVector2D texSize = tex->getSize();
        destRect.width = (double)((int)(texSize.x * scale.x));
        destRect.height = (double)((int)(texSize.y * scale.y));
    } else {
        destRect.width = (double)((int)(srcRect.width * scale.x));
        destRect.height = (double)((int)(srcRect.height * scale.y));
    }
    
    draw(tex, destRect, srcRect, color, rotation, origin, flip, layerDepth);    
}

void GMSpriteBatch::__applyGraphicsSettings()
{
    // TODO: mTransformMatrix の反映
    //mGraphics->multiplyViewMatrix(mTransformMatrix);
}

static bool compareSpriteBackToFront(GMSprite* first, GMSprite* second)
{
    if (first->layerDepth > second->layerDepth) {
        return true;
    }
    if (first->tex->__getName() > second->tex->__getName()) {
        return true;
    }
    if (first->count < second->count) {
        return true;
    }
    return false;
}

static bool compareSpriteFrontToBack(GMSprite* first, GMSprite* second)
{
    if (first->layerDepth < second->layerDepth) {
        return true;
    }
    if (first->tex->__getName() < second->tex->__getName()) {
        return true;
    }
    if (first->count < second->count) {
        return true;
    }
    return false;
}

static bool compareSpriteTexture(GMSprite* first, GMSprite* second)
{
    if (first->tex->__getName() > second->tex->__getName()) {
        return false;
    }
    return true;    
}

void GMSpriteBatch::__flushBatchDraws()
{
    if (mSpriteList.size() == 0) {
        printf("sb: nothing to flush");
        return;
    }
    
    // スプライト描画のソート
    switch (mSortMode) {
        case GMSpriteSortModeBackToFront:
            mSpriteList.sort(compareSpriteBackToFront);
            break;
        case GMSpriteSortModeFrontToBack:
            mSpriteList.sort(compareSpriteFrontToBack);
            break;
        case GMSpriteSortModeTexture:
            mSpriteList.sort(compareSpriteTexture);
            break;
        case GMSpriteSortModeDeferred:
        case GMSpriteSortModeImmediate:
        default:
            // Do nothing
            break;
    }
    
    GMBasicEffect* effect = (GMBasicEffect*)GMEffect::CurrentEffect;
    
    // スプライト描画の実行
    GMDraw::Begin();
    effect->enableTexture(true);
    GMTexture2D* currentTex = NULL;
    for (std::list<GMSprite*>::iterator it = mSpriteList.begin(), it_end = mSpriteList.end(); it != it_end; it++) {
        GMRect2D& destRect = (*it)->destRect;
        GMRect2D srcRect = (*it)->srcRect;
        GMVector2D texSize = (*it)->tex->getSize();
        GMVector2D texScale = (*it)->tex->getScale();
        
        if (srcRect.width == 0.0 && srcRect.height == 0.0) {
            srcRect.width = texSize.x;
            srcRect.height = texSize.y;
        }

        GMVector2D origin = (*it)->origin;
        origin.x = (origin.x / srcRect.width) * destRect.width;
        origin.y = (origin.y / srcRect.height) * destRect.height;
        
        GMVector2D p1, p2, p3, p4;
        
        p1.x = p4.x = 0.0;
        p2.x = p3.x = destRect.width;

        p1.y = p2.y = 0.0;
        p3.y = p4.y = destRect.height;

        p1.x -= origin.x;
        p2.x -= origin.x;
        p3.x -= origin.x;
        p4.x -= origin.x;
        p1.y -= origin.y;
        p2.y -= origin.y;
        p3.y -= origin.y;
        p4.y -= origin.y;

        double& rotation = (*it)->rotation;
        if (rotation != 0.0) {
            double cos_v = cos(rotation);
            double sin_v = sin(rotation);
            
            double p1_x = p1.x * cos_v - p1.y * sin_v;
            double p2_x = p2.x * cos_v - p2.y * sin_v;
            double p3_x = p3.x * cos_v - p3.y * sin_v;
            double p4_x = p4.x * cos_v - p4.y * sin_v;

            double p1_y = p1.x * sin_v + p1.y * cos_v;
            double p2_y = p2.x * sin_v + p2.y * cos_v;
            double p3_y = p3.x * sin_v + p3.y * cos_v;
            double p4_y = p4.x * sin_v + p4.y * cos_v;

            p1.x = p1_x;
            p1.y = p1_y;
            p2.x = p2_x;
            p2.y = p2_y;
            p3.x = p3_x;
            p3.y = p3_y;
            p4.x = p4_x;
            p4.y = p4_y;
        }

        p1.x += destRect.x;
        p2.x += destRect.x;
        p3.x += destRect.x;
        p4.x += destRect.x;
        p1.y += destRect.y;
        p2.y += destRect.y;
        p3.y += destRect.y;
        p4.y += destRect.y;
        
        srcRect.x /= texSize.x;
        srcRect.y /= texSize.y;
        srcRect.width /= texSize.x;
        srcRect.height /= texSize.y;
        
        double tMinX = srcRect.minX() * texScale.x;
        double tMinY = srcRect.minY() * texScale.y;
        double tMaxX = srcRect.maxX() * texScale.x;
        double tMaxY = srcRect.maxY() * texScale.y;
        
        GMTexture2D* tex = (*it)->tex;
        if (tex != currentTex) {
            GMDraw::End();
            GMDraw::Begin();
            effect->setTexture(tex);
        }
        GMDraw::FillQuad(p1, p2, p3, p4,
                         (*it)->color,
                         GMVector2D(tMinX, tMinY), GMVector2D(tMaxX, tMinY), GMVector2D(tMaxX, tMaxY), GMVector2D(tMinX, tMaxY));
    }
    GMDraw::End();
    
    // 描画リストのクリア
    for (std::list<GMSprite*>::iterator it = mSpriteList.begin(); it != mSpriteList.end(); it++) {
        delete *it;
    }
    mSpriteList.clear();
}


