//
//  GMButton.cpp
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/31.
//  Copyright (c) 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMButton.h"
#include "GMException.h"
#include "GMScene.h"
#include "GMGame.h"

#include <TargetConditionals.h>


GMButton::GMButton(const GMRect2D& frame, const std::string& imageName)
    : mFrame(frame), mIsPressed(false), mIsReleased(false)
{
    mTexImage = new GMTexture2D(imageName);
}

GMButton::~GMButton()
{
    delete mTexImage;
    mTexImage = NULL;
}

void GMButton::startPress()
{
    mIsPressed = true;
    mIsReleased = false;
}

bool GMButton::isPressed() const
{
    return mIsPressed;
}

void GMButton::endPress()
{
    mIsPressed = false;
}

bool GMButton::isReleased() const
{
    return mIsReleased;
}

void GMButton::setReleased(bool flag)
{
    mIsReleased = flag;
}

bool GMButton::contains(const GMVector2D& pos)
{
    return mFrame.contains(pos);
}

bool GMButton::process(GMInput* input)
{
    bool hasTouch = false;
    
#if TARGET_OS_IPHONE
    if (input->getTouchCount() > 0) {
        hasTouch = true;
    }
#else
    if (input->isMouseDown()) {
        hasTouch = true;
    }
#endif
    
    if (isPressed()) {
        if (!hasTouch) {
            endPress();
            if (!isReleased()) {
                GMScene* scene = GMGame::GetCurrentScene();
                if (scene != NULL) {
                    scene->buttonPressed(this);
                } else {
                    throw GMException("Cannot find GMButton target scene!!");
                }
            }
        } else {
#if TARGET_OS_IPHONE
            GMVector2D pos = input->getTouchLocationAny();
#else
            GMVector2D pos = input->getMouseLocation();
#endif
            if (contains(pos)) {
                setReleased(false);
            } else {
                setReleased(true);
            }
        }
        return true;
    }
    else {
#if TARGET_OS_IPHONE
        GMVector2D pos = input->getTouchLocationAny();
#else
        GMVector2D pos = input->getMouseLocation();
#endif
        if (hasTouch && contains(pos)) {
            startPress();
            return true;
        }
        return false;
    }
}

void GMButton::draw(GMSpriteBatch* spriteBatch)
{
    if (mIsPressed && !mIsReleased) {
        spriteBatch->draw(mTexImage, GMVector2D(mFrame.x, mFrame.y), GMColor(0.7, 0.7, 0.7, 1.0));
    } else {
        spriteBatch->draw(mTexImage, GMVector2D(mFrame.x, mFrame.y));
    }
}


