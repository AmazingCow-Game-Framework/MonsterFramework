//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    CCBNode_Loader_Decoders.cpp                 //
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
#include "CCBNodeLoader_Decoders.h"

//MonsterFramework
#include "MonsterFramework/include/Graphics/GraphicsHelper.h"

//Usings.
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
cc::Point mf::_decodeAsPosition(const cc::Value &value, cc::Node *pNode)
{
    //Constants
    constexpr auto kIndex_X    = 0;
    constexpr auto kIndex_Y    = 1;
    constexpr auto kIndex_Type = 2;
    
    constexpr auto kType_Abs = 0;
    constexpr auto kType_Per = 4;
    
    //Get the values.
    auto x = value.asValueVector().at(kIndex_X).asFloat();
    auto y = value.asValueVector().at(kIndex_Y).asFloat();
    
    auto type = value.asValueVector().at(kIndex_Type).asInt();
    
    MF_ASSERT_EX(
        ((type == kType_Abs) || (type == kType_Per)),
        "SceneBuilder - _decodeAsPosition",
        "Tried decoded an unsuported type of position: (%d)",
        type
    );
    
    if(type == kType_Abs)
    {
        return cc::Vec2(x, y);
    }
    else if(type == kType_Per)
    {
        auto size = (pNode && pNode->getParent())
                    ? pNode->getParent()->getContentSize()
                    : cc::Director::getInstance()->getWinSize();
        
        return mf::GraphicsHelper::getAbsolutePosition(x, y, size);
    }
    
    return cc::Point::ZERO; //Just to make the compile happy.
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

cc::Size mf::_decodeAsSize(const cc::Value &value, cc::Node *pNode)
{
    //Constants.
    constexpr auto kIndex_Width  = 0;
    constexpr auto kIndex_Height = 1;
    constexpr auto kIndex_Type   = 2;
    
    constexpr auto kType_Abs = 0;
    constexpr auto kType_Per = 1;
    
    //Get the Values.
    auto w = value.asValueVector().at(kIndex_Width ).asFloat();
    auto h = value.asValueVector().at(kIndex_Height).asFloat();
    
    auto type = value.asValueVector().at(kIndex_Type).asInt();
    
    
    MF_ASSERT_EX(
        ((type == kType_Abs) || (type == kType_Per)),
        "SceneBuilder - _decodeAsSize",
        "Tried decoded an unsuported type of size: (%d)",
        type
    );
    
    if(type == kType_Abs)
    {
        return cc::Size(w, h);
    }
    else if(type == kType_Per)
    {
        auto parentSize = (pNode && pNode->getParent())
                          ? pNode->getParent()->getContentSize()
                          : cc::Director::getInstance()->getWinSize();
        
        return cc::Size(
                   parentSize.width  * (w / 100.0f),
                   parentSize.height * (h / 100.0f)
               );
    }
    
    return cc::Size::ZERO; //Just to make the compile happy.
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
