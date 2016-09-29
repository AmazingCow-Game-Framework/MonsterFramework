//----------------------------------------------------------------------------//
//       █      █                                                             //
//       ████████                                                             //
//     ██        ██     File    : Device_Android.cpp                          //
//    ███  █  █  ███    Project : GameMemory                                  //
//    █ █        █ █    Author  : N2OMatt                                     //
//     ████████████     Date    : Wed Sep 28 2016 17:21:49 2016 BRT           //
//   █              █                                                         //
//  █     █    █     █  Copyright (c) 2016                                    //
//  █     █    █     █  AmazingCow - www.AmazingCow.com                       //
//   █              █                                                         //
//     ████████████     This File / Project is PROPRIETARY                    //
//                                                                            //
//                          Enjoy :)                                          //
//----------------------------------------------------------------------------//

//Header
#include "MonsterFramework/include/Platform/Device.h"

//Prevent the inclusion on NON ANDROID builds.
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )

//Usings
USING_NS_MF;

////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
cc::Size Device::getScreenSize()
{
    //COWTODO: NOT_IMPLEMENTED_YET
    return cc::Size(800, 480);
}


#endif // ( CC_TARGET_PLATFORM == CC_PLATFORM_LINUX ) //
