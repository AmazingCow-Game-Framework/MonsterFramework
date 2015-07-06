//----------------------------------------------------------------------------//
//                   _   _ ____   ___  ____                                   //
//                  | \ | |___ \ / _ \| __ )  ___  _   _ ____                 //
//                  |  \| | __) | | | |  _ \ / _ \| | | |_  /                 //
//                  | |\  |/ __/| |_| | |_) | (_) | |_| |/ /                  //
//                  |_| \_|_____|\___/|____/ \___/ \__, /___|                 //
//                                                 |___/                      //
//                                                                            //
//                                   N2OMatt                                  //
//                             N2OMatt@N2OBoyz.com                            //
//                           www.N2OBoyz.com/N2OMatt                          //
//                                                                            //
//                         Copyright (C) 2015 N2OBoyz.                        //
//                                                                            //
//      This software is provided 'as-is', without any express or implied     //
//    warranty. In no event will the authors be held liable for any damages   //
//                   arising from the use of this software.                   //
//                                                                            //
//    Permission is granted to anyone to use this software for any purpose,   //
//   including commercial applications, and to alter it and redistribute it   //
//               freely, subject to the following restrictions:               //
//                                                                            //
//     1. The origin of this software must not be misrepresented;             //
//        you must not claim that you wrote the original software.            //
//     2. If you use this software in a product, an acknowledgment in the     //
//        product IS HIGHLY APPRECIATED, both in source and binary forms.     //
//        (See opensource.N2OBoyz.com/acknowledgment.html for details).       //
//        If you will not acknowledge, just send us a email. We'll be         //
//        *VERY* happy to see our work being used by other people. :)         //
//        The email is: acknowledgment.opensource@N2OBoyz.com                 //
//     3. Altered source versions must be plainly marked as such,             //
//        and must notbe misrepresented as being the original software.       //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//         Visit OpenSource.N2OBoyz.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//

#include "CCBNodeLoader_Decoders.h"

USING_NS_STD_CC_CD_MF

//Decoders.
cc::Point mf::_decodeAsPoint(const cc::Value &value)
{
    return cc::Point(value.asValueVector().at(0).asFloat(),
                     value.asValueVector().at(1).asFloat());
}
bool mf::_decodeAsCheck(const cc::Value &value)
{
    return value.asBool();
}
cc::Point mf::_decodeAsPosition(const cc::Value &value, cc::Node *parent)
{
    auto x = value.asValueVector().at(0).asFloat();
    auto y = value.asValueVector().at(1).asFloat();
    auto t = value.asValueVector().at(2).asInt();

    auto fx = x;
    auto fy = y;

    if(t == 4)
    {
        fx *= (parent->getContentSize().width  / 200.f);
        fy *= (parent->getContentSize().height / 200.f);
    }

    return cc::Point(fx, fy);
}
std::string mf::_decodeAsSpriteFrame(const cc::Value &value)
{
    return value.asValueVector().at(1).asString();
}
std::string mf::_decodeAsBlock(const cc::Value &value)
{
    return value.asValueVector().at(0).asString();
}
cc::Color3B mf::_decodeAsColor3(const cc::Value &value)
{
    auto color = cc::Color3B(value.asValueVector().at(0).asInt(),
                             value.asValueVector().at(1).asInt(),
                             value.asValueVector().at(2).asInt());
    return color;
}
cc::Size mf::_decodeAsSize(const cc::Value &value)
{
    return cc::Size(value.asValueVector().at(0).asFloat(),
                    value.asValueVector().at(1).asFloat());
}
float mf::_decodeAsDegrees(const cc::Value &value)
{
    return value.asFloat();
}
float mf::_decodeAsFontScale(const cc::Value &value)
{
    return value.asValueVector().at(0).asFloat();
}
std::string mf::_decodeAsString(const cc::Value &value)
{
    return value.asString();
}
int mf::_decodeAsByte(const cc::Value &value)
{
    return value.asInt();
}
