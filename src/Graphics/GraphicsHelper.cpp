//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    GraphicsHelper.cpp                          //
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
#include "MonsterFramework/include/Graphics/GraphicsHelper.h"

//Usings
USING_NS_STD_CC_CD_MF

// Public Static Methods //
void GraphicsHelper::setAnchorToCenter(cc::Node *pNode)
{
    pNode->ignoreAnchorPointForPosition(false);
    pNode->setAnchorPoint(cc::Point(0.5, 0.5));
}

// Position Methods //
//Getters.
cc::Point GraphicsHelper::getAbsolutePosition(float px, float py,
                                              cc::Node *pParentNode)
{
    //COWTODO: this should call the methods or perform the operation by itself.
    //COWTODO: now the pParentNode::getContentSize is being called twice.
    return cc::Point(getAbsolutePositionX(px, pParentNode),
                     getAbsolutePositionY(py, pParentNode));
}
cc::Point GraphicsHelper::getAbsolutePositionCenter(cc::Node *pParentNode)
{
    return getAbsolutePosition(50, 50, pParentNode);
}
float GraphicsHelper::getAbsolutePositionX(float px, cc::Node *pParentNode)
{
    return (pParentNode->getContentSize().width * (px/100.0f));
}
float GraphicsHelper::getAbsolutePositionY(float py, cc::Node *pParentNode)
{
    return (pParentNode->getContentSize().height * (py/100.0f));
}

//Setters.
void GraphicsHelper::setRelativePosition(float px, float py,
                                         cc::Node *pNode,
                                         cc::Node *pParentNode)
{
    auto point = getAbsolutePosition(px, py, pParentNode);
    pNode->setPosition(point);
}

void GraphicsHelper::setPositionToCenter(cc::Node *pNode,
                                         cc::Node *pParentNode)
{
    setRelativePosition(50, 50, pNode, pParentNode);
}
