//----------------------------------------------------------------------------//
//                  _   _ ____   ___  ____                                    //
//                 | \ | |___ \ / _ \| __ )  ___  _   _ ____                  //
//                 |  \| | __) | | | |  _ \ / _ \| | | |_  /                  //
//                 | |\  |/ __/| |_| | |_) | (_) | |_| |/ /                   //
//                 |_| \_|_____|\___/|____/ \___/ \__, /___|                  //
//                                                |___/                       //
//                                                                            //
//                            Mateus Mesquita                                 //
//                       www.N2OBoyz.com/~n2omatt                             //
//                          N2OMatt@N2OBoyz.com                               //
//                                                                            //
//                   Copyright (C) 2015 Mateus Mesquita.                      //
//                       Copyright (C) 2015 N2OBoyz.                          //
//                                                                            //
//  This software is provided 'as-is', without any express or implied         //
//  warranty. In no event will the authors be held liable for any damages     //
//  arising from the use of this software.                                    //
//                                                                            //
//  Permission is granted to anyone to use this software for any purpose,     //
//  including commercial applications, and to alter it and redistribute it    //
//  freely, subject to the following restrictions:                            //
//                                                                            //
//  1. The origin of this software must not be misrepresented;                //
//     you must not claim that you wrote the original software.               //
//  2. If you use this software in a product, an acknowledgment in the        //
//     product IS HIGHLY APPRECIATED, both in source and binary forms.        //
//     If you will not acknowledge, just send me a email. We'll be VERY       //
//     happy to see our work being used by other people. :)                   //
//     (See opensource.N2OBoyz.com/acknowledgment.html for details).          //
//  3. Altered source versions must be plainly marked as such, and must not   //
//     be misrepresented as being the original software.                      //
//  4. This notice may not be removed or altered from any source              //
//     distribution.                                                          //
//  5. Most important, you must have fun. ;)                                  //
//                                                                            //
//       Visit OpenSource.N2OBoyz.com for more open-source projects.          //
//                                                                            //
//                            Enjoy :)                                        //
//----------------------------------------------------------------------------//

//Header
#include "MonsterFramework/include/Graphics/SceneBuilder.h"
//MonsterFramework
#include "CCBNodeLoader.h"

//Usings
USING_NS_STD_CC_CD_MF

// Static Methods //
cc::Point SceneBuilder::EXCCP(float px, float py, cc::Node *pNode)
{
    auto size = pNode->getContentSize();
    return Point((size.width * (px/100.0f)), size.height * (py/100.0f));
}

// Public Methods //
void SceneBuilder::build(const std::string &name, cc::Node *pOwner,
                         mf::ILoadResolver *pResolver)

{
    std::string fullname = name;
    if(name.find(".ccb") == std::string::npos)
        fullname += ".ccb";
    
    std::string fullpath = cc::FileUtils::getInstance()->fullPathForFilename(fullname);
    
    auto ccbMap = cc::FileUtils::getInstance()->getValueMapFromFile(fullpath);

    auto nodeGraphMap = ccbMap.at("nodeGraph").asValueMap();
    auto sequencesMap = ccbMap.at("sequences").asValueVector();
    
    CCBNodeLoader b;
    b.loadNodeGraph(nodeGraphMap, pOwner, pResolver);

    
}