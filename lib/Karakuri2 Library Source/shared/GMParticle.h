//
//  GMParticle.h
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/25.
//  Copyright (c) 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//


#ifndef __GM_PARTICLE_H__
#define __GM_PARTICLE_H__


#include "GMObject.h"
#include "GMGraphics.h"
#include "GMTexture2D.h"
#include "GMSpriteBatch.h"
#include <list>
#include <string>


class GMParticle2D;


class GMParticleSystem2D : public GMObject {
    
    GMTexture2D*    mTex;
    std::list<GMParticle2D*>    mParticles;
    GMVector2D                  mCenterPos;
    int                         mLife;
    bool                        mWasTextureEnabled;
    
public:
    GMParticleSystem2D(const std::string& imageName);
    ~GMParticleSystem2D();

public:
    void    startDraw();
    void    endDraw();
    
public:
    void    draw();
    void    step();
    
public:
    void    setCenterPos(const GMVector2D& center);
    void    setLife(int life);
    
};


class GMParticle2D : public GMObject {
    
    GMVector2D  mPos;
    GMVector2D  mV;
    GMVector2D  mA;
    unsigned    mLife;
    float       mAlpha;
    float       mAlphaDelta;

public:
    GMParticle2D(const GMVector2D& pos, unsigned life);
    
public:
    void    draw();
    bool    step();
    
};


#endif  //#ifndef __GM_PARTICLE_H__

