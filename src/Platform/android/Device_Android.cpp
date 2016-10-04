//----------------------------------------------------------------------------//
//       █      █                                                             //
//       ████████                                                             //
//     ██        ██     File    : Device_Android.cpp                          //
//    ███  █  █  ███    Project : GameMemory                                  //
//    █ █        █ █    Author  : N2OMatt                                     //
//     ████████████     Date    : Wed Sep 28 2016 17:21:49 2016 BRT           //
//   █              █                                                         //
//  █     █    █     █  Copyright (c) 2016                                    //
//  █     █    █     █  AmazingCow - www.AmazingCow.com                       //
//   █              █                                                         //
//     ████████████     This File / Project is PROPRIETARY                    //
//                                                                            //
//                          Enjoy :)                                          //
//----------------------------------------------------------------------------//

//Header
#include "MonsterFramework/include/Platform/Device.h"

//Prevent the inclusion on NON ANDROID builds.
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )

//std
#include <sstream>

//Usings
USING_NS_MF;

////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
cc::Size Device::getScreenSize()
{
    constexpr auto kClassPath = "org/cocos2dx/cpp/AppActivity";
    constexpr auto kMethodName = "getScreenSize";
    constexpr auto kMethodSig  = "()Ljava/lang/String;";

    JNIEnv* pEnv;

    JavaVM*   j_jvm      = cc::JniHelper::getJavaVM();
    jint      j_ret      = j_jvm->GetEnv((void**)&pEnv, JNI_VERSION_1_4);
    jclass    j_class    = pEnv->FindClass(kClassPath);
    jmethodID j_methodId = pEnv->GetStaticMethodID(j_class, kMethodName, kMethodSig);
    jstring   j_str      = (jstring)pEnv->CallStaticObjectMethod(j_class, j_methodId);

    const char* cstr = pEnv->GetStringUTFChars(j_str, JNI_FALSE);

    //We're getting a string with the width and height separated
    //by a space. So we need to parse it here.
    std::stringstream ss(cstr);

    auto size = cc::Size::ZERO;
    ss >> size.height;
    ss >> size.width;


    pEnv->ReleaseStringUTFChars(j_str, cstr); //Release the Java stuff.
}

#endif // ( CC_TARGET_PLATFORM == CC_PLATFORM_LINUX ) //
