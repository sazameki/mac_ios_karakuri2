//
//  GMRandom.cpp
//  Game Framework
//
//  Created by numata on Aug 05, 2009.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GMRandom.h"

#include <ctime>
#include <unistd.h>


static unsigned sGeneratedCount = 0;


static GMRandom*    sGMRandInst = NULL;


double GMRandom::NextDouble()
{
    return sGMRandInst->getNextDouble();
}

int GMRandom::NextInt()
{
    return sGMRandInst->getNextInt();
}

int GMRandom::NextInt(int upper)
{
    return sGMRandInst->getNextInt(upper);
}

unsigned GMRandom::GetFirstSeed()
{
    return sGMRandInst->getFirstSeed();
}

void GMRandom::SetFirstSeed(unsigned seed0)
{
    sGMRandInst->__setFirstSeed(seed0);
}



GMRandom::GMRandom()
{
    sGMRandInst = this;

    __resetSeed();
}

void GMRandom::__resetSeed()
{
    unsigned the_time = (unsigned)(time(NULL));
    unsigned pid = (unsigned)getpid();
    __setFirstSeed(the_time * pid);
}

void GMRandom::__setFirstSeed(unsigned seed0)
{
    firstSeed = seed0;
    unsigned seed = firstSeed;
    
    seed = 1812433253U * (seed ^ (seed >> 30)) + 1;
    x = seed;
    seed = 1812433253U * (seed ^ (seed >> 30)) + 2;
    y = seed;
    seed = 1812433253U * (seed ^ (seed >> 30)) + 3;
    z = seed;
    seed = 1812433253U * (seed ^ (seed >> 30)) + 4;
    w = seed;
}

unsigned GMRandom::getX() const
{
    return x;
}

unsigned GMRandom::getY() const
{
    return y;
}

unsigned GMRandom::getZ() const
{
    return z;
}

unsigned GMRandom::getW() const
{
    return w;
}

void GMRandom::setXYZW(unsigned _x, unsigned _y, unsigned _z, unsigned _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

unsigned GMRandom::xor128()
{
    sGeneratedCount++;

    unsigned t = (x ^ (x << 11));
    x = y;
    y = z;
    z = w;
    return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
}

int GMRandom::getNextInt()
{
    return (int)xor128();
}

int GMRandom::getNextInt(int upper)
{
    return (int)(xor128() % upper);
}

float GMRandom::getNextFloat()
{
    return ((float)xor128() / 0xffffffff);
}

double GMRandom::getNextDouble()
{
    return ((double)xor128() / 0xffffffff);
}

unsigned GMRandom::getFirstSeed() const
{
    return firstSeed;
}



