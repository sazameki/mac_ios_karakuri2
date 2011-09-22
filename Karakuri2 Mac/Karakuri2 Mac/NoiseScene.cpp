//
//  NoiseScene.cpp
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/31.
//  Copyright (c) 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "NoiseScene.h"


static const double NoiseSceneBandHeightBottom  = 30.0;
static const double NoiseSceneBandHeightUp      = 15.0;


NoiseScene::NoiseScene()
{
    // Do nothing
}

NoiseScene::~NoiseScene()
{
    // Do nothing
}

/*
    このシーンが表示されるときに呼ばれます。
 */
void NoiseScene::willAppear(GMGraphics* g)
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
    mTitleLabel->setText("Noise Screen");
    
    mBandY = -(NoiseSceneBandHeightBottom + NoiseSceneBandHeightUp);
    
    mBGMPlayer = new GMMusic("pink_noise.caf");
    mBGMPlayer->setVolume(0.3);
    mBGMPlayer->play();
}

/*
    他のシーンへの以降時またはアプリケーションの終了時に呼ばれます。
 */
void NoiseScene::didDisappear()
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
    
    mBGMPlayer->stop();
    delete mBGMPlayer;
    mBGMPlayer = NULL;
}

/*
    ビューを描画します。
    明示的なミラーリング処理を行う場合、プロジェクション行列、ビュー行列、グラフィックス設定は毎フレーム行ってください。
 */
void NoiseScene::drawView(GMGraphics* g)
{
    g->clear(GMColor::Black);
    
    GMVector2D screenSize = g->getScreenSize();
    
    mBasicEffect->begin();
    mBasicEffect->enableLighting(false);
    {
        GMDrawSys::SetBlendMode(GMBlendModeAlpha);
        mBasicEffect->enableTexture(false);
        GMDraw::Begin();
        {
            for (int i = 0; i < screenSize.x*screenSize.y/100; i++) {
                GMDraw::DrawPoint(GMVector2D(GMRandom::NextInt(screenSize.x), GMRandom::NextInt(screenSize.y)), GMColor::Gray);
            }

            GMDraw::FillQuad(GMVector2D(0, mBandY), GMVector2D(screenSize.x, mBandY),
                             GMVector2D(screenSize.x, mBandY+NoiseSceneBandHeightBottom), GMVector2D(0, mBandY+NoiseSceneBandHeightBottom),
                             GMColor(1.0, 1.0, 1.0, 0.2), GMColor(1.0, 1.0, 1.0, 0.2),
                             GMColor(1.0, 1.0, 1.0, 0.05), GMColor(1.0, 1.0, 1.0, 0.05));
            GMDraw::FillQuad(GMVector2D(0, mBandY+NoiseSceneBandHeightBottom), GMVector2D(screenSize.x, mBandY+NoiseSceneBandHeightBottom),
                             GMVector2D(screenSize.x, mBandY+NoiseSceneBandHeightBottom+NoiseSceneBandHeightUp), GMVector2D(0, mBandY+NoiseSceneBandHeightBottom+NoiseSceneBandHeightUp),
                             GMColor(1.0, 1.0, 1.0, 0.05), GMColor(1.0, 1.0, 1.0, 0.05),
                             GMColor(1.0, 1.0, 1.0, 0.2), GMColor(1.0, 1.0, 1.0, 0.2));
        }
        GMDraw::End();
        
        mSpriteBatch->begin(GMSpriteSortModeFrontToBack);
        {
            GMTexture2D* labelTex = mTitleLabel->getTexture();
            int width = labelTex->getSize().x;
            mSpriteBatch->draw(labelTex, GMVector2D((screenSize.x-width)/2, screenSize.y/2), GMColor(1.0, 1.0, 1.0, 0.35));
            mNextButton->draw(mSpriteBatch);
        }
        mSpriteBatch->end();
    }
    mBasicEffect->end();
}

/*
    モデルを1フレーム分更新します。
 */
void NoiseScene::updateModel(GMInput* input)
{
    mNextButton->process(input);

    GMVector2D screenSize = GMGraphics::Graphics1->getScreenSize();
    mBandY += 1.0;
    if (mBandY >= screenSize.y) {
        mBandY = -(NoiseSceneBandHeightBottom + NoiseSceneBandHeightUp);
    }
}

void NoiseScene::buttonPressed(GMButton* button)
{
    GMGame::ChangeScene("cube3d");
}


