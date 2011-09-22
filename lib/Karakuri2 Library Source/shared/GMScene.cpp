//
//  GMScene.cpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import "GMScene.h"
#import "GMDraw.h"
#import "GMButton.h"


GMScene::GMScene()
{
    // サブクラスで実装する
}

GMScene::~GMScene()
{
    // サブクラスで実装する
}

void GMScene::willAppear(GMGraphics* g)
{
    // サブクラスで実装する
}

void GMScene::didDisappear()
{
    // サブクラスで実装する
}

void GMScene::willAppear2(GMGraphics* g2)
{
    // サブクラスで実装する
}

void GMScene::didDisappear2()
{
    // サブクラスで実装する
}

void GMScene::drawView(GMGraphics* g)
{
    // サブクラスで実装する
}

void GMScene::drawView2(GMGraphics* g2)
{
    drawView2Mirrored(g2);
}

void GMScene::drawView2Mirrored(GMGraphics* g2)
{
    // TODO: ミラーリング処理の実装
    /*
    // ミラーリング処理1
    static bool UseScaling = true; // スケーリングしない場合は false にする
    static int paddingX = 0;
    static int paddingY = 0;
    static float scale = 1.0f;
    static GMVector2D screenSize1;
    static GMVector2D screenSize2;
    static GMMatrix matProjection2D;
    if (paddingX == 0) {
        screenSize1 = GMGraphics::Graphics1->getScreenSize();
        screenSize2 = g2->getScreenSize();
        if (UseScaling) {
            float ratio1 = screenSize1.x / screenSize1.y;
            float ratio2 = screenSize2.x / screenSize2.y;
            // 縦を合わせる
            if (ratio1 < ratio2) {
                scale = screenSize2.y / screenSize1.y;
            }
            // 横を合わせる
            else {
                scale = screenSize2.x / screenSize1.x;
            }
        }
        paddingX = (screenSize2.x - screenSize1.x * scale) / 2;
        paddingY = (screenSize2.y - screenSize1.y * scale) / 2;
        
        matProjection2D = GMMatrix::CreateOrthographicOffCenter(0.0, screenSize2.x, 0.0, screenSize2.y, -1.0, 1.0);
    }
    g2->pushViewMatrix();
    
    // ミラーリング処理2
    GMViewport oldViewport = g2->getViewport();
    g2->setViewport(GMViewport(paddingX, paddingY, screenSize1.x*scale, screenSize1.y*scale));
    drawView(g2);
    g2->setViewport(oldViewport);
    
    // ミラーリング処理3
    {
        g2->popViewMatrix();
        g2->pushProjectionMatrix();
        g2->setProjectionMatrix(matProjection2D);
        
        GMDraw::Begin();
        GMDraw::FillQuad(GMVector2D(0, 0),
                         GMVector2D(screenSize2.x, 0),
                         GMVector2D(screenSize2.x, paddingY),
                         GMVector2D(0, paddingY), GMColor::Black);
        GMDraw::FillQuad(GMVector2D(0, screenSize2.y-paddingY),
                         GMVector2D(screenSize2.x, screenSize2.y-paddingY),
                         GMVector2D(screenSize2.x, screenSize2.y),
                         GMVector2D(0, screenSize2.y), GMColor::Black);
        GMDraw::FillQuad(GMVector2D(0, paddingY),
                         GMVector2D(paddingX, paddingY),
                         GMVector2D(paddingX, screenSize2.y-paddingY),
                         GMVector2D(0, screenSize2.y-paddingY), GMColor::Black);
        GMDraw::FillQuad(GMVector2D(screenSize2.x-paddingX, paddingY),
                         GMVector2D(screenSize2.x, paddingY),
                         GMVector2D(screenSize2.x, screenSize2.y-paddingY),
                         GMVector2D(screenSize2.x-paddingX, screenSize2.y-paddingY), GMColor::Black);
        GMDraw::End();
        
        g2->popProjectionMatrix();
    }
     */
}

void GMScene::updateModel(GMInput* input)
{
    // サブクラスで実装する
}

std::string GMScene::getName() const
{
    return mSceneName;
}

void GMScene::__setName(const std::string& name)
{
    mSceneName = name;
}

void GMScene::buttonPressed(GMButton* button)
{
    // Do nothing
}

