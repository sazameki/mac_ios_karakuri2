//
//  GMAppDelegate.h
//  Karakuri2 Mac
//
//  Created by Satoshi Numata on 11/08/07.
//  Copyright (c) 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "GMOpenGLView.h"


@interface GMAppDelegate : NSObject {
    NSWindow*       window;
    GMOpenGLView*   glView;
}

@property (assign) IBOutlet NSWindow*       window;
@property (assign) IBOutlet GMOpenGLView*   glView;

+ (GMAppDelegate*)sharedInstance;

@end
