//
//  TitleScene.cpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "TitleScene.h"


TitleScene::TitleScene()
{
    // Do nothing
}

TitleScene::~TitleScene()
{
    // Do nothing
}

/*
    このシーンが表示されるときに呼ばれます。
 */
void TitleScene::willAppear(GMGraphics* g)
{
    // 基本のシェーダ、2D描画用バッチ
    mBasicEffect = new GMBasicEffect();
    mSpriteBatch = new GMSpriteBatch();

    // 2D用画面設定
    GMVector2D screenSize = g->getScreenSize();
    mBasicEffect->setProjectionMatrix(GMMatrix::CreateOrthographicOffCenter(0.0, screenSize.x, 0.0, screenSize.y, -1.0, 1.0));
    mBasicEffect->setViewMatrix(GMMatrix::Identity);
    mBasicEffect->enableLighting(false);

    g->enableDepthTest(false);

    // タイトル画面のテクスチャ
    mTexTitle = new GMTexture2D("title.png");
}

/*
    他のシーンへの以降時またはアプリケーションの終了時に呼ばれます。
 */
void TitleScene::didDisappear()
{
    // 各種リソースのクリーンアップ
    delete mBasicEffect;
    mBasicEffect = NULL;
    
    delete mSpriteBatch;
    mSpriteBatch = NULL;
    
    delete mTexTitle;
    mTexTitle = NULL;
}

/*
    ビューを描画します。
 */
void TitleScene::drawView(GMGraphics* g)
{
    // 画面のクリア
    g->clear(GMColor::White);

    // 画面の描画
    mBasicEffect->begin();
    {
        mSpriteBatch->begin();
        GMVector2D screenSize = g->getScreenSize();
        GMVector2D imageSize = mTexTitle->getSize();
        mSpriteBatch->draw(mTexTitle, GMVector2D((screenSize.x - imageSize.x)/2, (screenSize.y - imageSize.y)/2));
        mSpriteBatch->end();
    }
    mBasicEffect->end();
}

/*
    モデルを1フレーム分更新します。
 */
void TitleScene::updateModel(GMInput* input)
{
    if (input->getTouchCount() >= 1) {
        GMGame::ChangeScene("fire");
        return;
    }
}

