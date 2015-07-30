//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    ADManager.h                                 //
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

#ifndef __MonsterFramework_AD_ADManager_h__
#define __MonsterFramework_AD_ADManager_h__

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
#endif // defined(__MonsterFramework_AD_ADManager_h__) //
