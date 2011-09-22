//
//  Cube3DScene.h
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/31.
//  Copyright (c) 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __CUBE_3D_SCENE_H__
#define __CUBE_3D_SCENE_H__


#include "Karakuri.h"


class Cube3DScene : public GMScene {
    
    GMBasicEffect*  mBasicEffect;
    GMSpriteBatch*  mSpriteBatch;

    GMLabel*        mTitleLabel;
    GMButton*       mNextButton;

    GMMatrix        mProjection2D;
    GMMatrix        mProjection3D;
    GMMatrix        mView3D;
    
    GMVector3D      mCameraPos;
    GMVector3D      mCameraTarget;
    GMVector3D      mCameraUp;
    double          mCameraAngle;
    
    double          mCubeAngleY;
    GMTexture2D*    mTexBlock;
    
public:
    Cube3DScene();
    virtual ~Cube3DScene();
    
public:
    virtual void    willAppear(GMGraphics* g);
    virtual void    didDisappear();
    
public:
    virtual void    drawView(GMGraphics* g);
    virtual void    updateModel(GMInput* input);
    
public:
    virtual void    buttonPressed(GMButton* button);

private:
    void    drawCube() const;
    
};



#endif  //#ifndef __CUBE_3D_SCENE_H__

