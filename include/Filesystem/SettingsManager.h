//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    SettingsManager.h                           //
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

#ifndef __MonsterFramework_Filesystem_SettingsManager_h__
#define __MonsterFramework_Filesystem_SettingsManager_h__

//std
#include <string>
#include <sstream>
//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"
#include "../../../../../cocos2d/cocos/storage/local-storage/LocalStorage.h"

NS_MF_BEGIN
class SettingsManager
{
    // Singleton //
public:
    SINGLETON_OF(SettingsManager);

    // Private CTOR/DTOR //
private:
    SettingsManager();
    ~SettingsManager();

    // Public Methods //
public:
    template <typename T>
    void setValueForKey(const std::string &key, const T &value)
    {
        std::stringstream ss;
        ss << value;

        localStorageSetItem(key, ss.str());
    }
    template <typename T>
    T getValueForKey(const std::string &key)
    {
        std::stringstream ss;
        ss << localStorageGetItem(key);
        T t;
        ss >> t;
        return t;
    }

    //Remove
    void removeValueForKey(const std::string &key);

    //Other
    const std::string& getStoragePath();

    // iVars //
private:
    std::string m_path;
};

NS_MF_END
#endif // defined(__MonsterFramework_Filesystem_SettingsManager_h__) //
