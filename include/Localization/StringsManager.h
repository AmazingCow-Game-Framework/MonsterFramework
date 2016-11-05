//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        ILoadResolver.h                           //
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

#ifndef __MonsterFramework_include_Localization_StringsManager_h__
#define __MonsterFramework_include_Localization_StringsManager_h__

//std
#include <cstdarg>
#include <string>
#include <unordered_map>

//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"

NS_MF_BEGIN
class StringsManager
{
    // Enums / Constants / Typedefs //
public:
    typedef std::unordered_map<std::string, std::string> StringsMap;
    typedef std::unordered_map<std::string, StringsMap>  LanguageMap;


    // Singleton //
public:
    SINGLETON_OF(StringsManager);


    // CTOR/DTOR //
private:
    StringsManager () { /* Empty... */ }
    ~StringsManager() { /* Empty... */ }


    // Public Methods //
public:
    //Load / Purge
    void loadStrings(const std::string &filename,
                     const std::string &languageName);

    void purgeStrings(const std::string &languageName);


    //Get String
    //COWTODO: Clean up...
    template <typename... Args>
    std::string getString(const std::string str, Args... argList)
    {
        MF_ASSERT_EX(
            m_pCurrStringsMap != nullptr,
            "StringsManager::getString",
            "m_pCurrStringsMap is null - Probably didn't loaded the strings"
        );

        auto it = m_pCurrStringsMap->find(str);
        MF_ASSERT_EX(
            it != std::end(*m_pCurrStringsMap),
            "StringsManager::getString",
            "Cannot find string (%s) for language (%s)",
            str.c_str(),
            getCurrentLanguageName().c_str()
        );

        auto localizedStr = (*it).second;

        if(sizeof...(argList) == 0)
            return localizedStr;

        return _getString(localizedStr.c_str(), argList...);
    }

    //Language Map
    const std::string& getCurrentLanguageName() const;
    void setCurrentLanguageName(const std::string &languageName);


    // Private Methods //
private:
    //COWTODO: Clean up.
    std::string _getString(const char *string, ...) const;

    void parseStringsFile(const std::string &fullname,
                          const std::string &languageName);


    // iVars //
private:
    LanguageMap m_languageMap;

    std::string m_currLanguageName;
    StringsMap *m_pCurrStringsMap;
};

#define MF_LocalizedString(_str_, ...) \
    StringsManager::instance()->getString(_str_, ##__VA_ARGS__)

NS_MF_END
#endif // defined(__MonsterFramework_include_Localization_StringsManager_h__) //
