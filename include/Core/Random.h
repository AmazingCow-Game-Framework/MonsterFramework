//COWTODO: We dont' need this class. cc::random is pretty good.

//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    Random.h                                    //
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

#ifndef __MonsterFramework_include_Core_Random_h__
#define __MonsterFramework_include_Core_Random_h__

//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"
//std
#include <random>

NS_MF_BEGIN
class Random
{
    // Enums/Constants/Typedefs //
public:
    typedef std::mt19937                       RandomEngineType;
    typedef std::uniform_int_distribution<int> DistributionType;

    static const int kRandomSeed = -1;

    // CTOR/DTOR //
public:
    Random(int seed = kRandomSeed);

    // Public Methods //
public:
    int next();
    int next(int max);
    int next(int min, int max);

    int  getSeed() const;
    void setSeed(int seed);

    bool isUsingRandomSeed() const;

    // Private Methods //
private:

    // iVars //
private:
    RandomEngineType              m_randomEngine;
    RandomEngineType::result_type m_seed;
    DistributionType              m_distribution;
    bool                          m_isUsingRandomSeed;

}; //class
NS_MF_END

#endif // defined(__MonsterFramework_include_Core_Random_h__) //
