//
//  GMOpenGLView.h
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/08.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#include "GMGraphics.h"
#include "GMInput.h"
#include "GameMain.h"
#include "GMRandom.h"
#include "Globals.h"


@class GMOpenGLView2;


@interface GMOpenGLView : UIView {
    EAGLContext*    context;
    
    BOOL            animating;
    NSInteger       animationFrameInterval;
    CADisplayLink*  displayLink;

    GLint           framebufferWidth;
    GLint           framebufferHeight;
    GLuint          defaultFramebuffer;
    GLuint          colorRenderbuffer;
    GLuint          depthRenderbuffer;
    
#if GM_USES_MULTI_SAMPLE_ANTI_ALIASING
	GLuint          msaaRenderbuffer;
    GLuint          msaaFramebuffer;
#endif
    
    GMOpenGLView2*  glView2;
    
    // ゲーム関係の変数
    GameMain*       mGameInst;
    GMGraphics*     mGraphics;
    GMInput*        mInput;
    GMRandom*       mRandom;
}

@property(readonly, nonatomic, getter=isAnimating) BOOL animating;
@property(nonatomic) NSInteger animationFrameInterval;
@property(nonatomic, retain) EAGLContext *context;
@property(readonly) GMGraphics* graphics;

- (void)startAnimation;
- (void)stopAnimation;

- (void)setGLView2:(GMOpenGLView2*)_glView2;

- (GameMain*)game;

@end

