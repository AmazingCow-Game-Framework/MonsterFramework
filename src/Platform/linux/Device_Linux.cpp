//----------------------------------------------------------------------------//
//       █      █                                                             //
//       ████████                                                             //
//     ██        ██     File    : Device_Linux.cpp                            //
//    ███  █  █  ███    Project : GameMemory                                  //
//    █ █        █ █    Author  : N2OMatt                                     //
//     ████████████     Date    : Wed Sep 28 2016 17:13:41 2016 BRT           //
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

//Prevent the inclusion on NON LINUX builds.
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_LINUX )

//Usings
USING_NS_MF;

////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
cc::Size Device::getScreenSize()
{
    //COWTODO: NOT_IMPLEMENTED_YET
    return cc::Size(1024, 758);
}


#endif // ( CC_TARGET_PLATFORM == CC_PLATFORM_LINUX ) //
