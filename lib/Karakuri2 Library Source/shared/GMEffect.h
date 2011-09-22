//
//  GMEffect.h
//  Game Framework
//
//  Created by numata on Jan 11, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_EFFECT_H__
#define __GM_EFFECT_H__


#include "GMObject.h"
#include "GMGraphics.h"

#include <string>
#include <TargetConditionals.h>

// Special Basic
#if TARGET_OS_IPHONE
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#else
#include <OpenGL/glu.h>
#endif  //#if TARGET_OS_IPHONE


/*!
    @class      GMEffect
    @group      Graphics
    @abstract   シェーダとのやり取りを行うための基本クラスです。
 */
class GMEffect : public GMObject {

    std::string     mVertShaderName;
    std::string     mFragShaderName;
    GLuint          mProgram;

public:
    static GMEffect*    CurrentEffect;
    
public:
    GMEffect(const std::string& vertShaderName, const std::string& fragShaderName);
    virtual ~GMEffect();
    
public:
    /*!
        @task 描画の開始・終了処理
     */
    
    /*!
        @method     begin
        @abstract   描画を開始します。
     */
    virtual void    begin();

    /*!
        @method     end
        @abstract   描画を終了します。
     */
    virtual void    end();
    
protected:
    /*!
        @task オーバーライド・メソッド
     */
    /*!
        @method     bindAttribLocations
     */
    virtual void    bindAttribLocations();

    /*!
        @method     getUniformLocations
     */
    virtual void    getUniformLocations();

    /*!
        @task サブクラス内でのみ使用可能なメソッド
     */

    /*!
        @method     bindAttribLocation
     */
    void    bindAttribLocation(GLuint index, const GLchar* name);

    /*!
        @method     getUniformLocation
     */
    int     getUniformLocation(const GLchar* name);
    
private:
    bool    loadShaders();
    
};


#endif  //#ifndef __GM_EFFECT_H__


