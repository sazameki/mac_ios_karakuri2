//
//  GMTexture2DLoader.mm
//  Game Framework
//
//  Created by numata on Dec 31, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import "GMTexture2DLoader.h"


/*
    画像を元にしたテクスチャの作成
 */
GLuint __GMTexture2DLoad(const std::string& imageNameCpp, GMTexture2DScaleMode scaleMode, GMVector2D* imageSize, GLushort* resizedWidth, GLushort* resizedHeight)
{
    GLuint ret = GL_INVALID_VALUE;
    
    // 画像の名前→画像のパス
    NSString* imageName = [[[NSString alloc] initWithCString:imageNameCpp.c_str() encoding:NSUTF8StringEncoding] autorelease];
    NSBundle* bundle = [NSBundle mainBundle];
#if MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_6
    NSURL* imageURL = [bundle URLForImageResource:imageName];
#else
    NSString *imagePath = [bundle pathForImageResource:imageName];
    NSURL* imageURL = nil;
    if (imagePath) {
        imageURL = [NSURL fileURLWithPath:imagePath];
    }
#endif
    if (!imageURL) {
        return ret;
    }
    
    // 画像の読み込み
    CGImageSourceRef imageSourceRef = CGImageSourceCreateWithURL((CFURLRef)imageURL, NULL);
    CGImageRef imageRef = CGImageSourceCreateImageAtIndex(imageSourceRef, 0, NULL);
    if (imageRef == NULL) {
        return ret;
	}    
    
    // 画像サイズの取得と調整
    imageSize->x = (float)CGImageGetWidth(imageRef);
    imageSize->y = (float)CGImageGetHeight(imageRef);
    *resizedWidth = imageSize->x;
    *resizedHeight = imageSize->y;
    if ((*resizedWidth != 1) && (*resizedWidth & (*resizedWidth - 1))) {
		GLushort i = 1;
		while (i < *resizedWidth) {
            i *= 2;
        }
		*resizedWidth = i;
	}
    if ((*resizedHeight != 1) && (*resizedHeight & (*resizedHeight - 1))) {
		GLushort i = 1;
		while (i < *resizedHeight) {
            i *= 2;
        }
		*resizedHeight = i;
	}
    
    // ビットマップ（RGBAの並び）への変換
    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    NSMutableData* data = [NSMutableData dataWithLength:(4 * (int)(*resizedWidth) * (int)(*resizedHeight))];
    CGContextRef bitmapContextRef = CGBitmapContextCreate([data mutableBytes],
                                                          (size_t)(*resizedWidth),
                                                          (size_t)(*resizedHeight),
                                                          8,                        // Bits per component
                                                          (size_t)(*resizedWidth) * 4, // Bytes per Row
                                                          colorSpaceRef,
                                                          kCGImageAlphaPremultipliedLast);
    CGContextDrawImage(bitmapContextRef,
                       CGRectMake(0, 0, (int)imageSize->x, (int)imageSize->y),
                       imageRef);
    
    // アルファ値に対する調整（これがないと半透明部分が黒くなってしまう）
    unsigned char* p = (unsigned char*)[data mutableBytes];
    for (int i = 0; i < (*resizedWidth) * (*resizedHeight); i++) {
        float alpha = (float)*(p + 3) / 0xff;
        if (alpha > 0.0f && alpha < 1.0f) {
            *p = (unsigned char)((float)*p / alpha);
            p++;
            *p = (unsigned char)((float)*p / alpha);
            p++;
            *p = (unsigned char)((float)*p / alpha);
            p += 2;
        } else {
            p += 4;
        }
    }
    
    // テクスチャの名前を作る
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &ret);
    glBindTexture(GL_TEXTURE_2D, ret);
    
    // ビットマップを割り当てる
    glPixelStorei(GL_UNPACK_ROW_LENGTH, (GLint)(*resizedWidth));            // テクスチャ画像の横幅
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);                                  // テクスチャ画像はバイト単位で並んでいる
    
    if (scaleMode == GMTexture2DScaleModeLinear) {
        // 拡大・縮小時の線形補間の指定
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        // 拡大・縮小時のニアレストネイバー補間の指定
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);      
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    // クランプ処理の指定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    // 各行のピクセルデータの境界の種類
    // 1: バイト単位
    // 2: 偶数バイト単位
    // 4: WORD（2バイト）単位
    // 8: DWORD（4バイト）単位
    glTexImage2D(GL_TEXTURE_2D,
                 0,                             // MIPMAPのレベル
                 GL_RGBA,                       // テクスチャで使うカラーコンポーネント数
                 (GLsizei)(*resizedWidth),      // テクスチャ画像の横幅
                 (GLsizei)(*resizedHeight),     // テクスチャ画像の高さ
                 0,                             // ボーダー（0:境界線なし、1:境界線あり）
                 GL_RGBA,                       // ビットマップの色の並び順
                 GL_UNSIGNED_BYTE,
                 [data bytes]);
    
    ///// クリーンアップ
    CGContextRelease(bitmapContextRef);
    CGColorSpaceRelease(colorSpaceRef);
    CGImageRelease(imageRef);
    CFRelease(imageSourceRef);
    
    return ret;
}



/*
    フォントを元にしたテクスチャの作成
 */
GLuint __GMTexture2DCreateFromString(const std::string& str, void* nsFont, GMVector2D* imageSize, GLushort* resizedWidth, GLushort* resizedHeight)
{
    GLuint ret = GL_INVALID_VALUE;
    
    NSDictionary* attrDict = [[NSDictionary alloc] initWithObjectsAndKeys:
                              (NSFont*)nsFont, NSFontAttributeName,
                              [NSColor whiteColor], NSForegroundColorAttributeName,
                              nil];
    
    NSString* strStr = [[[NSString alloc] initWithCString:str.c_str() encoding:NSUTF8StringEncoding] autorelease];
    
    NSSize size;
    if ([strStr length] > 0) {
        size = [strStr sizeWithAttributes:attrDict];
    } else {
        size = NSMakeSize(1.0f, 1.0f);
    }
    
    NSSize revisedSize = size;
    int rwidth = revisedSize.width;
    if ((rwidth != 1) && (rwidth & (rwidth - 1))) {
        int i = 1;
        while (i < rwidth) {
            i *= 2;
        }
        rwidth = i;
    }
    
    int rheight = revisedSize.height;
    if ((rheight != 1) && (rheight & (rheight - 1))) {
        int i = 1;
        while (i < rheight) {
            i *= 2;
        }
        rheight = i;
    }
    
    revisedSize.width = (float)rwidth;
    revisedSize.height = (float)rheight;
    
    NSImage* image = [[NSImage alloc] initWithSize:revisedSize];
    [image lockFocus];
    if ([strStr length] > 0) {
        [strStr drawAtPoint:NSMakePoint(0, 0) withAttributes:attrDict];
    }
    
    NSBitmapImageRep* bitmap = [[NSBitmapImageRep alloc] initWithFocusedViewRect:NSMakeRect(0.0f, 0.0f, revisedSize.width, revisedSize.height)];
    [image unlockFocus];
    
	glEnable(GL_TEXTURE_2D);
    
    glPixelStorei(GL_UNPACK_ROW_LENGTH, revisedSize.width);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &ret);
    
    if (ret != GL_INVALID_VALUE && ret != GL_INVALID_OPERATION) {
        glBindTexture(GL_TEXTURE_2D, ret);
        
        unsigned* p = (unsigned*)[bitmap bitmapData];
        for (int i = 0; i < rwidth * rheight; i++) {
#ifdef __LITTLE_ENDIAN__
            p[i] |= 0x00ffffff;
#else
            p[i] |= 0xffffff00;
#endif
        }
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, revisedSize.width, revisedSize.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, [bitmap bitmapData]);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        ret = GL_INVALID_VALUE;
    }
    
	//glDisable(GL_TEXTURE_2D);
    
    //[[bitmap TIFFRepresentation] writeToFile:[@"~/Desktop/test.tiff" stringByExpandingTildeInPath] atomically:NO];
    
    [bitmap release];
	[image release];
    [attrDict release];

    imageSize->x = size.width;
    imageSize->y = size.height;
    *resizedWidth = (GLushort)revisedSize.width;
    *resizedHeight = (GLushort)revisedSize.height;

    return ret;
}




