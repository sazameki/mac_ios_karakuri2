//
//  GMInputObjC.mm
//  Game Framework
//
//  Created by numata on Dec 31, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMInput.h"

#import "GMAppDelegate.h"


GMVector2D GMInput::getMouseLocation() const
{
    NSPoint location = [[GMAppDelegate sharedInstance].window convertScreenToBase:[NSEvent mouseLocation]];
    return GMVector2D(location.x, location.y);
}

