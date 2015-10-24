//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    BasicStorage.h                              //
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

#ifndef __MonsterFramework_src_Filesystem_private_BasicStorage_h__
#define __MonsterFramework_src_Filesystem_private_BasicStorage_h__

//std
#include <string>
//sqlite3
#include <sqlite3.h>
//MonsterFramework.
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"

NS_MF_BEGIN
class BasicStorage
{
    // CTOR/DTOR //
public:
    BasicStorage(const std::string &storagePath);
    ~BasicStorage();
    
    // Public Methods //
public:
    //Set.
    void setItem(const std::string &key, const std::string &item);
    
    //Get.
    std::string getItem(const std::string &key, bool *pExists);
    
    //Remove.
    void removeItem(const std::string &key);
    void removeAllItems();

    // Private Methods //
private:
    //Create / Open / Close.
    void createDatabase();
    void openDatabase  ();
    void closeDatabase ();
    
    //Prepare.
    void prepareStatement(const std::string &sql);
 
    void prepareStatement(const std::string &sql,
                          const std::string &key);
    
    void prepareStatement(const std::string &sql,
                          const std::string &key,
                          const std::string &value);
    
    //Bind Text.
    void bindStatementText(const std::string &txt, int index);
    
    //Execute / Finalize.
    void executeStatement ();
    void finalizeStatement();
    
    std::string getSQLError();
    
    // iVars //
private:
    std::string  m_storagePath;

    sqlite3      *m_pDB;
    sqlite3_stmt *m_pStmt;
};

NS_MF_END
#endif // defined( __MonsterFramework_src_Filesystem_private_BasicStorage_h__ ) //
