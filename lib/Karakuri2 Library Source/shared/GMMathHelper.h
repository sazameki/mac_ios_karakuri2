//
//  GMMathHelper.h
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_MATH_HELPER_H__
#define __GM_MATH_HELPER_H__


#include "GMObject.h"


/*!
    @class  GMMathHelper
    @group  Math
 */
struct GMMathHelper : public GMObject {

    
    static const double DoubleEqThreshold;
    static const float  FloatEqThreshold;

    /*!
        @task   数値補完
     */

    /*!
        @method     Barycentric
        @abstract   指定されたトライアングルと2つの正規化された重心 (エリア) 座標に基づいて定義されたポイントの、特定の軸でのデカルト座標を返します。
     */
    static double   Barycentric(double value1, double value2, double value3, double amount1, double amount2);
    
    /*!
        @method     CatmullRom
     */
    static double   CatmullRom(double value1, double value2, double value3, double value4, double amount);
    
    /*!
        @method     EaseIn
     */
    static double   EaseIn(double value1, double value2, double amount);
    
    /*!
        @method     EaseInOut
     */
    static double   EaseInOut(double value1, double value2, double amount);

    /*!
        @method     EaseOut
     */
    static double   EaseOut(double value1, double value2, double amount);
    
    /*!
        @method     Hermite
     */
    static double   Hermite(double value1, double tan1, double value2, double tan2, double amount);

    /*!
        @method     Lerp
     */
    static double   Lerp(double value1, double value2, double amount);

    /*!
        @method     SmoothStep
     */
    static double   SmoothStep(double edge0, double edge1, double x);

    /*!
        @task   数値処理
     */
    
    /*!
        @method     Clamp
     */
    static double   Clamp(double x, double minVal, double maxVal);

    /*!
        @method     Distance
     */
    static double   Distance(double value1, double value2);

    /*!
        @method     Max
     */
    static double   Max(double value1, double value2);

    /*!
        @method     Min
     */
    static double   Min(double value1, double value2);
    
    /*!
        @task   角度の変換
     */
    
    /*!
        @method     ToDegrees
        @abstract   ラジアン単位の角度を度に変換します。
     */
    static double   ToDegrees(double radians);

    /*!
        @method     ToRadians
        @abstract   度をラジアン単位の角度に変換します。
     */
    static double   ToRadians(double degrees);

    /*!
        @method     WrapAngle
        @abstract   指定された角度を π ～ -π の間の値に狭めます。
     */
    static double   WrapAngle(double radians);
    
};


#endif  //#ifndef __GM_MATH_HELPER_H__


