//
//  GMMatrix.h
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_MATRIX_H__
#define __GM_MATRIX_H__


#include "GMObject.h"

struct GMMatrix;
struct GMPlane;
struct GMQuat;
struct GMVector3D;


/*
    ///// 2D設定
    GMVector2D screenSize = g->getScreenSize();
    g->setProjectionMatrix(GMMatrix::CreateOrthographicOffCenter(0.0, screenSize.x, 0.0, screenSize.y, 1.0, 1500.0));
    g->setViewMatrix(GMMatrix::Identity);
 
    ///// 3D設定
    // 視錐体の設定
    //   35mmフィルムに対する実際のレンズの画角例
    //     ・望遠域（135mmレンズで18度、300mmレンズで8度）
    //     ・標準域（肉眼に近い）（50mmレンズで45度）
    //     ・広角域（35mmレンズで62度、24mmレンズで84度、20mmレンズで94度）
    GMVector2D screenSize = g->getScreenSize();
    g->setProjectionMatrix(GMMatrix::CreatePerspectiveFieldOfView(M_PI/4, screenSize.x/screenSize.y, 1.0, 1500.0));
 */


/*!
    @class      GMMatrix
    @group      Math
    @abstract   4x4 の変換行列をサポートするためのクラスです。
 */
struct GMMatrix : public GMObject {
    
public:
    /*!
        @const  Identity
     */
    static const GMMatrix&  Identity;

public:
    union {
        float   mat[16];
        struct {
            /*!
                @var m11
             */
            float m11;

            /*!
                @var m12
             */
            float m12;

            /*!
                @var m13
             */
            float m13;

            /*!
                @var m14
             */
            float m14;
            
            /*!
                @var m21
             */
            float m21;
            
            /*!
                @var m22
             */
            float m22;
            
            /*!
                @var m23
            */
            float m23;
            
            /*!
                @var m24
             */
            float m24;

            /*!
                @var m31
             */
            float m31;
            
            /*!
                @var m32
             */
            float m32;

            /*!
                @var m33
             */
            float m33;
            
            /*!
                @var m34
             */
            float m34;
            
            /*!
                @var m41
             */
            float m41;

            /*!
                @var m42
             */
            float m42;

            /*!
                @var m43
             */
            float m43;

            /*!
                @var m44
             */
            float m44;
        };
    };
    
    /*!
        @task   生成メソッド
     */
    
    /*!
        @method     CreateBillboard
     */
    static GMMatrix     CreateBillboard(const GMVector3D& objectPos, const GMVector3D& cameraPos,
                                        const GMVector3D& cameraUpVec, const GMVector3D cameraForwardVec);
    
    /*!
        @method     CreateConstrainedBillboard
     */
    static GMMatrix     CreateConstrainedBillboard(const GMVector3D& objectPos, const GMVector3D& cameraPos, const GMVector3D& rotateAxis,
                                                   const GMVector3D& cameraForwardVec, const GMVector3D& objectForwardVec);
    
    /*!
        @method     CreateFromAxisAngle
     */
    static GMMatrix     CreateFromAxisAngle(const GMVector3D& axis, double angle);
    
    /*!
        @method     CreateFromYawPitchRoll
     */
    static GMMatrix     CreateFromYawPitchRoll(double yaw, double pitch, double roll);
    
    /*!
        @method     CreateLookAt
     */
    static GMMatrix     CreateLookAt(const GMVector3D& cameraPos, const GMVector3D& cameraTarget, const GMVector3D& cameraUpVec);
    
    /*!
        @method     CreateOrthographic
     */
    static GMMatrix     CreateOrthographic(double width, double height, double zNear, double zFar);
    
    /*!
        @method     CreateOrthographicOffCenter
     */
    static GMMatrix     CreateOrthographicOffCenter(double left, double right, double bottom, double top, double zNear, double zFar);
    
    /*!
        @method     CreatePerspective
     */
    static GMMatrix     CreatePerspective(double width, double height, double nearDist, double farDist);
    
    /*!
        @method     CreatePerspectiveFieldOfView
     */
    static GMMatrix     CreatePerspectiveFieldOfView(double fieldOfView, double aspectRatio, double nearDist, double farDist);
    
    /*!
        @method     CreatePerspectiveOffCenter
     */
    static GMMatrix     CreatePerspectiveOffCenter(double left, double right, double bottom, double top, double nearDist, double farDist);
    
    /*!
        @method     CreateReflection
     */
    static GMMatrix     CreateReflection(const GMPlane& plane);
    
    /*!
        @method     CreateRotationX
     */
    static GMMatrix     CreateRotationX(double radians);
    
    /*!
        @method     CreateRotationY
     */
    static GMMatrix     CreateRotationY(double radians);
    
    /*!
        @method     CreateRotationZ
     */
    static GMMatrix     CreateRotationZ(double radians);
    
    /*!
        @method     CreateScale
     */
    static GMMatrix     CreateScale(double scale);
    
    /*!
        @method     CreateScale
     */
    static GMMatrix     CreateScale(double x, double y, double z);
    
    /*!
        @method     CreateScale
     */
    static GMMatrix     CreateScale(const GMVector3D& vec);
    
    /*!
        @method     CreateShadow
     */
    static GMMatrix     CreateShadow(const GMVector3D& lightDir, const GMPlane& plane);
    
    /*!
        @method     CreateTranslation
     */
    static GMMatrix     CreateTranslation(double x, double y, double z);
    
    /*!
        @method     CreateTranslation
     */
    static GMMatrix     CreateTranslation(const GMVector3D& vec);
    
    /*!
        @method     CreateWorld
     */
    static GMMatrix     CreateWorld(const GMVector3D& pos, const GMVector3D& forward, const GMVector3D& up);
    
    /*!
        @task   数値補完
     */
    
    /*!
        @method     EaseIn
     */
    static GMMatrix     EaseIn(const GMMatrix& mat1, const GMMatrix& mat2, double amount);

    /*!
        @method     EaseInOut
     */
    static GMMatrix     EaseInOut(const GMMatrix& mat1, const GMMatrix& mat2, double amount);

    /*!
        @method     EaseOut
     */
    static GMMatrix     EaseOut(const GMMatrix& mat1, const GMMatrix& mat2, double amount);
    
    /*!
        @method     Lerp
     */
    static GMMatrix     Lerp(const GMMatrix& mat1, const GMMatrix& mat2, double amount);
    
    /*!
        @task コンストラクタ
     */

    /*!
        @method     GMMatrix
        @abstract   すべての要素が 0.0 の行列を生成します。
     */
    GMMatrix();

    /*!
        @method     GMMatrix
        @abstract   各要素を設定して行列を生成します。
     */
    GMMatrix(double m11, double m12, double m13, double m14, double m21, double m22, double m23, double m24, double m31, double m32, double m33, double m34, double m41, double m42, double m43, double m44);

    /*!
        @method     GMMatrix
        @abstract   各要素をコピーして行列を生成します。
     */
    GMMatrix(const GMQuat& quat);

    /*!
        @task   メインの操作
     */
    
    /*!
        @method     decompose
     */
    bool        decompose(GMVector3D& scale, GMQuat& rotation, GMVector3D& translation) const;

    /*!
        @method     determinant
        @abstract   この行列の行列式を計算します。
     */
    double      determinant() const;
    
    /*!
        @method     equals
     */
    bool        equals(const GMMatrix& matrix, double accuracy) const;
    
    /*!
        @method     invert
     */
    GMMatrix    invert() const;
    
    /*!
        @method     toQuat
     */
    GMQuat      toQuat() const;
    
    /*!
        @method     transform
        この行列にクォータニオンの回転を適用した行列を求めます。
     */
    GMMatrix    transform(const GMQuat& quat) const;
    
    /*!
        @method     transpose
        @abstract   この行列の転置行列を求めます。
     */
    GMMatrix    transpose() const;
    
    /*!
        @task   アクセッサ
     */
    
    /*!
        @method setBackward
     */
    void        setBackward(const GMVector3D& vec);
    
    /*!
        @method setDown
     */
    void        setDown(const GMVector3D& vec);
    
    /*!
        @method setForward
     */
    void        setForward(const GMVector3D& vec);
    
    /*!
        @method setLeft
     */
    void        setLeft(const GMVector3D& vec);
    
    /*!
        @method setRight
     */
    void        setRight(const GMVector3D& vec);
    
    /*!
        @method setTranslation
     */
    void        setTranslation(const GMVector3D& vec);
    
    /*!
        @method setUp
     */
    void        setUp(const GMVector3D& vec);
    
    /*!
        @task   演算子のオーバーロード
     */
    
    /*!
        @method     operator=
     */
    GMMatrix&   operator=(const GMMatrix& matrix);
    
    /*!
        @method     operator-
     */
    GMMatrix    operator-() const;

    /*!
        @method     operator+
     */
    GMMatrix    operator+(const GMMatrix& matrix) const;

    /*!
        @method     operator-
     */
    GMMatrix    operator-(const GMMatrix& matrix) const;

    /*!
        @method     operator*
     */
    GMMatrix    operator*(const GMMatrix& matrix) const;

    /*!
        @method     operator/
     */
    GMMatrix    operator/(const GMMatrix& matrix) const;

    /*!
        @method     operator*
     */
    GMMatrix    operator*(double value) const;

    /*!
        @method     operator/
     */
    GMMatrix    operator/(double value) const;
    
    
    friend GMMatrix operator*(double value, const GMMatrix& matrix);
    
    
    /*!
        @method     operator+=
     */
    GMMatrix&   operator+=(const GMMatrix& matrix);
    
    /*!
        @method     operator-=
     */
    GMMatrix&   operator-=(const GMMatrix& matrix);
    
    /*!
        @method     operator*=
     */
    GMMatrix&   operator*=(const GMMatrix& matrix);
    
    /*!
        @method     operator/=
     */
    GMMatrix&   operator/=(const GMMatrix& matrix);
    
    /*!
        @method     operator*=
     */
    GMMatrix&   operator*=(double value);
    
    /*!
        @method     operator/=
     */
    GMMatrix&   operator/=(double value);
    
    
    /*!
        @method     operator==
     */
    bool        operator==(const GMMatrix& matrix) const;
    
    /*!
        @method     operator!=
     */
    bool        operator!=(const GMMatrix& matrix) const;
    
};


#endif  //#ifndef __GM_MATRIX_H__


