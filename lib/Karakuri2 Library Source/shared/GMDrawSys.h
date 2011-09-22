//
//  GMDrawSys.h
//  Karakuri2 Mac
//
//  Created by Numata Satoshi on 11/09/06.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_DRAW_SYS_H__
#define __GM_DRAW_SYS_H__

#include <TargetConditionals.h>

#include "GMObject.h"
#include "GMColor.h"
#include "GMTypes.h"
#include "GMTexture2D.h"
#include "GMGraphics.h"


/*!
    @enum   GMBlendMode
    @group  Graphics

    @constant   GMBlendModeAlpha       アルファ合成
    @constant   GMBlendModeAdd         加算合成
    @constant   GMBlendModeClear       クリア合成
    @constant   GMBlendModeCopy        コピー合成
    @constant   GMBlendModeInvert      反転合成
    @constant   GMBlendModeMultiply    乗算合成
    @constant   GMBlendModeScreen      スクリーン合成
    @constant   GMBlendModeXOR         XOR合成
 */
enum GMBlendMode {
    GMBlendModeNone,
    GMBlendModeAlpha,
    GMBlendModeAdd,
    GMBlendModeClear,
    GMBlendModeCopy,
    GMBlendModeInvert,
    GMBlendModeMultiply,
    GMBlendModeScreen,
    GMBlendModeXOR,
};

/*!
    @enum   GMPrimitiveType
    @group  Graphics
 
    @constant   GMPrimitiveTypePointList        点のリスト
    @constant   GMPrimitiveTypeLineList         線のリスト
    @constant   GMPrimitiveTypeLineStrip        連続した線のリスト
    @constant   GMPrimitiveTypeTriangleList     三角形のリスト
    @constant   GMPrimitiveTypeTriangleStrip    連続した三角形のリスト
 */
enum GMPrimitiveType {
    __GMPrimitiveTypeNone,
    GMPrimitiveTypePointList,
    GMPrimitiveTypeLineList,
    GMPrimitiveTypeLineStrip,
    GMPrimitiveTypeTriangleList,
    GMPrimitiveTypeTriangleStrip,
};

enum __GMVertexDataType {
    __GMVertexDataTypeVC,
    __GMVertexDataTypeVT,
    __GMVertexDataTypeVCT,
    __GMVertexDataTypeVNT,
    __GMVertexDataTypeVCNT,
};


/*!
    @struct     GMVertexDataVC
    @group      Graphics
 */
struct GMVertexDataVC {
    
    float   vx, vy, vz;
    float   cr, cg, cb, ca;
    
};


/*!
    @struct     GMVertexDataVT
    @group      Graphics
 */
struct GMVertexDataVT {
    
    float       vx, vy, vz;
    float       tx, ty;
    
};

/*!
    @struct     GMVertexDataVCT
    @group      Graphics
 */
struct GMVertexDataVCT {
    
    float   vx, vy, vz;
    float   cr, cg, cb, ca;
    float   tx, ty;
    
};

/*!
    @struct     GMVertexDataVNT
    @group      Graphics
 */
struct GMVertexDataVNT {
    
    float   vx, vy, vz;
    float   nx, ny, nz;
    float   tx, ty;
    
};

struct __GMVertexDataVCNT {
    
    float   vx, vy, vz;
    float   cr, cg, cb, ca;
    float   nx, ny, nz;
    float   tx, ty;
    
};


/*!
    @class  GMIndexBuffer
    @group  Graphics
    頂点インデックスバッファを表すクラスです。
 */
class GMIndexBuffer : public GMObject {

    GLuint  mIndexBuffer;
    
public:
    /*!
        @task   コンストラクタ・デストラクタ
     */
    /*!
        @method     GMIndexBuffer
     */
    GMIndexBuffer();
    /*!
        @method     ~GMIndexBuffer
     */
    ~GMIndexBuffer();
    
public:
    /*!
        @task   バッファの操作
     */
    /*!
        @method     setData
     */
    void    setData(unsigned short* data, int startIndex, int elementCount);

};

/*!
    @class  GMVertexBuffer
    @group  Graphics
    頂点バッファを表すクラスです。
 */
class GMVertexBuffer : public GMObject {
    
    GLuint              mVertexBuffer;
    __GMVertexDataType  mDataType;
    
public:
    /*!
        @task   コンストラクタ・デストラクタ
     */
    /*!
        @method GMVertexBuffer
     */
    GMVertexBuffer();

    /*!
        @method ~GMVertexBuffer
     */
    ~GMVertexBuffer();

public:
    /*!
        @task   バッファの操作
     */
    /*!
        @method     setData
     */
    void    setData(GMVertexDataVC* data, int startIndex, int elementCount);

    /*!
        @method     setData
     */
    void    setData(GMVertexDataVT* data, int startIndex, int elementCount);

    /*!
        @method     setData
     */
    void    setData(GMVertexDataVCT* data, int startIndex, int elementCount);

    /*!
        @method     setData
     */
    void    setData(GMVertexDataVNT* data, int startIndex, int elementCount);

};


/*!
    @class  GMDrawSys
    @group  Graphics
    @abstract もっとも基本的な描画機能を提供するためのクラスです。
    <p>OpenGL / OpenGL ES の描画命令の発行はすべてこのクラスによって行われます。</p>
    <p>アルファブレンディングの設定はこのクラスで管理しています。</p>
 */
class GMDrawSys : public GMObject {

public:
    /*!
        @task   アルファブレンディングの設定
     */

    // ブレンドモードの設定
    //     cf. http://tobysoft.net/wiki/index.php?PhotoShop%2F%A5%EC%A5%A4%A5%E4%A1%BC%A4%CE%B7%D7%BB%BB%CA%FD%CB%A1%A4%CB%A4%C4%A4%A4%A4%C6
    //     cf. http://blog.jyoken.net/?eid=553888
    //     cf. http://d.hatena.ne.jp/keim_at_Si/20060210/p1
    //     cf. http://www.bea.hi-ho.ne.jp/gaku-iwa/color/conjn.html
    //     cf. http://www.simpelfilter.de/en/basics/mixmods.html
    
    /*!
        @method     GetBlendMode
        @abstract   現在のブレンドモードを取得します。
     */
    static GMBlendMode GetBlendMode();
    
    /*!
        @method     SetBlendMode
        @abstract   ブレンドモードを設定します。
        <p>
            以下の値を指定することができます。
            <ul>
                <li>GMBlendModeAlpha（アルファ合成）</li>
                <li>GMBlendModeAdd（加算合成）</li>
                <li>GMBlendModeClear（クリア合成）</li>
                <li>GMBlendModeCopy（コピー合成）</li>
                <li>GMBlendModeInvert（反転合成）</li>
                <li>GMBlendModeMultiply（乗算合成）</li>
                <li>GMBlendModeScreen（スクリーン合成）</li>
                <li>GMBlendModeXOR（XOR合成）</li>
            </ul>
        </p>
     */
    static void    SetBlendMode(GMBlendMode mode);

public:
    /*!
        @task   頂点配列を使用した描画
     */
    /*!
        @method     DrawPrimitivesUser
        @abstract   渡されたバッファに対して、頂点配列を使用した描画を行います。
     */
    static void DrawPrimitivesUser(GMPrimitiveType type, GMVertexDataVC* data, int startIndex, int primitiveCount);

    /*!
        @method     DrawPrimitivesUser
        @abstract   渡されたバッファに対して、頂点配列を使用した描画を行います。
     */
    static void DrawPrimitivesUser(GMPrimitiveType type, GMVertexDataVT* data, int startIndex, int primitiveCount);

    /*!
        @method     DrawPrimitivesUser
        @abstract   渡されたバッファに対して、頂点配列を使用した描画を行います。
     */
    static void DrawPrimitivesUser(GMPrimitiveType type, GMVertexDataVCT* data, int startIndex, int primitiveCount);

    /*!
        @method     DrawPrimitivesUser
        @abstract   渡されたバッファに対して、頂点配列を使用した描画を行います。
     */
    static void DrawPrimitivesUser(GMPrimitiveType type, GMVertexDataVNT* data, int startIndex, int primitiveCount);

    static void __DrawPrimitivesUser(GMPrimitiveType type, __GMVertexDataVCNT* data, int startIndex, int primitiveCount);

public:
    /*!
        @task   頂点バッファを使用した描画（未実装）
     */
    
    /*!
        @method     DrawPrimitives
        @abstract   SetVertexBuffer() でセットされた頂点バッファを使用して、プリミティブの描画を行います。
     */
    static void DrawPrimitives(GMPrimitiveType type, int startIndex, int primitiveCount);

    /*!
        @method     SetVertexBuffer
        @abstract   DrawPrimitives() で描画するための頂点バッファを設定します。
     */
    static void SetVertexBuffer(GMVertexBuffer* vertexBuffer);

public:
    /*!
        @task   頂点インデックスバッファを使用した描画（未実装）
     */
    /*!
        @method     DrawPrimitivesIndexed
        @abstract   SetVertexBuffer() でセットされた頂点バッファに対して、SetIndexBuffer() でセットされた頂点インデックスバッファを使用して、プリミティブの描画を行います。
     */
    static void DrawPrimitivesIndexed(GMPrimitiveType type, int startIndex, int primitiveCount);
    
    /*!
        @method     SetIndexBuffer
        @abstract   DrawPrimitivesIndexed() で描画するための頂点インデックスバッファを設定します。
     */
    static void SetIndexBuffer(GMIndexBuffer* indexBuffer);

};


#endif  //#ifndef __GM_DRAW_SYS_H__

