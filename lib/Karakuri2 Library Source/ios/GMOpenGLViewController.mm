//
//  GMOpenGLViewController.m
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/22.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import "GMOpenGLViewController.h"
#import "Globals.h"


@implementation GMOpenGLViewController

- (id)initWithGLView:(GMOpenGLView *)glView
{
    self = [super init];
    if (self) {
        self.view = glView;
    }
    return self;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    if (GMScreenIsVertical) {
        return UIInterfaceOrientationIsPortrait(interfaceOrientation);
    } else {
        return UIInterfaceOrientationIsLandscape(interfaceOrientation);
    }
}

@end

