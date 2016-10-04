
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
    constexpr auto kClassPath = "org/cocos2dx/cpp/AppActivity";
    constexpr auto kMethodName = "getApplicationName";
    constexpr auto kMethodSig  = "()Ljava/lang/String;";

    JNIEnv* pEnv;

    JavaVM*   j_jvm      = cc::JniHelper::getJavaVM();
    jint      j_ret      = j_jvm->GetEnv((void**)&pEnv, JNI_VERSION_1_4);
    jclass    j_class    = pEnv->FindClass(kClassPath);
    jmethodID j_methodId = pEnv->GetStaticMethodID(j_class, kMethodName, kMethodSig);
    jstring   j_str      = (jstring)pEnv->CallStaticObjectMethod(j_class, j_methodId);

    const char* cstr = pEnv->GetStringUTFChars(j_str, JNI_FALSE);
    m_appName = cstr;

    pEnv->ReleaseStringUTFChars(j_str, cstr); //Release the Java stuff.
}


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
const std::string& mf::Application::getApplicationName() const
{
    return m_appName;
}

#endif // ( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //
