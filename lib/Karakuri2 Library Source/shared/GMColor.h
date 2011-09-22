//
//  GMColor.h
//  Game Framework
//
//  Created by numata on Dec 26, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_COLOR_H__
#define __GM_COLOR_H__

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#else
#include <OpenGL/OpenGL.h>
#endif
#include "GMObject.h"


struct GMVector3D;
struct GMVector4D;

/*!
    @class      GMColor
    @group      Graphics
    @abstract   ゲームで使用される色を表現するためのクラスです。
 */
struct GMColor : public GMObject {

public:
    // Color A-
    /*!
        @const AliceBlue
        色の定数です。
     */
    static const GMColor&   AliceBlue;
    /*!
        @const AntiqueWhite
        色の定数です。
     */
 	static const GMColor&   AntiqueWhite;
    /*!
        @const Aqua
        色の定数です。
     */
 	static const GMColor&   Aqua;
    /*!
        @const Aquamarine
        色の定数です。
     */
 	static const GMColor&   Aquamarine;
    /*!
        @const Azure
        色の定数です。
     */
 	static const GMColor&   Azure;

    // Color B-
    /*!
        @const Beige
        色の定数です。
     */
    static const GMColor&   Beige;
    /*!
        @const Bisque
        色の定数です。
     */
    static const GMColor&   Bisque;
    /*!
        @const Black
        色の定数です。
     */
    static const GMColor&   Black;
    /*!
        @const BlanchedAlmond
        色の定数です。
     */
    static const GMColor&   BlanchedAlmond;
    /*!
        @const Blue
        色の定数です。
     */
    static const GMColor&   Blue;
    /*!
        @const BlueViolet
        色の定数です。
     */
    static const GMColor&   BlueViolet;
    /*!
        @const Brown
        色の定数です。
     */
    static const GMColor&   Brown;
    /*!
        @const BurlyWood
        色の定数です。
     */
    static const GMColor&   BurlyWood;
    
    // Color C-
    /*!
        @const CadetBlue
        色の定数です。
     */
    static const GMColor&   CadetBlue;
    /*!
        @const Chartreuse
        色の定数です。
     */
 	static const GMColor&   Chartreuse;
    /*!
        @const Chocolate
        色の定数です。
     */
 	static const GMColor&   Chocolate;
    /*!
        @const Coral
        色の定数です。
     */
 	static const GMColor&   Coral;
    /*!
        @const CornflowerBlue
        色の定数です。
     */
 	static const GMColor&   CornflowerBlue;
    /*!
        @const Cornsilk
        色の定数です。
     */
 	static const GMColor&   Cornsilk;
    /*!
        @const Crimson
        色の定数です。
     */
 	static const GMColor&   Crimson;
    /*!
        @const Cyan
        色の定数です。
     */
 	static const GMColor&   Cyan;
    
    // Color D-
    /*!
        @const DarkBlue
        色の定数です。
     */
    static const GMColor&   DarkBlue;
    /*!
        @const AliceBlue
        色の定数です。
     */
 	static const GMColor&   DarkCyan;
    /*!
        @const DarkGoldenrod
        色の定数です。
     */
 	static const GMColor&   DarkGoldenrod;
    /*!
        @const DarkGray
        色の定数です。
     */
 	static const GMColor&   DarkGray;
    /*!
        @const DarkGreen
        色の定数です。
     */
 	static const GMColor&   DarkGreen;
    /*!
        @const DarkKhaki
        色の定数です。
     */
 	static const GMColor&   DarkKhaki;
    /*!
        @const DarkMagenta
        色の定数です。
     */
 	static const GMColor&   DarkMagenta;
    /*!
        @const DarkOliveGreen
        色の定数です。
     */
 	static const GMColor&   DarkOliveGreen;
    /*!
        @const DarkOrange
        色の定数です。
     */
 	static const GMColor&   DarkOrange;
    /*!
        @const DarkOrchid
        色の定数です。
     */
 	static const GMColor&   DarkOrchid;
    /*!
        @const DarkRed
        色の定数です。
     */
 	static const GMColor&   DarkRed;
    /*!
        @const DarkSalmon
        色の定数です。
     */
 	static const GMColor&   DarkSalmon;
    /*!
        @const DarkSeaGreen
        色の定数です。
     */
 	static const GMColor&   DarkSeaGreen;
    /*!
        @const DarkSlateBlue
        色の定数です。
     */
 	static const GMColor&   DarkSlateBlue;
    /*!
        @const DarkSlateGray
        色の定数です。
     */
 	static const GMColor&   DarkSlateGray;
    /*!
        @const DarkTurquoise
        色の定数です。
     */
 	static const GMColor&   DarkTurquoise;
    /*!
        @const DarkViolet
        色の定数です。
     */
 	static const GMColor&   DarkViolet;
    /*!
        @const DeepPink
        色の定数です。
     */
 	static const GMColor&   DeepPink;
    /*!
        @const DeepSkyBlue
        色の定数です。
     */
 	static const GMColor&   DeepSkyBlue;
    /*!
        @const DimGray
        色の定数です。
     */
 	static const GMColor&   DimGray;
    /*!
        @const DodgerBlue
        色の定数です。
     */
 	static const GMColor&   DodgerBlue;
    
    // Color F-
    /*!
        @const Firebrick
        色の定数です。
     */
    static const GMColor&   Firebrick;
    /*!
        @const FloralWhite
        色の定数です。
     */
 	static const GMColor&   FloralWhite;
    /*!
        @const ForestGreen
        色の定数です。
     */
 	static const GMColor&   ForestGreen;
    /*!
        @const Fuchsia
        色の定数です。
     */
 	static const GMColor&   Fuchsia;
    
    // Color G-
    /*!
        @const Gainsboro
        色の定数です。
     */
    static const GMColor&   Gainsboro;
    /*!
        @const GhostWhite
        色の定数です。
     */
 	static const GMColor&   GhostWhite;
    /*!
        @const Gold
        色の定数です。
     */
 	static const GMColor&   Gold;
    /*!
        @const Goldenrod
        色の定数です。
     */
 	static const GMColor&   Goldenrod;
    /*!
        @const Gray
        色の定数です。
     */
 	static const GMColor&   Gray;
    /*!
        @const Green
        色の定数です。
     */
 	static const GMColor&   Green;
    /*!
        @const GreenYellow
        色の定数です。
     */
 	static const GMColor&   GreenYellow;

    // Color H-
    /*!
        @const Honeydew
        色の定数です。
     */
    static const GMColor&   Honeydew;
    /*!
        @const HotPink
        色の定数です。
     */
 	static const GMColor&   HotPink;

    // Color I-
    /*!
        @const IndianRed
        色の定数です。
     */
    static const GMColor&   IndianRed;
    /*!
        @const Indigo
        色の定数です。
     */
 	static const GMColor&   Indigo;
    /*!
        @const Ivory
        色の定数です。
     */
 	static const GMColor&   Ivory;
    
    // Color K-
    /*!
        @const Khaki
        色の定数です。
     */
 	static const GMColor&   Khaki;
    
    // Color L-
    /*!
        @const Lavender
        色の定数です。
     */
    static const GMColor&   Lavender;
    /*!
        @const LavenderBlush
        色の定数です。
     */
 	static const GMColor&   LavenderBlush;
    /*!
        @const LawnGreen
        色の定数です。
     */
 	static const GMColor&   LawnGreen;
    /*!
        @const LemonChiffon
        色の定数です。
     */
 	static const GMColor&   LemonChiffon;
    /*!
        @const LightBlue
        色の定数です。
     */
 	static const GMColor&   LightBlue;
    /*!
        @const LightCoral
        色の定数です。
     */
 	static const GMColor&   LightCoral;
    /*!
        @const LightCyan
        色の定数です。
     */
 	static const GMColor&   LightCyan;
    /*!
        @const LightGoldenrodYellow
        色の定数です。
     */
 	static const GMColor&   LightGoldenrodYellow;
    /*!
        @const LightGray
        色の定数です。
     */
 	static const GMColor&   LightGray;
    /*!
        @const LightGreen
        色の定数です。
     */
 	static const GMColor&   LightGreen;
    /*!
        @const LightPink
        色の定数です。
     */
 	static const GMColor&   LightPink;
    /*!
        @const LightSalmon
        色の定数です。
     */
 	static const GMColor&   LightSalmon;
    /*!
        @const LightSeaGreen
        色の定数です。
     */
 	static const GMColor&   LightSeaGreen;
    /*!
        @const LightSkyBlue
        色の定数です。
     */
 	static const GMColor&   LightSkyBlue;
    /*!
        @const LightSlateGray
        色の定数です。
     */
 	static const GMColor&   LightSlateGray;
    /*!
        @const LightSteelBlue
        色の定数です。
     */
 	static const GMColor&   LightSteelBlue;
    /*!
        @const LightYellow
        色の定数です。
     */
 	static const GMColor&   LightYellow;
    /*!
        @const Lime
        色の定数です。
     */
 	static const GMColor&   Lime;
    /*!
        @const LimeGreen
        色の定数です。
     */
 	static const GMColor&   LimeGreen;
    /*!
        @const Linen
        色の定数です。
     */
 	static const GMColor&   Linen;

    // Color M-
    /*!
        @const Magenta
        色の定数です。
     */
    static const GMColor&   Magenta;
    /*!
        @const Maroon
        色の定数です。
     */
 	static const GMColor&   Maroon;
    /*!
        @const MediumAquamarine
        色の定数です。
     */
 	static const GMColor&   MediumAquamarine;
    /*!
        @const MediumBlue
        色の定数です。
     */
 	static const GMColor&   MediumBlue;
    /*!
        @const MediumOrchid
        色の定数です。
     */
 	static const GMColor&   MediumOrchid;
    /*!
        @const MediumPurple
        色の定数です。
     */
 	static const GMColor&   MediumPurple;
    /*!
        @const MediumSeaGreen
        色の定数です。
     */
 	static const GMColor&   MediumSeaGreen;
    /*!
        @const MediumSlateBlue
        色の定数です。
     */
 	static const GMColor&   MediumSlateBlue;
    /*!
        @const MediumSpringGreen
        色の定数です。
     */
 	static const GMColor&   MediumSpringGreen;
    /*!
        @const MediumTurquoise
        色の定数です。
     */
 	static const GMColor&   MediumTurquoise;
    /*!
        @const MediumVioletRed
        色の定数です。
     */
 	static const GMColor&   MediumVioletRed;
    /*!
        @const MidnightBlue
        色の定数です。
     */
 	static const GMColor&   MidnightBlue;
    /*!
        @const MintCream
        色の定数です。
     */
 	static const GMColor&   MintCream;
    /*!
        @const MistyRose
        色の定数です。
     */
 	static const GMColor&   MistyRose;
    /*!
        @const Moccasin
        色の定数です。
     */
 	static const GMColor&   Moccasin;

    // Color N-
    /*!
        @const NavajoWhite
        色の定数です。
     */
 	static const GMColor&   NavajoWhite;
    /*!
        @const Navy
        色の定数です。
     */
	static const GMColor&   Navy;

    // Color O-
    /*!
        @const OldLace
        色の定数です。
     */
 	static const GMColor&   OldLace;
    /*!
        @const Olive
        色の定数です。
     */
 	static const GMColor&   Olive;
    /*!
        @const OliveDrab
        色の定数です。
     */
 	static const GMColor&   OliveDrab;
    /*!
        @const Orange
        色の定数です。
     */
 	static const GMColor&   Orange;
    /*!
        @const OrangeRed
        色の定数です。
     */
 	static const GMColor&   OrangeRed;
    /*!
        @const Orchid
        色の定数です。
     */
 	static const GMColor&   Orchid;

    // Color P-
    /*!
        @const PaleGoldenrod
        色の定数です。
     */
 	static const GMColor&   PaleGoldenrod;
    /*!
        @const PaleGreen
        色の定数です。
     */
 	static const GMColor&   PaleGreen;
    /*!
        @const PaleTurquoise
        色の定数です。
     */
 	static const GMColor&   PaleTurquoise;
    /*!
        @const PaleVioletRed
        色の定数です。
     */
 	static const GMColor&   PaleVioletRed;
    /*!
        @const PapayaWhip
        色の定数です。
     */
 	static const GMColor&   PapayaWhip;
    /*!
        @const PeachPuff
        色の定数です。
     */
 	static const GMColor&   PeachPuff;
    /*!
        @const Peru
        色の定数です。
     */
 	static const GMColor&   Peru;
    /*!
        @const Pink
        色の定数です。
     */
 	static const GMColor&   Pink;
    /*!
        @const Plum
        色の定数です。
     */
 	static const GMColor&   Plum;
    /*!
        @const PowderBlue
        色の定数です。
     */
 	static const GMColor&   PowderBlue;
    /*!
        @const Purple
        色の定数です。
     */
 	static const GMColor&   Purple;
    
    // Color R-
    /*!
        @const Red
        色の定数です。
     */
    static const GMColor&   Red;
    /*!
        @const RosyBrown
        色の定数です。
     */
 	static const GMColor&   RosyBrown;
    /*!
        @const RoyalBlue
        色の定数です。
     */
 	static const GMColor&   RoyalBlue;

    // Color S-
    /*!
        @const SaddleBrown
        色の定数です。
     */
 	static const GMColor&   SaddleBrown;
    /*!
        @const Salmon
        色の定数です。
     */
 	static const GMColor&   Salmon;
    /*!
        @const SandyBrown
        色の定数です。
     */
 	static const GMColor&   SandyBrown;
    /*!
        @const SeaGreen
        色の定数です。
     */
 	static const GMColor&   SeaGreen;
    /*!
        @const SeaShell
        色の定数です。
     */
 	static const GMColor&   SeaShell;
    /*!
        @const Sienna
        色の定数です。
     */
 	static const GMColor&   Sienna;
    /*!
        @const Silver
        色の定数です。
     */
 	static const GMColor&   Silver;
    /*!
        @const SkyBlue
        色の定数です。
     */
 	static const GMColor&   SkyBlue;
    /*!
        @const SlateBlue
        色の定数です。
     */
 	static const GMColor&   SlateBlue;
    /*!
        @const SlateGray
        色の定数です。
     */
 	static const GMColor&   SlateGray;
    /*!
        @const Snow
        色の定数です。
     */
 	static const GMColor&   Snow;
    /*!
        @const SpringGreen
        色の定数です。
     */
 	static const GMColor&   SpringGreen;
    /*!
        @const SteelBlue
        色の定数です。
     */
 	static const GMColor&   SteelBlue;
    
    // Color T-
    /*!
        @const Tan
        色の定数です。
     */
    static const GMColor&   Tan;
    /*!
        @const Teal
        色の定数です。
     */
 	static const GMColor&   Teal;
    /*!
        @const Thistle
        色の定数です。
     */
 	static const GMColor&   Thistle;
    /*!
        @const Tomato
        色の定数です。
     */
 	static const GMColor&   Tomato;
    /*!
        @const TransparentBlack
        色の定数です。
     */
 	static const GMColor&   TransparentBlack;
    /*!
        @const TransparentWhite
        色の定数です。
     */
 	static const GMColor&   TransparentWhite;
    /*!
        @const Turquoise
        色の定数です。
     */
 	static const GMColor&   Turquoise;
    
    // Color V-
    /*!
        @const Violet
        色の定数です。
     */
    static const GMColor&   Violet;
    
    // Color W-
    /*!
        @const Wheat
        色の定数です。
     */
    static const GMColor&   Wheat;
    /*!
        @const White
        色の定数です。
     */
    static const GMColor&   White;
    /*!
        @const WhiteSmoke
        色の定数です。
     */
    static const GMColor&   WhiteSmoke;
    
    // Color Y-
    /*!
        @const Yellow
        色の定数です。
     */
    static const GMColor&   Yellow;
    /*!
        @const YellowGreen
        色の定数です。
     */
 	static const GMColor&   YellowGreen;
    
public:
    /*!
        @task   補間計算
     */

    /*!
        @method     EaseIn
        @abstract   2つの色の間を Ease In 補間した色を作成します。
     */
    static GMColor  EaseIn(const GMColor& color1, const GMColor& color2, double amount);
    
    /*!
        @method     EaseInOut
        @abstract   2つの色の間を Ease In Out 補間した色を作成します。
     */
    static GMColor  EaseInOut(const GMColor& color1, const GMColor& color2, double amount);

    /*!
        @method     EaseOut
        @abstract   2つの色の間を Ease Out 補間した色を作成します。
     */
    static GMColor  EaseOut(const GMColor& color1, const GMColor& color2, double amount);
    
    /*!
        @method     Lerp
        @abstract   2つの色の間を線形補間した色を作成します。
     */
    static GMColor  Lerp(const GMColor& color1, const GMColor& color2, double amount);


public:
    /*!
        @var        r
        @abstract   赤の色成分（0〜255）
     */
    GLfloat     r;

    /*!
        @var        g
        @abstract   緑の色成分（0〜255）
     */
    GLfloat     g;

    /*!
        @var        b
        @abstract   青の色成分（0〜255）
     */
    GLfloat     b;

    /*!
        @var        a
        @abstract   アルファの色成分（0〜255）
     */
    GLfloat     a;

public:
    /*!
        @task   コンストラクタ
     */

    /*!
        @method     GMColor
        @abstract   赤、緑、青の各色成分が 0 で、アルファ成分が 255 の色を作成します。
     */
    GMColor();

    /*!
        @method     GMColor
        @abstract   赤、緑、青、アルファの各色成分を 0.0〜1.0 で指定して色を作成します。
     */
    GMColor(double r, double g, double b, double a);
    
    /*!
        @method     GMColor
        @abstract   渡された色と同じ色情報をもつ色を作成します。
     */
    GMColor(const GMColor& color);

    /*!
        @method     GMColor
        @abstract   渡されたベクトルを利用して、r=x, g=y, b=z となるように、アルファ成分が 255 の色を作成します。
     */
    GMColor(const GMVector3D& vector);

    /*!
        @method     GMColor
        @abstract   渡されたベクトルを利用して、r=x, g=y, b=z, a=w となるように色を作成します。
     */
    GMColor(const GMVector4D& vector);
    
    /*!
        @task   メインの操作
     */

    /*!
        @method equals
     */
    bool        equals(const GMColor& color, double accuracy) const;

    
    /*!
        @task   演算子のオーバーロード
     */
    
    /*!
        @method operator=
        @abstract 渡された色情報をこのオブジェクトにコピーします。
     */
    GMColor&    operator=(const GMColor& color);

    /*!
        @method operator==
        @abstract 渡された色の色情報とこのオブジェクトのもつ色情報が等しいかどうかをチェックします。
     */
    bool        operator==(const GMColor& color) const;

    /*!
        @method operator!=
        @abstract 渡された色の色情報とこのオブジェクトのもつ色情報が等しくないかどうかをチェックします。
     */
    bool        operator!=(const GMColor& color) const;
    
    /*!
        @task   ベクトルサポート
     */
    
    /*!
        @method     toVector3D
        @abstract   3次元ベクトルに変換します。
     */
    GMVector3D  toVector3D() const;

    /*!
        @method     toVector4D
        @abstract   4次元ベクトルに変換します。
     */
    GMVector4D  toVector4D() const;
    
};


#endif  //#ifndef __GM_COLOR_H__


