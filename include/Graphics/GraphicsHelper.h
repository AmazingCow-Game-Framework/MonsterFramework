//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        GraphicsHelper.h                          //
//            █ █        █ █        MonsterFramework                          //
//             ████████████                                                   //
//           █              █       Copyright (c) 2015, 2016                  //
//          █     █    █     █      AmazingCow - www.AmazingCow.com           //
//          █     █    █     █                                                //
//           █              █       N2OMatt - n2omatt@amazingcow.com          //
//             ████████████         www.amazingcow.com/n2omatt                //
//                                                                            //
//                  This software is licensed as GPLv3                        //
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
//        The email is: acknowledgment_opensource@AmazingCow.com              //
//     3. Altered source versions must be plainly marked as such,             //
//        and must not be misrepresented as being the original software.      //
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
public:
    //COWNOTE: [Explaining why we need this method]
    //  This is needed due a lack of a "Label Button" in CocosBuilder
    //  so we must add a label in the editor and convert it to a
    //  MenuItemLabel in code :(
    static cc::MenuItemLabel* createMenuItemLabelFromLabel(cc::Label *pLabel,
                                                           const cc::ccMenuCallback &callback);

    // Copy Properties //
public:
    static void copyPosition   (cc::Node *pSrc, cc::Node *pDst);
    static void copySize       (cc::Node *pSrc, cc::Node *pDst);
    static void copyAnchorPoint(cc::Node *pSrc, cc::Node *pDst);
    static void copyScale      (cc::Node *pSrc, cc::Node *pDst);
    
    // ??? //
public:
    static cc::Vec2 getSizeScaleRatio(cc::Node *pNode1, cc::Node *pNode2);


    // Anchor //
public:
    static void setAnchorToTop   (cc::Node *pNode);
    static void setAnchorToCenter(cc::Node *pNode);


    // Get Absolute Position //
public:
    static cc::Point getAbsolutePositionCenter(cc::Node *pParentNode);

    //Get Absolute Position
    static cc::Point getAbsolutePosition(float px, float py,
                                         cc::Node *pParentNode);

    static cc::Point getAbsolutePosition(float px, float py,
                                         cc::Size size);

    static cc::Point getAbsolutePosition(float px, float py,
                                         cc::Rect rect);


    //Get Absolute Position X
    static float getAbsolutePositionX(float px, cc::Node *pParentNode);
    static float getAbsolutePositionX(float px, cc::Rect rect);
    static float getAbsolutePositionX(float px, cc::Size size);

    //Get Absolute Position Y
    static float getAbsolutePositionY(float py, cc::Node *pParentNode);
    static float getAbsolutePositionY(float px, cc::Rect rect);
    static float getAbsolutePositionY(float py, cc::Size size);



public:
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
