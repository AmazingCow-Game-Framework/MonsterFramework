//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        FileReader.cpp                            //
//            █ █        █ █        MonsterFramework                          //
//             ████████████                                                   //
//           █              █       Copyright (c) 2016                        //
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

//Header
#include "MonsterFramework/include/Filesystem/FileReader.h"
//std
#include <sstream>

//Usings
USING_NS_STD_CC_CD_MF;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
FileReader::FileReader(const std::string &filename)
{
    MF_LOG_EX("FileReader::FileReader", "Filename: (%s)", filename.c_str());

    auto fullname = cc::FileUtils::getInstance()->fullPathForFilename(filename);
    auto data     = cc::FileUtils::getInstance()->getDataFromFile(fullname);

    MF_ASSERT_EX(
        data.isNull() == false,
        "FileReader::FileReader",
        "Cannot open file: %s",
        fullname.c_str()
    );

    auto size    = data.getSize ();
    auto pBuffer = data.getBytes();

    //Inserting in the vector so we have our own copy.
    //  This way the cocos2d are free to do whatever they
    //  seem to fit.
    m_data.insert(
        std::end(m_data),
        pBuffer,
        (pBuffer + size)
    );
}

FileReader::~FileReader()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
std::vector<std::string> FileReader::readlines()
{
    std::stringstream instream(
        std::string(std::begin(m_data), std::end(m_data))
    );

    std::vector<std::string> lines;
    lines.reserve(1024);

    while(!instream.eof())
    {
        std::string line;
        std::getline(instream, line);

        lines.push_back(line);
    }

    return lines;
}
