//
//  GameMain.h
//  Game Framework
//
//  Created by numata on Dec 27, 2010.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GAMEMAIN_H__
#define __GAMEMAIN_H__


#include "Karakuri.h"
#include "Globals.h"


// このクラスのインスタンスには、gGameInst 変数でアクセスできます。

class GameMain : public GMGame {

public:
    GameMain();
    virtual ~GameMain();

};


extern GameMain *gGameInst;


#endif  //#ifndef __GAMEMAIN_H__

