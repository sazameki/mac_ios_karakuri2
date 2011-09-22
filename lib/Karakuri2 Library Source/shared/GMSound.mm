/*
 *  GMSound.cpp
 *  Game Framework
 *
 *  Created by numata on 09/07/23.
 *  Copyright 2009 Satoshi Numata. All rights reserved.
 *
 */

#include "GMSound.h"
#include "GMTypes.h"
#include "GMException.h"
#import "GMSoundImpl.h"


static GMVector3D   sListenerPos;


void _GMInitSound()
{
    sListenerPos = GMVector3D::Zero;
}


double GMSound::getListenerHorizontalOrientation()
{
    return [GMSoundImpl listenerHorizontalOrientation];
}

void GMSound::setListenerHorizontalOrientation(double radAngle)
{
    [GMSoundImpl setListenerHorizontalOrientation:radAngle];
}

GMVector3D GMSound::getListenerPos()
{
    return sListenerPos;
}

void GMSound::setListenerPos(double x, double y, double z)
{
    sListenerPos.x = x;
    sListenerPos.y = y;
    sListenerPos.z = z;
    [GMSoundImpl setListenerX:x y:y z:z];
}

void GMSound::setListenerPos(const GMVector3D& vec3)
{
    setListenerPos(vec3.x, vec3.y, vec3.z);
}

GMSound::GMSound(const std::string& filename, bool doLoop)
{
    mFileName = filename;
    mDoLoop = doLoop;
 
    mSourcePos = GMVector3D::Zero;
    
    // Get the path
    NSString* filenameStr = [NSString stringWithCString:filename.c_str() encoding:NSUTF8StringEncoding];
    mSoundImpl = [[GMSoundImpl alloc] initWithName:filenameStr doLoop:(doLoop? YES: NO)];    
    if (!mSoundImpl) {
        throw GMException("Failed to load a sound file: \"%s\"", filename.c_str());
    }
}

GMSound::~GMSound()
{
    [(GMSoundImpl*)mSoundImpl release];
}

bool GMSound::isPlaying() const
{
    return [(GMSoundImpl*)mSoundImpl isPlaying];
}

void GMSound::play()
{
    [(GMSoundImpl*)mSoundImpl play];
}

void GMSound::stop()
{
    [(GMSoundImpl*)mSoundImpl stop];
}

GMVector3D GMSound::getSourcePos() const
{
    return mSourcePos;
}

void GMSound::setSourcePos(const GMVector3D& vec3)
{
    mSourcePos = vec3;
    [(GMSoundImpl*)mSoundImpl setSourceX:vec3.x y:vec3.y z:vec3.z];
}

double GMSound::getPitch() const
{
    return (double)[(GMSoundImpl*)mSoundImpl pitch];
}

void GMSound::setPitch(double value)
{
    [(GMSoundImpl*)mSoundImpl setPitch:(float)value];
}

double GMSound::getVolume() const
{
    return (double)[(GMSoundImpl*)mSoundImpl volume];
}

void GMSound::setVolume(double value)
{
    [(GMSoundImpl*)mSoundImpl setVolume:(float)value];
}

std::string GMSound::to_s() const
{
    return "<sound>(file=\"" + mFileName + "\", loop=" + (mDoLoop? "true": "false") + ")";
}



