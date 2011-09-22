//
//  GMButton.h
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/31.
//  Copyright (c) 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_BUTTON_H__
#define __GM_BUTTON_H__


#include "GMSpriteBatch.h"
#include "GMInput.h"


/*!
    @class GMButton
    @group Graphics
    @abstract プッシュボタンを表すためのクラスです。
 */
class GMButton {
    
    GMRect2D        mFrame;
    GMTexture2D*    mTexImage;
    bool            mIsPressed;
    bool            mIsReleased;
    
public:
    /*!
        @task 基本の操作
     */
    
    /*!
        @method GMButton
        ボタンの大きさと画像を指定して、このボタンを生成します。
     */
    GMButton(const GMRect2D& frame, const std::string& imageName);
    ~GMButton();
    
public:
    /*!
        @method     draw
        @abstract   与えられた spriteBatch による2次元描画でこのボタンを描画します。
     */
    void    draw(GMSpriteBatch* spriteBatch);

    /*!
        @method     process
        @abstract   与えられた input 引数を元に、ボタンの処理を行います。
     */
    bool    process(GMInput* input);

private:
    bool    contains(const GMVector2D& pos);

    void    startPress();
    bool    isPressed() const;
    void    endPress();
    
    bool    isReleased() const;
    void    setReleased(bool flag);
    
};


#endif  //#ifndef __GM_BUTTON_H__

