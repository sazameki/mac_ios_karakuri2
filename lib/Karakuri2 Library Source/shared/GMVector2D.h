//
//  GMVector2D.h
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_VECTOR2D_H__
#define __GM_VECTOR2D_H__


#include "GMObject.h"

struct GMVector2D;
struct GMMatrix;
struct GMQuat;

    
/*!
    @class  GMVector2D
    @group  Math
 */
struct GMVector2D : public GMObject {
    
public:
    /*!
        @const  One
     */
    static const GMVector2D&    One;

    /*!
        @const  UnitX
     */
    static const GMVector2D&    UnitX;

    /*!
        @const  UnitY
     */
    static const GMVector2D&    UnitY;

    /*!
        @const  Zero
     */
    static const GMVector2D&    Zero;

public:
    /*!
        @var    x
     */
    double x;

    /*!
        @var    y
     */
    double y;
    
    /*!
        @task   数値補完
     */
    
    /*!
        @method     Barycentric
     */
    static GMVector2D   Barycentric(const GMVector2D& v1, const GMVector2D& v2, const GMVector2D& v3, double amount1, double amount2);
    
    /*!
        @method     CatmullRom
     */
    static GMVector2D   CatmullRom(const GMVector2D& vec1, const GMVector2D& vec2, const GMVector2D& vec3, const GMVector2D& vec4, double amount);

    /*!
        @method     EaseIn
     */
    static GMVector2D   EaseIn(const GMVector2D& vec1, const GMVector2D& vec2, double amount);

    /*!
        @method     EaseInOut
     */
    static GMVector2D   EaseInOut(const GMVector2D& vec1, const GMVector2D& vec2, double amount);

    /*!
        @method     EaseOut
     */
    static GMVector2D   EaseOut(const GMVector2D& vec1, const GMVector2D& vec2, double amount);

    /*!
        @method     Hermite
     */
    static GMVector2D   Hermite(const GMVector2D& vec1, const GMVector2D& tan1, const GMVector2D& vec2, const GMVector2D& tan2, double amount);
    
    /*!
        @method     Lerp
     */
    static GMVector2D   Lerp(const GMVector2D& vec1, const GMVector2D& vec2, double amount);
    
    /*!
        @method     SmoothStep
     */
    static GMVector2D   SmoothStep(const GMVector2D& vec1, const GMVector2D& vec2, double amount);
    
    /*!
        @task   数値処理
     */
    
    /*!
        @method     Max
     */
    static GMVector2D   Max(const GMVector2D& vec1, const GMVector2D& vec2);
    
    /*!
        @method     Min
     */
    static GMVector2D   Min(const GMVector2D& vec1, const GMVector2D& vec2);
    
    /*!
        @task   コンストラクタ
     */
    
    /*!
        @method     GMVector2D
     */
    GMVector2D();
    
    /*!
        @method     GMVector2D
     */
    GMVector2D(double value);
    
    /*!
        @method     GMVector2D
     */
    GMVector2D(double x, double y);
    
    /*!
        @method     GMVector2D
     */
    GMVector2D(const GMVector2D& vec);

    /*!
        メインの操作
     */
    
    /*!
        @method     clamp
     */
    GMVector2D  clamp(const GMVector2D& min, const GMVector2D& max) const;
    
    /*!
        @method     cross
     */
    double      cross(const GMVector2D& vec) const;
    
    /*!
        @method     distance
     */
    double      distance(const GMVector2D& vec) const;
    
    /*!
        @method     distanceSq
     */
    double      distanceSq(const GMVector2D& vec) const;
    
    /*!
        @method     dot
     */
    double      dot(const GMVector2D& vec) const;
    
    /*!
        @method     equals
     */
    bool        equals(const GMVector2D& vec, double accuracy) const;
    
    /*!
        @method     length
     */
    double      length() const;
    
    /*!
        @method     lengthSq
     */
    double      lengthSq() const;
    
    /*!
        @method     normal
     */
    GMVector2D  normal() const;
    
    /*!
        @method     normalize
     */
    GMVector2D& normalize();
    
    /*!
        @method     reflect
     */
    GMVector2D  reflect(const GMVector2D& normal) const;
    
    /*!
        @method     transform
     */
    GMVector2D  transform(const GMMatrix& matrix) const;
    
    /*!
        @method     transform
     */
    GMVector2D  transform(const GMQuat& quat) const;
    
    /*!
        @task   演算子のオーバーロード
     */
    
    /*!
        @method     operator=
     */
    GMVector2D& operator=(const GMVector2D& vec);
        
    /*!
        @method     operator-
     */
    GMVector2D operator-() const;
    
    /*!
        @method     operator+
     */
    GMVector2D operator+(const GMVector2D& vec) const;
    
    /*!
        @method     operator-
     */
    GMVector2D operator-(const GMVector2D& vec) const;
    
    /*!
        @method     operator*
     */
    GMVector2D operator*(const GMVector2D& vec) const;
    
    /*!
        @method     operator/
     */
    GMVector2D operator/(const GMVector2D& vec) const;
    
    /*!
        @method     operator*
     */
    GMVector2D operator*(double value) const;
    
    /*!
        @method     operator/
     */
    GMVector2D operator/(double value) const;
    
    friend GMVector2D operator*(double value, const GMVector2D& vec);
    
    
    /*!
        @method     operator+=
     */
    GMVector2D& operator+=(const GMVector2D& vec);
    
    /*!
        @method     operator-=
     */
    GMVector2D& operator-=(const GMVector2D& vec);
    
    /*!
        @method     operator*=
     */
    GMVector2D& operator*=(const GMVector2D& vec);
    
    /*!
        @method     operator/=
     */
    GMVector2D& operator/=(const GMVector2D& vec);
    
    /*!
        @method     operator*=
     */
    GMVector2D& operator*=(double value);
    
    /*!
        @method     operator/=
     */
    GMVector2D& operator/=(double value);
    
    
    /*!
        @method     operator==
     */
    bool        operator==(const GMVector2D& vec) const;
    
    /*!
        @method     operator!=
     */
    bool        operator!=(const GMVector2D& vec) const;
    
};


#endif  //#ifndef __GM_VECTOR2D_H__


