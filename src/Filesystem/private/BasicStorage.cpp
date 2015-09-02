//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    BasicStorage.cpp                            //
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
#include "BasicStorage.h"

//Usings
USING_NS_STD_CC_CD_MF;

// Constants //
#define kTable_Name   "Data_Table"
#define kColumn_Key   "Key"
#define kColumn_Value "Value"

//COWTODO: Several methods have same code, check if could refactor them.

// CTOR/DTOR //
BasicStorage::BasicStorage(const std::string &storagePath) :
    m_storagePath(storagePath),
    m_pDB(nullptr)
{
    MF_LOG("BasicStorage - CTOR");
    init();
}

BasicStorage::~BasicStorage()
{
    MF_LOG("BasicStorage - DTOR");
    denit();
}

// Public Methods //
void BasicStorage::setItem(const std::string &key, const std::string &item)
{
    //REPALCE
    auto sql = cc::StringUtils::format("REPLACE INTO %s (%s, %s) VALUES (?,?);",
                                       kTable_Name,
                                       kColumn_Key,
                                       kColumn_Value);
    
    //Create the Statement.
    sqlite3_stmt *stmt;
    if(sqlite3_prepare_v2(m_pDB,
                          sql.c_str(),
                          -1,
                          &stmt,
                          nullptr) != SQLITE_OK)
    {
        MF_LOG_ERROR("Basic Storage - Failed to create the REPLACE Statement - %s",
                     getSQLError().c_str());
    }
    
    //Execute the Statement.
    if(sqlite3_step(stmt) != SQLITE_DONE)
    {
        MF_LOG_ERROR("Basic Storage - Failed while executing REPLACE Statement - %s",
                     getSQLError().c_str());
    }
}

std::string BasicStorage::getItem(const std::string &key, bool *pExists)
{
    //SELECT
    auto sql = cc::StringUtils::format("SELECT %s FROM %s WHERE %s=?;",
                                       kColumn_Value,
                                       kTable_Name,
                                       kColumn_Key);
    
    //Create the Statement.
    sqlite3_stmt *stmt;
    if(sqlite3_prepare_v2(m_pDB,
                          sql.c_str(),
                          -1,
                          &stmt,
                          nullptr) != SQLITE_OK)
    {
        MF_LOG_ERROR("Basic Storage - Failed to create the Select Statement - %s",
                     getSQLError().c_str());
    }
    
    //Execute the Statement.
    if(sqlite3_step(stmt) != SQLITE_DONE)
    {
        MF_LOG_ERROR("Basic Storage - Failed while executing Select Statement - %s",
                     getSQLError().c_str());
    }
    
    //Get the column's value.
    auto colText = sqlite3_column_text(stmt, 0);
    *pExists = (colText != nullptr);
    
    return cc::StringUtils::format("%s", colText);
}

void BasicStorage::removeItem(const std::string &key)
{
    //DELETE
    auto sql = cc::StringUtils::format("DELETE FROM %s WHERE %s=?;",
                                       kTable_Name,
                                       kColumn_Key);
    
    //Create the Statement.
    sqlite3_stmt *stmt;
    if(sqlite3_prepare_v2(m_pDB,
                          sql.c_str(),
                          -1,
                          &stmt,
                          nullptr) != SQLITE_OK)
    {
        MF_LOG_ERROR("Basic Storage - Failed to create the Delete Statement - %s",
                     getSQLError().c_str());
    }
    
    //Execute the Statement.
    if(sqlite3_step(stmt) != SQLITE_DONE)
    {
        MF_LOG_ERROR("Basic Storage - Failed while executing DELETE Statement - %s",
                     getSQLError().c_str());
    }
}

void BasicStorage::removeAllItems()
{
    //DELETE
    auto sql = cc::StringUtils::format("DELETE FROM %s;",
                                       kTable_Name);
    
    //Create the Statement.
    sqlite3_stmt *stmt;
    if(sqlite3_prepare_v2(m_pDB,
                          sql.c_str(),
                          -1,
                          &stmt,
                          nullptr) != SQLITE_OK)
    {
        MF_LOG_ERROR("Basic Storage - Failed to create the Delete Statement - %s",
                     getSQLError().c_str());
    }
    
    //Execute the Statement.
    if(sqlite3_step(stmt) != SQLITE_DONE)
    {
        MF_LOG_ERROR("Basic Storage - Failed while executing DELETE Statement - %s",
                     getSQLError().c_str());
    }
}

// Private Methods //
void BasicStorage::init()
{
    //If database is already initialized just do nothing.
    if(m_pDB)
    {
        MF_LOG("Basic Storage - Database already initialized.");
        return;
    }
    
    //Log.
    MF_LOG("Basic Storage - Initializing the storage at %s",
           m_storagePath.c_str());

    
    //Open the Database...
    if(sqlite3_open(m_storagePath.c_str(), &m_pDB) != SQLITE_OK)
    {
        MF_LOG_ERROR("Basic Storage - Failed to open database - %s",
                     getSQLError().c_str());
    }
    
    //COWTODO: Check which size of VARCHAR(XXXX) will be enough
    //COWTODO: Or if has a better way to create it.
    auto create_table_sql = cc::StringUtils::format(
                                    "CREATE TABLE IF NOT EXISTS %s(\
                                    %s   VARCHAR(100) PRIMARY KEY, \
                                    %s VARCHAR(100) ); ",
                                    kTable_Name,
                                    kColumn_Key,
                                    kColumn_Value);
    

    //Create the statement.
    sqlite3_stmt *stmt;
    if(sqlite3_prepare_v2(m_pDB,
                          create_table_sql.c_str(),
                          -1,
                          &stmt,
                          nullptr) != SQLITE_OK)
    {
        MF_LOG_ERROR("Basic Storage - Failed to prepare statement - %s",
                     getSQLError().c_str());
    }
    
    //Execute the statement.
    if(sqlite3_step(stmt) != SQLITE_DONE)
    {
        MF_LOG_ERROR("Basic Storage - Failed to step - %s",
                     getSQLError().c_str());
    }
    
    //Finalize the statement.
    if(sqlite3_finalize(stmt) != SQLITE_OK)
    {
        MF_LOG_ERROR("Basic Storage - Failed to finalize statement - %s",
                     getSQLError().c_str());
    }
}

void BasicStorage::denit()
{
    //If database is not initialized just do nothing.
    if(!m_pDB)
    {
        MF_LOG("Basic Storage - Database is not initialized.");
        return;
    }
    
    //Log.
    MF_LOG("Basic Storage - Denitializing the storage at %s",
           m_storagePath.c_str());

    //Close and set null.
    sqlite3_close(m_pDB);
    m_pDB = nullptr;
}


std::string BasicStorage::getSQLError()
{
    return cc::StringUtils::format("error code:(%d) - error msg:(%s)",
                                   sqlite3_errcode(m_pDB),
                                   sqlite3_errmsg(m_pDB));
}
