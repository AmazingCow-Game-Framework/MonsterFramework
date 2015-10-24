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

#define kQuery_Replace   "REPLACE INTO %s (%s, %s) VALUES (?, ?);"
#define kQuery_Select    "SELECT %s FROM %s WHERE %s=?;"
#define kQuery_Delete    "DELETE FROM %s WHERE %s=?;"
#define kQuery_DeleteAll "DELETE FROM %s;"

#define kQuery_CreateTables "CREATE TABLE IF NOT EXISTS %s( %s VARCHAR(100) PRIMARY KEY, %s VARCHAR(100) );"

// CTOR/DTOR //
BasicStorage::BasicStorage(const std::string &storagePath) :
    m_storagePath(storagePath),
    m_pDB        (nullptr),
    m_pStmt      (nullptr)
{
    MF_LOG("BasicStorage - CTOR");
    createDatabase();
}

BasicStorage::~BasicStorage()
{
    MF_LOG("BasicStorage - DTOR");
    closeDatabase();
}

// Public Methods //
//Set.
void BasicStorage::setItem(const std::string &key, const std::string &item)
{
    //REPLACE.
    auto sql = cc::StringUtils::format(kQuery_Replace,
                                       kTable_Name,
                                       kColumn_Key,
                                       kColumn_Value);
    openDatabase();
    prepareStatement(sql, key, item);
    
    executeStatement();
    
    finalizeStatement();
    closeDatabase();
}

//Get.
std::string BasicStorage::getItem(const std::string &key, bool *pExists)
{
    //SELECT.
    auto sql = cc::StringUtils::format(kQuery_Select,
                                       kColumn_Value,
                                       kTable_Name,
                                       kColumn_Key);
    
    openDatabase();
    prepareStatement(sql, key);
    
    executeStatement();
    
    //Let's assume that values won't be found.
    //Set a "empty" return value.
    *pExists   = false;
    std::string returnValue = "";
    
    //Get the column's value.
    auto collumnValue = sqlite3_column_text(m_pStmt, 0);
    
    //Check if there's a value.
    if(collumnValue)
    {
        *pExists    = true;
        returnValue = cc::StringUtils::format("%s", collumnValue);
    }
    
    finalizeStatement();
    closeDatabase();
    
    return returnValue;
}

//Remove.
void BasicStorage::removeItem(const std::string &key)
{
    //DELETE.
    auto sql = cc::StringUtils::format(kQuery_Delete,
                                       kTable_Name,
                                       kColumn_Key);
    
    openDatabase();
    prepareStatement(sql, key);
    
    executeStatement();
    
    finalizeStatement();
    closeDatabase();
}
void BasicStorage::removeAllItems()
{
    //DELETE ALL.
    auto sql = cc::StringUtils::format(kQuery_DeleteAll,
                                       kTable_Name);
    
    openDatabase();
    prepareStatement(sql);
    
    executeStatement();
    
    finalizeStatement();
    closeDatabase();
}

// Private Methods //
//Create / Open / Close.
void BasicStorage::createDatabase()
{
    //Log.
    MF_LOG("Basic Storage - Initializing the storage at %s",
           m_storagePath.c_str());
    
    if(cc::FileUtils::getInstance()->isFileExist(m_storagePath))
        return;

    
    //COWTODO: Check which size of VARCHAR(XXXX) will be enough
    //COWTODO: Or if has a better way to create it.
    auto sql = cc::StringUtils::format(kQuery_CreateTables,
                                       kTable_Name,
                                       kColumn_Key,
                                       kColumn_Value);
    
    
    openDatabase();
    prepareStatement(sql);

    executeStatement();
    
    finalizeStatement();
    closeDatabase();
}
void BasicStorage::openDatabase()
{
    //Sanity checks.
    MF_ASSERT(m_pDB == nullptr, "Database must be not open.");
    
    //Try open - Fail if anything goes wrong.
    if(sqlite3_open(m_storagePath.c_str(), &m_pDB) != SQLITE_OK)
    {
        MF_LOG_ERROR("Basic Storage - Failed to open database - %s",
                     getSQLError().c_str());
    }
}
void BasicStorage::closeDatabase()
{
    //Try close - Fail if anything goes wrong.
    if(sqlite3_close(m_pDB) != SQLITE_OK)
    {
        MF_LOG_ERROR("BasicStorage - closeDatabase - %s", getSQLError().c_str());
    }
    m_pDB = nullptr;
}

//Prepare.
void BasicStorage::prepareStatement(const std::string &sql)
{
    //Sanity checks...
    MF_ASSERT(m_pStmt == nullptr, "m_pStmt has invalid state, it cannot be non-null here.");
    
    //Try create a statement - Fail if anything goes wrong.
    if(sqlite3_prepare_v2(m_pDB,
                          sql.c_str(),
                          -1,
                          &m_pStmt,
                          nullptr) != SQLITE_OK)
    {
        MF_LOG_ERROR("Basic Storage - prepareStatement - Failed to prepare statement (%s) - %s",
                     sql.c_str(),
                     getSQLError().c_str());
    }
}
void BasicStorage::prepareStatement(const std::string &sql,
                                    const std::string &key)
{
    //Call the basic version to prepare the statment.
    prepareStatement(sql);
    //Bind the key into the statment ("replace" the "?" for the key...)
    bindStatementText(key, 1);
}
void BasicStorage::prepareStatement(const std::string &sql,
                                    const std::string &key,
                                    const std::string &value)
{
    //Call the basic version to prepare the statment.
    prepareStatement(sql, key);
    //Bind the value into the statment ("replace" the "?" for the value...)
    bindStatementText(value, 2);
}

//Bind Text.
void BasicStorage::bindStatementText(const std::string &txt, int index)
{
    //Try bind the value - Fail if anything goes wrong..
    if(sqlite3_bind_text(m_pStmt,
                         index,
                         txt.c_str(),
                         -1,
                         SQLITE_TRANSIENT) != SQLITE_OK)
    {
        MF_LOG_ERROR("Basic Storage - bindStatementText - Failed %s",
                     getSQLError().c_str());
    }
}

//Execute / Finialize.
void BasicStorage::executeStatement()
{
    //Sanity checks.
    MF_ASSERT(m_pDB,   "m_pDB must be openned first.");
    MF_ASSERT(m_pStmt, "m_pStmt cannot be null here.");
    
    //Execute - Fail if anything goes wrong.
    auto result = sqlite3_step(m_pStmt);
    if(result != SQLITE_DONE && result != SQLITE_ROW) //ROW is for the SELECT...
    {
        MF_LOG_ERROR("Basic Storage - Failed while executing statement - %s",
                     getSQLError().c_str());
    }
}
void BasicStorage::finalizeStatement()
{
    //Sanity checks...
    MF_ASSERT(m_pStmt != nullptr, "m_pStmt has invalid state, it cannot be null here.");

    
    //Finalize - - Fail if anything goes wrong.
    if(sqlite3_finalize(m_pStmt) != SQLITE_OK)
    {
        MF_LOG_ERROR("Basic Storage - prepareStatement - Failed to finalize statement - %s",
                     getSQLError().c_str());
    }
    
    m_pStmt = nullptr;
}


std::string BasicStorage::getSQLError()
{
    return cc::StringUtils::format("error code:(%d) - error msg:(%s)",
                                   sqlite3_errcode(m_pDB),
                                   sqlite3_errmsg(m_pDB));
}
