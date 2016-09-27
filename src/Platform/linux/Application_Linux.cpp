
//Header
#include "MonsterFramework/include/Platform/Application.h"

//Prevent the file to be compiled in NON LINUX builds.
#if( CC_TARGET_PLATFORM == CC_PLATFORM_LINUX )

//std
#include <unistd.h> //For readlink
#include <limits.h> //for PATH_MAX

//Usings
USING_NS_MF;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Application::Application() :
    cc::Application()
{
    char fullpath[PATH_MAX] = {0};
    auto pathLen = readlink("/proc/self/exe", fullpath, PATH_MAX);

    MF_ASSERT_EX(
        pathLen > 0,
        "[Linux] Application::Application()",
        "Cannot get the application path from readlink(2)"
    );

    fullpath[pathLen] = '\0';

    m_appName = fullpath;
    m_appName = m_appName.substr(m_appName.find_last_of("/")+1); //+1 to skip the /
}

////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
const std::string& Application::getApplicationName() const
{
    return m_appName;
}


#endif // ( CC_TARGET_PLATFORM == CC_PLATFORM_LINUX ) //




