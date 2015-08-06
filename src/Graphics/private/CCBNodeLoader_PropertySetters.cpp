//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    CCBNode_Loader_PropertySetters.cpp          //
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
//        The email is: acknowledgment.opensource@AmazingCow.com              //
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

#include "CCBNodeLoader_PropertySetters.h"
#include "CCBNodeLoader_Decoders.h"

USING_NS_STD_CC_CD_MF

void mf::_set_anchorPoint(cc::Node *obj, const cc::Value &value)
{
    obj->setAnchorPoint(_decodeAsPoint(value));
}
void mf::_set_scale(cc::Node *obj, const cc::Value &value)
{
    //EMSG: We're decided treat scale as a stand alone
    //property. So it's not depends of anything else.
    auto point = _decodeAsPoint(value);
    obj->setScale(point.x, point.y);
}
void mf::_set_ignoreAnchorPointForPosition(cc::Node *obj, const cc::Value &value)
{
    obj->ignoreAnchorPointForPosition(_decodeAsCheck(value));
}
void mf::_set_isTouchEnabled(cc::Node *obj, const cc::Value &value)
{
    //COWTODO:: Ignoring by now, but must check what this method will do.
}
void mf::_set_isAccelerometerEnabled(cc::Node *obj, const cc::Value &value)
{
    //COWTODO:: Ignoring by now, but must check what this method will do.
}
void mf::_set_position(cc::Node *obj, const cc::Value &value)
{
    obj->setPosition(_decodeAsPosition(value, obj->getParent()));
}
void mf::_set_displayFrame(cc::Node *obj, const cc::Value &value)
{
    static_cast<cc::Sprite *>(obj)->setSpriteFrame(_decodeAsSpriteFrame(value));
}
void mf::_set_block(cc::Node *obj, const cc::Value &value, ILoadResolver *pResolver)
{
    pResolver->resolveMenuSelector(_decodeAsBlock(value),
                                   static_cast<cc::MenuItem *>(obj));
}
void mf::_set_isEnabled(cc::Node *obj, const cc::Value &value)
{
    static_cast<cc::MenuItem *>(obj)->setEnabled(_decodeAsCheck(value));
}
void mf::_set_normalSpriteFrame(cc::Node *obj, const cc::Value &value)
{
    cc::Sprite *sprite = cc::Sprite::create();
    mf::_set_displayFrame(sprite, value);

    static_cast<cc::MenuItemSprite *>(obj)->setNormalImage(sprite);
}
void mf::_set_selectedSpriteFrame(cc::Node *obj, const cc::Value &value)
{
    cc::Sprite *sprite = cc::Sprite::create();
    mf::_set_displayFrame(sprite, value);

    static_cast<cc::MenuItemSprite *>(obj)->setSelectedImage(sprite);
}
void mf::_set_disabledSpriteFrame(cc::Node *obj, const cc::Value &value)
{
    cc::Sprite *sprite = cc::Sprite::create();
    mf::_set_displayFrame(sprite, value);

    static_cast<cc::MenuItemSprite *>(obj)->setDisabledImage(sprite);
}
void mf::_set_color(cc::Node *obj, const cc::Value &value)
{
    static_cast<cc::LayerColor *>(obj)->setColor(_decodeAsColor3(value));
}
void mf::_set_contentSize(cc::Node *obj, const cc::Value &value)
{
    obj->setContentSize(_decodeAsSize(value));
}
void mf::_set_rotation(cc::Node *obj, const cc::Value &value)
{
    obj->setRotation(_decodeAsDegrees(value));
}
void mf::_set_fontName(cc::Node *obj, const cc::Value &value)
{
    static_cast<cc::Label *>(obj)->setSystemFontName(value.asString());
}
void mf::_set_fontSize(cc::Node *obj, const cc::Value &value)
{
    static_cast<cc::Label *>(obj)->setSystemFontSize(_decodeAsFontScale(value));
}
void mf::_set_string(cc::Node *obj, const cc::Value &value)
{
    static_cast<cc::Label *>(obj)->setString(_decodeAsString(value));
}
void mf::_set_opacity(cc::Node *obj, const cc::Value &value)
{
    obj->setOpacity(_decodeAsByte(value));
}
