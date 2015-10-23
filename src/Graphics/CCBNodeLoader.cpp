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

// MACROS //
#define _SET_PROPERTY_FUNCTION(_target_name_, _name_, _obj_, _value_) \
if(_name_ == #_target_name_) {                                        \
    _set_ ## _target_name_(_obj_, _value_);                           \
}

// Public Methods //
void CCBNodeLoader::load(const cc::ValueMap &map, cc::Node *parent,
                         mf::ILoadResolver *pResolver)
{
    //Retrieve the values
    auto baseClass               = map.at("baseClass"              ).asString();
    auto customClass             = map.at("customClass"            ).asString();
    auto children                = map.at("children"               ).asValueVector();
    auto memberVarAssignmentName = map.at("memberVarAssignmentName").asString();
    auto properties              = map.at("properties"             ).asValueVector();

    cc::ValueVector customProperties;
    auto customPropertiesIt = map.find("customProperties");
    if(customPropertiesIt != end(map))
         customProperties = map.at("customProperties").asValueVector();

    //LOG
//    MF_LOG("Loading a Node with BaseClass:(%s) with CustomClass:(%s) and MemberVarAssignment:(%s)",
//          baseClass.c_str(), customClass.c_str(), memberVarAssignmentName.c_str());

    //Create the node and assign its properties.
    cc::Node *node = nullptr;
    if(baseClass == "CCBFile")
    {
        auto ccbFilename = findCCBFilename(properties);
        node = pResolver->resolveCustomClass(ccbFilename);
    }
    else if(customClass.empty())
    {
        node = resolveDefaultClasses(baseClass);
    }
    else if(customClass.size() > 2 && customClass.substr(0, 2) == "MF")
    {
        node = resolveMFClasses(customClass);
    }
    
    //Node isn't a Default class nor a custom MF class, so let's do a last
    //try and check if the client code has a loader for it.
    if(!node)
    {
        node = resolveCustomClasses(customClass, pResolver, customProperties);
    }

    MF_ASSERT(node, "CCBNodeLoader - Node is null (%s)", baseClass.c_str());

    parent->addChild(node);
    assignProperties(node, properties, pResolver);

    //Resolve Custom Class.

    //Resolve Member Var Assignment
    if(!memberVarAssignmentName.empty())
        pResolver->resolveVarAssignment(memberVarAssignmentName, node);

    //Create the Node's children.
    for(const auto &childItem : children)
    {
        CCBNodeLoader nodeLoader;
        nodeLoader.load(childItem.asValueMap(), node, pResolver);
    }
}
void CCBNodeLoader::loadNodeGraph(const cc::ValueMap &map, cc::Node *parent, mf::ILoadResolver *pResolver)
{
    auto children   = map.at("children"  ).asValueVector();
    auto properties = map.at("properties").asValueVector();

    assignProperties(parent, properties, pResolver);

    //Create the Node's children.
    for(const auto &childItem : children)
    {
        CCBNodeLoader nodeLoader;
        nodeLoader.load(childItem.asValueMap(), parent, pResolver);
    }
}

// Private Methods //
std::string CCBNodeLoader::findCCBFilename(const cc::ValueVector &properties)
{
    //Search for a property named ccbFile and return its value
    //if found, otherwise just return an empty string.
    for(auto it = begin(properties); it != end(properties); ++it)
    {
        const auto &item = it->asValueMap();

        if(item.at("name").asString() == "ccbFile")
            return item.at("value").asString();
    }
    return "";
}
cc::Node* CCBNodeLoader::assignProperties(cc::Node *obj,
                                          const cc::ValueVector &properties,
                                          ILoadResolver *pResolver)
{
    //Iterate for all properties.
    for(auto it = begin(properties); it != end(properties); ++it)
    {
        //Get the item.
        const auto &item  = it->asValueMap();
        //Get the name/value pair.
        const auto &name  = item.at("name" ).asString();
        const auto &value = item.at("value");

        MF_LOG("CCBNodeLoader - %s", name.c_str());

        //Check if the name of property matches and set the property.
        _SET_PROPERTY_FUNCTION(anchorPoint,                  name, obj, value);
        _SET_PROPERTY_FUNCTION(scale,                        name, obj, value);
        _SET_PROPERTY_FUNCTION(ignoreAnchorPointForPosition, name, obj, value);
        _SET_PROPERTY_FUNCTION(isTouchEnabled,               name, obj, value);
        _SET_PROPERTY_FUNCTION(isAccelerometerEnabled,       name, obj, value);
        _SET_PROPERTY_FUNCTION(position,                     name, obj, value);
        _SET_PROPERTY_FUNCTION(displayFrame,                 name, obj, value);
        _SET_PROPERTY_FUNCTION(isEnabled,                    name, obj, value);
        _SET_PROPERTY_FUNCTION(normalSpriteFrame,            name, obj, value);
        _SET_PROPERTY_FUNCTION(selectedSpriteFrame,          name, obj, value);
        _SET_PROPERTY_FUNCTION(disabledSpriteFrame,          name, obj, value);
        _SET_PROPERTY_FUNCTION(color,                        name, obj, value);
        _SET_PROPERTY_FUNCTION(contentSize,                  name, obj, value);
        _SET_PROPERTY_FUNCTION(rotation,                     name, obj, value);
        _SET_PROPERTY_FUNCTION(fontName,                     name, obj, value);
        _SET_PROPERTY_FUNCTION(fontSize,                     name, obj, value);
        _SET_PROPERTY_FUNCTION(string,                       name, obj, value);
        _SET_PROPERTY_FUNCTION(opacity,                      name, obj, value);

        //Block is special, because we need the ILoadResolver
        //to communicate with the object owner class.
        if(name == "block")
            _set_block(obj, value, pResolver);
    }

    return obj;
}


cc::Node* CCBNodeLoader::resolveDefaultClasses(const std::string &baseClass)
{
    cc::Node *node = nullptr;

    //Layer.
    if(baseClass == "CCLayer")
        node = cc::Layer::create();

    //LayerColor
    //COWTODO: Bug?
    //This is very strange. With we don't set a color here at craetion
    //of the LayerColor, later the object will not set any color. So any color
    //set in CCB won't be applied. I don't know why this behaviour is occurring
    //but know works in this way.
    else if(baseClass == "CCLayerColor")
        node = cc::LayerColor::create(cc::Color4B::BLUE);

    //Sprite
    else if(baseClass == "CCSprite")
        node = cc::Sprite::create();

    //Menu
    else if(baseClass == "CCMenu")
        node = cc::Menu::create();

    //MenuItem
    else if(baseClass == "CCMenuItemImage")
        node = cc::MenuItemSprite::create(nullptr, nullptr);

    //LabelTTF
    else if(baseClass == "CCLabelTTF")
        node = cc::Label::create();

    return node;
}
cc::Node* CCBNodeLoader::resolveMFClasses(const std::string &customClass)
{
    if(customClass == "MFToggle")
        return cc::MenuItemToggle::create();
    
    return nullptr;
}
cc::Node* CCBNodeLoader::resolveCustomClasses(const std::string &customClass,
                                              mf::ILoadResolver *pResolver,
                                              const cc::ValueVector &customProperties)
{
    
//    cc::Node *node = nullptr;
//    if(customClass == "MFSpriteBatch")
//    {
//        auto imageName = customProperties.at(0).asValueMap().at("value").asString();
//        MF_LOG("%s", imageName.c_str());
//        auto texture = cc::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(imageName);
//        node = cc::SpriteBatchNode::createWithTexture(texture);
//    }
//    return node;


    return pResolver->resolveCustomClass(customClass);
}


#undef _SET_PROPERTY_FUNCTION
