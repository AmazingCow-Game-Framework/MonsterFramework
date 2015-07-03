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

#ifndef __DonkeyBas_iPhone_Base__Random__
#define __DonkeyBas_iPhone_Base__Random__

//std
#include <ctime>
//DonkeyBas
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"

NS_MF_BEGIN
class Random
{
    // Enums/Constants/Typedefs //
public:
    static const int RANDOM_SEED = -1;
    
    // CTOR/DTOR //
public:
    Random(int seed = RANDOM_SEED);
    
    // Public Methods //
public:
    int next();
    int next(int max);
    int next(int min, int max);
    
    float nextFloat();

    int getSeed() const;
    void setSeed(int seed);
    bool isUsingRandomSeed() const;
    
    // Private Methods //
private:
    
    // iVars //
private:
    std::time_t m_seed;
    bool m_usingRandomSeed;
    
}; //class
NS_MF_END

#endif /* defined(__DonkeyBas_iPhone_Base__Random__) */
