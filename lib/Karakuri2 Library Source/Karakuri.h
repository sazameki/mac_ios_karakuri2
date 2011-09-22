//
//  Karakuri.h
//  Game Framework
//
//  Created by numata on Dec 27, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GAME_FRAMEWORK_H__
#define __GAME_FRAMEWORK_H__

#include <TargetConditionals.h>

// Special Basic
#if TARGET_OS_IPHONE
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#else
#include <OpenGL/glu.h>
#endif

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// Shader Support
#include "GMEffect.h"
#include "GMBasicEffect.h"

// Foundation Base
#include "GMGlobals.h"
#include "GMTypes.h"
#include "GMException.h"
#include "GMGame.h"
#include "GMInput.h"
#include "GMRandom.h"
#include "GMTextReader.h"
#include "GMStringSupport.h"
//#include "GMViewport.h"

// Foundation Ext
#include "GMScene.h"

// Graphics Base
#include "GMDrawSys.h"
#include "GMDraw.h"
#include "GMTexture2D.h"
#include "GMGraphics.h"
#include "GMButton.h"
#include "GMLabel.h"
#include "GMRenderTarget2D.h"

// Graphics Ext
#include "GMSpriteBatch.h"
#include "GMParticle.h"

// Model
//#include "GMModel.h"

// Shader
#include "GMEffect.h"
#include "GMBasicEffect.h"

// Audio
#include "GMMusic.h"
#include "GMSound.h"

// Debugging Support
#include "GMDebug.h"


#endif  //#ifndef __GAME_FRAMEWORK_H__

