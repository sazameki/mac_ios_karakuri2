//
//  GMEffect.mm
//  Game Framework
//
//  Created by numata on Jan 11, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMEffect.h"
#include "GMGraphics.h"

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#endif  //#if TARGET_OS_IPHONE
#include <iostream>


GMEffect* GMEffect::CurrentEffect = NULL;


GMEffect::GMEffect(const std::string& vertShaderName, const std::string& fragShaderName)
    : mVertShaderName(vertShaderName), mFragShaderName(fragShaderName), mProgram(0)
{
    if (GMGraphics::Graphics1->isShaderEnabled()) {
        if (!loadShaders()) {
            std::cerr << "Failed to load shaders!! (\"" << vertShaderName << "\", \"" << fragShaderName << "\")" << std::endl;
        } else {
            std::cerr << "Successfully loaded shaders!! (\"" << vertShaderName << "\", \"" << fragShaderName << "\")" << std::endl;
        }
    }
}

GMEffect::~GMEffect()
{
    if (mProgram != 0) {
        glDeleteProgram(mProgram);
        mProgram = 0;
    }
}

void GMEffect::begin()
{
    CurrentEffect = this;
    if (GMGraphics::Graphics1->isShaderEnabled()) {
        glUseProgram(mProgram);
    }
}

void GMEffect::end()
{
    CurrentEffect = NULL;
}

static bool __GMCompileShader(GLuint* shader,  GLenum type, NSString* file)
{
    GLint status;
    const GLchar *source;
    
    source = (GLchar *)[[NSString stringWithContentsOfFile:file encoding:NSUTF8StringEncoding error:nil] UTF8String];
    if (!source) {
        return false;
    }
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
#if defined(DEBUG)
    GLint logLength;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);
        NSLog(@"Shader compile log:\n%s", log);
        free(log);
    }
#endif
    
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        glDeleteShader(*shader);
        return false;
    }
    
    return true;
}

static bool __GMValidateProgram(GLuint prog)
{
    GLint logLength, status;
    
    glValidateProgram(prog);
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        NSLog(@"Program validate log:\n%s", log);
        free(log);
    }
    
    glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
    if (status == 0) {
        return false;
    }
    
    return true;
}

static bool __GMLinkProgram(GLuint prog)
{
    GLint status;
    
    glLinkProgram(prog);
    
#if defined(DEBUG)
    GLint logLength;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        NSLog(@"Program link log:\n%s", log);
        free(log);
    }
#endif
    
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status == 0) {
        return false;
    }
    return true;
}

bool GMEffect::loadShaders()
{
    GLuint vertShader, fragShader;
    
    NSString* vertNameStr = [[[NSString alloc] initWithCString:mVertShaderName.c_str() encoding:NSUTF8StringEncoding] autorelease];
    NSString* fragNameStr = [[[NSString alloc] initWithCString:mFragShaderName.c_str() encoding:NSUTF8StringEncoding] autorelease];
    
    // Create shader program.
    mProgram = glCreateProgram();
    
    // Create and compile vertex shader.
    NSString* vertShaderPathname = [[NSBundle mainBundle] pathForResource:[vertNameStr stringByDeletingPathExtension] ofType:[vertNameStr pathExtension]];
    if (!__GMCompileShader(&vertShader, GL_VERTEX_SHADER, vertShaderPathname)) {
        NSLog(@"Failed to compile vertex shader");
        return false;
    }
    
    // Create and compile fragment shader.
    NSString* fragShaderPathname = [[NSBundle mainBundle] pathForResource:[fragNameStr stringByDeletingPathExtension] ofType:[fragNameStr pathExtension]];
    if (!__GMCompileShader(&fragShader, GL_FRAGMENT_SHADER, fragShaderPathname)) {
        NSLog(@"Failed to compile fragment shader");
        return false;
    }
    
    // Attach vertex and fragment shaders to a program.
    glAttachShader(mProgram, vertShader);
    glAttachShader(mProgram, fragShader);
    
    // Bind attribute locations. This needs to be done prior to linking.
    bindAttribLocations();
    
    // Link program.
    if (!__GMLinkProgram(mProgram)) {
        NSLog(@"Failed to link program: %d", mProgram);
        
        if (vertShader) {
            glDeleteShader(vertShader);
            vertShader = 0;
        }
        if (fragShader) {
            glDeleteShader(fragShader);
            fragShader = 0;
        }
        if (mProgram) {
            glDeleteProgram(mProgram);
            mProgram = 0;
        }
        
        return FALSE;
    }
    
    // Get uniform locations.
    getUniformLocations();
    
    // Release vertex and fragment shaders.
    if (vertShader) {
        glDeleteShader(vertShader);
    }
    if (fragShader) {
        glDeleteShader(fragShader);
    }
    
    return true;
}

void GMEffect::bindAttribLocations()
{
    // Do nothing
}

void GMEffect::getUniformLocations()
{
    // Do nothing
}

void GMEffect::bindAttribLocation(GLuint index, const GLchar* name)
{
    glBindAttribLocation(mProgram, index, name);
}

int GMEffect::getUniformLocation(const GLchar* name)
{
    return glGetUniformLocation(mProgram, name);
}


