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

#ifndef __MonsterFramework_ADManager_h__
#define __MonsterFramework_ADManager_h__

//std
#include <string>
//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"

NS_MF_BEGIN

class ADManager
{
    // Inner Types //
public:
    struct AdOptions
    {
        // Enums/Constants/Typedefs //
        enum class AdType { Banner, Interstitial };
        
        // Public Vars //
        std::string Key;
        AdType      Type;
    };
    
    // Enums/Constants/Typedefs //
public:
    static const std::string kADBasedKey;
    
    // Singleton //
public:
    SINGLETON_OF(ADManager);

    // Private CTOR/DTOR //
private:
     ADManager();
    ~ADManager();
    
    // Public Methods //
public:
    void setGameIsAdBased(bool adBased);
    bool getGameIsAdBased() const;
    
    bool showAd(const AdOptions &options);
    bool hideAd(const AdOptions &options);
    
    bool addAd   (const AdOptions &options);
    bool removeAd(const AdOptions &options);
    
    // Private Methods //
private:
    void saveSettings();
    void loadSettings();
    
    // iVars //
private:
    bool m_adBased;
};
    
NS_MF_END
#endif // defined(__MonsterFramework_ADManager_h__) //