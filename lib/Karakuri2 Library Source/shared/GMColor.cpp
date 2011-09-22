//
//  GMColor.cpp
//  Game Framework
//
//  Created by numata on Dec 26, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import "GMColor.h"
#import "GMTypes.h"

#include <cmath>


// Color A-
const GMColor& GMColor::AliceBlue       = GMColor(240/255.0, 248/255.0, 255/255.0, 1.0);
const GMColor& GMColor::AntiqueWhite    = GMColor(250/255.0, 235/255.0, 215/255.0, 1.0);
const GMColor& GMColor::Aqua            = GMColor(  0/255.0, 255/255.0, 255/255.0, 1.0);
const GMColor& GMColor::Aquamarine      = GMColor(127/255.0, 255/255.0, 212/255.0, 1.0);
const GMColor& GMColor::Azure           = GMColor(240/255.0, 255/255.0, 255/255.0, 1.0);

// Color B-
const GMColor& GMColor::Beige           = GMColor(245/255.0, 245/255.0, 220/255.0, 1.0);
const GMColor& GMColor::Bisque          = GMColor(255/255.0, 228/255.0, 196/255.0, 1.0);
const GMColor& GMColor::Black           = GMColor(  0/255.0,   0/255.0,   0/255.0, 1.0);
const GMColor& GMColor::BlanchedAlmond  = GMColor(255/255.0, 235/255.0, 205/255.0, 1.0);
const GMColor& GMColor::Blue            = GMColor(  0/255.0,   0/255.0, 255/255.0, 1.0);
const GMColor& GMColor::BlueViolet      = GMColor(138/255.0,  43/255.0, 226/255.0, 1.0);
const GMColor& GMColor::Brown           = GMColor(165/255.0,  42/255.0,  42/255.0, 1.0);
const GMColor& GMColor::BurlyWood       = GMColor(222/255.0, 184/255.0, 135/255.0, 1.0);

// Color C-
const GMColor& GMColor::CadetBlue       = GMColor( 95/255.0, 158/255.0, 160/255.0, 1.0);
const GMColor& GMColor::Chartreuse      = GMColor(127/255.0, 255/255.0,   0/255.0, 1.0);
const GMColor& GMColor::Chocolate       = GMColor(210/255.0, 105/255.0,  30/255.0, 1.0);
const GMColor& GMColor::Coral           = GMColor(255/255.0, 127/255.0,  80/255.0, 1.0);
const GMColor& GMColor::CornflowerBlue  = GMColor(100/255.0, 149/255.0, 237/255.0, 1.0);
const GMColor& GMColor::Cornsilk        = GMColor(255/255.0, 248/255.0, 220/255.0, 1.0);
const GMColor& GMColor::Crimson         = GMColor(220/255.0, 20/255.0,   60/255.0, 1.0);
const GMColor& GMColor::Cyan            = GMColor(  0/255.0, 255/255.0, 255/255.0, 1.0);

// Color D-
const GMColor& GMColor::DarkBlue        = GMColor(  0/255.0,   0/255.0, 139/255.0, 1.0);
const GMColor& GMColor::DarkCyan        = GMColor(  0/255.0, 139/255.0, 139/255.0, 1.0);
const GMColor& GMColor::DarkGoldenrod   = GMColor(184/255.0, 134/255.0,  11/255.0, 1.0);
const GMColor& GMColor::DarkGray        = GMColor(169/255.0, 169/255.0, 169/255.0, 1.0);
const GMColor& GMColor::DarkGreen       = GMColor(  0/255.0, 100/255.0,   0/255.0, 1.0);
const GMColor& GMColor::DarkKhaki       = GMColor(189/255.0, 183/255.0, 107/255.0, 1.0);
const GMColor& GMColor::DarkMagenta     = GMColor(139/255.0,   0/255.0, 139/255.0, 1.0);
const GMColor& GMColor::DarkOliveGreen  = GMColor( 85/255.0, 107/255.0,  47/255.0, 1.0);
const GMColor& GMColor::DarkOrange      = GMColor(255/255.0, 140/255.0,   0/255.0, 1.0);
const GMColor& GMColor::DarkOrchid      = GMColor(153/255.0,  50/255.0, 204/255.0, 1.0);
const GMColor& GMColor::DarkRed         = GMColor(139/255.0,   0/255.0,   0/255.0, 1.0);
const GMColor& GMColor::DarkSalmon      = GMColor(233/255.0, 150/255.0, 122/255.0, 1.0);
const GMColor& GMColor::DarkSeaGreen    = GMColor(143/255.0, 188/255.0, 139/255.0, 1.0);
const GMColor& GMColor::DarkSlateBlue   = GMColor( 72/255.0,  61/255.0, 139/255.0, 1.0);
const GMColor& GMColor::DarkSlateGray   = GMColor( 47/255.0,  79/255.0,  79/255.0, 1.0);
const GMColor& GMColor::DarkTurquoise   = GMColor(  0/255.0, 206/255.0, 209/255.0, 1.0);
const GMColor& GMColor::DarkViolet      = GMColor(148/255.0,   0/255.0, 211/255.0, 1.0);
const GMColor& GMColor::DeepPink        = GMColor(255/255.0,  20/255.0, 147/255.0, 1.0);
const GMColor& GMColor::DeepSkyBlue     = GMColor(  0/255.0, 191/255.0, 255/255.0, 1.0);
const GMColor& GMColor::DimGray         = GMColor(105/255.0, 105/255.0, 105/255.0, 1.0);
const GMColor& GMColor::DodgerBlue      = GMColor( 30/255.0, 144/255.0, 255/255.0, 1.0);

// Color F-
const GMColor& GMColor::Firebrick       = GMColor(178/255.0,  34/255.0,  34/255.0, 1.0);
const GMColor& GMColor::FloralWhite     = GMColor(255/255.0, 250/255.0, 240/255.0, 1.0);
const GMColor& GMColor::ForestGreen     = GMColor( 34/255.0, 139/255.0,  34/255.0, 1.0);
const GMColor& GMColor::Fuchsia         = GMColor(255/255.0,   0/255.0, 255/255.0, 1.0);

// Color G-
const GMColor& GMColor::Gainsboro       = GMColor(220/255.0, 220/255.0, 220/255.0, 1.0);
const GMColor& GMColor::GhostWhite      = GMColor(248/255.0, 248/255.0, 255/255.0, 1.0);
const GMColor& GMColor::Gold            = GMColor(255/255.0, 215/255.0,   0/255.0, 1.0);
const GMColor& GMColor::Goldenrod       = GMColor(218/255.0, 165/255.0,  32/255.0, 1.0);
const GMColor& GMColor::Gray            = GMColor(128/255.0, 128/255.0, 128/255.0, 1.0);
const GMColor& GMColor::Green           = GMColor(  0/255.0, 128/255.0,   0/255.0, 1.0);
const GMColor& GMColor::GreenYellow     = GMColor(173/255.0, 255/255.0,  47/255.0, 1.0);

// Color H-
const GMColor& GMColor::Honeydew        = GMColor(240/255.0, 255/255.0, 240/255.0, 1.0);
const GMColor& GMColor::HotPink         = GMColor(255/255.0, 105/255.0, 180/255.0, 1.0);

// Color I-
const GMColor& GMColor::IndianRed       = GMColor(205/255.0,  92/255.0,  92/255.0, 1.0);
const GMColor& GMColor::Indigo          = GMColor( 75/255.0,   0/255.0, 130/255.0, 1.0);
const GMColor& GMColor::Ivory           = GMColor(255/255.0, 255/255.0, 240/255.0, 1.0);

// Color K-
const GMColor& GMColor::Khaki           = GMColor(240/255.0, 230/255.0, 140/255.0, 1.0);

// Color L-
const GMColor& GMColor::Lavender                = GMColor(230/255.0, 230/255.0, 250/255.0, 1.0);
const GMColor& GMColor::LavenderBlush           = GMColor(255/255.0, 240/255.0, 245/255.0, 1.0);
const GMColor& GMColor::LawnGreen               = GMColor(124/255.0, 252/255.0,   0/255.0, 1.0);
const GMColor& GMColor::LemonChiffon            = GMColor(255/255.0, 250/255.0, 205/255.0, 1.0);
const GMColor& GMColor::LightBlue               = GMColor(173/255.0, 216/255.0, 230/255.0, 1.0);
const GMColor& GMColor::LightCoral              = GMColor(240/255.0, 128/255.0, 128/255.0, 1.0);
const GMColor& GMColor::LightCyan               = GMColor(224/255.0, 255/255.0, 255/255.0, 1.0);
const GMColor& GMColor::LightGoldenrodYellow    = GMColor(250/255.0, 250/255.0, 210/255.0, 1.0);
const GMColor& GMColor::LightGray               = GMColor(211/255.0, 211/255.0, 211/255.0, 1.0);
const GMColor& GMColor::LightGreen              = GMColor(144/255.0, 238/255.0, 144/255.0, 1.0);
const GMColor& GMColor::LightPink               = GMColor(255/255.0, 182/255.0, 193/255.0, 1.0);
const GMColor& GMColor::LightSalmon             = GMColor(255/255.0, 160/255.0, 122/255.0, 1.0);
const GMColor& GMColor::LightSeaGreen           = GMColor( 32/255.0, 178/255.0, 170/255.0, 1.0);
const GMColor& GMColor::LightSkyBlue	        = GMColor(135/255.0, 206/255.0, 250/255.0, 1.0);
const GMColor& GMColor::LightSlateGray	        = GMColor(119/255.0, 136/255.0, 153/255.0, 1.0);
const GMColor& GMColor::LightSteelBlue          = GMColor(176/255.0, 196/255.0, 222/255.0, 1.0);
const GMColor& GMColor::LightYellow             = GMColor(255/255.0, 255/255.0, 224/255.0, 1.0);
const GMColor& GMColor::Lime                    = GMColor(  0/255.0, 255/255.0,   0/255.0, 1.0);
const GMColor& GMColor::LimeGreen               = GMColor( 50/255.0, 205/255.0,  50/255.0, 1.0);
const GMColor& GMColor::Linen                   = GMColor(250/255.0, 240/255.0, 230/255.0, 1.0);

// Color M-
const GMColor& GMColor::Magenta                 = GMColor(255/255.0,   0/255.0, 255/255.0, 1.0);
const GMColor& GMColor::Maroon                  = GMColor(128/255.0,   0/255.0,   0/255.0, 1.0);
const GMColor& GMColor::MediumAquamarine        = GMColor(102/255.0, 205/255.0, 170/255.0, 1.0);
const GMColor& GMColor::MediumBlue              = GMColor(  0/255.0,   0/255.0, 205/255.0, 1.0);
const GMColor& GMColor::MediumOrchid            = GMColor(186/255.0,  85/255.0, 211/255.0, 1.0);
const GMColor& GMColor::MediumPurple            = GMColor(147/255.0, 112/255.0, 219/255.0, 1.0);
const GMColor& GMColor::MediumSeaGreen          = GMColor( 60/255.0, 179/255.0, 113/255.0, 1.0);
const GMColor& GMColor::MediumSlateBlue         = GMColor(123/255.0, 104/255.0, 238/255.0, 1.0);
const GMColor& GMColor::MediumSpringGreen       = GMColor(  0/255.0, 250/255.0, 154/255.0, 1.0);
const GMColor& GMColor::MediumTurquoise         = GMColor( 72/255.0, 209/255.0, 204/255.0, 1.0);
const GMColor& GMColor::MediumVioletRed         = GMColor(199/255.0,  21/255.0, 133/255.0, 1.0);
const GMColor& GMColor::MidnightBlue            = GMColor( 25/255.0,  25/255.0, 112/255.0, 1.0);
const GMColor& GMColor::MintCream               = GMColor(245/255.0, 255/255.0, 250/255.0, 1.0);
const GMColor& GMColor::MistyRose               = GMColor(255/255.0, 228/255.0, 225/255.0, 1.0);
const GMColor& GMColor::Moccasin                = GMColor(255/255.0, 228/255.0, 181/255.0, 1.0);
const GMColor& GMColor::NavajoWhite             = GMColor(255/255.0, 222/255.0, 173/255.0, 1.0);
const GMColor& GMColor::Navy                    = GMColor(  0/255.0,   0/255.0, 128/255.0, 1.0);

// Color O-
const GMColor& GMColor::OldLace         = GMColor(253/255.0, 245/255.0, 230/255.0, 1.0);
const GMColor& GMColor::Olive           = GMColor(128/255.0, 128/255.0,   0/255.0, 1.0);
const GMColor& GMColor::OliveDrab       = GMColor(107/255.0, 142/255.0,  35/255.0, 1.0);
const GMColor& GMColor::Orange          = GMColor(255/255.0, 165/255.0,   0/255.0, 1.0);
const GMColor& GMColor::OrangeRed       = GMColor(255/255.0,  69/255.0,   0/255.0, 1.0);
const GMColor& GMColor::Orchid          = GMColor(218/255.0, 112/255.0, 214/255.0, 1.0);

// Color P-
const GMColor& GMColor::PaleGoldenrod   = GMColor(238/255.0, 232/255.0, 170/255.0, 1.0);
const GMColor& GMColor::PaleGreen       = GMColor(152/255.0, 251/255.0, 152/255.0, 1.0);
const GMColor& GMColor::PaleTurquoise   = GMColor(175/255.0, 238/255.0, 238/255.0, 1.0);
const GMColor& GMColor::PaleVioletRed   = GMColor(219/255.0, 112/255.0, 147/255.0, 1.0);
const GMColor& GMColor::PapayaWhip      = GMColor(255/255.0, 239/255.0, 213/255.0, 1.0);
const GMColor& GMColor::PeachPuff       = GMColor(255/255.0, 218/255.0, 185/255.0, 1.0);
const GMColor& GMColor::Peru            = GMColor(205/255.0, 133/255.0,  63/255.0, 1.0);
const GMColor& GMColor::Pink            = GMColor(255/255.0, 192/255.0, 203/255.0, 1.0);
const GMColor& GMColor::Plum            = GMColor(221/255.0, 160/255.0, 221/255.0, 1.0);
const GMColor& GMColor::PowderBlue      = GMColor(176/255.0, 224/255.0, 230/255.0, 1.0);
const GMColor& GMColor::Purple          = GMColor(128/255.0,   0/255.0, 128/255.0, 1.0);

// Color R-
const GMColor& GMColor::Red             = GMColor(255/255.0,   0/255.0,   0/255.0, 1.0);
const GMColor& GMColor::RosyBrown       = GMColor(188/255.0, 143/255.0, 143/255.0, 1.0);
const GMColor& GMColor::RoyalBlue       = GMColor( 65/255.0, 105/255.0, 225/255.0, 1.0);

// Color S-
const GMColor& GMColor::SaddleBrown     = GMColor(139/255.0,  69/255.0,  19/255.0, 1.0);
const GMColor& GMColor::Salmon          = GMColor(250/255.0, 128/255.0, 114/255.0, 1.0);
const GMColor& GMColor::SandyBrown      = GMColor(244/255.0, 164/255.0,  96/255.0, 1.0);
const GMColor& GMColor::SeaGreen        = GMColor( 46/255.0, 139/255.0,  87/255.0, 1.0);
const GMColor& GMColor::SeaShell        = GMColor(255/255.0, 245/255.0, 238/255.0, 1.0);
const GMColor& GMColor::Sienna	        = GMColor(160/255.0,  82/255.0,  45/255.0, 1.0);
const GMColor& GMColor::Silver	        = GMColor(192/255.0, 192/255.0, 192/255.0, 1.0);
const GMColor& GMColor::SkyBlue	        = GMColor(135/255.0, 206/255.0, 235/255.0, 1.0);
const GMColor& GMColor::SlateBlue       = GMColor(106/255.0,  90/255.0, 205/255.0, 1.0);
const GMColor& GMColor::SlateGray       = GMColor(112/255.0, 128/255.0, 144/255.0, 1.0);
const GMColor& GMColor::Snow	        = GMColor(255/255.0, 250/255.0, 250/255.0, 1.0);
const GMColor& GMColor::SpringGreen     = GMColor(  0/255.0, 255/255.0, 127/255.0, 1.0);
const GMColor& GMColor::SteelBlue       = GMColor( 70/255.0, 130/255.0, 180/255.0, 1.0);

// Color T-
const GMColor& GMColor::Tan                 = GMColor(210/255.0, 180/255.0, 140/255.0, 1.0);
const GMColor& GMColor::Teal                = GMColor(  0/255.0, 128/255.0, 128/255.0, 1.0);
const GMColor& GMColor::Thistle             = GMColor(216/255.0, 191/255.0, 216/255.0, 1.0);
const GMColor& GMColor::Tomato              = GMColor(255/255.0,  99/255.0,  71/255.0, 1.0);
const GMColor& GMColor::TransparentBlack    = GMColor(  0/255.0,   0/255.0,   0/255.0, 0.0);
const GMColor& GMColor::TransparentWhite    = GMColor(255/255.0, 255/255.0, 255/255.0, 0.0);
const GMColor& GMColor::Turquoise           = GMColor( 64/255.0, 224/255.0, 208/255.0, 1.0);

// Color V-
const GMColor& GMColor::Violet          = GMColor(238/255.0, 130/255.0, 238/255.0, 1.0);

// Color W-
const GMColor& GMColor::Wheat           = GMColor(245/255.0, 222/255.0, 179/255.0, 1.0);
const GMColor& GMColor::White           = GMColor(255/255.0, 255/255.0, 255/255.0, 1.0);
const GMColor& GMColor::WhiteSmoke      = GMColor(245/255.0, 245/255.0, 245/255.0, 1.0);

// Color Y-
const GMColor& GMColor::Yellow          = GMColor(255/255.0, 255/255.0,   0/255.0, 1.0);
const GMColor& GMColor::YellowGreen     = GMColor(154/255.0, 205/255.0,  50/255.0, 1.0);


GMColor GMColor::EaseIn(const GMColor& c1, const GMColor& c2, double t)
{
    if (t < 0.0) {
        t = 0.0;
    } else if (t > 1.0) {
        t = 1.0;
    }

    t *= t;
    
    return GMColor(c1.r + (c2.r - c1.r) * t,
                   c1.g + (c2.g - c1.g) * t,
                   c1.b + (c2.b - c1.b) * t,
                   c1.a + (c2.a - c1.a) * t);
}

GMColor GMColor::EaseInOut(const GMColor& c1, const GMColor& c2, double t)
{
    if (t < 0.0) {
        t = 0.0;
    } else if (t > 1.0) {
        t = 1.0;
    }
    
    double rm = (c1.r + c2.r) / 2;
    double gm = (c1.g + c2.g) / 2;
    double bm = (c1.b + c2.b) / 2;
    double am = (c1.a + c2.a) / 2;

    t *= 2;
    if (t <= 1.0) {
        t *= t;
        return GMColor(c1.r + (rm - c1.r) * t,
                       c1.g + (gm - c1.g) * t,
                       c1.b + (bm - c1.b) * t,
                       c1.a + (am - c1.a) * t);
    }

    t -= 1;
    t *= t;
    
    return GMColor(rm + (c2.r - rm) * t,
                   gm + (c2.g - gm) * t,
                   bm + (c2.b - bm) * t,
                   am + (c2.a - am) * t);
}

GMColor GMColor::EaseOut(const GMColor& c1, const GMColor& c2, double t)
{
    if (t < 0.0) {
        t = 0.0;
    } else if (t > 1.0) {
        t = 1.0;
    }
    
    t *= (t - 2);
    
    return GMColor(c1.r - (c2.r - c1.r) * t,
                   c1.g - (c2.g - c1.g) * t,
                   c1.b - (c2.b - c1.b) * t,
                   c1.a - (c2.a - c1.a) * t);
}

GMColor GMColor::Lerp(const GMColor& c1, const GMColor& c2, double t)
{
    if (t < 0.0) {
        t = 0.0;
    } else if (t > 1.0) {
        t = 1.0;
    }
    
    return GMColor(c1.r + (c2.r - c1.r) * t,
                   c1.g + (c2.g - c1.g) * t,
                   c1.b + (c2.b - c1.b) * t,
                   c1.a + (c2.a - c1.a) * t);
}

GMColor::GMColor()
    : r(1.0), g(1.0), b(1.0), a(1.0)
{
    // Do nothing
}

GMColor::GMColor(double r_, double g_, double b_, double a_)
    : r(r_), g(g_), b(b_), a(a_)
{
    // Do nothing
}

GMColor::GMColor(const GMColor& color)
    : r(color.r), g(color.g), b(color.b), a(color.a)
{
    // Do nothing
}

GMColor::GMColor(const GMVector3D& vector)
    : a(1.0)
{
    double red = vector.x;
    if (red < 0.0) {
        red = 0.0;
    } else if (red > 1.0) {
        red = 1.0;
    }
    r = red;
    
    double green = vector.y;
    if (green < 0.0) {
        green = 0.0;
    } else if (green > 1.0) {
        green = 1.0;
    }
    g = green;
    
    double blue = vector.z;
    if (blue < 0.0) {
        blue = 0.0;
    } else if (blue > 1.0) {
        blue = 1.0;
    }
    b = blue;
}

GMColor::GMColor(const GMVector4D& vector)
{
    double red = vector.x;
    if (red < 0.0) {
        red = 0.0;
    } else if (red > 1.0) {
        red = 1.0;
    }
    r = red;
    
    double green = vector.y;
    if (green < 0.0) {
        green = 0.0;
    } else if (green > 1.0) {
        green = 1.0;
    }
    g = green;
    
    double blue = vector.z;
    if (blue < 0.0) {
        blue = 0.0;
    } else if (blue > 1.0) {
        blue = 1.0;
    }
    b = blue;
    
    double alpha = vector.w;
    if (alpha < 0.0) {
        alpha = 0.0;
    } else if (alpha > 1.0) {
        alpha = 1.0;
    }
    a = alpha;
}

GMColor& GMColor::operator=(const GMColor& color)
{
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
    return *this;
}

bool GMColor::operator==(const GMColor& color) const
{
    return equals(color, GMMathHelper::DoubleEqThreshold);
}

bool GMColor::operator!=(const GMColor& color) const
{
    return !equals(color, GMMathHelper::DoubleEqThreshold);
}

bool GMColor::equals(const GMColor& color, double accuracy) const
{
    return (fabs(r - color.r) < accuracy &&
            fabs(g - color.g) < accuracy &&
            fabs(b - color.b) < accuracy &&
            fabs(a - color.a) < accuracy)? true: false;
}

GMVector3D GMColor::toVector3D() const
{
    return GMVector3D(r, g, b);
}

GMVector4D GMColor::toVector4D() const
{
    return GMVector4D(r, g, b, a);
}




