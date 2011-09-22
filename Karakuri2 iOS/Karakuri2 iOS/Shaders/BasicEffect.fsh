//
//  BasicEffect.fsh
//  Karakuri2 iOS
//
//  Created by Satoshi Numata on 11/08/08.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
