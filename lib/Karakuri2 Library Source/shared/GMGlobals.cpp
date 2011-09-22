//
//  GMGlobals.cpp
//  Game Framework
//
//  Created by numata on Dec 26, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import "GMGlobals.h"


GMColor     gGMDefaultStartUpColor      = GMColor(1.0, 1.0, 1.0, 1.0);
bool        gGMHasTerminatedWithError   = false;
GMScene*    gGMNextScene                = NULL;
bool        gGMIsDrawing                = false;
bool        gGMHasGameStartError        = false;
std::string gGMErrorStr                 = "";
double      gGMLineWidth                = 0.0;
double      gGMPointSize                = 0.0;

