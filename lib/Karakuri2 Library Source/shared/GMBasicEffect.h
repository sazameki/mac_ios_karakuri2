//
//  GMBasicEffect.h
//  Game Framework
//
//  Created by numata on Jan 11, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_BASIC_EFFECT_H__
#define __GM_BASIC_EFFECT_H__


#include "GMEffect.h"
#include "GMMatrix.h"
#include "GMTexture2D.h"


struct __GMMaterial {
    GMVector3D  diffuse;
    GMVector3D  specular;
    GMVector3D  ambient;
    GMVector3D  emission;
    double      shininess;
    
    __GMMaterial()
    {
        diffuse = GMVector3D(0.8, 0.8, 0.8);
        specular = GMVector3D(0.0, 0.0, 0.0);
        ambient = GMVector3D(0.2, 0.2, 0.2);
        emission = GMVector3D(0.0, 0.0, 0.0);
        shininess = 0.0;
    }
    
    void set()
    {
        {
            GLfloat params[] = { diffuse.x, diffuse.y, diffuse.z, 1.0 };
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, params);
        }
        {
            GLfloat params[] = { specular.x, specular.y, specular.z, 1.0 };
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, params);
        }
        {
            GLfloat params[] = { ambient.x, ambient.y, ambient.z, 1.0 };
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, params);
        }
        {
            GLfloat params[] = { emission.x, emission.y, emission.z, 1.0 };
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, params);
        }
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, (GLfloat)shininess);
    }
    
};


/*!
    @class      GMBasicEffect
    @group      Graphics
    @abstract   行列、ライティング、テクスチャ、マテリアルを管理し、シェーダとのやり取りを行うためのクラスです。
    <p>カメラ特性などの射影変換の設定はプロジェクション行列で、カメラの向きなどの設定はビュー行列で、各モデルの位置などの設定はワールド行列で行います。</p>
    <p>アルファブレンディングの設定は、GMDraw クラスで管理されています。また、ビューの大きさとポイントスプライトの設定は GMGraphics クラスで管理されています。</p>
    <p>Globals.cpp の設定で、GMShaderEnabled の値が true に設定されていなければ、OpenGL（あるいは OpenGL ES）の固定シェーダが利用されます。</p>
 */
class GMBasicEffect : public GMEffect {
    
    GMMatrix        mProjectionMatrix;
    GMMatrix        mViewMatrix;
    GMMatrix        mWorldMatrix;

    bool            mIsLightingEnabled;
    
    GMTexture2D*    mTexture;
    bool            mIsTextureEnabled;

    __GMMaterial    mMaterial;
    
public:
    GMBasicEffect();
    virtual ~GMBasicEffect();
    
public:
    virtual void    begin();
    virtual void    end();
    
protected:
    virtual void    bindAttribLocations();
    virtual void    getUniformLocations();
    
public:
    /*!
        @task   各種行列の管理
     */
    
    /*!
        @method     getProjectionMatrix
     */
    GMMatrix    getProjectionMatrix() const;
    
    /*!
        @method     getViewMatrix
     */
    GMMatrix    getViewMatrix() const;
    
    /*!
        @method     getWorldMatrix
     */
    GMMatrix    getWorldMatrix() const;
    
    /*!
        @method     setProjectionMatrix
     */
    void        setProjectionMatrix(const GMMatrix& matrix);
    
    /*!
        @method     setViewMatrix
     */
    void        setViewMatrix(const GMMatrix& matrix);
    
    /*!
        @method     setWorldMatrix
     */
    void        setWorldMatrix(const GMMatrix& matrix);


    /*!
        @task   ライティング設定
     */

    /*!
        @method     enableLighting
        @abstract   ライティングを有効または無効にします。
     */
    void        enableLighting(bool flag);
    
    /*!
        @method     isLightingEnabled
        @abstract   ライティングを有効にしているかどうかを取得します。
     */
    bool        isLightingEnabled() const;


    /*!
        @task   ライト設定
     */

    /*!
        @method enableLight
     */
    void        enableLight(int index, bool flag);
    
    /*!
        @method setLightAmbientColor
     */
    void        setLightAmbientColor(int index, const GMVector3D& vec);
    
    /*!
        @method setLightDiffuseColor
     */
    void        setLightDiffuseColor(int index, const GMVector3D& vec);
    
    /*!
        @method setLightSpecularColor
     */
    void        setLightSpecularColor(int index, const GMVector3D& vec);
    
    /*!
        @method setLightTypeAsPoint
        @abstract 位置を指定して点光源としてライトを設定します。
     */
    void        setLightTypeAsPoint(int index, const GMVector3D& vecPosition);
    
    /*!
        @method setLightTypeAsParallel
        @abstract 方向を指定して平行光源としてライトを設定します。
     */
    void        setLightTypeAsParallel(int index, const GMVector3D& vecDirection);
    
    /*!
        @method setLightTypeAsSpot
        @abstract 位置、方向、開き角度、拡散の度合いを指定して、スポットライトとしてライトを設定します。
        拡散の度合いを示す exponent には 0.0〜128.0 の値を指定します。
     */
    void        setLightTypeAsSpot(int index, const GMVector3D& vecPosition, const GMVector3D& vecDirection, double radAngle, double exponent);
    
    /*!
     @method setLightAttenuation
     @abstract 光の減衰率を指定します。
     */
    void        setLightAttenuation(int index, double constant, double linear, double quadratic);

    
    /*!
        @task   テクスチャ設定
     */
    
    /*!
        @method     enableTexture
     */
    void            enableTexture(bool flag);

    /*!
        @method     getTexture
     */
    GMTexture2D*    getTexture() const;

    /*!
        @method     isTextureEnabled
     */
    bool            isTextureEnabled() const;

    /*!
        @method     setTexture
     */
    void            setTexture(GMTexture2D* tex);


    /*!
        @task   マテリアル設定
     */
    
    /*!
        @method     getMaterialDiffuse
     */
    GMVector3D      getMaterialDiffuse() const;

    /*!
        @method     getMaterialSpecular
     */
    GMVector3D      getMaterialSpecular() const;

    /*!
        @method     getMaterialAmbient
     */
    GMVector3D      getMaterialAmbient() const;

    /*!
        @method     getMaterialEmission
     */
    GMVector3D      getMaterialEmission() const;

    /*!
        @method     getMaterialShininess
     */
    double          getMaterialShininess() const;

    /*!
        @method     setMaterial
        @method     マテリアルの設定を行います。この設定は、ライティングが有効な環境でのみ反映されます。
        引数なしで実行した場合、OpenGL 標準のデフォルトマテリアル設定が使用されます。
     */
    void            setMaterial(const GMVector3D& diffuse = GMVector3D(0.8, 0.8, 0.8), const GMVector3D& specular = GMVector3D::Zero, const GMVector3D& ambient = GMVector3D(0.2, 0.2, 0.2), const GMVector3D& emission = GMVector3D::Zero, const double shininess = 0.0);

};


#endif  //#ifndef __GM_BASIC_EFFECT_H__

