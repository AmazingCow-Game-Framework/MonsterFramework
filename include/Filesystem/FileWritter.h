//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        FileWritter.h                             //
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

#ifndef FILEWRITTER_H
#define FILEWRITTER_H

//std
#include <cstdio>
#include <string>
#include <sstream>
//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"

NS_MF_BEGIN

class FileWritter
{

    // CTOR / DTOR //
public:
    FileWritter(const std::string &basename, bool append = false);

    FileWritter(const std::string &dirname,
                const std::string &basename,
                bool append);

    ~FileWritter();


    // File Methods //
public:
    // Write
    template <typename T>
    FileWritter& write(const T& t)
    {
        std::stringstream ss;
        ss << t;

        return this->write(ss.str());
    }

    FileWritter& write    (const std::string &str);


    // Writeline
    template <typename T>
    FileWritter& writeline(const T& t)
    {
        std::stringstream ss;
        ss << t;

        return this->writeline(ss.str());
    }

    FileWritter& writeline(const std::string &str);


    // Close
    void close();


    // Query Methods //
public:
    const std::string& getBasename() const;
    const std::string& getDirname () const;
    std::string        getFullpath() const;


    // iVars //
private:
    FILE *m_pFILE;

    std::string m_dirname;
    std::string m_basename;
};

NS_MF_END
#endif // FILEWRITTER_H
