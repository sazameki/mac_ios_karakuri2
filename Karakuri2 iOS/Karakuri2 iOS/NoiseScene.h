//
//  NoiseScene.h
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/31.
//  Copyright (c) 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __NOISE_SCENE_H__
#define __NOISE_SCENE_H__


#include "Karakuri.h"


class NoiseScene : public GMScene {

    GMBasicEffect*  mBasicEffect;
    GMSpriteBatch*  mSpriteBatch;
    
    GMLabel*        mTitleLabel;
    GMButton*       mNextButton;
    
    GMMusic*        mBGMPlayer;
    
    double          mBandY;
    
public:
    NoiseScene();
    virtual ~NoiseScene();
    
public:
    virtual void    willAppear(GMGraphics* g);
    virtual void    didDisappear();
    
public:
    virtual void    drawView(GMGraphics* g);
    virtual void    updateModel(GMInput* input);
    
public:
    virtual void    buttonPressed(GMButton* button);

};


#endif  //#ifndef __NOISE_SCENE_H__

