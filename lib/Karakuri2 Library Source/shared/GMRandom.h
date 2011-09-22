//
//  GMRandom.h
//  Game Framework
//
//  Created by numata on Aug 05, 2009.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_RANDOM_H__
#define __GM_RANDOM_H__


#include "GMObject.h"


/*
    @class  GMRandom
    @group  Math
    @abstract 乱数を生成するクラスです。
 
    <p><a href="http://www.jstatsoft.org/v08/i14/" target="_blank">XorShift</a> 法を 128bit で使って、疑似乱数を生成します。</p>
    <p>乱数のシードは、ゲームの起動時に time() 関数（標準C言語ライブラリ）と getpid() 関数（POSIX.1規格）のリターン値を元にして設定されます。デモなどでのシーン再現のために乱数シードを保存する場合には、GetFirstSeed() メソッドを使ってシードを取得し、任意のタイミングで SetFirstSeed() メソッドを使ってシードを設定します。</p>
 */
class GMRandom : public GMObject {

    unsigned firstSeed;
    unsigned x, y, z, w;

public:
    /*!
        @task   乱数の生成
     */
    
    /*!
        @method NextDouble
        @abstract 0.0 ～ 1.0 の範囲で double 型の擬似乱数をリターンします。
     */
    static double NextDouble();
    
    /*!
        @method NextInt
        @abstract int 型の擬似乱数をリターンします。
        32ビットの int 型が取り得るすべての値が、ほぼ均等な確率で生成されます。
     */
    static int NextInt();
    
    /*!
        @method NextInt
        @abstract 0 から指定された値までの範囲（0 は含み、指定された値は含まない）の int 型の擬似乱数をリターンします。
        指定された範囲内で取り得るすべての値が、ほぼ均等な確率で生成されます。
     */
    static int NextInt(int upper);

public:
    /*!
        @task   乱数シードの管理
     */
    
    /*!
        @method     GetFirstSeed
        @abstract   現在のこのクラスにおける最初の乱数シードを取得します。
     */
    static unsigned GetFirstSeed();

    /*!
        @method     SetFirstSeed
        @abstract   最初の乱数シードを設定します。
     */
    static void     SetFirstSeed(unsigned seed0);

    
public:
	GMRandom();

private:
    void        __resetSeed();
    void        __setFirstSeed(unsigned seed0);
    unsigned    xor128();

private:
    int     getNextInt();
    int     getNextInt(int upper);
    float   getNextFloat();
    double  getNextDouble();
    
public:
    unsigned    getX() const;
    unsigned    getY() const;
    unsigned    getZ() const;
    unsigned    getW() const;
    void        setXYZW(unsigned x, unsigned y, unsigned z, unsigned w);
    
    unsigned    getFirstSeed() const;
    
};


#endif  //#ifndef __GM_RANDOM_H__


