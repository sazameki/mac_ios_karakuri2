//
//  FireScene.cpp
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/30.
//  Copyright (c) 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//


#include "FireScene.h"


FireScene::FireScene()
{
    // Do nothing
}

FireScene::~FireScene()
{
    // Do nothing
}

/*
    このシーンが表示されるときに呼ばれます。
 */
void FireScene::willAppear(GMGraphics* g)
{
    // 基本のシェーダ、2Dテクスチャ描画用のバッチ
    mBasicEffect = new GMBasicEffect();
    mSpriteBatch = new GMSpriteBatch();

    // 2D用画面設定
    GMVector2D screenSize = g->getScreenSize();
    mBasicEffect->setProjectionMatrix(GMMatrix::CreateOrthographicOffCenter(0.0, screenSize.x, 0.0, screenSize.y, -1.0, 1.0));
    mBasicEffect->setViewMatrix(GMMatrix::Identity);
    mBasicEffect->enableLighting(false);

    g->enableDepthTest(false);

    // 「次へ」ボタン
    mNextButton = new GMButton(GMRect2D(10, screenSize.y-48, 140, 38), "next_button.png");

    // タイトル文字列のセットアップ
    mTitleLabel = new GMLabel("Verdana", 40.0);
    mTitleLabel->setText("Fire Explosion");

    // パーティクルのセットアップ
    mParticleSystem = new GMParticleSystem2D("particle_smoke_128.png");
    mParticleSystem->setCenterPos(GMVector2D(screenSize.x/2, screenSize.y/2-20));
    mParticleSystem->setLife(60);
    
    mParticleSystem2 = new GMParticleSystem2D("particle_fire_128.png");
    mParticleSystem2->setCenterPos(GMVector2D(screenSize.x/2, screenSize.y/2));
    mParticleSystem2->setLife(10);
    
    mMovingCenterPos = false;
}

/*
 他のシーンへの以降時またはアプリケーションの終了時に呼ばれます。
 */
void FireScene::didDisappear()
{
    // 各種リソースのクリーンアップ
    delete mBasicEffect;
    mBasicEffect = NULL;

    delete mSpriteBatch;
    mSpriteBatch = NULL;

    delete mTitleLabel;
    mTitleLabel = NULL;
    
    delete mNextButton;
    mNextButton = NULL;

    delete mParticleSystem;
    mParticleSystem = NULL;
    
    delete mParticleSystem2;
    mParticleSystem2 = NULL;
}

/*
    ビューを描画します。
    明示的なミラーリング処理を行う場合、プロジェクション行列、ビュー行列、グラフィックス設定は毎フレーム行ってください。
 */
void FireScene::drawView(GMGraphics* g)
{
    g->clear(GMColor::CornflowerBlue);
    
    GMVector2D screenSize = g->getScreenSize();
    
    mBasicEffect->begin();
    {
        GMDrawSys::SetBlendMode(GMBlendModeAlpha);
        mSpriteBatch->begin();
        {
            GMTexture2D* labelTex = mTitleLabel->getTexture();
            int width = labelTex->getSize().x;
            mSpriteBatch->draw(labelTex, GMVector2D((screenSize.x-width)/2, screenSize.y/2), GMColor(1.0, 1.0, 1.0, 0.35));
        }
        mSpriteBatch->end();

        GMDrawSys::SetBlendMode(GMBlendModeAlpha);
        mParticleSystem->startDraw();
        {
            mParticleSystem->draw();
        }
        mParticleSystem->endDraw();

        GMDrawSys::SetBlendMode(GMBlendModeAdd);
        mParticleSystem->startDraw();
        {
            mParticleSystem2->draw();
        }
        mParticleSystem->endDraw();

        GMDrawSys::SetBlendMode(GMBlendModeAlpha);
        mSpriteBatch->begin();
        {
            mNextButton->draw(mSpriteBatch);
        }
        mSpriteBatch->end();
    }
    mBasicEffect->end();
}

/*
    モデルを1フレーム分更新します。
 */
void FireScene::updateModel(GMInput* input)
{
    if (!mMovingCenterPos) {
        if (!mNextButton->process(input)) {
            // パーティクル発生源移動の処理
            if (input->isMouseDown()) {
                GMVector2D pos = input->getMouseLocation();
                mParticleSystem->setCenterPos(pos);
                mParticleSystem2->setCenterPos(pos+GMVector2D(0, 20));
                mMovingCenterPos = true;
            }
        }
    } else {
        if (input->isMouseDown()) {
            GMVector2D pos = input->getMouseLocation();
            mParticleSystem->setCenterPos(pos);
            mParticleSystem2->setCenterPos(pos+GMVector2D(0, 20));
        } else {
            mMovingCenterPos = false;
        }
    }

    // パーティクル生成のステップ処理
    mParticleSystem->step();
    mParticleSystem2->step();
}

void FireScene::buttonPressed(GMButton* button)
{
    GMGame::ChangeScene("noise");
}

