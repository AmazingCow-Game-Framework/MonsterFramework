
#include "MonsterFramework/include/Platform/Application.h"

//Prevent the file to be compiled in NON Android builds.
#if( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )

//Jni
#include "platform/android/jni/JniHelper.h"

//Usings
USING_NS_MF;
USING_NS_CC;

////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
mf::Application::Application() :
    cc::Application()
{
    JniMethodInfo t;
    auto success = JniHelper::getStaticMethodInfo(
                        t,
                        "org/cocos2dx/cpp/AppActivity",
                        "getApplicationName",
                        "()Ljava/lang/String;"
                    );
    MF_ASSERT_EX(
        success == true,
        "[Android] Application::Application()",
        "Cannot extract method info"
    );

    jstring s = (jstring)t.env->CallObjectMethod(t.classID, t.methodID);
    m_appName = JniHelper::jstring2string(s);
}


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
const std::string& mf::Application::getApplicationName() const
{
    return m_appName;
}

#endif // ( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //
