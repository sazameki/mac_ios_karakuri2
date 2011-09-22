//
//  GMAppDelegate.h
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/08.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "GMOpenGLView.h"
#import "GMOpenGLView2.h"
#import "GMOpenGLViewController.h"


@interface GMAppDelegate : NSObject <UIApplicationDelegate, UIAlertViewDelegate> {
    UIWindow*               window;
    GMOpenGLView*           glView;
    GMOpenGLView2*          glView2;
    GMOpenGLViewController* glViewController;
}

@property(readonly) GMOpenGLView*   glView;
@property(readonly) GMOpenGLView2*  glView2;

+ (GMAppDelegate*)sharedAppDelegate;

- (void)showRuntimeError:(NSString *)message;

@end

