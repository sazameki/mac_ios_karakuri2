//
//  GMInput.h
//  Game Framework
//
//  Created by numata on Dec 27, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//


#ifndef __GM_INPUT_H__
#define __GM_INPUT_H__

#include <TargetConditionals.h>

#include "GMObject.h"
#include "GMTypes.h"
#include <map>
#include <set>


#if !TARGET_OS_IPHONE

// 64キーまでサポート
typedef unsigned long  GMKeyMask;

/*!
    @const GMKeyMaskUp
    @group System
    上向きの矢印キーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskUp;

/*!
    @const GMKeyMaskDown
    @group System
    下向きの矢印キーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskDown;

/*!
    @const GMKeyMaskLeft
    @group System
    左向きの矢印キーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskLeft;

/*!
    @const GMKeyMaskRight
    @group System
    右向きの矢印キーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskRight;

/*!
    @const GMKeyMaskSpace
    @group System
    スペースキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskSpace;

/*!
    @const GMKeyMaskEscape
    @group System
    escキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskEscape;

/*!
    @const GMKeyMaskReturn
    @group System
    returnキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskReturn;

/*!
    @const GMKeyMaskShift
    @group System
    shiftキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskShift;

/*!
    @const GMKeyMaskA
    @group System
    Aキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskA;

/*!
    @const GMKeyMaskB
    @group System
    Bキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskB;

/*!
    @const GMKeyMaskC
    @group System
    Cキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskC;

/*!
    @const GMKeyMaskD
    @group System
    Dキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskD;

/*!
    @const GMKeyMaskE
    @group System
    Eキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskE;

/*!
    @const GMKeyMaskF
    @group System
    Fキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskF;

/*!
    @const GMKeyMaskG
    @group System
    Gキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskG;

/*!
    @const GMKeyMaskH
    @group System
    Hキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskH;

/*!
    @const GMKeyMaskI
    @group System
    Iキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskI;

/*!
    @const GMKeyMaskJ
    @group System
    Jキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskJ;

/*!
    @const GMKeyMaskK
    @group System
    Kキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskK;

/*!
    @const GMKeyMaskL
    @group System
    Lキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskL;

/*!
    @const GMKeyMaskM
    @group System
    Mキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskM;

/*!
    @const GMKeyMaskN
    @group System
    Nキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskN;

/*!
    @const GMKeyMaskO
    @group System
    Oキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskO;

/*!
    @const GMKeyMaskP
    @group System
    Pキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskP;

/*!
    @const GMKeyMaskQ
    @group System
    Qキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskQ;

/*!
    @const GMKeyMaskR
    @group System
    Rキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskR;

/*!
    @const GMKeyMaskS
    @group System
    Sキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskS;

/*!
    @const GMKeyMaskT
    @group System
    Tキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskT;

/*!
    @const GMKeyMaskU
    @group System
    Uキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskU;

/*!
    @const GMKeyMaskV
    @group System
    Vキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskV;

/*!
    @const GMKeyMaskW
    @group System
    Wキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskW;

/*!
    @const GMKeyMaskX
    @group System
    Xキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskX;

/*!
    @const GMKeyMaskY
    @group System
    Yキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskY;

/*!
    @const GMKeyMaskZ
    @group System
    Zキーを表す定数です。
 */
extern const GMKeyMask GMKeyMaskZ;

/*!
    @const GMKeyMask0
    @group System
    0キーを表す定数です。
 */
extern const GMKeyMask GMKeyMask0;

/*!
    @const GMKeyMask1
    @group System
    1キーを表す定数です。
 */
extern const GMKeyMask GMKeyMask1;

/*!
    @const GMKeyMask2
    @group System
    2キーを表す定数です。
 */
extern const GMKeyMask GMKeyMask2;

/*!
    @const GMKeyMask3
    @group System
    3キーを表す定数です。
 */
extern const GMKeyMask GMKeyMask3;

/*!
    @const GMKeyMask4
    @group System
    4キーを表す定数です。
 */
extern const GMKeyMask GMKeyMask4;

/*!
    @const GMKeyMask5
    @group System
    5キーを表す定数です。
 */
extern const GMKeyMask GMKeyMask5;

/*!
    @const GMKeyMask6
    @group System
    6キーを表す定数です。
 */
extern const GMKeyMask GMKeyMask6;

/*!
    @const GMKeyMask7
    @group System
    7キーを表す定数です。
 */
extern const GMKeyMask GMKeyMask7;

/*!
    @const GMKeyMask8
    @group System
    8キーを表す定数です。
 */
extern const GMKeyMask GMKeyMask8;

/*!
    @const GMKeyMask9
    @group System
    9キーを表す定数です。
 */
extern const GMKeyMask GMKeyMask9;

/*!
    @const GMKeyMaskAny
    @group System
    あらゆるキーのマスクを表す定数です。
 */
extern const GMKeyMask GMKeyMaskAny;

#endif  //#if !TARGET_OS_IPHONE



/*!
    @class      GMInput
    @group      System
    @abstract   キーボードとマウスの入力を管理するためのクラスです。
    このクラスのインスタンスには、クラス変数 GMInput::Inst を使ってアクセスできます。
 */
class GMInput : public GMObject {

#if !TARGET_OS_IPHONE
    GMKeyMask   mKeyState;
    GMKeyMask   mKeyStateOld;
    GMKeyMask   mKeyDownStateTriggered;
    GMKeyMask   mKeyUpStateTriggered;
    
    bool        mIsMouseDown;
    bool        mIsMouseDownOld;
    bool        mIsMouseDownTriggered;
    bool        mIsMouseUpTriggered;
#endif  //#if !TARGET_OS_IPHONE

#if TARGET_OS_IPHONE
    std::set<unsigned>              mTouchIDs;
    std::map<unsigned, unsigned>    mTapCountMap;
    std::map<unsigned, GMVector2D>  mTouchLocationMap;
#endif  //#if TARGET_OS_IPHONE

public:
    /*!
        @var    Inst
     */    
    static GMInput*     Inst;
    
public:
    GMInput();
    
#if !TARGET_OS_IPHONE
public:
    /*!
        @task   キーボードの管理
     */
    /*!
        @method     isKeyDown
        @abstract   マスクで指定されたキーが押されていることをチェックします。
     */
    bool    isKeyDown(GMKeyMask mask) const;

    /*!
        @method     isKeyDownTriggered
        @abstract   マスクで指定されたキーが押されていることをチェックします。キーが押された直後のフレームでしか判定されません。
     */
    bool    isKeyDownTriggered(GMKeyMask mask) const;

    /*!
        @method     isKeyUp
        @abstract   マスクで指定されたキーが押されていないことをチェックします。
     */
    bool    isKeyUp(GMKeyMask mask) const;

    /*!
        @method     isKeyUpTriggered
        @abstract   マスクで指定されたキーが押されていないことをチェックします。キーが離された直後のフレームでしか判定されません。
     */
    bool    isKeyUpTriggered(GMKeyMask mask) const;

    
    /*!
        @task   マウスの管理
     */
    
    /*!
        @method     getMouseLocation
        @abstract   マウスの現在のカーソル位置を取得します。
     */
    GMVector2D  getMouseLocation() const;
    
    /*!
        @method     isMouseDown
        @abstract   マウスボタンが押されていることをチェックします。
        左のマウスボタンにのみ対応します。
     */
    bool    isMouseDown() const;

    /*!
        @method     isMouseDownTriggered
        @abstract   マウスボタンが押されていることをチェックします。ボタンが押された直後のフレームでしか判定されません。
        左のマウスボタンにのみ対応します。
     */
    bool    isMouseDownTriggered() const;

    /*!
        @method     isMouseUp
        @abstract   マウスボタンが押されていないことをチェックします。
        左のマウスボタンにのみ対応します。
     */
    bool    isMouseUp() const;

    /*!
        @method     isMouseUpTriggered
        @abstract   マウスボタンが押されていないことをチェックします。ボタンが離された直後のフレームでしか判定されません。
        左のマウスボタンにのみ対応します。
     */
    bool    isMouseUpTriggered() const;
    
public:
    void    __processKeyDown(GMKeyMask mask);
    void    __processKeyUp(GMKeyMask mask);
    void    __processMouseDown();
    void    __processMouseUp();
#endif  //#if !TARGET_OS_IPHONE
    
    
#if TARGET_OS_IPHONE
public:
    /*!
        @task   タッチの管理（ID指定なし）
     */
    /*!
        @method getTapCountMax
        @abstract   すべてのタッチの中から、最大のタップ回数を取得します。
        画面がタッチされていない場合、0 がリターンされます。
     */
    unsigned    getTapCountMax() const;

    /*!
        @method getTouchCount
        @abstract 現在のマルチタッチの個数を取得します。
     */
    unsigned    getTouchCount() const;
    
    /*!
        @method     getTouchLocationAny
        @abstract   現在タッチされている画面上の位置をいずれか1点取得します。
        1点もタッチされていない場合には、X座標、Y座標ともに DBL_MAX がセットされた GMVector2D がリターンされます。
     */
    GMVector2D  getTouchLocationAny() const;


    /*!
        @task   タッチの管理（ID指定）
     */

    /*!
        @method getTapCount
        @abstract   タッチのIDを指定して、タップ回数を取得します。
        タッチIDに対応するタッチが見つからない場合、0 がリターンされます。
     */
    unsigned    getTapCount(unsigned touchID) const;
    
    /*!
        @method     getTouchIDs
        @abstract   現在のすべてのタッチのIDを取得します。
     */
    std::set<unsigned>  getTouchIDs() const;

    /*!
        @method     getTouchLocation
        @abstract   タッチのIDを指定して、現在タッチされている画面上の位置を取得します。
        タッチIDに対応するタッチが見つからない場合、X座標、Y座標ともに DBL_MAX がセットされます。
     */
    GMVector2D  getTouchLocation(unsigned touchID) const;

public:
    void    __addTouch(unsigned touchID, const GMVector2D& pos, unsigned tapCount);
    void    __updateTouch(unsigned touchID, const GMVector2D& pos, unsigned tapCount);
    void    __removeTouch(unsigned touchID);
#endif  //#if TARGET_OS_IPHONE

    
#if TARGET_OS_IPHONE
public:
    /*!
        @task   モーションの管理
     */
    /*!
        @method     StartMotionUpdates
        @abstract   加速度センサまたはジャイロを使用したユーザモーションの取得を開始します。
     */
    static void         StartMotionUpdates();

    /*!
        @method     StopMotionUpdates
        @abstract   加速度センサまたはジャイロを使用したユーザモーションの取得を終了します。
     */
    static void         StopMotionUpdates();

    /*!
        @method     GetAcceleration
        @abstract   加速度センサによって取得された3次元の加速度を取得します。
     */
    static GMVector3D   GetAcceleration();

    /*!
        @method     GetGyroRotationRate
        @abstract   ジャイロセンサによって取得された3次元の回転値を取得します。
     */
    static GMVector3D   GetGyroRotationRate();
    
    /*!
        @method     IsAccelerometerAvailable
        @abstract   加速度センサが使用可能かどうかを取得します。
     */
    static bool         IsAccelerometerAvailable();

    /*!
        @method     IsGyroAvailable
        @abstract   ジャイロセンサが使用可能かどうかを取得します。
     */
    static bool         IsGyroAvailable();
    
#endif

    
public:
    void    __updateTriggers();
};


#endif  //#ifndef __GM_INPUT_H__


