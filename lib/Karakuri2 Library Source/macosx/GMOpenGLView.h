//
//  GMOpenGLView.h
//  Game Framework
//
//  Created by numata on Dec 25, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_OPENGL_VIEW_H__
#define __GM_OPENGL_VIEW_H__


#import <Cocoa/Cocoa.h>

#include "GMGraphics.h"
#include "GMInput.h"
#include "GameMain.h"
#include "GMRandom.h"


@interface GMOpenGLView : NSOpenGLView {
    // アニメーションサポートのための変数
    CGLContextObj   mCGLContext;    // Core OpenGL のコンテキスト
    BOOL            mIsRunning;     // ゲームを実行中かどうか
    BOOL            mIsFinished;    // スレッドが完了しているか
    
    // ゲーム関係の変数
    GameMain*       mGameInst;
    GMGraphics*     mGraphics;
    GMInput*        mInput;
    GMRandom*       mRandom;

    bool            mIsShiftKeyDown;
}

- (GameMain*)game;

@end


#endif  //#ifndef __GM_OPENGL_VIEW_H__


