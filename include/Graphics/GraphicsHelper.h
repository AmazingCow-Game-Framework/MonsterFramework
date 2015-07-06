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

#ifndef U7_MasterKidsGames_GraphicsHelper_h
#define U7_MasterKidsGames_GraphicsHelper_h

//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"

NS_MF_BEGIN

namespace GraphicsHelper {

    static void setAnchorToCenter(cc::Node *pNode)
    {
        pNode->ignoreAnchorPointForPosition(false);
        pNode->setAnchorPoint(cc::Point(0.5, 0.5));
    }

    static cc::Point getAbsolutePosition(float px, float py,
                                           cc::Node *pParentNode)
    {
        auto size = pParentNode->getContentSize();
        return cc::Point((size.width * (px/100.0f)), size.height * (py/100.0f));
    }
    static cc::Point getAbsolutePositionCenter(cc::Node *pParentNode)
    {
        return getAbsolutePosition(50, 50, pParentNode);
    }

    static void setRelativePosition(float px, float py,
                              cc::Node *pNode,
                              cc::Node *pParentNode)
    {
        auto point = getAbsolutePosition(px, py, pParentNode);
        pNode->setPosition(point);
    }

    static void setPositionToCenter(cc::Node *pNode,
                                    cc::Node *pParentNode)
    {
        setRelativePosition(50, 50, pNode, pParentNode);
    }
}

NS_MF_END
#endif
