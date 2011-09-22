//
//  GMOpenGLView2.m
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/25.
//  Copyright (c) 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import "GMOpenGLView2.h"

#import "GMOpenGLView.h"
#import "GMAppDelegate.h"
#include "Globals.h"
#import <QuartzCore/QuartzCore.h>


@interface GMOpenGLView2 ()

@property (nonatomic, retain) EAGLContext *context;

- (void)setFramebuffer;
- (void)deleteFramebuffer;
- (BOOL)presentFramebuffer;

- (void)prepareOpenGL;

@end


@implementation GMOpenGLView2

@synthesize context;
@synthesize graphics = mGraphics;

+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

- (void)setupEAGL
{
    EAGLContext *aContext = nil;
    
    if (GMShaderEnabled) {
        aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2 sharegroup:[mainGLView.context sharegroup]];
        if (!aContext) {
            NSLog(@"Failed to create GLES2 context.");
        } else {
#if DEBUG
            NSLog(@"Using GLES2 (Sub Display)");
#endif  //#if DEBUG
        }
    }
    
    if (!aContext) {
        aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1 sharegroup:[mainGLView.context sharegroup]];
        if (!aContext) {
            NSLog(@"Failed to create GLES1 context.");
        } else {
#if DEBUG
            NSLog(@"Using GLES1 (Sub Display)");
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
}

- (id)initWithFrame:(CGRect)frame mainGLView:(GMOpenGLView*)glView
{
    self = [super initWithFrame:frame];
    if (self) {
        mainGLView = glView;
        [mainGLView setGLView2:self];
        
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

- (void)dealloc
{
    [self deleteFramebuffer];
    
    if ([EAGLContext currentContext] == context) {
        [EAGLContext setCurrentContext:nil];
    }
    [context release];
    
    delete mGraphics;
    
    [super dealloc];
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
    
    // グラフィックコンテキストの初期化
    mGraphics = new GMGraphics();
    CGSize frameSize = [self frame].size;
    mGraphics->__setOpenGLViewFrameSize(GMVector2D(frameSize.width, frameSize.height));
    
    if ([context API] == kEAGLRenderingAPIOpenGLES2) {
        mGraphics->__setShaderEnabled(true);
    } else {
        mGraphics->__setShaderEnabled(false);
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
        NSLog(@"frame: %d, %d", framebufferWidth, framebufferHeight);
        
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);
        
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
    }
}

- (void)setFramebuffer
{
    if (context) {
        [EAGLContext setCurrentContext:context];
        
        if (!defaultFramebuffer) {
            [self createFramebuffer];
        }
        
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
        
        glViewport(0, 0, framebufferWidth, framebufferHeight);
    }
}

- (BOOL)presentFramebuffer
{
    BOOL success = NO;
    
    if (context) {
        [EAGLContext setCurrentContext:context];
        
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        
        success = [context presentRenderbuffer:GL_RENDERBUFFER];
    }
    
    return success;
}

- (void)drawFrame:(GMGame*)game
{
    [self setFramebuffer];
    
    GMGraphics::CurrentGraphics = mGraphics;
    if ([context API] == kEAGLRenderingAPIOpenGLES2) {
        // We don' use the GLES2 at now.
    } else {
        try {
            game->drawView2(mGraphics);
        } catch (GMException& e) {
            [[GMAppDelegate sharedAppDelegate] showRuntimeError:[NSString stringWithFormat:@"%s", e.what()]];
        }
    }
    
    [self presentFramebuffer];
}

@end

