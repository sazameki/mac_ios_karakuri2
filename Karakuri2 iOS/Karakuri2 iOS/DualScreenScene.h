//
//  DualScreenScene.h
//  Karakuri2 iOS
//
//  Created by 沼田 哲史 on 11/08/31.
//  Copyright (c) 2011年 Satoshi Numata. All rights reserved.
//


#ifndef __DUAL_SCREEN_SCENE_H__
#define __DUAL_SCREEN_SCENE_H__


#include "Karakuri.h"


class DualScreenScene : public GMScene {
    
    GMBasicEffect*  mBasicEffect;
    GMSpriteBatch*  mSpriteBatch;
    
    GMLabel*        mTitleLabel;
    
public:
    DualScreenScene();
    virtual ~DualScreenScene();
    
public:
    virtual void    willAppear(GMGraphics* g);
    virtual void    didDisappear();

public:
    virtual void    willAppear2(GMGraphics* g);
    virtual void    didDisappear2();

public:
    virtual void    drawView(GMGraphics* g);
    virtual void    drawView2(GMGraphics* g);
    virtual void    updateModel(GMInput* input);
    
};


#endif  //#ifndef __DUAL_SCREEN_SCENE_H__

