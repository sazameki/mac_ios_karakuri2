//
//  GMOpenGLView.mm
//  Game Framework
//
//  Created by numata on Dec 25, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import "GMOpenGLView.h"
#import <OpenGL/OpenGL.h>
#import <OpenGL/glu.h>
#import <mach/mach.h>
#import <mach/mach_time.h>
#include "GMGlobals.h"
#include "GMException.h"
#include "GMDraw.h"
#include "GMGlobals.h"
#include "GMGraphics.h"
#include "GMTexture2D.h"


// OpenGL の型とサイズ
//     GLubyte (1byte): 0〜255
//     GLshort (2byte): -32768〜32767

// XIB における NSOpenGLView の設定について
//     ※ ウィンドウの「One Shot」設定は OFF にしておくこと。
//     Color: カラーバッファのサイズ
//     Depth: デプスバッファのサイズ
//     Stencil: ステンシルバッファのサイズ
//     Accum: アキュムレーションバッファのサイズ（glAccum() で操作する）
//     Auxiliary Buffers: 補助バッファのサイズ。使い方はユーザ次第。
//     Buffer: ダブルバッファリングの指定
//     Sampling: マルチサンプルの指定（アンチエイリアスの方法）
//     Renderer: 
//         Accelerated: Hardware-accelerated → 通常の Accelerated の順でレンダラを選択する。（基本的にこれを使う）
//         Allow Offline: 速度よりも優先してオフラインレンダリングを行う。基本的に遅いので ON にするべきではない。
//         No Recovery: Accelerated renderer がリソース不足で失敗した場合に、OpenGL が他のレンダラにスイッチしないようにするかどうかを指定する。
//                      どの道、リソース不足になるのが異常事態なので、どっちでもあまり変わらないと思う。
//                      いちおう OFF にしておいた方がユーザには優しいのかな？
//     Policy: 指定に合致するピクセルフォーマットの選択ポリシー
//         Minimum: 最低でも要求されたバッファサイズ以上のサイズが選択される。
//         Maximum: ゼロでないバッファサイズが指定された場合、可能な限り大きなバッファサイズが選択される。
//         Closest: 要求されたバッファサイズにもっとも近いカラーバッファのサイズが選択される。
//             Minimum と Maximum はカラーバッファ、デプスバッファ、アキュムレーションバッファのバッファサイズにのみ適用される。
//             Closest はカラーバッファのバッファサイズにのみ適用される。


@implementation GMOpenGLView

/*
    ゲームの初期化を行う。
 */
- (void)prepareGame
{
    mIsShiftKeyDown = false;
    
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
    delete mRandom;
    delete mGameInst;
    
    [super dealloc];
}

- (GameMain*)game
{
    return mGameInst;
}

/*
    起動時の設定を行う。
 */
- (void)prepareOpenGL
{
    // CGL コンテキストの取得
    mCGLContext = (CGLContextObj)[[self openGLContext] CGLContextObj];
    
    // デプステストの設定
    glDisable(GL_DEPTH_TEST);
    
    // ブレンドモードの設定
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // ビューポート切り取りの設定
    glDisable(GL_SCISSOR_TEST);
    
    // 各種頂点配列操作の有効化・無効化
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    // VSYNC を有効にする場合には、以下の2行のコメントアウトを取り除く。ただし、あまり推奨できない。
    // チラツキの対処方法は、あきらめるのがいちばん。ゲームをプレイしている者はそこまで気にしない。
    //GLint sync = 1;
    //CGLSetParameter(mCGLContext, kCGLCPSwapInterval, &sync);

    // グラフィックコンテキストの初期化
    mGraphics = new GMGraphics();
    NSSize frameSize = [self frame].size;
    mGraphics->__setOpenGLViewFrameSize(GMVector2D(frameSize.width, frameSize.height));

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
    
    // 表画面と裏画面の両方に描画しておく
    GMColor startUpColor = mGameInst->getStartUpColor();
    glClearColor(startUpColor.r, startUpColor.g, startUpColor.b, startUpColor.a);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    CGLFlushDrawable(mCGLContext);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    CGLFlushDrawable(mCGLContext);

    // ゲームスレッドの作成
    if (!gGMHasGameStartError) {
        mIsRunning = NO;
        mIsFinished = NO;
        [NSThread detachNewThreadSelector:@selector(gameProc:)
                                 toTarget:self
                               withObject:nil];
    }
}

/*
    画面サイズ変更時の処理を行う。
    → 画面サイズ変更は禁止しておく。
 */
- (void)reshape
{
    //NSSize frameSize = [self frame].size;
    //mGraphics->setOpenGLViewFrameSize(GMVector2D(frameSize.width, frameSize.height));
}

/*
    描画のメインの処理を行う。
 */
- (void)drawRect:(NSRect)dirtyRect
{
    if (!gGMHasGameStartError) {
        CGLLockContext(mCGLContext);
        CGLSetCurrentContext(mCGLContext);

        GMGraphics::CurrentGraphics = mGraphics;
        try {
            mGameInst->drawView(mGraphics);
        } catch (GMException& e) {
        }
        
        CGLFlushDrawable(mCGLContext);
        CGLUnlockContext(mCGLContext);
    }
}

- (void)stopGame
{
    mIsRunning = NO;
}

- (void)gameProc:(id)dummy
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    
    // ナノ秒から Mach 時間に変換
    mach_timebase_info_data_t timebaseInfo;
    mach_timebase_info(&timebaseInfo);
    uint64_t frameInterval = (uint64_t)(1000000000 / GM_ANIMATION_RATE) * timebaseInfo.denom / timebaseInfo.numer;
    uint64_t prevTime = mach_absolute_time();
    
    mIsRunning = YES;
    
    gGMHasTerminatedWithError = NO;
    BOOL mIsCGLContextLocked = NO;
    try {
        CGLLockContext(mCGLContext);
        CGLSetCurrentContext(mCGLContext);
        //mGraphics->setViewport(mGraphics->getViewport());
        CGLUnlockContext(mCGLContext);

        while (mIsRunning) {
            // ビューの描画
            CGLLockContext(mCGLContext);
            CGLSetCurrentContext(mCGLContext);
            mIsCGLContextLocked = YES;
            GMGraphics::CurrentGraphics = mGraphics;
            mGameInst->drawView(mGraphics);
            if (gGMIsDrawing) {
                throw GMInvalidOperationException("GMDraw::end() was not invoked after GMDraw::begin().");
            }
            CGLFlushDrawable(mCGLContext);
            CGLUnlockContext(mCGLContext);
            mIsCGLContextLocked = NO;
            
            // モデル更新回数の計算
            uint64_t endTime = prevTime + frameInterval;
            int modelUpdateCount = (int)((mach_absolute_time() - prevTime) / frameInterval);
            if (modelUpdateCount <= 0) {
                modelUpdateCount = 1;
            } else if (modelUpdateCount > 5) {
                modelUpdateCount = 5;
            }
            
            // モデルの更新
            for (int i = 0; i < modelUpdateCount; i++) {
                mInput->__updateTriggers();
                mGameInst->updateModel(mInput);
                if (gGMNextScene != NULL) {
                    break;
                }
            }
            if (gGMNextScene != NULL) {
                mGameInst->__applySceneChange();
            }
            
            // 休ませる
            prevTime = mach_absolute_time();
            if (endTime > prevTime) {
                mach_wait_until(endTime);
                prevTime = endTime;
            }
        }
    } catch (GMException& e) {
        gGMHasTerminatedWithError= YES;
        
        CGLUnlockContext(mCGLContext);
        
        NSAlert* alert = [NSAlert alertWithMessageText:[NSString stringWithFormat:@"%s", e.getExceptionClassName().c_str()]
                                         defaultButton:@"OK"
                                       alternateButton:nil
                                           otherButton:nil
                             informativeTextWithFormat:[NSString stringWithFormat:@"%s", e.what()], nil];
        [alert beginSheetModalForWindow:[self window] modalDelegate:self didEndSelector:@selector(gameErrorAlertDidEnd:returnCode:contextInfo:) contextInfo:NULL];
    }
    
    delete mGraphics;
    delete mInput;
    delete mRandom;
    
    delete mGameInst;

    mIsFinished = YES;
    
    if (!gGMHasTerminatedWithError) {
        [NSApp replyToApplicationShouldTerminate:YES];
    }
    
    [pool drain];
}

- (void)gameErrorAlertDidEnd:(NSAlert*)alert
                  returnCode:(NSInteger)returnCode
                 contextInfo:(void*)contextInfo
{
    [NSApp terminate:self];
}

- (void)keyDown:(NSEvent*)theEvent
{
    unsigned short keyCode = [theEvent keyCode];
    
    if (keyCode == 0x7e) {
        mInput->__processKeyDown(GMKeyMaskUp);
    }
    else if (keyCode == 0x7d) {
        mInput->__processKeyDown(GMKeyMaskDown);
    }
    else if (keyCode == 0x7b) {
        mInput->__processKeyDown(GMKeyMaskLeft);
    }
    else if (keyCode == 0x7c) {
        mInput->__processKeyDown(GMKeyMaskRight);
    }
    else if (keyCode == 0x00) {
        mInput->__processKeyDown(GMKeyMaskA);
    }
    else if (keyCode == 0x0b) {
        mInput->__processKeyDown(GMKeyMaskB);
    }
    else if (keyCode == 0x08) {
        mInput->__processKeyDown(GMKeyMaskC);
    }
    else if (keyCode == 0x02) {
        mInput->__processKeyDown(GMKeyMaskD);
    }
    else if (keyCode == 0x0e) {
        mInput->__processKeyDown(GMKeyMaskE);
    }
    else if (keyCode == 0x03) {
        mInput->__processKeyDown(GMKeyMaskF);
    }
    else if (keyCode == 0x05) {
        mInput->__processKeyDown(GMKeyMaskG);
    }
    else if (keyCode == 0x04) {
        mInput->__processKeyDown(GMKeyMaskH);
    }
    else if (keyCode == 0x22) {
        mInput->__processKeyDown(GMKeyMaskI);
    }
    else if (keyCode == 0x26) {
        mInput->__processKeyDown(GMKeyMaskJ);
    }
    else if (keyCode == 0x28) {
        mInput->__processKeyDown(GMKeyMaskK);
    }
    else if (keyCode == 0x25) {
        mInput->__processKeyDown(GMKeyMaskL);
    }
    else if (keyCode == 0x2e) {
        mInput->__processKeyDown(GMKeyMaskM);
    }
    else if (keyCode == 0x2d) {
        mInput->__processKeyDown(GMKeyMaskN);
    }
    else if (keyCode == 0x1f) {
        mInput->__processKeyDown(GMKeyMaskO);
    }
    else if (keyCode == 0x23) {
        mInput->__processKeyDown(GMKeyMaskP);
    }
    else if (keyCode == 0x0c) {
        mInput->__processKeyDown(GMKeyMaskQ);
    }
    else if (keyCode == 0x0f) {
        mInput->__processKeyDown(GMKeyMaskR);
    }
    else if (keyCode == 0x01) {
        mInput->__processKeyDown(GMKeyMaskS);
    }
    else if (keyCode == 0x11) {
        mInput->__processKeyDown(GMKeyMaskT);
    }
    else if (keyCode == 0x20) {
        mInput->__processKeyDown(GMKeyMaskU);
    }
    else if (keyCode == 0x09) {
        mInput->__processKeyDown(GMKeyMaskV);
    }
    else if (keyCode == 0x0d) {
        mInput->__processKeyDown(GMKeyMaskW);
    }
    else if (keyCode == 0x07) {
        mInput->__processKeyDown(GMKeyMaskX);
    }
    else if (keyCode == 0x10) {
        mInput->__processKeyDown(GMKeyMaskY);
    }
    else if (keyCode == 0x06) {
        mInput->__processKeyDown(GMKeyMaskZ);
    }
    else if (keyCode == 0x1d || keyCode == 0x52) {
        mInput->__processKeyDown(GMKeyMask0);
    }
    else if (keyCode == 0x12 || keyCode == 0x53) {
        mInput->__processKeyDown(GMKeyMask1);
    }
    else if (keyCode == 0x13 || keyCode == 0x54) {
        mInput->__processKeyDown(GMKeyMask2);
    }
    else if (keyCode == 0x14 || keyCode == 0x55) {
        mInput->__processKeyDown(GMKeyMask3);
    }
    else if (keyCode == 0x15 || keyCode == 0x56) {
        mInput->__processKeyDown(GMKeyMask4);
    }
    else if (keyCode == 0x17 || keyCode == 0x57) {
        mInput->__processKeyDown(GMKeyMask5);
    }
    else if (keyCode == 0x16 || keyCode == 0x58) {
        mInput->__processKeyDown(GMKeyMask6);
    }
    else if (keyCode == 0x1a || keyCode == 0x59) {
        mInput->__processKeyDown(GMKeyMask7);
    }
    else if (keyCode == 0x1c || keyCode == 0x5b) {
        mInput->__processKeyDown(GMKeyMask8);
    }
    else if (keyCode == 0x19 || keyCode == 0x5c) {
        mInput->__processKeyDown(GMKeyMask9);
    }
    else if (keyCode == 0x31) {
        mInput->__processKeyDown(GMKeyMaskSpace);
    }
    else if (keyCode == 0x35) {
        mInput->__processKeyDown(GMKeyMaskEscape);
    }
    else if (keyCode == 0x24 || keyCode == 0x4c) {
        mInput->__processKeyDown(GMKeyMaskReturn);
    }
    else {
        NSLog(@"Key: 0x%02x", keyCode);
    }
}

- (void)flagsChanged:(NSEvent*)theEvent
{
    NSUInteger modifierFlags = [theEvent modifierFlags];
    
    if (modifierFlags & NSShiftKeyMask) {
        mIsShiftKeyDown = true;
        mInput->__processKeyDown(GMKeyMaskShift);
    } else if (mIsShiftKeyDown) {
        mIsShiftKeyDown = false;
        mInput->__processKeyUp(GMKeyMaskShift);
    }
}

- (void)keyUp:(NSEvent*)theEvent
{
    unsigned short keyCode = [theEvent keyCode];
    
    if (keyCode == 0x7e) {
        mInput->__processKeyUp(GMKeyMaskUp);
    }
    else if (keyCode == 0x7d) {
        mInput->__processKeyUp(GMKeyMaskDown);
    }
    else if (keyCode == 0x7b) {
        mInput->__processKeyUp(GMKeyMaskLeft);
    }
    else if (keyCode == 0x7c) {
        mInput->__processKeyUp(GMKeyMaskRight);
    }
    else if (keyCode == 0x00) {
        mInput->__processKeyUp(GMKeyMaskA);
    }
    else if (keyCode == 0x0b) {
        mInput->__processKeyUp(GMKeyMaskB);
    }
    else if (keyCode == 0x08) {
        mInput->__processKeyUp(GMKeyMaskC);
    }
    else if (keyCode == 0x02) {
        mInput->__processKeyUp(GMKeyMaskD);
    }
    else if (keyCode == 0x0e) {
        mInput->__processKeyUp(GMKeyMaskE);
    }
    else if (keyCode == 0x03) {
        mInput->__processKeyUp(GMKeyMaskF);
    }
    else if (keyCode == 0x05) {
        mInput->__processKeyUp(GMKeyMaskG);
    }
    else if (keyCode == 0x04) {
        mInput->__processKeyUp(GMKeyMaskH);
    }
    else if (keyCode == 0x22) {
        mInput->__processKeyUp(GMKeyMaskI);
    }
    else if (keyCode == 0x26) {
        mInput->__processKeyUp(GMKeyMaskJ);
    }
    else if (keyCode == 0x28) {
        mInput->__processKeyUp(GMKeyMaskK);
    }
    else if (keyCode == 0x25) {
        mInput->__processKeyUp(GMKeyMaskL);
    }
    else if (keyCode == 0x2e) {
        mInput->__processKeyUp(GMKeyMaskM);
    }
    else if (keyCode == 0x2d) {
        mInput->__processKeyUp(GMKeyMaskN);
    }
    else if (keyCode == 0x1f) {
        mInput->__processKeyUp(GMKeyMaskO);
    }
    else if (keyCode == 0x23) {
        mInput->__processKeyUp(GMKeyMaskP);
    }
    else if (keyCode == 0x0c) {
        mInput->__processKeyUp(GMKeyMaskQ);
    }
    else if (keyCode == 0x0f) {
        mInput->__processKeyUp(GMKeyMaskR);
    }
    else if (keyCode == 0x01) {
        mInput->__processKeyUp(GMKeyMaskS);
    }
    else if (keyCode == 0x11) {
        mInput->__processKeyUp(GMKeyMaskT);
    }
    else if (keyCode == 0x20) {
        mInput->__processKeyUp(GMKeyMaskU);
    }
    else if (keyCode == 0x09) {
        mInput->__processKeyUp(GMKeyMaskV);
    }
    else if (keyCode == 0x0d) {
        mInput->__processKeyUp(GMKeyMaskW);
    }
    else if (keyCode == 0x07) {
        mInput->__processKeyUp(GMKeyMaskX);
    }
    else if (keyCode == 0x10) {
        mInput->__processKeyUp(GMKeyMaskY);
    }
    else if (keyCode == 0x06) {
        mInput->__processKeyUp(GMKeyMaskZ);
    }
    else if (keyCode == 0x1d || keyCode == 0x52) {
        mInput->__processKeyUp(GMKeyMask0);
    }
    else if (keyCode == 0x12 || keyCode == 0x53) {
        mInput->__processKeyUp(GMKeyMask1);
    }
    else if (keyCode == 0x13 || keyCode == 0x54) {
        mInput->__processKeyUp(GMKeyMask2);
    }
    else if (keyCode == 0x14 || keyCode == 0x55) {
        mInput->__processKeyUp(GMKeyMask3);
    }
    else if (keyCode == 0x15 || keyCode == 0x56) {
        mInput->__processKeyUp(GMKeyMask4);
    }
    else if (keyCode == 0x17 || keyCode == 0x57) {
        mInput->__processKeyUp(GMKeyMask5);
    }
    else if (keyCode == 0x16 || keyCode == 0x58) {
        mInput->__processKeyUp(GMKeyMask6);
    }
    else if (keyCode == 0x1a || keyCode == 0x59) {
        mInput->__processKeyUp(GMKeyMask7);
    }
    else if (keyCode == 0x1c || keyCode == 0x5b) {
        mInput->__processKeyUp(GMKeyMask8);
    }
    else if (keyCode == 0x19 || keyCode == 0x5c) {
        mInput->__processKeyUp(GMKeyMask9);
    }
    else if (keyCode == 0x31) {
        mInput->__processKeyUp(GMKeyMaskSpace);
    }
    else if (keyCode == 0x35) {
        mInput->__processKeyUp(GMKeyMaskEscape);
    }
    else if (keyCode == 0x24 || keyCode == 0x4c) {
        mInput->__processKeyUp(GMKeyMaskReturn);
    }
}

- (void)mouseDown:(NSEvent*)theEvent
{
    mInput->__processMouseDown();
}

- (void)mouseUp:(NSEvent*)theEvent
{
    mInput->__processMouseUp();
}

@end

