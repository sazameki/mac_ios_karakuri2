//
//  GMParticle.cpp
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/25.
//  Copyright (c) 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMParticle.h"
#include "GMRandom.h"
#include "GMDraw.h"


GMParticleSystem2D::GMParticleSystem2D(const std::string& imageName)
{
    mTex = new GMTexture2D(imageName);
    mLife = 60;
}

GMParticleSystem2D::~GMParticleSystem2D()
{
    delete mTex;
}

void GMParticleSystem2D::startDraw()
{
    GMDraw::Begin();
    GMGraphics::CurrentGraphics->enablePointSprite(true);
    
    GMBasicEffect* effect = (GMBasicEffect*)GMEffect::CurrentEffect;
    mWasTextureEnabled = effect->isTextureEnabled();
    effect->enableTexture(true);
}

void GMParticleSystem2D::endDraw()
{
    GMDraw::End();
    GMGraphics::CurrentGraphics->enablePointSprite(false);
    
    GMBasicEffect* effect = (GMBasicEffect*)GMEffect::CurrentEffect;
    effect->enableTexture(mWasTextureEnabled);
}

void GMParticleSystem2D::draw()
{
    GMBasicEffect* effect = (GMBasicEffect*)GMEffect::CurrentEffect;
    effect->setTexture(mTex);
    std::list<GMParticle2D*>::iterator it = mParticles.begin();
    while (it != mParticles.end()) {
        (*it)->draw();
        it++;
    }
}

void GMParticleSystem2D::step()
{
    for (int i = 0; i < 1; i++) {
        GMParticle2D* aParticle = new GMParticle2D(mCenterPos, mLife);
        mParticles.push_back(aParticle);
    }

    std::list<GMParticle2D*>::iterator it = mParticles.begin();
    while (it != mParticles.end()) {
        if ((*it)->step()) {
            it++;
        } else {
            delete *it;
            it = mParticles.erase(it);
        }
    }
}

void GMParticleSystem2D::setCenterPos(const GMVector2D& center)
{
    mCenterPos = center;
}

void GMParticleSystem2D::setLife(int life)
{
    mLife = life;
}


GMParticle2D::GMParticle2D(const GMVector2D& pos, unsigned life)
    : mPos(pos), mLife(life)
{
    mV.x = (GMRandom::NextDouble() - 0.5) * 6.0;
    mV.y = (GMRandom::NextDouble() - 0.5) * 6.0;
    mA.x = 0.0;
    mA.y = GMRandom::NextDouble() * 0.3;
    mAlpha = 1.0;
    mAlphaDelta = -1.0 / life;
}

void GMParticle2D::draw()
{
    float alpha = mAlpha;
    if (alpha < 0.0) {
        alpha = 0.0;
    } else if (alpha > 1.0) {
        alpha = 1.0;
    }
    
    GMDraw::DrawPoint(mPos, GMColor(1.0, 1.0, 1.0, mAlpha), 64);
}

bool GMParticle2D::step()
{
    mV += mA;
    mPos += mV;
    mAlpha += mAlphaDelta;
    mLife--;
    return (mLife == 0)? false: true;
}

