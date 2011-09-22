//
//  GMLabel.h
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/29.
//  Copyright (c) 2011 Satoshi Numata, Ph.D. All rights reserved.
//


#ifndef __GM_LABEL_H__
#define __GM_LABEL_H__


#include "GMObject.h"

#include <string>

class GMTexture2D;


class __GMFont {
    
    void*       mFontObj;
    
public:
    __GMFont(const std::string& fontName, double fontSize);
    ~__GMFont();
    
public:
    GMTexture2D*    createTextTexture(const std::string& str) const;
    
public:
    void*           __getFontObject() const;
    
};


/*!
    @class GMLabel
    @group Graphics
    <p>テキストラベルを表すためのクラスです。</p>
    <p>
        このクラスは、フォントの名前と大きさを指定して作成し、表示したいテキストを適宜セットします。<br />
        描画が必要なときには、getTexture() メソッドでテクスチャを取得して描画してください。<br />
        テクスチャは、白のテキスト色で用意されます。
    </p>
    <p>利用できるフォントの名前は、開発ガイドの「<a href="../../../../guide/font_list.html">フォント一覧</a>」を参照してください。</p>
 */
class GMLabel : public GMObject {
    
    __GMFont*       mFont;
    std::string     mText;
    GMTexture2D*    mTex;
    
public:
    /*!
        @task 基本の操作
     */
    /*!
        @method GMLabel
        @abstract フォントの名前と大きさを指定して、このラベルを生成します。
     */
    GMLabel(const std::string& fontName, double fontSize);
    virtual ~GMLabel();
    
public:
    /*!
        @method getTexture
        @abstract 現在のテキストラベルの内容を表すテクスチャを取得します。
     */
    GMTexture2D*    getTexture() const;

    /*!
        @method getText
        @abstract 現在設定されているテキストを取得します。
     */
    std::string     getText() const;

    /*!
        @method setText
        @abstract 新しいテキストを設定します。
        渡されたテキストが前と同じものであった場合、テクスチャの更新を行いません。
     */
    void            setText(const std::string& str);
    
};


#endif  //#ifndef __GM_LABEL_H__

