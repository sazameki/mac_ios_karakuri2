/*
 *  GMMusic.h
 *  Game Framework
 *
 *  Created by numata on 09/07/23.
 *  Copyright 2009 Satoshi Numata. All rights reserved.
 *
 */

#ifndef __GM_MUSIC_H__
#define __GM_MUSIC_H__

#include "GMObject.h"
#include <string>


/*!
    @class  GMMusic
    @group  Audio
    <p>ゲームの BGM を再生するためのクラスです。</p>
 */
class GMMusic : public GMObject {
    
private:
    std::string mFileName;
    void*       mImpl;
    bool        mDoLoop;
    bool        mIsPausing;
    int         mBGMID;
    
public:
    /*!
        @task コンストラクタ
     */
    
    /*!
        @method GMMusic
        @abstract ファイル名（拡張子含む）を指定して、BGM再生用のインスタンスを作成します。
        デフォルトではループ再生しますが、第2引数に false を指定するとループ再生しないようになります。
     */
    GMMusic(const std::string& filename, bool loop=true);
    ~GMMusic();
    
public:
    /*!
        @task 基本の操作
     */

    /*!
        @method play
        @abstract   BGM の再生を開始します。
     */
    void    play();

    /*!
        @method pause
        @abstract   BGM の再生を一時停止します。
     */
    void    pause();

    /*!
        @method stop
        @abstract   BGM の再生を中断します。
        このメソッドの呼び出し後、BGM の再生位置は先頭に戻ります。
     */
    void    stop();

    /*!
        @method isPlaying
        @abstract   BGM が再生中かどうかを取得します。
        @return     BGM が再生中であれば true、そうでなければ false
     */    
    bool    isPlaying() const;

    /*!
        @method getVolume
        @abstract   BGM の現在の音量を取得します。
        @return BGM の現在の音量
     */    
    double  getVolume() const;

    /*!
        @method setVolume
        @abstract   BGM の音量を設定します。
     */    
    void    setVolume(double value);

    
#pragma mark -
#pragma mark Debug Support

public:
    std::string to_s() const;

};


#endif  //#ifndef __GM_MUSIC_H__


