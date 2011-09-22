//
//  DualScreenScene.cpp
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/31.
//  Copyright (c) 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "DualScreenScene.h"


DualScreenScene::DualScreenScene()
{
    // Do nothing
}

DualScreenScene::~DualScreenScene()
{
    // Do nothing
}

/*
    このシーンが表示されるときに呼ばれます。
 */
void DualScreenScene::willAppear(GMGraphics* g)
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
}

/*
    サブディスプレイが接続されたときに呼ばれます。
    テクスチャの名前空間はメインディスプレイと共有しているので、テクスチャの再読み込みは必要ありません。
    引数として渡される GMGraphics は、メインディスプレイとは独立したものです。
    デプステスト、ライティング等の基本設定を行ってください。
 */
void DualScreenScene::willAppear2(GMGraphics* g2)
{
    g2->enableDepthTest(false);
}

/*
    他のシーンへの以降時またはアプリケーションの終了時に呼ばれます。
 */
void DualScreenScene::didDisappear()
{
    // 各種リソースのクリーンアップ
    delete mBasicEffect;
    mBasicEffect = NULL;
    
    delete mSpriteBatch;
    mSpriteBatch = NULL;
}

/*
    サブディスプレイが切断されたときに呼ばれます。
 */
void DualScreenScene::didDisappear2()
{
    // Do nothing
}

/*
    ビューを描画します。
    明示的なミラーリング処理を行う場合、プロジェクション行列、ビュー行列、グラフィックス設定は毎フレーム行ってください。
 */
void DualScreenScene::drawView(GMGraphics* g)
{
    // 画面のクリア
    g->clear(GMColor::CornflowerBlue);
    
    mBasicEffect->begin();
    {
    }
    mBasicEffect->end();
}

/*
    サブディスプレイのビューを描画します。
 */
void DualScreenScene::drawView2(GMGraphics* g2)
{
    g2->clear(GMColor::CornflowerBlue);
    
    GMViewport oldViewport = g2->getViewport();
    GMVector2D screenSize2 = g2->getScreenSize();
    
    g2->setViewport(GMViewport(0, 0, screenSize2.x/2, screenSize2.y));
    mBasicEffect->begin();
    {
    }
    mBasicEffect->end();
    
    g2->setViewport(GMViewport(screenSize2.x/2, 0, screenSize2.x/2, screenSize2.y));
    mBasicEffect->begin();
    {
    }
    mBasicEffect->end();
    
    g2->setViewport(oldViewport);
}

/*
    モデルを1フレーム分更新します。
 */
void DualScreenScene::updateModel(GMInput* input)
{
    if (input->getTouchCount() >= 1) {
        GMGame::ChangeScene("fire");
        return;
    }
}

