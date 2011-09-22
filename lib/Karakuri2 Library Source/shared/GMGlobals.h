//
//  GMGlobals.h
//  Game Framework
//
//  Created by numata on Dec 26, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_GLOBALS_H__
#define __GM_GLOBALS_H__


#include "GMColor.h"
#include "GMScene.h"

#include <string>


// アニメーションの更新レート
#define GM_ANIMATION_RATE       60.0

// ポリゴン描画のバッチ処理サイズ
#define GM_DRAW_BATCH_SIZE      1024

// スプライト描画のバッチ処理サイズ
#define GM_SPRITE_BATCH_SIZE    1024

// タイトル指定がない場合にウィンドウタイトルに設定する文字列
#define GM_DEFAULT_TITLE        "Game Framework"


// ゲーム画面サイズのデフォルト設定
extern GMVector2D   gGMDefaultScreenSize;

// ゲーム起動時に一瞬だけ表示される可能性のある背景色のデフォルト設定
extern GMColor      gGMDefaultStartUpColor;

// ゲーム内のエラー処理によってゲームが中断されたかどうか
extern bool         gGMHasTerminatedWithError;

extern bool         gGMIsDrawing;

// 次に移動するゲームシーン
extern GMScene*     gGMNextScene;

// 起動時にエラーが起こったかどうか（最初のシーンのテクスチャ読み込みなど）
extern bool         gGMHasGameStartError;

extern std::string  gGMErrorStr;

extern double       gGMLineWidth;
extern double       gGMPointSize;


#endif  //#ifndef __GM_GLOBALS_H__


