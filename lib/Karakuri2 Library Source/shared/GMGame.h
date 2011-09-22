//
//  GMGame.h
//  Game Framework
//
//  Created by numata on Jan 04, 2011.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_GAME_H__
#define __GM_GAME_H__


#include "GMObject.h"
#include "GMScene.h"
#include <map>
#include <string>


/*!
    @class  GMGame
    @group  System
    @abstract ゲームの基本設定の確認とシーン管理の機能を提供するためのクラスです。
 */
class GMGame : public GMObject {

    GMColor                         mStartUpColor;
    std::string                     mTitle;
    
    GMScene*                        mCurrentScene;
    std::map<std::string, GMScene*> mSceneMap;
    
    bool                            mSubDisplayConnectionNotified;

public:
    GMGame();
    virtual ~GMGame();
    
protected:
    void        setStartUpColor(const GMColor& color);
    void        setTitle(const std::string& str);
    
public:
    /*!
        @task ゲームの基本設定
     */

    /*!
        @method     getStartUpColor
        @abstract   特定シーンの drawView() メソッドが呼ばれる前の起動時の画面を塗り潰すための色を取得します。
        この色は、Globals.h の STARTUP_COLOR マクロで設定してください。
     */
    GMColor     getStartUpColor() const;

    /*!
        @method     getTitle
        @abstract   このゲームのウィンドウのタイトルバーに表示されているタイトル文字列を取得します。
     */
    std::string getTitle() const;
    
public:
    ///// ゲーム進行
    void        drawView(GMGraphics* g);
    void        drawView2(GMGraphics* g2);
    void        updateModel(GMInput* input);
    
    /*!
        @task シーン管理（登録）
     */
protected:
    /*!
        @method     addScene
        @abstract   新しいシーンを名前を付けて追加します。
        このメソッドで登録されたシーンは、ゲーム終了時に自動的に解放されます。絶対に自分で delete しないでください。
     */
    void    addScene(const std::string& name, GMScene* aScene);
    
public:
    /*!
        @task シーン管理
     */

    /*!
        @method     ChangeScene
        @abstract   名前を指定して次フレームから使用されるシーンを選択します。
        <p>このメソッドは、必ず GMScene クラスの updateModel() メソッドの実行中に使用してください。</p>
        <p>このメソッドが実行されても、現在のフレームで実行されている updateModel() メソッドが暗黙的に中断されることはありません。
           基本的には、このメソッドを呼び出した直後に、return するなどして、updateModel() メソッドの実行を自分で中断してください。</p>
     */
    static void     ChangeScene(const std::string& name);
    
    /*!
        @method     GetCurrentScene
        @abstract   現在選択されているシーンを取得します。
     */
    static GMScene* GetCurrentScene();
    
    /*!
        @method     GetScene
        @abstract   指定された名前で登録されたシーンを取得します。
     */
    static GMScene* GetScene(const std::string& name);
    
public:
    // シーン管理のためにスレッド管理部から呼ばれるメソッド
    void        __applySceneChange();    

};


#endif  //#ifndef __GM_GAME_H__



