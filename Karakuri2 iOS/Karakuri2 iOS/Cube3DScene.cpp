//
//  Cube3DScene.cpp
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/31.
//  Copyright (c) 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "Cube3DScene.h"


Cube3DScene::Cube3DScene()
{
    // Do nothing
}

Cube3DScene::~Cube3DScene()
{
    // Do nothing
}

/*
    このシーンが表示されるときに呼ばれます。
 */
void Cube3DScene::willAppear(GMGraphics* g)
{
    // 基本のシェーダ
    mBasicEffect = new GMBasicEffect();
    mSpriteBatch = new GMSpriteBatch();
    
    // 3D用画面設定
    GMVector2D screenSize = g->getScreenSize();
    mProjection2D = GMMatrix::CreateOrthographicOffCenter(0.0, screenSize.x, 0.0, screenSize.y, -1.0, 1.0);
    mProjection3D = GMMatrix::CreatePerspectiveFieldOfView(M_PI/4, screenSize.x/screenSize.y, 1.0, 5000.0);
    
    mCameraAngle = 0.0;
    mCameraTarget = GMVector3D(0, 0, 0);
    mCameraUp = GMVector3D::Up;
    mCameraPos = GMVector3D(cos(mCameraAngle)*500, 200, sin(mCameraAngle)*500);
    mView3D = GMMatrix::CreateLookAt(mCameraPos, mCameraTarget, mCameraUp);
    
    mCubeAngleY = 0.0;
    mTexBlock = new GMTexture2D("block_wall.png");
    
    mBasicEffect->enableLighting(true);

    mBasicEffect->enableLight(0, true);
    mBasicEffect->setLightTypeAsPoint(0, GMVector3D(0.0, 100.0, 500.0));
    mBasicEffect->setLightAmbientColor(0, GMVector3D(0.5, 0.5, 0.5));
    mBasicEffect->setLightDiffuseColor(0, GMVector3D(1.0, 1.0, 1.0));
    mBasicEffect->setLightSpecularColor(0, GMVector3D(1.0, 1.0, 1.0));
    
    // 「次へ」ボタン
    mNextButton = new GMButton(GMRect2D(10, screenSize.y-48, 140, 38), "next_button.png");

    // タイトル文字列のセットアップ
    mTitleLabel = new GMLabel("Verdana", 40.0);
    mTitleLabel->setText("Cube 3D");
    
    mRenderTarget = new GMRenderTarget2D(512, 512);
}

/*
    他のシーンへの以降時またはアプリケーションの終了時に呼ばれます。
 */
void Cube3DScene::didDisappear()
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
    
    delete mTexBlock;
    mTexBlock = NULL;
    
    delete mRenderTarget;
    mRenderTarget = NULL;
}

void Cube3DScene::drawCube() const
{
    GMVector3D p1(-50, -50, -50);
    GMVector3D p2(50, -50, -50);
    GMVector3D p3(50, 50, -50);
    GMVector3D p4(-50, 50, -50);
    GMVector3D p5(-50, -50, 50);
    GMVector3D p6(50, -50, 50);
    GMVector3D p7(50, 50, 50);
    GMVector3D p8(-50, 50, 50);
    
    mBasicEffect->setTexture(mTexBlock);

    GMDraw::FillQuad(p4, p3, p2, p1,
                     GMVector3D(0, 0, -1), GMVector3D(0, 0, -1), GMVector3D(0, 0, -1), GMVector3D(0, 0, -1),
                     GMVector2D(0.0, 0.0), GMVector2D(1.0, 0.0), GMVector2D(1.0, 1.0), GMVector2D(0.0, 1.0));

    GMDraw::FillQuad(p8, p4, p1, p5,
                     GMVector3D(-1, 0, 0), GMVector3D(-1, 0, 0), GMVector3D(-1, 0, 0), GMVector3D(-1, 0, 0),
                     GMVector2D(0.0, 0.0), GMVector2D(1.0, 0.0), GMVector2D(1.0, 1.0), GMVector2D(0.0, 1.0));

    GMDraw::FillQuad(p7, p8, p5, p6,
                     GMVector3D(0, 0, 1), GMVector3D(0, 0, 1), GMVector3D(0, 0, 1), GMVector3D(0, 0, 1),
                     GMVector2D(0.0, 0.0), GMVector2D(1.0, 0.0), GMVector2D(1.0, 1.0), GMVector2D(0.0, 1.0));
    
    GMDraw::FillQuad(p7, p3, p4, p8,
                     GMVector3D(0, 1, 0), GMVector3D(0, 1, 0), GMVector3D(0, 1, 0), GMVector3D(0, 1, 0),
                     GMVector2D(0.0, 0.0), GMVector2D(1.0, 0.0), GMVector2D(1.0, 1.0), GMVector2D(0.0, 1.0));
    
    GMDraw::FillQuad(p3, p7, p6, p2,
                     GMVector3D(1, 0, 0), GMVector3D(1, 0, 0), GMVector3D(1, 0, 0), GMVector3D(1, 0, 0),
                     GMVector2D(0.0, 0.0), GMVector2D(1.0, 0.0), GMVector2D(1.0, 1.0), GMVector2D(0.0, 1.0));

    GMDraw::FillQuad(p2, p6, p5, p1,
                     GMVector3D(0, -1, 0), GMVector3D(0, -1, 0), GMVector3D(0, -1, 0), GMVector3D(0, -1, 0),
                     GMVector2D(0.0, 0.0), GMVector2D(1.0, 0.0), GMVector2D(1.0, 1.0), GMVector2D(0.0, 1.0));
}

/*
    ビューを描画します。
 */
void Cube3DScene::drawView(GMGraphics* g)
{
    g->clear(GMColor::CornflowerBlue);
    
    GMVector2D screenSize = g->getScreenSize();
    
    g->setRenderTarget(mRenderTarget);
    g->clear(GMColor::Black);
    GMDrawSys::SetBlendMode(GMBlendModeClear);
    GMDraw::Begin();
    GMDraw::FillQuad(GMVector2D(0, 0), GMVector2D(512, 0), GMVector2D(512, 512), GMVector2D(0, 512), GMColor::White);
    GMDraw::End();
    GMDrawSys::SetBlendMode(GMBlendModeAlpha);

    // ボタン描画 (2D)
    g->enableDepthTest(false);
    mBasicEffect->enableLighting(false);
    mBasicEffect->setProjectionMatrix(mProjection2D);
    mBasicEffect->setViewMatrix(GMMatrix::Identity);
    mBasicEffect->begin();
    {
        mSpriteBatch->begin();
        {
            GMTexture2D* labelTex = mTitleLabel->getTexture();
            mSpriteBatch->draw(labelTex, GMVector2D((screenSize.x-labelTex->getSize().x)/2, screenSize.y/2-180), GMColor(1.0, 1.0, 1.0, 0.35));
        }
        mSpriteBatch->end();
    }
    mBasicEffect->end();

    // 3D描画
    g->enableDepthTest(true);
    mBasicEffect->enableLighting(true);
    mBasicEffect->setProjectionMatrix(mProjection3D);
    mBasicEffect->setViewMatrix(mView3D);
    mBasicEffect->begin();
    {
        mBasicEffect->setWorldMatrix(GMMatrix::CreateRotationY(mCubeAngleY) * GMMatrix::CreateTranslation(100.0, 0.0, 0.0));
        GMDraw::Begin();
        mBasicEffect->setMaterial(GMVector3D(1.0, 1.0, 1.0), GMVector3D::Zero, GMVector3D(0.4, 0.4, 0.4));
        drawCube();
        GMDraw::End();

        mBasicEffect->setWorldMatrix(GMMatrix::CreateRotationY(mCubeAngleY) * GMMatrix::CreateTranslation(-100.0, 0.0, 0.0));
        GMDraw::Begin();
        mBasicEffect->setMaterial(GMVector3D(1.0, 1.0, 1.0), GMVector3D::Zero, GMVector3D(1.0, 0.0, 0.0));
        drawCube();
        GMDraw::End();
    }
    mBasicEffect->end();
    
    // ボタン描画 (2D)
    g->enableDepthTest(false);
    mBasicEffect->enableLighting(false);
    mBasicEffect->setProjectionMatrix(mProjection2D);
    mBasicEffect->setViewMatrix(GMMatrix::Identity);
    mBasicEffect->begin();
    {
        mSpriteBatch->begin();
        mNextButton->draw(mSpriteBatch);
        mSpriteBatch->end();
    }
    mBasicEffect->end();
    
    g->setRenderTarget(NULL);
    g->clear(GMColor::CornflowerBlue);
    mBasicEffect->setProjectionMatrix(mProjection2D);
    mBasicEffect->setViewMatrix(GMMatrix::Identity);
    mBasicEffect->begin();
    {
        mSpriteBatch->begin();
        {
            GMDrawSys::SetBlendMode(GMBlendModeScreen);
            int blurCount = 3;
            int blurSize = 9;
            for (int i = 1; i <= blurCount; i++) {
                mSpriteBatch->draw(mRenderTarget, GMVector2D(i*blurSize-27, i*blurSize-27), GMColor(1, 1, 1, (double)(i)/(blurCount)));
            }
            GMDrawSys::SetBlendMode(GMBlendModeAlpha);
            mSpriteBatch->draw(mRenderTarget, GMVector2D(0, 0));
        }
        mSpriteBatch->end();
    }
    mBasicEffect->end();
}

/*
    モデルを1フレーム分更新します。
 */
void Cube3DScene::updateModel(GMInput* input)
{
    mNextButton->process(input);

    mCameraAngle += 0.01;
    mCameraPos.x = cos(mCameraAngle) * 500;
    mCameraPos.z = sin(mCameraAngle) * 500;
    mView3D = GMMatrix::CreateLookAt(mCameraPos, mCameraTarget, mCameraUp);
    
    mCubeAngleY += 0.02;
}

void Cube3DScene::buttonPressed(GMButton* button)
{
    GMGame::ChangeScene("fire");
}



