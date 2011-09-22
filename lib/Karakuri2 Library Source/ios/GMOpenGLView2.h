//
//  GMOpenGLView2.h
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/25.
//  Copyright (c) 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#import "GMOpenGLView.h"

#include "GMGraphics.h"
#include "GMGame.h"


@interface GMOpenGLView2 : UIView {    
    EAGLContext*    context;
    
    GLint           framebufferWidth;
    GLint           framebufferHeight;
    GLuint          defaultFramebuffer;
    GLuint          colorRenderbuffer;

    GMOpenGLView*   mainGLView;
    
    GMGraphics*     mGraphics;
}

@property(readonly) GMGraphics*     graphics;

- (id)initWithFrame:(CGRect)frame mainGLView:(GMOpenGLView*)glView;

- (void)drawFrame:(GMGame*)game;

@end

