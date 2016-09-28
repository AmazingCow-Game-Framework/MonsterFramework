//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    CCBNodeLoader.cpp                           //
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
#include "CCBNodeLoader.h"
//std
#include <string>
//MonsterFramework
#include "MonsterFramework/include/Graphics/ILoadResolver.h"
#include "MonsterFramework/src/Graphics/private/CCBNodeLoader_Decoders.h"
#include "MonsterFramework/src/Graphics/private/CCBNodeLoader_PropertySetters.h"

//Usings
USING_NS_STD_CC_CD_MF

////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
void CCBNodeLoader::load(const cc::ValueMap &map,
                         cc::Node          *pParent,
                         mf::ILoadResolver *pResolver)
{
    //Constants.
    constexpr auto kBaseClass        = "baseClass";
    constexpr auto kCustomClass      = "customClass";
    constexpr auto kChildren         = "children";
    constexpr auto kMemberVar        = "memberVarAssignmentName";
    constexpr auto kProperties       = "properties";
    constexpr auto kCustomProperties = "customProperties";
    constexpr auto kCCBFile          = "CCBFile";

    //Load info.
    auto baseClass               = map.at(kBaseClass  ).asString     ();
    auto customClass             = map.at(kCustomClass).asString     ();
    auto children                = map.at(kChildren   ).asValueVector();
    auto memberVarAssignmentName = map.at(kMemberVar  ).asString     ();
    auto properties              = map.at(kProperties ).asValueVector();

    cc::ValueVector customProperties;
    auto customPropertiesIt = map.find(kCustomProperties);
    if(customPropertiesIt != std::end(map))
         customProperties = map.at(kCustomProperties).asValueVector();


    //Load the node.
    cc::Node *pNode = nullptr;

    // CCBFile.
    if(baseClass == kCCBFile)
    {
        auto ccbFilename = findCCBFilename(properties);
        pNode = pResolver->resolveCustomClass(ccbFilename, customProperties);
    }
    // Default Classes.
    else if(customClass.empty())
    {
        pNode = this->resolveDefaultClasses(baseClass);
    }
    // Custom Classes.
    else
    {
        pNode = pResolver->resolveCustomClass(customClass, customProperties);
    }

    //Ensure that Node was loaded.
    MF_ASSERT_EX(
        pNode,
        "CCBNodeLoader::load",
        "Node is null (%s)",
        baseClass.c_str()
    );

    pParent->addChild(pNode);

    //Assign Properties.
    this->assignProperties(pNode, properties, pResolver);

    //Resolve Var Assignment.
    if(!memberVarAssignmentName.empty())
        pResolver->resolveVarAssignment(memberVarAssignmentName, pNode);

    //Create the Node's children.
    CCBNodeLoader nodeLoader;
    for(const auto &childItem : children)
    {
        nodeLoader.load(
            childItem.asValueMap(), //Graph
            pNode,                  //Owner
            pResolver               //Resolver
        );
    }
}

void CCBNodeLoader::loadNodeGraph(const cc::ValueMap &map,
                                  cc::Node           *pParent,
                                  mf::ILoadResolver  *pResolver)
{
    constexpr auto kChildren   = "children";
    constexpr auto kProperties = "properties";

    //Load info.
    auto children   = map.at(kChildren  ).asValueVector();
    auto properties = map.at(kProperties).asValueVector();

    //Make the Code Owner (The class object) has equal
    //prorperties as the CCBFile Owner (First Object).
    this->assignProperties(pParent, properties, pResolver);

    //Create the Node's children.
    CCBNodeLoader nodeLoader;
    for(const auto &childItem : children)
    {
        nodeLoader.load(
           childItem.asValueMap(),  //Graph
           pParent,                 //Owner
           pResolver                //Resolver
        );
    }
}

////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
std::string CCBNodeLoader::findCCBFilename(const cc::ValueVector &properties)
{
    //Constants.
    constexpr auto kName    = "name";
    constexpr auto kCCBFile = "ccbFile";
    constexpr auto kValue   = "value";

    //Search for a property named ccbFile and return its value
    //if found, otherwise just return an empty string.
    for(const auto &item : properties)
    {
        const auto &map = item.asValueMap();

        if(map.at(kName).asString() == kCCBFile)
            return map.at(kValue).asString();
    }

    return "";
}

cc::Node* CCBNodeLoader::assignProperties(cc::Node              *pObj,
                                          const cc::ValueVector &properties,
                                          ILoadResolver         *pResolver)
{
    //Constants
    constexpr auto kName  = "name";
    constexpr auto kValue = "value";

    //Iterate for all properties.
    for(const auto &item : properties)
    {
        //Get the item.
        const auto &propMap = item.asValueMap();
        //Get the name/value pair.
        const auto &name  = propMap.at(kName ).asString();
        const auto &value = propMap.at(kValue);

//This macro is just to ease the typing and make the code less cluttered
//Since all functions follows the "same signature" chaging only the part
//of it's name. This macro is undefined just after it's use.
#define _SET_PROPERTY_FUNCTION(_target_name_)     \
    if(name == #_target_name_) {                  \
        _set_ ## _target_name_(pObj, value);      \
    }

        //Check if the name of property matches and set the property.
        _SET_PROPERTY_FUNCTION(anchorPoint                 );
        _SET_PROPERTY_FUNCTION(color                       );
        _SET_PROPERTY_FUNCTION(contentSize                 );
        _SET_PROPERTY_FUNCTION(disabledSpriteFrame         );
        _SET_PROPERTY_FUNCTION(displayFrame                );
        _SET_PROPERTY_FUNCTION(fontName                    );
        _SET_PROPERTY_FUNCTION(fontSize                    );
        _SET_PROPERTY_FUNCTION(ignoreAnchorPointForPosition);
        _SET_PROPERTY_FUNCTION(isAccelerometerEnabled      );
        _SET_PROPERTY_FUNCTION(isEnabled                   );
        _SET_PROPERTY_FUNCTION(isTouchEnabled              );
        _SET_PROPERTY_FUNCTION(normalSpriteFrame           );
        _SET_PROPERTY_FUNCTION(opacity                     );
        _SET_PROPERTY_FUNCTION(position                    );
        _SET_PROPERTY_FUNCTION(rotation                    );
        _SET_PROPERTY_FUNCTION(scale                       );
        _SET_PROPERTY_FUNCTION(selectedSpriteFrame         );
        _SET_PROPERTY_FUNCTION(string                      );
        _SET_PROPERTY_FUNCTION(dimensions                  );
        _SET_PROPERTY_FUNCTION(horizontalAlignment         );
        _SET_PROPERTY_FUNCTION(verticalAlignment           );

#undef _SET_PROPERTY_FUNCTION //We don't want this anymore ;)

        //Block is special, because we need the ILoadResolver
        //to communicate with the object owner class.
        if(name == "block")
            _set_block(pObj, value, pResolver);
    }

    return pObj;
}

cc::Node* CCBNodeLoader::resolveDefaultClasses(const std::string &baseClass)
{
    //Constants
    constexpr auto kCCLayer         = "CCLayer";
    constexpr auto kCCLayerColor    = "CCLayerColor";
    constexpr auto kCCSprite        = "CCSprite";
    constexpr auto kCCMenu          = "CCMenu";
    constexpr auto kCCMenuItemImage = "CCMenuItemImage";
    constexpr auto kCCLabelTTF      = "CCLabelTTF";
    
    //Layer
    if(baseClass == kCCLayer)
        return cc::Layer::create();

    //LayerColor
    //COWTODO: Bug? \
    //  This is very strange. With we don't set a color here at creations   \
    //  of the LayerColor, later the object will not set any color.        \
    //  So any color m_options.panelType == DialogPanel::PanelType::Pause  \
    //  x is occurring  but know works in this way.
    //
    if(baseClass == kCCLayerColor)
        return cc::LayerColor::create(cc::Color4B::BLUE);

    //Sprite
    if(baseClass == kCCSprite)
        return cc::Sprite::create();

    //Menu
    if(baseClass == kCCMenu)
        return cc::Menu::create();

    //MenuItem
    if(baseClass == kCCMenuItemImage)
        return cc::MenuItemSprite::create(nullptr, nullptr);

    //LabelTTF
    else if(baseClass == kCCLabelTTF)
        return cc::Label::create();
    
    
    return nullptr;
}
