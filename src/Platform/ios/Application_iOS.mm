
//Header
#include "MonsterFramework/include/Platform/Application.h"

//Prevent the file to be compiled in NON IOS builds.
#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )

//ObjC
#import <Foundation/Foundation.h>


//Usings
USING_NS_MF;

////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Application::Application() :
    cc::Application()
{
    id ns_dict = [[NSBundle mainBundle] infoDictionary];
    id ns_name = [ns_dict objectForKey:(id)kCFBundleNameKey];

    m_appName = [ns_name UTF8String];
}

////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
const std::string& Application::getApplicationName() const
{
    return m_appName;
}


#endif // ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS ) //
