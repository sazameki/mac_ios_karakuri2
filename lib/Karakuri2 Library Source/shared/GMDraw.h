//
//  GMDraw.h
//  Game Framework
//
//  Created by numata on Dec 26, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_DRAW_H__
#define __GM_DRAW_H__

#include <TargetConditionals.h>

#include "GMObject.h"
#include "GMColor.h"
#include "GMTypes.h"
#include "GMTexture2D.h"
#include "GMGraphics.h"


/*!
    @class      GMDraw
    @group      Graphics
    @abstract   ポリゴンを作成して簡易な画面描画を行う機能を提供するためのクラスです。<br/>色とテクスチャを指定して、点、線、三角形、四角形を描画することができます。
    <p><strong>GMDraw クラスを使用した描画は、GMBasicEffect クラスのオブジェクトの begin()〜end() の呼び出し内で行う必要があります。</strong></p>
    <p>このクラスにおける複数の描画処理は、可能な限りまとめられてバッチ処理されます。<br/><strong>必ず描画の前後で GMDraw::Begin() メソッドと GMDraw::End() メソッドを呼び出してください。</strong></p>
    <p>実際の OpenGL / OpenGL ES の描画命令の発行は、GMDrawSys クラスによって行われます。</p>
 */
class GMDraw : public GMObject {

public:    
    /*!
        @task   描画の開始と終了
     */
    
    /*!
        @method     Begin
     */
    static void Begin();

    /*!
        @method     End
     */
    static void End();

    static void __FlushBatchDraws();

public:
    /*!
        @task   点の描画
     */
    
    /*!
        @method     DrawPoint
        @abstract   座標を指定して点を描画します。
        GMGraphics クラスの enablePointSprite() メソッドを使用することにより、ポイントスプライトを有効化して使用することができます。
        ポイントスプライトに使用できる点のサイズには上限があります。
     */
    static void DrawPoint(const GMVector2D& pos, const GMColor& color, double size=1.0);

    /*!
        @method     DrawPoint
        @abstract   座標を指定して点を描画します。
        GMGraphics クラスの enablePointSprite() メソッドを使用することにより、ポイントスプライトを有効化して使用することができます。
        ポイントスプライトに使用できる点のサイズには上限があります。
     */
    static void DrawPoint(const GMVector3D& pos, const GMColor& color, double size=1.0);

    
    /*!
        @task   線の描画
     */
    
    /*!
        @method     DrawLine
     */
    static void DrawLine(const GMVector2D& p1, const GMVector2D& p2, const GMColor& color, double width = 1.0);
    
    /*!
        @method     DrawLine
     */
    static void DrawLine(const GMVector2D& p1, const GMVector2D& p2, const GMColor& color1, const GMColor& color2, double width = 1.0);

    /*!
        @method     DrawLine
     */
    static void DrawLine(const GMVector3D& p1, const GMVector3D& p2, const GMColor& color, double width = 1.0);
    
    /*!
        @method     DrawLine
     */
    static void DrawLine(const GMVector3D& p1, const GMVector3D& p2, const GMColor& color1, const GMColor& color2, double width = 1.0);

    
    /*!
        @task   三角形の描画
     */

    /*!
        @method     FillTriangle
     */
    static void FillTriangle(const GMVector2D& p1, const GMVector2D& p2, const GMVector2D& p3, const GMColor& color = GMColor::White, const GMVector2D& t1 = GMVector2D::Zero, const GMVector2D& t2 = GMVector2D::Zero, const GMVector2D& t3 = GMVector2D::Zero);
    
    /*!
        @method     FillTriangle
     */
    static void FillTriangle(const GMVector2D& p1, const GMVector2D& p2, const GMVector2D& p3, const GMColor& c1, const GMColor& c2, const GMColor& c3, const GMVector2D& t1 = GMVector2D::Zero, const GMVector2D& t2 = GMVector2D::Zero, const GMVector2D& t3 = GMVector2D::Zero);
    
    /*!
        @method     FillTriangle
     */
    static void FillTriangle(const GMVector3D& p1, const GMVector3D& p2, const GMVector3D& p3, const GMVector3D& n1, const GMVector3D& n2, const GMVector3D& n3, const GMVector2D& t1 = GMVector2D::Zero, const GMVector2D& t2 = GMVector2D::Zero, const GMVector2D& t3 = GMVector2D::Zero);

    static void __FillTriangle(const GMVector3D& p1, const GMVector3D& p2, const GMVector3D& p3, const GMVector3D& n1, const GMVector3D& n2, const GMVector3D& n3, const GMColor& c1, const GMColor& c2, const GMColor& c3, const GMVector2D& t1, const GMVector2D& t2, const GMVector2D& t3);
    
    /*!
        @task   四角形の描画
     */
    
    /*!
        @method     FillQuad
        @abstract   4点の頂点座標を指定して、四角形を描画します。
        <p>すべての頂点に共通の色を指定することができますが、ライティングが有効な環境下では有効になりません。</p>
        <p>各頂点のテクスチャ座標を指定することができますが、別途 GMBasicEffect クラスでのテクスチャの有効化とテクスチャ指定が必要です。</p>
     */
    static void FillQuad(const GMVector2D& p1, const GMVector2D& p2, const GMVector2D& p3, const GMVector2D& p4, const GMColor& color = GMColor::White, const GMVector2D& t1 = GMVector2D::Zero, const GMVector2D& t2 = GMVector2D::Zero, const GMVector2D& t3 = GMVector2D::Zero, const GMVector2D& t4 = GMVector2D::Zero);
    
    /*!
        @method     FillQuad
        @abstract   4点の頂点座標を指定して、四角形を描画します。
        <p>各頂点に個別の色を指定することができますが、ライティングが有効な環境下では有効になりません。</p>
        <p>各頂点のテクスチャ座標を指定することができますが、別途 GMBasicEffect クラスでのテクスチャの有効化とテクスチャ指定が必要です。</p>
     */
    static void FillQuad(const GMVector2D& p1, const GMVector2D& p2, const GMVector2D& p3, const GMVector2D& p4, const GMColor& c1, const GMColor& c2, const GMColor& c3, const GMColor& c4, const GMVector2D& t1 = GMVector2D::Zero, const GMVector2D& t2 = GMVector2D::Zero, const GMVector2D& t3 = GMVector2D::Zero, const GMVector2D& t4 = GMVector2D::Zero);

    /*!
        @method     FillQuad
        @abstract   4点の頂点座標、各頂点の法線ベクトル、テクスチャ座標を指定して、四角形を描画します。
        <p>テクスチャマッピングには、別途 GMBasicEffect クラスでのテクスチャの有効化とテクスチャ指定が必要です。</p>
     */
    static void FillQuad(const GMVector3D& p1, const GMVector3D& p2, const GMVector3D& p3, const GMVector3D& p4, const GMVector3D& n1, const GMVector3D& n2, const GMVector3D& n3, const GMVector3D& n4, const GMVector2D& t1 = GMVector2D::Zero, const GMVector2D& t2 = GMVector2D::Zero, const GMVector2D& t3 = GMVector2D::Zero, const GMVector2D& t4 = GMVector2D::Zero);

    static void __FillQuad(const GMVector3D& p1, const GMVector3D& p2, const GMVector3D& p3, const GMVector3D& p4,
                         const GMVector3D& n1, const GMVector3D& n2, const GMVector3D& n3, const GMVector3D& n4,
                         const GMColor& c1, const GMColor& c2, const GMColor& c3, const GMColor& c4,
                         const GMVector2D& t1, const GMVector2D& t2, const GMVector2D& t3, const GMVector2D& t4);    
    
};


#endif  //#ifndef __GM_DRAW_H__

