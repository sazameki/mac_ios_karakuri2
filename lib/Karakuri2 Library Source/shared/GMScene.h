//
//  GMScene.h
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_SCENE_H__
#define __GM_SCENE_H__


#include "GMObject.h"
#include "GMGraphics.h"
#include "GMInput.h"
#include <string>


class GMButton;


/*!
    @class      GMScene
    @group      System
    @abstract   ゲームのシーン管理を行うためのクラスです。
 */
class GMScene : public GMObject {
    
    std::string     mSceneName;
    
public:
    /*!
        @task   コンストラクタとデストラクタ
     */
    /*!
        @method     GMScene
     */
    GMScene();

    /*!
        @method     ~GMScene
     */
    virtual ~GMScene();
    
public:
    /*!
        @task   メインの操作
     */

    /*!
        @method     willAppear
        @abstract   画面に描画される直前に呼ばれるメソッドです。リソース読み込みとモデル変数の初期化を行います。
     */
    virtual void    willAppear(GMGraphics* g);

    /*!
        @method     didDisappear
        @abstract   画面に表示されなくなった直後に呼ばれるメソッドです。リソースの解放を行います。
     */
    virtual void    didDisappear();

public:
    virtual void    willAppear2(GMGraphics* g2);
    virtual void    didDisappear2();

public:
    /*!
        @method     drawView
        @abstract   このシーンの描画を行います。
     */
    virtual void    drawView(GMGraphics* g);

    /*!
        @method     drawView2
        @abstract   このシーンのサブディスプレイへの描画を行います。
     */
    virtual void    drawView2(GMGraphics* g2);

    /*!
        @method     updateModel
        @abstract   シーンのモデル内容を1フレーム分更新します。
     */
    virtual void    updateModel(GMInput* input);
    
public:
    /*!
        @task   コントロール関係の操作
     */
    /*!
        @method     buttonPressed
     */
    virtual void    buttonPressed(GMButton* button);

protected:
    /*!
        @task   サブクラス内で使うためのユーティリティ・メソッド
     */
    /*!
        @method     drawView2Mirrored
        @abstract   サブディスプレイの描画をミラー処理で行います。drawView2() メソッドから呼び出してください。
     */
    void    drawView2Mirrored(GMGraphics* g2);

public:
    /*!
        @task   その他の操作
     */
    /*!
        @method     getName
        @abstract   このシーンに設定された名前を取得します。
     */
    std::string     getName() const;
    
    void            __setName(const std::string& name);
    
};


#endif  //#ifndef __GM_SCENE_H__


