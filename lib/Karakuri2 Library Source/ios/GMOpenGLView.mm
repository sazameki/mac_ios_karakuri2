//
//  GMOpenGLView.m
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/08.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import "GMOpenGLView.h"

#import "GMAppDelegate.h"
#import "GMOpenGLView2.h"
#include "Globals.h"
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/ES1/glext.h>


@interface GMOpenGLView ()

@property (nonatomic, assign) CADisplayLink *displayLink;

- (void)setFramebuffer;
- (void)deleteFramebuffer;
- (BOOL)presentFramebuffer;

- (void)prepareOpenGL;

@end


@implementation GMOpenGLView

@synthesize animating;
@synthesize context;
@synthesize displayLink;
@synthesize graphics = mGraphics;

+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

- (void)setupEAGL
{
    EAGLContext *aContext = nil;
    
    if (GMShaderEnabled) {
        aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        if (!aContext) {
            NSLog(@"Failed to create GLES2 context.");
        } else {
#if DEBUG
            NSLog(@"Using GLES2 (Main Display)");
#endif  //#if DEBUG
        }
    }
    
    if (!aContext) {
        aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
        if (!aContext) {
            NSLog(@"Failed to create GLES1 context.");
        } else {
#if DEBUG
            NSLog(@"Using GLES1 (Main Display)");
#endif  //#if DEBUG
        }
    }
    
    if (![EAGLContext setCurrentContext:aContext]) {
        NSLog(@"Failed to set the GLES context as a current context.");
        return;
    }
    
	self.context = aContext;
	[aContext release];
	
    [self setFramebuffer];
    
    animating = NO;
    animationFrameInterval = 1;
    self.displayLink = nil;
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // グラフィックコンテキストの初期化
        mGraphics = new GMGraphics();
        CGSize frameSize = frame.size;
        if (GMScreenIsVertical) {
            mGraphics->__setOpenGLViewFrameSize(GMVector2D(frameSize.width, frameSize.height));
        } else {
            mGraphics->__setOpenGLViewFrameSize(GMVector2D(frameSize.height, frameSize.width));
        }

        [self setupEAGL];

        CAEAGLLayer* eaglLayer = (CAEAGLLayer*)self.layer;
        
        eaglLayer.opaque = YES;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking,
                                        kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat,
                                        nil];
    }
    return self;
}

/*
    ゲームの初期化を行う。
 */
- (void)prepareGame
{
    try {
        // 乱数の初期化
        mRandom = new GMRandom();
        
        // ゲーム本体の作成
        mGameInst = new GameMain();
    } catch (GMException& e) {
        gGMErrorStr = e.what();
        gGMHasGameStartError = true;
    }
}

- (void)dealloc
{
    [self deleteFramebuffer];
    
    if ([EAGLContext currentContext] == context) {
        [EAGLContext setCurrentContext:nil];
    }
    [context release];
    
    delete mRandom;
    delete mGameInst;
    delete mGraphics;
    
    [super dealloc];
}

- (GameMain*)game
{
    return mGameInst;
}

- (void)prepareOpenGL
{
    // デプステストの設定
    glDisable(GL_DEPTH_TEST);
    
    // ブレンドモードの設定
    glEnable(GL_BLEND);

    // ビューポート切り取りの設定
    glDisable(GL_SCISSOR_TEST);
    
    // 各種頂点配列操作の有効化
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    // シェーダを使用しているかどうかをセットする
    if ([context API] == kEAGLRenderingAPIOpenGLES2) {
        mGraphics->__setShaderEnabled(true);
    } else {
        mGraphics->__setShaderEnabled(false);
    }

    // 入力マネージャの初期化
    mInput = new GMInput();    

    // ゲームの初期化
    if (gGMNextScene != NULL) {
        try {
            mGameInst->__applySceneChange();
        } catch (GMException& e) {
            gGMErrorStr = e.what();
            gGMHasGameStartError = true;
        }
    }
}

- (NSInteger)animationFrameInterval
{
    return animationFrameInterval;
}

- (void)setAnimationFrameInterval:(NSInteger)frameInterval
{
    /*
	 Frame interval defines how many display frames must pass between each time the display link fires.
	 The display link will only fire 30 times a second when the frame internal is two on a display that refreshes 60 times a second. The default frame interval setting of one will fire 60 times a second when the display refreshes at 60 times a second. A frame interval setting of less than one results in undefined behavior.
	 */
    if (frameInterval >= 1) {
        animationFrameInterval = frameInterval;
        
        if (animating) {
            [self stopAnimation];
            [self startAnimation];
        }
    }
}

- (void)createFramebuffer
{
    if (context && !defaultFramebuffer) {
        [EAGLContext setCurrentContext:context];
        
        // Create default framebuffer object.
        glGenFramebuffers(1, &defaultFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);

        // Create color render buffer and allocate backing store.
        glGenRenderbuffers(1, &colorRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer *)self.layer];
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &framebufferWidth);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &framebufferHeight);

        // Create depth buffer and allocate backing store.
        glGenRenderbuffers(1, &depthRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, framebufferWidth, framebufferHeight);
        
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);

#if GM_USES_MULTI_SAMPLE_ANTI_ALIASING
        glGenFramebuffers(1, &msaaFramebuffer);
        glGenRenderbuffers(1, &msaaRenderbuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, msaaFramebuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, msaaRenderbuffer);
        GLint maxSamplesAllowed;
        glGetIntegerv(GL_MAX_SAMPLES_APPLE, &maxSamplesAllowed);
        glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, maxSamplesAllowed, GL_RGB5_A1, framebufferWidth, framebufferHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, msaaRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
        glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, maxSamplesAllowed, GL_DEPTH_COMPONENT16, framebufferWidth , framebufferHeight);
#endif
        
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            NSLog(@"Failed to make complete framebuffer object %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
        }
    }
}

- (void)deleteFramebuffer
{
    if (context) {
        [EAGLContext setCurrentContext:context];
        
        if (defaultFramebuffer) {
            glDeleteFramebuffers(1, &defaultFramebuffer);
            defaultFramebuffer = 0;
        }
        
        if (colorRenderbuffer) {
            glDeleteRenderbuffers(1, &colorRenderbuffer);
            colorRenderbuffer = 0;
        }

        if (depthRenderbuffer) {
            glDeleteRenderbuffers(1, &depthRenderbuffer);
            depthRenderbuffer = 0;
        }
        
#if GM_USES_MULTI_SAMPLE_ANTI_ALIASING
        if (msaaFramebuffer) {
            glDeleteFramebuffers(1, &msaaFramebuffer);
            msaaFramebuffer = 0;
        }
        if (msaaRenderbuffer) {
            glDeleteRenderbuffersOES(1, &msaaRenderbuffer);
            msaaRenderbuffer = 0;
        }
#endif
    }
}

- (void)setFramebuffer
{
    if (context) {
        [EAGLContext setCurrentContext:context];
        
        if (!defaultFramebuffer) {
            [self createFramebuffer];
        }
        
#if GM_USES_MULTI_SAMPLE_ANTI_ALIASING
        glBindFramebuffer(GL_FRAMEBUFFER, msaaFramebuffer);
        mGraphics->__setCurrentMainFramebuffer(msaaFramebuffer);
#else
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
        mGraphics->__setCurrentMainFramebuffer(defaultFramebuffer);
#endif
        glViewport(0, 0, framebufferWidth, framebufferHeight);
    }
}

- (BOOL)presentFramebuffer
{
    BOOL success = NO;
    
    if (context) {
        [EAGLContext setCurrentContext:context];
        
#if GM_USES_MULTI_SAMPLE_ANTI_ALIASING
        GLenum attachments[] = { GL_DEPTH_ATTACHMENT };
        glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, 1, attachments);
        
        glBindFramebuffer(GL_READ_FRAMEBUFFER_APPLE, msaaFramebuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER_APPLE, defaultFramebuffer); 
        glResolveMultisampleFramebufferAPPLE();
#endif
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        success = [context presentRenderbuffer:GL_RENDERBUFFER];
    }
    
    return success;
}

- (void)startAnimation
{
    if (animating) {
        return;
    }
    
    if (gGMHasGameStartError) {
        return;
    }

    CADisplayLink *aDisplayLink = [[UIScreen mainScreen] displayLinkWithTarget:self selector:@selector(drawFrame)];
    [aDisplayLink setFrameInterval:animationFrameInterval];
    [aDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    self.displayLink = aDisplayLink;
    
    animating = YES;
}

- (void)stopAnimation
{
    if (!animating) {
        return;
    }
    
    [self.displayLink invalidate];
    self.displayLink = nil;
    animating = NO;
}

- (void)drawFrame
{
    [self setFramebuffer];
    
    GMGraphics::CurrentGraphics = mGraphics;
    try {
        mGameInst->drawView(mGraphics);
    } catch (GMException& e) {
        [[GMAppDelegate sharedAppDelegate] showRuntimeError:[NSString stringWithFormat:@"%s", e.what()]];
    }

    [self presentFramebuffer];
    
    if (glView2) {
        [glView2 drawFrame:mGameInst];
    }
    
    mInput->__updateTriggers();
    try {
        mGameInst->updateModel(mInput);
    } catch (GMException& e) {
        [[GMAppDelegate sharedAppDelegate] showRuntimeError:[NSString stringWithFormat:@"%s", e.what()]];
    }
    if (gGMNextScene != NULL) {
        mGameInst->__applySceneChange();
    }
}

- (void)touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event
{
    GMVector2D screenSize = [GMAppDelegate sharedAppDelegate].glView.graphics->getScreenSize();
    for (UITouch* aTouch in [touches allObjects]) {
        CGPoint pos = [aTouch locationInView:self];
        mInput->__addTouch((unsigned)aTouch, GMVector2D(pos.x, screenSize.y-pos.y), aTouch.tapCount);
    }
}

- (void)touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event
{
    GMVector2D screenSize = [GMAppDelegate sharedAppDelegate].glView.graphics->getScreenSize();
    for (UITouch* aTouch in touches) {
        CGPoint pos = [aTouch locationInView:self];
        mInput->__updateTouch((unsigned)aTouch, GMVector2D(pos.x, screenSize.y-pos.y), aTouch.tapCount);
    }
}

- (void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event
{
    for (UITouch* aTouch in touches) {
        mInput->__removeTouch((unsigned)aTouch);
    }
}

- (void)setGLView2:(GMOpenGLView2*)_glView2
{
    glView2 = _glView2;
}

@end


