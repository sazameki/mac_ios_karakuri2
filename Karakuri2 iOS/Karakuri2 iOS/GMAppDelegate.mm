//
//  GMAppDelegate.mm
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/08.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import "GMAppDelegate.h"
#include "GMSound.h"
#import "GMSoundImpl.h"


static GMAppDelegate*   sInstance = nil;


@interface GMOpenGLView ()

- (void)prepareGame;
- (void)prepareOpenGL;

@end


@interface GMOpenGLView2 ()

- (void)prepareOpenGL;

@end


@implementation GMAppDelegate

@synthesize glView;
@synthesize glView2;

+ (GMAppDelegate*)sharedAppDelegate
{
    return sInstance;
}

- (void)prepareSubScreen:(UIScreen*)subScreen
{
    CGRect frame = subScreen.bounds;
    UIWindow* subWindow = [[UIWindow alloc] initWithFrame:frame];
    [subWindow setScreen:subScreen];
    
    glView2 = [[GMOpenGLView2 alloc] initWithFrame:frame mainGLView:glView];
    glView2.backgroundColor = [UIColor whiteColor];
    [subWindow addSubview:glView2];
    [glView2 release];
    
    [glView2 prepareOpenGL];
    
    subWindow.hidden = NO;
}

- (void)subScreenDidConnect:(NSNotification*)notification
{
    [self prepareSubScreen:[notification object]];
}

- (void)subScreenDidDisconnect:(NSNotification*)notification
{
    // TODO: サブディスプレイ切断時の処理
}

- (void)subScreenModeDidChange:(NSNotification*)notification
{
    // TODO: サブディスプレイのモード変更時の処理
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    sInstance = self;

    _GMInitSound();
    _GMInitOpenAL();
    
    CGRect bounds = [[UIScreen mainScreen] bounds];
    bounds.origin = CGPointZero;

    window = [[UIWindow alloc] initWithFrame:bounds];
    
    if (!GMScreenIsVertical) {
        CGFloat originalWidth = bounds.size.width;
        bounds.size.width = bounds.size.height;
        bounds.size.height = originalWidth;
    }
    glView = [[GMOpenGLView alloc] initWithFrame:bounds];
    glView.backgroundColor = [UIColor whiteColor];
    glView.multipleTouchEnabled = YES;
    
    glViewController = [[GMOpenGLViewController alloc] initWithGLView:glView];
    window.rootViewController = glViewController;
    
    [glView prepareGame];
    [glView prepareOpenGL];
    
    if (GMSubdisplayEnabled) {
        if ([[UIScreen screens] count] >= 2) {
            UIScreen* subScreen = [[UIScreen screens] lastObject];
            [self prepareSubScreen:subScreen];
        }
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(subScreenDidConnect:) name:UIScreenDidConnectNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(subScreenDidDisconnect:) name:UIScreenDidDisconnectNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(subScreenModeDidChange:) name: UIScreenModeDidChangeNotification object: nil];
    }
    
    [window makeKeyAndVisible];
    
    if (gGMHasGameStartError) {
        [self showRuntimeError:[NSString stringWithFormat:@"%s", gGMErrorStr.c_str()]];
    }
    
    return YES;
}

- (void)showRuntimeError:(NSString *)message
{
    UIAlertView* alert = [[UIAlertView alloc] initWithTitle:@"Karakuri2 Runtime Error"
                                                    message:[message stringByAppendingString:@" (See backtrace)"]
                                                   delegate:self cancelButtonTitle:nil otherButtonTitles:@"OK", nil];
    [alert show];
}

- (void)dealloc
{
    [window release];
    [glView release];
    [glViewController release];
    
    _GMCleanUpOpenAL();

    [super dealloc];
}

- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex
{
    exit(0);
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    [glView stopAnimation];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
     */
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    /*
     Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
     */
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    [glView startAnimation];
}

/*
    アプリケーション終了直前に呼ばれる。
    保存するデータがあれば保存する。
 */
- (void)applicationWillTerminate:(UIApplication *)application
{
    [glView stopAnimation];
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
