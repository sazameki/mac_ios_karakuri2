//
//  Globals.h
//  Game Framework
//
//  Created by numata on Jan 04, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GLOBALS_H__
#define __GLOBALS_H__


/*!
    @var        GMScreenIsVertical
    @abstract   iPhone/iPad ゲームを縦方向で作るかどうかを指定します。
    縦方向で使う場合は true を、横方向で使う場合は false を指定します。
 */
extern  bool    GMScreenIsVertical;

/*!
    @var        GMSubdisplayEnabled
    @abstract   接続されたディスプレイをサブディスプレイとして使用するかどうかを指定します。
    iPad 2 の場合、false にしておくと自動的にミラーリングされます。
 */
extern  bool    GMSubdisplayEnabled;

/*!
    @var        GMShaderEnabled
    @abstract   シェーダを使用したプログラム記述を行うかどうかを指定します。
    シェーダを使用する場合は true を、そうでない場合は false を指定します。
 */
extern  bool    GMShaderEnabled;        // Currently not working

/*!
    @define     GM_USES_MULTI_SAMPLE_ANTI_ALIASING
    @abstract   1を指定するとマルチアンチエイリアシングを有効にします。0で無効です。
    マルチアンチエイリアシングが有効となるデバイスは限られていることに注意してください。
 */
#define GM_USES_MULTI_SAMPLE_ANTI_ALIASING  0


#endif  //#ifndef __GLOBALS_H__


