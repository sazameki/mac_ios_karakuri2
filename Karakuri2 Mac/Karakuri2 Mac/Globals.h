//
//  Globals.h
//  Game Framework
//
//  Created by numata on Jan 04, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GLOBALS_H__
#define __GLOBALS_H__


// タイトル文字列
//   これで設定されるのは、ウィンドウのタイトルだけです。
//   メニューや Finder に表示されるタイトル文字列やアプリケーションタイトルの変更は、MainMenu.xib とターゲットの設定で行ってください。
#define GAME_TITLE              "My Great Game"

// 画面サイズ
#define SCREEN_SIZE             GMVector2D(640, 480)


/*!
    @var        GMShaderEnabled
    @abstract   シェーダを使用したプログラム記述を行うかどうかを指定します。
    シェーダを使用する場合は true を、そうでない場合は false を指定します。
 */
extern  bool    GMShaderEnabled;        // Currently not working


#endif  //#ifndef __GLOBALS_H__


