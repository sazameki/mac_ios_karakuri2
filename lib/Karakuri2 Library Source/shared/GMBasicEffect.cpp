//
//  GMBasicEffect.cpp
//  Game Framework
//
//  Created by numata on Jan 11, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMBasicEffect.h"

#include <cstdio>
#include <iostream>


// Uniform index.
enum {
    UNIFORM_TRANSLATE,
    NUM_UNIFORMS
};
GLint uniforms[NUM_UNIFORMS];

// Attribute index.
enum {
    ATTRIB_VERTEX,
    ATTRIB_COLOR,
    NUM_ATTRIBUTES
};


GMBasicEffect::GMBasicEffect()
    : GMEffect("BasicEffect.vsh", "BasicEffect.fsh")
{
    mProjectionMatrix = GMMatrix::Identity;
    mViewMatrix = GMMatrix::Identity;
    mWorldMatrix = GMMatrix::Identity;
    
    mIsLightingEnabled = false;
    
    mTexture = NULL;
    mIsTextureEnabled = false;
}

GMBasicEffect::~GMBasicEffect()
{
}

void GMBasicEffect::begin()
{
    GMEffect::begin();

    ///// シェーダを使った場合の描画開始
    if (GMGraphics::CurrentGraphics->isShaderEnabled()) {
        // シェーダを使う場合には常にプロジェクション行列とビュー行列をセットする
        // TODO: プロジェクション行列とビュー行列をかけ合わせてセットする
    }
    ///// シェーダを使わない場合の描画開始
    else {
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(mProjectionMatrix.mat);

        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(mViewMatrix.mat);
    }
    
    ///// テスト
    if (GMGraphics::CurrentGraphics->isShaderEnabled()) {
        static const GLfloat squareVertices[] = {
            -0.5f, -0.33f,
            0.5f, -0.33f,
            -0.5f,  0.33f,
            0.5f,  0.33f,
        };
        
        static const GLubyte squareColors[] = {
            255, 255,   0, 255,
            0,   255, 255, 255,
            0,     0,   0,   0,
            255,   0, 255, 255,
        };
        
        static float transY = 0.0f;
        
        glUniform1f(uniforms[UNIFORM_TRANSLATE], (GLfloat)transY);
        transY += 0.075f;

        // Update attribute values.
        glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT, 0, 0, squareVertices);
        glEnableVertexAttribArray(ATTRIB_VERTEX);
        glVertexAttribPointer(ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, 1, 0, squareColors);
        glEnableVertexAttribArray(ATTRIB_COLOR);
        
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
}

void GMBasicEffect::end()
{
    GMEffect::end();
}


#pragma mark -
#pragma mark <<<< シェーダとのやり取り >>>>

void GMBasicEffect::bindAttribLocations()
{
    bindAttribLocation(ATTRIB_VERTEX, "position");
    bindAttribLocation(ATTRIB_COLOR, "color");
}

void GMBasicEffect::getUniformLocations()
{
    uniforms[UNIFORM_TRANSLATE] = getUniformLocation("translate");
}


#pragma mark -
#pragma mark <<<< 各種行列の管理 >>>>

GMMatrix GMBasicEffect::getProjectionMatrix() const
{
    return mProjectionMatrix;
}

GMMatrix GMBasicEffect::getViewMatrix() const
{
    return mViewMatrix;
}

GMMatrix GMBasicEffect::getWorldMatrix() const
{
    return mWorldMatrix;
}

void GMBasicEffect::setProjectionMatrix(const GMMatrix& matrix)
{
    mProjectionMatrix = matrix;
}

void GMBasicEffect::setViewMatrix(const GMMatrix& matrix)
{
    mViewMatrix = matrix;
}

void GMBasicEffect::setWorldMatrix(const GMMatrix& matrix)
{
    mWorldMatrix = matrix;
    
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf((mWorldMatrix * mViewMatrix).mat);
}


#pragma mark -
#pragma mark <<<< ライティング関係 >>>>

void GMBasicEffect::enableLighting(bool flag)
{
    mIsLightingEnabled = flag;

    if (mIsLightingEnabled) {
        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE);
    } else {
        glDisable(GL_LIGHTING);
        glDisable(GL_NORMALIZE);
    }
}

bool GMBasicEffect::isLightingEnabled() const
{
    return mIsLightingEnabled;
}

void GMBasicEffect::enableLight(int index, bool flag)
{
    if (flag) {
        if (index == 0) {
            glEnable(GL_LIGHT0);
        } else if (index == 1) {
            glEnable(GL_LIGHT1);
        } else if (index == 2) {
            glEnable(GL_LIGHT2);
        } else if (index == 3) {
            glEnable(GL_LIGHT3);
        } else if (index == 4) {
            glEnable(GL_LIGHT4);
        } else if (index == 5) {
            glEnable(GL_LIGHT5);
        } else if (index == 6) {
            glEnable(GL_LIGHT6);
        } else if (index == 7) {
            glEnable(GL_LIGHT7);
        } else {
            // TODO: エラー処理
        }
    } else {
        if (index == 0) {
            glDisable(GL_LIGHT0);
        } else if (index == 1) {
            glDisable(GL_LIGHT1);
        } else if (index == 2) {
            glDisable(GL_LIGHT2);
        } else if (index == 3) {
            glDisable(GL_LIGHT3);
        } else if (index == 4) {
            glDisable(GL_LIGHT4);
        } else if (index == 5) {
            glDisable(GL_LIGHT5);
        } else if (index == 6) {
            glDisable(GL_LIGHT6);
        } else if (index == 7) {
            glDisable(GL_LIGHT7);
        } else {
            // TODO: エラー処理
        }
    }
}

static void __GMSetLightf(GLenum type, int index, GLfloat value)
{
    if (index == 0) {
        glLightf(GL_LIGHT0, type, value);
    } else if (index == 1) {
        glLightf(GL_LIGHT1, type, value);
    } else if (index == 2) {
        glLightf(GL_LIGHT2, type, value);
    } else if (index == 3) {
        glLightf(GL_LIGHT3, type, value);
    } else if (index == 4) {
        glLightf(GL_LIGHT4, type, value);
    } else if (index == 5) {
        glLightf(GL_LIGHT5, type, value);
    } else if (index == 6) {
        glLightf(GL_LIGHT6, type, value);
    } else if (index == 7) {
        glLightf(GL_LIGHT7, type, value);
    } else {
        // TODO: エラー処理
    }
}

static void __GMSetLightfv(GLenum type, int index, const GMVector4D& vec)
{
    GLfloat params[] = { vec.x, vec.y, vec.z, vec.w };
    
    if (index == 0) {
        glLightfv(GL_LIGHT0, type, params);
    } else if (index == 1) {
        glLightfv(GL_LIGHT1, type, params);
    } else if (index == 2) {
        glLightfv(GL_LIGHT2, type, params);
    } else if (index == 3) {
        glLightfv(GL_LIGHT3, type, params);
    } else if (index == 4) {
        glLightfv(GL_LIGHT4, type, params);
    } else if (index == 5) {
        glLightfv(GL_LIGHT5, type, params);
    } else if (index == 6) {
        glLightfv(GL_LIGHT6, type, params);
    } else if (index == 7) {
        glLightfv(GL_LIGHT7, type, params);
    } else {
        // TODO: エラー処理
    }
}

static void __GMSetLightfv(GLenum type, int index, const GMVector3D& vec)
{
    __GMSetLightfv(type, index, GMVector4D(vec, 1.0f));
}

void GMBasicEffect::setLightAmbientColor(int index, const GMVector3D& vec)
{
    __GMSetLightfv(GL_AMBIENT, index, vec);
}

void GMBasicEffect::setLightDiffuseColor(int index, const GMVector3D& vec)
{
    __GMSetLightfv(GL_DIFFUSE, index, vec);
}

void GMBasicEffect::setLightSpecularColor(int index, const GMVector3D& vec)
{
    __GMSetLightfv(GL_SPECULAR, index, vec);
}

void GMBasicEffect::setLightTypeAsPoint(int index, const GMVector3D& vecPosition)
{
    __GMSetLightfv(GL_POSITION, index, GMVector4D(vecPosition, 1.0f));
}

void GMBasicEffect::setLightTypeAsParallel(int index, const GMVector3D& vecDirection)
{
    __GMSetLightfv(GL_POSITION, index, GMVector4D(vecDirection, 0.0f));
}

void GMBasicEffect::setLightTypeAsSpot(int index, const GMVector3D& vecPosition, const GMVector3D& vecDirection, double radAngle, double exponent)
{
    __GMSetLightfv(GL_POSITION, index, GMVector4D(vecPosition, 1.0f));
    __GMSetLightfv(GL_SPOT_DIRECTION, index, vecDirection);
    __GMSetLightf(GL_SPOT_CUTOFF, index, (GLfloat)GMMathHelper::ToDegrees(radAngle / 2));
    __GMSetLightf(GL_SPOT_EXPONENT, index, (GLfloat)exponent);
}

void GMBasicEffect::setLightAttenuation(int index, double constant, double linear, double quadratic)
{
    __GMSetLightf(GL_CONSTANT_ATTENUATION, index, (GLfloat)constant);
    __GMSetLightf(GL_LINEAR_ATTENUATION, index, (GLfloat)linear);
    __GMSetLightf(GL_QUADRATIC_ATTENUATION, index, (GLfloat)quadratic);
}


#pragma mark -
#pragma mark <<<< テクスチャ関係 >>>>

void GMBasicEffect::enableTexture(bool flag)
{
    if ((mIsTextureEnabled && flag) || (!mIsTextureEnabled && !flag)) {
        return;
    }
    mIsTextureEnabled = flag;
    if (mIsTextureEnabled) {
        glEnable(GL_TEXTURE_2D);
    } else {
        glDisable(GL_TEXTURE_2D);
    }
}

GMTexture2D* GMBasicEffect::getTexture() const
{
    return mTexture;
}

bool GMBasicEffect::isTextureEnabled() const
{
    return mIsTextureEnabled;
}

void GMBasicEffect::setTexture(GMTexture2D* tex)
{
    mTexture = tex;
    if (mTexture != NULL) {
        glBindTexture(GL_TEXTURE_2D, mTexture->__getName());
    }
}


#pragma mark -
#pragma mark <<<< マテリアル関係 >>>>

GMVector3D GMBasicEffect::getMaterialDiffuse() const
{
    return mMaterial.diffuse;
}

GMVector3D GMBasicEffect::getMaterialSpecular() const
{
    return mMaterial.specular;
}

GMVector3D GMBasicEffect::getMaterialAmbient() const
{
    return mMaterial.ambient;
}

GMVector3D GMBasicEffect::getMaterialEmission() const
{
    return mMaterial.emission;
}

double GMBasicEffect::getMaterialShininess() const
{
    return mMaterial.shininess;
}

void GMBasicEffect::setMaterial(const GMVector3D& diffuse, const GMVector3D& specular, const GMVector3D& ambient, const GMVector3D& emission, const double shininess)
{
    mMaterial.diffuse = diffuse;
    mMaterial.specular = specular;
    mMaterial.ambient = ambient;
    mMaterial.emission = emission;
    mMaterial.shininess = shininess;
    
    mMaterial.set();
}


