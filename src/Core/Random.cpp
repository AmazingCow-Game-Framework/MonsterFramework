//----------------------------------------------------------------------------//
//                  _   _ ____   ___  ____                                    //
//                 | \ | |___ \ / _ \| __ )  ___  _   _ ____                  //
//                 |  \| | __) | | | |  _ \ / _ \| | | |_  /                  //
//                 | |\  |/ __/| |_| | |_) | (_) | |_| |/ /                   //
//                 |_| \_|_____|\___/|____/ \___/ \__, /___|                  //
//                                                |___/                       //
//                                                                            //
//                            Mateus Mesquita                                 //
//                       www.N2OBoyz.com/~n2omatt                             //
//                          N2OMatt@N2OBoyz.com                               //
//                                                                            //
//                   Copyright (C) 2015 Mateus Mesquita.                      //
//                       Copyright (C) 2015 N2OBoyz.                          //
//                                                                            //
//  This software is provided 'as-is', without any express or implied         //
//  warranty. In no event will the authors be held liable for any damages     //
//  arising from the use of this software.                                    //
//                                                                            //
//  Permission is granted to anyone to use this software for any purpose,     //
//  including commercial applications, and to alter it and redistribute it    //
//  freely, subject to the following restrictions:                            //
//                                                                            //
//  1. The origin of this software must not be misrepresented;                //
//     you must not claim that you wrote the original software.               //
//  2. If you use this software in a product, an acknowledgment in the        //
//     product IS HIGHLY APPRECIATED, both in source and binary forms.        //
//     If you will not acknowledge, just send me a email. We'll be VERY       //
//     happy to see our work being used by other people. :)                   //
//     (See opensource.N2OBoyz.com/acknowledgment.html for details).          //
//  3. Altered source versions must be plainly marked as such, and must not   //
//     be misrepresented as being the original software.                      //
//  4. This notice may not be removed or altered from any source              //
//     distribution.                                                          //
//  5. Most important, you must have fun. ;)                                  //
//                                                                            //
//       Visit OpenSource.N2OBoyz.com for more open-source projects.          //
//                                                                            //
//                            Enjoy :)                                        //
//----------------------------------------------------------------------------//

//Header
#include "MonsterFramework/include/Core/Random.h"
//std
#include <cstdlib>
#include <ctime>

USING_NS_STD_CC_CD_MF

// CTOR/DTOR //
Random::Random(int seed)
{
    setSeed(seed);
}

// Public Methods //
int Random::next()
{
    return next(0, RAND_MAX);
}
int Random::next(int max)
{
    return next(0, max);
}
int Random::next(int min, int max)
{    
    return min + arc4random() % (max - min);
}

float Random::nextFloat()
{
    return next(10000) / 10000.0;
}

int Random::getSeed() const
{
    return static_cast<int>(m_seed);
}
void Random::setSeed(int seed)
{
    m_seed            = seed;
    m_usingRandomSeed = false;
    
    if(m_seed == RANDOM_SEED)
    {
        m_seed = time(0);
        m_usingRandomSeed = true;
    }
    
//    srand(time(&m_seed));
}
bool Random::isUsingRandomSeed() const
{
    return m_usingRandomSeed;
}