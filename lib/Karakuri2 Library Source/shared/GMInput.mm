//
//  GMInput.mm
//  Game Framework
//
//  Created by numata on Dec 27, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "Globals.h"
#include "GMInput.h"
#include "GMGraphics.h"
#include <algorithm>
#include <iostream>
#include <utility>

#if TARGET_OS_IPHONE
#import <CoreMotion/CoreMotion.h>
#endif


#if !TARGET_OS_IPHONE

const GMKeyMask GMKeyMaskUp     = (1UL << 0);
const GMKeyMask GMKeyMaskDown   = (1UL << 1);
const GMKeyMask GMKeyMaskLeft   = (1UL << 2);
const GMKeyMask GMKeyMaskRight  = (1UL << 3);
const GMKeyMask GMKeyMaskSpace  = (1UL << 4);
const GMKeyMask GMKeyMaskEscape = (1UL << 5);
const GMKeyMask GMKeyMaskReturn = (1UL << 6);
const GMKeyMask GMKeyMaskShift  = (1UL << 7);
const GMKeyMask GMKeyMaskA      = (1UL << 8);
const GMKeyMask GMKeyMaskB      = (1UL << 9);
const GMKeyMask GMKeyMaskC      = (1UL << 10);
const GMKeyMask GMKeyMaskD      = (1UL << 11);
const GMKeyMask GMKeyMaskE      = (1UL << 12);
const GMKeyMask GMKeyMaskF      = (1UL << 13);
const GMKeyMask GMKeyMaskG      = (1UL << 14);
const GMKeyMask GMKeyMaskH      = (1UL << 15);
const GMKeyMask GMKeyMaskI      = (1UL << 16);
const GMKeyMask GMKeyMaskJ      = (1UL << 17);
const GMKeyMask GMKeyMaskK      = (1UL << 18);
const GMKeyMask GMKeyMaskL      = (1UL << 19);
const GMKeyMask GMKeyMaskM      = (1UL << 20);
const GMKeyMask GMKeyMaskN      = (1UL << 21);
const GMKeyMask GMKeyMaskO      = (1UL << 22);
const GMKeyMask GMKeyMaskP      = (1UL << 23);
const GMKeyMask GMKeyMaskQ      = (1UL << 24);
const GMKeyMask GMKeyMaskR      = (1UL << 25);
const GMKeyMask GMKeyMaskS      = (1UL << 26);
const GMKeyMask GMKeyMaskT      = (1UL << 27);
const GMKeyMask GMKeyMaskU      = (1UL << 28);
const GMKeyMask GMKeyMaskV      = (1UL << 29);
const GMKeyMask GMKeyMaskW      = (1UL << 30);
const GMKeyMask GMKeyMaskX      = (1UL << 31);
const GMKeyMask GMKeyMaskY      = (1UL << 32);
const GMKeyMask GMKeyMaskZ      = (1UL << 33);
const GMKeyMask GMKeyMask0      = (1UL << 34);
const GMKeyMask GMKeyMask1      = (1UL << 35);
const GMKeyMask GMKeyMask2      = (1UL << 36);
const GMKeyMask GMKeyMask3      = (1UL << 37);
const GMKeyMask GMKeyMask4      = (1UL << 38);
const GMKeyMask GMKeyMask5      = (1UL << 39);
const GMKeyMask GMKeyMask6      = (1UL << 40);
const GMKeyMask GMKeyMask7      = (1UL << 41);
const GMKeyMask GMKeyMask8      = (1UL << 42);
const GMKeyMask GMKeyMask9      = (1UL << 43);
const GMKeyMask GMKeyMaskAny    = 0xffffffffffffffff;

#endif  //#if !TARGET_OS_IPHONE


#if TARGET_OS_IPHONE

static bool sIsUpdatingMotion = false;
static CMMotionManager* sMotionManager = nil;

#endif  //#if TARGET_OS_IPHONE


GMInput*    GMInput::Inst   = NULL;


GMInput::GMInput()
{
    GMInput::Inst = this;

#if TARGET_OS_IPHONE
    sMotionManager = [[CMMotionManager alloc] init];
#else
    mKeyState = 0;
    mKeyStateOld = 0;
    mKeyDownStateTriggered = 0;
    mKeyUpStateTriggered = 0;
    
    mIsMouseDown = false;
    mIsMouseDownOld = false;
    mIsMouseDownTriggered = false;
    mIsMouseUpTriggered = false;
#endif
}


#if !TARGET_OS_IPHONE

bool GMInput::isKeyDown(GMKeyMask mask) const
{
    return (mKeyState & mask)? true: false;
}

bool GMInput::isKeyDownTriggered(GMKeyMask mask) const
{
    return (mKeyDownStateTriggered & mask)? true: false;
}

bool GMInput::isKeyUp(GMKeyMask mask) const
{
    return (mKeyState & mask)? false: true;
}

bool GMInput::isKeyUpTriggered(GMKeyMask mask) const
{
    return (mKeyUpStateTriggered & mask)? true: false;
}

bool GMInput::isMouseDown() const
{
    return mIsMouseDown;
}

bool GMInput::isMouseDownTriggered() const
{
    return mIsMouseDownTriggered;
}

bool GMInput::isMouseUp() const
{
    return !mIsMouseDown;
}

bool GMInput::isMouseUpTriggered() const
{
    return mIsMouseUpTriggered;
}


/* GMVector2D GMInput::getMouseLocation() const は GMInputObjC.mm で実装している。 */


void GMInput::__processKeyDown(GMKeyMask mask)
{
    mKeyState |= mask;
}

void GMInput::__processKeyUp(GMKeyMask mask)
{
    mKeyState &= ~mask;
}

void GMInput::__processMouseDown()
{
    mIsMouseDown = true;
}

void GMInput::__processMouseUp()
{
    mIsMouseDown = false;
}

#endif  //#if !TARGET_OS_IPHONE


#if TARGET_OS_IPHONE

unsigned GMInput::getTapCount(unsigned touchID) const
{
    std::map<unsigned, unsigned>::const_iterator it = mTapCountMap.find(touchID);
    if (it == mTapCountMap.end()) {
        return 0;
    }
    return (*it).second;
}

unsigned GMInput::getTapCountMax() const
{
    unsigned ret = 0;
    std::map<unsigned, unsigned>::const_iterator it = mTapCountMap.begin();
    while (it != mTapCountMap.end()) {
        unsigned count = (*it).second;
        if (count > ret) {
            ret = count;
        }
        it++;
    }
    return ret;
}

GMVector2D GMInput::getTouchLocation(unsigned touchID) const
{
    std::map<unsigned, GMVector2D>::const_iterator it = mTouchLocationMap.find(touchID);
    if (it == mTouchLocationMap.end()) {
        return GMVector2D(DBL_MAX, DBL_MAX);
    }
    return (*it).second;
}

GMVector2D GMInput::getTouchLocationAny() const
{
    if (mTouchIDs.size() == 0) {
        return GMVector2D(DBL_MAX, DBL_MAX);
    }
    std::map<unsigned, GMVector2D>::const_iterator it = mTouchLocationMap.begin();
    return (*it).second;
}

unsigned GMInput::getTouchCount() const
{
    int ret;
    ret = mTouchIDs.size();
    return ret;
}

std::set<unsigned> GMInput::getTouchIDs() const
{
    return mTouchIDs;
}

void GMInput::__addTouch(unsigned touchID, const GMVector2D& pos, unsigned tapCount)
{
    mTouchIDs.insert(touchID);
    mTapCountMap[touchID] = tapCount;
    mTouchLocationMap[touchID] = pos;
}

void GMInput::__updateTouch(unsigned touchID, const GMVector2D& pos, unsigned tapCount)
{
    std::set<unsigned>::const_iterator it = mTouchIDs.find(touchID);
    if (it == mTouchIDs.end()) {
        return;
    }
    mTapCountMap[touchID] = tapCount;
    mTouchLocationMap[touchID] = pos;
}

void GMInput::__removeTouch(unsigned touchID)
{
    mTouchIDs.erase(mTouchIDs.find(touchID));
    mTapCountMap.erase(mTapCountMap.find(touchID));
    mTouchLocationMap.erase(mTouchLocationMap.find(touchID));
}

#endif  //#if TARGET_OS_IPHONE


#if TARGET_OS_IPHONE

void GMInput::StartMotionUpdates()
{
    if (sIsUpdatingMotion) {
        return;
    }
    
    if (sMotionManager.accelerometerAvailable) {
        sMotionManager.accelerometerUpdateInterval = 1.0 / 60;
        [sMotionManager startAccelerometerUpdates];
    }
    if (sMotionManager.gyroAvailable) {
        sMotionManager.gyroUpdateInterval = 1.0 / 60;
        [sMotionManager startGyroUpdates];
    }

    sIsUpdatingMotion = true;
}

void GMInput::StopMotionUpdates()
{
    if (!sIsUpdatingMotion) {
        return;
    }
    
    if (sMotionManager.accelerometerActive) {
        [sMotionManager stopAccelerometerUpdates];
    }
    if (sMotionManager.gyroActive) {
        [sMotionManager stopGyroUpdates];
    }

    sIsUpdatingMotion = false;
}

bool GMInput::IsAccelerometerAvailable()
{
    return sMotionManager.accelerometerAvailable;
}

GMVector3D GMInput::GetAcceleration()
{
    CMAccelerometerData *data = sMotionManager.accelerometerData;
    if (data) {
        CMAcceleration acc = data.acceleration;
        return GMVector3D(acc.x, acc.y, acc.z);
    }
    return GMVector3D::Zero;
}

bool GMInput::IsGyroAvailable()
{
    return sMotionManager.gyroAvailable;
}

GMVector3D GMInput::GetGyroRotationRate()
{
    CMGyroData *data = sMotionManager.gyroData;
    if (data) {
        CMRotationRate rate = data.rotationRate;
        return GMVector3D(rate.x, rate.y, rate.z);
    }
    return GMVector3D::Zero;
}

#endif


void GMInput::__updateTriggers()
{
#if !TARGET_OS_IPHONE
    mKeyDownStateTriggered = mKeyState & ~mKeyStateOld;
    mKeyUpStateTriggered = ~mKeyState & mKeyStateOld;
	mKeyStateOld = mKeyState;
    
    mIsMouseDownTriggered = mIsMouseDown & ~mIsMouseDownOld;
    mIsMouseUpTriggered = ~mIsMouseDown & mIsMouseDownOld;
    mIsMouseDownOld = mIsMouseDown;
#endif
}

