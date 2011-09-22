//
//  GMLabel.cpp
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/29.
//  Copyright (c) 2011 Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMLabel.h"

#include "GMTexture2D.h"
#include <TargetConditionals.h>


__GMFont::__GMFont(const std::string& fontName, double fontSize)
{
    NSString* fontNameStr = [[NSString alloc] initWithCString:fontName.c_str() encoding:NSUTF8StringEncoding];

#if TARGET_OS_IPHONE
    mFontObj = [[UIFont fontWithName:fontNameStr size:(float)fontSize] retain];
#else
    mFontObj = [[NSFont fontWithName:fontNameStr size:(float)fontSize] retain];
#endif  //#if TARGET_OS_IPHONE
    
    [fontNameStr release];
}

__GMFont::~__GMFont()
{
#if TARGET_OS_IPHONE
    [(UIFont*)mFontObj release];
#else
    [(NSFont*)mFontObj release];
#endif  //#if TARGET_OS_IPHONE
}

GMTexture2D* __GMFont::createTextTexture(const std::string& str) const
{
    return new GMTexture2D(str, this);
}

void* __GMFont::__getFontObject() const
{
    return mFontObj;
}



GMLabel::GMLabel(const std::string& fontName, double fontSize)
    : mTex(NULL), mText("****")
{
    mFont = new __GMFont(fontName, fontSize);
    setText("## LABEL ##");
}

GMLabel::~GMLabel()
{
    if (mTex != NULL) {
        delete mTex;
        mTex = NULL;
    }
    delete mFont;
    mFont = NULL;
}

GMTexture2D* GMLabel::getTexture() const
{
    return mTex;
}

std::string GMLabel::getText() const
{
    return mText;
}

void GMLabel::setText(const std::string& str)
{
    if (mText == str) {
        return;
    }
    mText = str;

    if (mTex != NULL) {
        delete mTex;
    }
    mTex = mFont->createTextTexture(mText);
}


