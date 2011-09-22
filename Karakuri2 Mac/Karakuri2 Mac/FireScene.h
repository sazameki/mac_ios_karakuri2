//
//  FireScene.h
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/30.
//  Copyright (c) 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __FIRE_SCENE_H__
#define __FIRE_SCENE_H__


#include "Karakuri.h"


class FireScene : public GMScene {
    
    GMBasicEffect*  mBasicEffect;
    GMSpriteBatch*  mSpriteBatch;
    
    GMLabel*        mTitleLabel;
    GMButton*       mNextButton;

    GMParticleSystem2D* mParticleSystem;
    GMParticleSystem2D* mParticleSystem2;
    
    bool            mMovingCenterPos;

public:
    FireScene();
    virtual ~FireScene();
    
public:
    virtual void    willAppear(GMGraphics* g);
    virtual void    didDisappear();
    
public:
    virtual void    drawView(GMGraphics* g);
    virtual void    updateModel(GMInput* input);
    
public:
    virtual void    buttonPressed(GMButton* button);
    
};


#endif  //#ifndef __FIRE_SCENE_H__

