//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    MonsterFramework_Utils.h                    //
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

#ifndef __MonsterFramework_include_Utils_MonsterFramework_Utils_h__
#define __MonsterFramework_include_Utils_MonsterFramework_Utils_h__

#include "cocos2d.h"

////////////////////////////////////////////////////////////////////////////////
// MonsterFramework Includes                                                  //
////////////////////////////////////////////////////////////////////////////////
#include "./Macros/MonsterFramework_Assert.h"
#include "./Macros/MonsterFramework_CreateSceneInitFunc.h"
#include "./Macros/MonsterFramework_Disallow.h"
#include "./Macros/MonsterFramework_Log.h"
#include "./Macros/MonsterFramework_Macros.h"
#include "./Macros/MonsterFramework_Namespaces.h"


////////////////////////////////////////////////////////////////////////////////
// Uncategorized                                                              //
////////////////////////////////////////////////////////////////////////////////
NS_MF_BEGIN

//Taken from: https://herbsutter.com/gotw/_102/
//This enable us to use the Lore::make_unique in C++11
//If code is to be compiled in C++14 is better use the std version :D
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

NS_MF_END

#endif // defined(__MonsterFramework_include_Utils_MonsterFramework_Utils_h__) //
