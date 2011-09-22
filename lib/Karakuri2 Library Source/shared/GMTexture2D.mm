//
//  GMTexture2D.mm
//  Game Framework
//
//  Created by numata on Dec 26, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMTexture2D.h"
#include "GMGlobals.h"
#include "GMGraphics.h"
#include "GMException.h"

#include <TargetConditionals.h>


static GLuint __CreateGMTexture2D(int width, int height, GMTextureFormat format) throw(GMInvalidOperationException, GMOutOfMemoryException)
{
    GLuint ret = GL_INVALID_VALUE;
    
    // テクスチャの名前を作る
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &ret);
    
    // エラーチェック
    if (ret == GL_INVALID_OPERATION) {
        throw GMInvalidOperationException("Failed to creaete a texture (INVALID_OPERATION).");
    }
    else if (ret == GL_INVALID_VALUE) {
        throw GMException("Failed to creaete a texture (INVALID_VALUE).");
    }
    else if (ret == GL_INVALID_ENUM) {
        throw GMException("Failed to creaete a texture (INVALID_ENUM).");
    }

    // テクスチャ作成の実作業
    glBindTexture(GL_TEXTURE_2D, ret);

    GLint internalFormat;
    GLenum theFormat;
    GLenum type;
    if (format == GMTextureFormat_RGBA8) {
        internalFormat = GL_RGBA;
        theFormat = GL_RGBA;
        type = GL_UNSIGNED_BYTE;
    } else if (format == GMTextureFormat_A8) {
        internalFormat = GL_ALPHA;
        theFormat = GL_ALPHA;
        type = GL_UNSIGNED_BYTE;
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,
                 0,                 // MIPMAPレベル
                 internalFormat,    // テクスチャで使うコンポーネント数
                 (GLsizei)width, (GLsizei)height,   // テクスチャのサイズ
                 0,                 // ボーダー（0:境界線なし、1:境界線あり）
                 theFormat,         // ビットマップの色の並び順
                 type,              // 各コンポーネントのサイズ
                 0);

    return ret;
}

GMTexture2D::GMTexture2D(int width, int height) throw(GMInvalidOperationException, GMOutOfMemoryException)
{
    mTexName = __CreateGMTexture2D(width, height, GMTextureFormat_RGBA8);
    mImageSize = GMVector2D(width, height);
    mImageScale = GMVector2D::One;
}

GMTexture2D::GMTexture2D(int width, int height, GMTextureFormat format) throw(GMInvalidOperationException, GMOutOfMemoryException)
{
    mTexName = __CreateGMTexture2D(width, height, format);
    mImageSize = GMVector2D(width, height);
    mImageScale = GMVector2D::One;
}

GMTexture2D::GMTexture2D(const std::string& imageName, GMTexture2DScaleMode mode)
{
    GLushort resizedWidth;
    GLushort resizedHeight;
    mTexName = __GMTexture2DLoad(imageName, mode, &mImageSize, &resizedWidth, &resizedHeight);
    if (mTexName == GL_INVALID_VALUE) {
        throw GMException("Failed to load a texture file: \"%s\"", imageName.c_str());
    }
    mImageScale.x = mImageSize.x / (float)resizedWidth;
    mImageScale.y = mImageSize.y / (float)resizedHeight;
}

GMTexture2D::GMTexture2D(const std::string& str, const __GMFont* font)
{
    GLushort resizedWidth;
    GLushort resizedHeight;
    mTexName = __GMTexture2DCreateFromString(str, font->__getFontObject(), &mImageSize, &resizedWidth, &resizedHeight);
    if (mTexName == GL_INVALID_VALUE) {
        throw GMException("Failed to create a texture for a string: \"%s\"", str.c_str());
    }
    mImageScale.x = mImageSize.x / (float)resizedWidth;
    mImageScale.y = mImageSize.y / (float)resizedHeight;
}

GMTexture2D::~GMTexture2D()
{
    if (mTexName != GL_INVALID_VALUE) {
        glDeleteTextures(1, &mTexName);
        mTexName = GL_INVALID_VALUE;
    }
}

GMVector2D GMTexture2D::getSize() const
{
    return mImageSize;
}

GMVector2D GMTexture2D::getScale() const
{
    return mImageScale;
}

void GMTexture2D::setScale(const GMVector2D& scale)
{
    mImageScale = scale;
}

GLuint GMTexture2D::__getName() const
{
    return mTexName;
}



