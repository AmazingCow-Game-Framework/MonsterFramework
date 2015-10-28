//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    GraphicsHelper.h                            //
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

#ifndef __MonsterFramework_include_Graphics_GraphicsHelper_h__
#define __MonsterFramework_include_Graphics_GraphicsHelper_h__

//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"

NS_MF_BEGIN

class GraphicsHelper
{
    // Public Static Methods //
public:
    static void setAnchorToCenter(cc::Node *pNode);

    
    // Position Methods //
    //Getters.
    static cc::Point getAbsolutePosition(float px, float py,
                                         cc::Node *pParentNode);

    static cc::Point getAbsolutePositionCenter(cc::Node *pParentNode);

    static float getAbsolutePositionX(float px, cc::Node *pParentNode);
    static float getAbsolutePositionY(float py, cc::Node *pParentNode);
    
    //Setters.
    static void setRelativePosition(float px, float py,
                                    cc::Node *pNode,
                                    cc::Node *pParentNode);

    static void setPositionToCenter(cc::Node *pNode,
                                    cc::Node *pParentNode);

    //COWTOOD: do something about this.
    typedef void PlatformImage;
    static PlatformImage* spriteToPlatformImage(cc::Sprite *pSprite);
};

NS_MF_END
#endif // defined(__MonsterFramework_include_Graphics_GraphicsHelper_h__) //
