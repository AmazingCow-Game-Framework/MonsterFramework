//COWTODO: We dont' need this class. cc::random is pretty good.

//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    Random.cpp                                  //
//              █ █        █ █    MonsterFramework                            //
//               ████████████                                                 //
//             █              █   Copyright (c) 2015 AmazingCow               //
//            █     █    █     █  www.AmazingCow.com                          //
//            █     █    █     █                                              //
//             █              █   N2OMatt - n2omatt@amazingcow.com            //
//               ████████████     www.amazingcow.com/n2omatt                  //
//                                                                            //
//                                                                            //
//                  This software is licensed as BSD-3                        //
//                 CHECK THE COPYING FILE TO MORE DETAILS                     //
//                                                                            //
//    Permission is granted to anyone to use this software for any purpose,   //
//   including commercial applications, and to alter it and redistribute it   //
//               freely, subject to the following restrictions:               //
//                                                                            //
//     0. You **CANNOT** change the type of the license.                      //
//     1. The origin of this software must not be misrepresented;             //
//        you must not claim that you wrote the original software.            //
//     2. If you use this software in a product, an acknowledgment in the     //
//        product IS HIGHLY APPRECIATED, both in source and binary forms.     //
//        (See opensource.AmazingCow.com/acknowledgment.html for details).    //
//        If you will not acknowledge, just send us a email. We'll be         //
//        *VERY* happy to see our work being used by other people. :)         //
//        The email is: acknowledgmentopensource@AmazingCow.com               //
//     3. Altered source versions must be plainly marked as such,             //
//        and must notbe misrepresented as being the original software.       //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//      Visit opensource.amazingcow.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//
//Header
#include "MonsterFramework/include/Core/Random.h"
//std
#include <limits>

//Usings
USING_NS_STD_CC_CD_MF

// CTOR/DTOR //
Random::Random(int seed)
{
    setSeed(seed);
}

// Public Methods //
int Random::next()
{
    return next(std::numeric_limits<int>::max());
}
int Random::next(int max)
{
    MF_ASSERT((max > 0), "Random - max must be greater than 0");
    return next(0, max);
}
int Random::next(int min, int max)
{
    MF_ASSERT((min < max), "Random - max must be greater than min");
    return min + (m_distribution(m_randomEngine) % (max - min));
}

int Random::getSeed() const
{
    return m_seed;
}
void Random::setSeed(int seed)
{
    if(seed == Random::kRandomSeed)
    {
        m_isUsingRandomSeed = true;
        m_seed            = static_cast<RandomEngineType::result_type>(time(nullptr));
        m_randomEngine.seed(m_seed);
    }
}
bool Random::isUsingRandomSeed() const
{
    return m_isUsingRandomSeed;
}
