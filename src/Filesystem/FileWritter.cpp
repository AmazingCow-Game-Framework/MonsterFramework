//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        FileWritter.cpp                           //
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
#include "MonsterFramework/include/Filesystem/FileWritter.h"

//Usings
USING_NS_STD_CC_CD_MF;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
FileWritter::FileWritter(const std::string &filename) :
    FileWritter(
        cc::FileUtils::getInstance()->getWritablePath(),
        filename
    )
{
    //Empty...
}


FileWritter::FileWritter(const std::string &dirname,
                         const std::string &basename) :
    m_pFILE   (nullptr),
    m_dirname (dirname ),
    m_basename(basename)
{
    m_pFILE = fopen(getFullpath().c_str(), "w");

    MF_ASSERT_EX(
        m_pFILE != nullptr,
        "FileWritter::FileWritter",
        "Cannot open file for write: (%s)",
        getFullpath().c_str()
    );
}

FileWritter::~FileWritter()
{
    //FILE is already closed.
    if(!m_pFILE)
        return;

    this->close();
}


////////////////////////////////////////////////////////////////////////////////
// File Methods                                                               //
////////////////////////////////////////////////////////////////////////////////
FileWritter& FileWritter::write(const std::string &str)
{
    fprintf(m_pFILE, "%s", str.c_str());
    return *this;
}

FileWritter& FileWritter::writeline(const std::string &str)
{
    fprintf(m_pFILE, "%s\n", str.c_str());
    return *this;
}

void FileWritter::close()
{
    MF_ASSERT_EX(
        m_pFILE != nullptr,
        "FileWritter::close",
        "Trying to close an aready closed (or invalid) file: (%s)",
        getFullpath().c_str()
    );

    fflush(m_pFILE);
    fclose(m_pFILE);

    m_pFILE = nullptr;
}


////////////////////////////////////////////////////////////////////////////////
// Query Methods                                                              //
////////////////////////////////////////////////////////////////////////////////
const std::string& FileWritter::getBasename() const
{
    return m_basename;
}

const std::string& FileWritter::getDirname() const
{
    return m_dirname;
}

std::string FileWritter::getFullpath() const
{
    if(m_dirname.back() == '/')
        return m_dirname + m_basename;

    return m_dirname + "/" + m_basename;
}
