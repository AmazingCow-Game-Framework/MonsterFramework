//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    StringsManager.cpp                          //
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
#include "MonsterFramework/include/Localization/StringsManager.h"
//std
#include <fstream>
#include <sstream>
#include <regex>
//MonsterFramework

//Usings
USING_NS_STD_CC_CD_MF


////////////////////////////////////////////////////////////////////////////////
// Constatns                                                                  //
////////////////////////////////////////////////////////////////////////////////
constexpr int kBufferSize = 1024;


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
//Load / Purge
void StringsManager::loadStrings(const std::string &filename,
                                 const std::string &languageName)
{
    //Already Loaded.
    if(m_languageMap.find(languageName) != std::end(m_languageMap))
    {
        MF_LOG_EX(
            "StringsManager::loadStrings",
            "Already loaded strings file for language %s",
            languageName.c_str()
        );
        return;
    }

    auto fullname = cc::FileUtils::getInstance()->fullPathForFilename(filename);

    MF_ASSERT_EX(
        !fullname.empty(),
        "StringsManager::loadStrings",
        "Cannot find file: %s",
        filename.c_str()
    );

    parseStringsFile(fullname, languageName);
}

void StringsManager::purgeStrings(const std::string &languageName)
{
    //Already Purged or Not loaded.
    if(m_languageMap.find(languageName) != std::end(m_languageMap))
    {
        MF_LOG_EX(
            "StringsManager::purgeStrings",
            "Already purged (or not loaded) strings file for language %s",
            languageName.c_str()
        );
        return;
    }

    m_languageMap.erase(languageName);
}

//Language Map
const std::string& StringsManager::getCurrentLanguageName() const
{
    return m_currLanguageName;
}

void StringsManager::setCurrentLanguageName(const std::string &languageName)
{
    //Already Loaded.
    MF_ASSERT_EX(
       m_languageMap.find(languageName) != std::end(m_languageMap),
       "StringsManager::setCurrentLanguageName",
       "Strings for language (%s) isn't loaded",
       languageName.c_str()
    );

    m_pCurrStringsMap  = &m_languageMap[languageName];
    m_currLanguageName = languageName;
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
std::string StringsManager::_getString(const char *string, ...) const
{
    char buffer[kBufferSize] = {'\0'};

    //Build the buffer with the variadic args list
    va_list ap;

    va_start(ap, string);
        vsnprintf(buffer, kBufferSize, string, ap);
    va_end(ap);

    return buffer;
}

void StringsManager::parseStringsFile(const std::string &fullname,
                                      const std::string &languageName)
 {

    //Check if we already have this language.
    MF_ASSERT_EX(
        m_languageMap.find(languageName) == std::end(m_languageMap),
        "StringsManager::parseStrings",
        "Already loaded language (%s)",
        languageName.c_str()
    );

    //COWTODO: MonsterFramework should provide a FileRead / Write class.
    //COWTODO: This code is problematic and very ugly.

    //This is needed because android cannot use c++ streams.
    ssize_t size;
    unsigned char* pData = cc::FileUtils::getInstance()->getFileData(
        fullname.c_str(),
        "r",
        &size
    );

    MF_ASSERT_EX(
        pData != nullptr,
        "StringsManager::parseStringsFile",
        "Cannot open file: %s",
        fullname.c_str()
    );

    std::stringstream instream;
    instream << pData;

    free(pData); //MUST FREE.

    //Read the file.
    std::regex  regex("\"(.*?)\".*?=.*?\"(.*?)\"");
    std::smatch match;


    //COWTODO: Check this code...
    while(!instream.eof())
    {
        std::string line;
        std::getline(instream, line);

        if(!std::regex_search(line, match, regex))
            continue;

        auto full = match[0].str();
        auto key  = match[1].str();
        auto val  = match[2].str();

        m_languageMap[languageName][key] = val;
    }
}
