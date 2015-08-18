//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    MonsterFramework_Utils.h                    //
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

#ifndef __MonsterFramework_include_Utils_MonsterFramework_Utils_h__
#define __MonsterFramework_include_Utils_MonsterFramework_Utils_h__

// Includes //
//cocos2d
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

// Namespaces //
//Create aliases to reduce the verbosity of the use of cocos2d's namespaces.
namespace cc    = cocos2d;
namespace cd    = CocosDenshion;
namespace ccext = cocos2d::extension;

//Help reduce verbosity of MonsterFramework namespace declarations.
#define NS_MF_BEGIN namespace mf {
#define NS_MF_END   }

//One shot using...
#define USING_NS_STD_CC_CD_MF \
    using namespace std;      \
    using namespace cocos2d;  \
    using namespace cd;       \
    using namespace ccext;    \
    using namespace mf;

// Macros //
#define SINGLETON_OF(__type__) static __type__ *instance() { static __type__ t; return &t; }

//Similar to cocos2d's CREATE_FUNC macro, but for scenes.
#define SCENE_FUNC(__LAYER_TYPE__)         \
static cc::Scene* scene()                  \
{                                          \
    auto scene = cc::Scene::create();      \
    auto layer = __LAYER_TYPE__::create(); \
    scene->addChild(layer);                \
    return scene;                          \
}

//Similar to SCENE_FUNC, but the scene will receive one
//parameter called options with the type passed in __OPT_TYPE__.
//This method will call the create(options) of the __LAYER_TYPE__.
#define SCENE_FUNC_OPTIONS(__LAYER_TYPE__, __OPT_TYPE__) \
static cc::Scene* scene(const __OPT_TYPE__ &options)     \
{                                                        \
    auto scene = cc::Scene::create();                    \
    auto layer = __LAYER_TYPE__::create(options);        \
    scene->addChild(layer);                              \
    return scene;                                        \
}

//Similar to the CREATE_FUNC of cocos2d, but the __TYPE__'s
//init will be called with the options of type __OPT_TYPE__
//passed as argument.
#define CREATE_FUNC_OPTIONS(__TYPE__, __OPT__)  \
static __TYPE__* create(const __OPT__ &options) \
{                                               \
    auto ret = new __TYPE__();                  \
    if(ret && ret->init((options)))             \
    {                                           \
        ret->autorelease();                     \
    }                                           \
    else                                        \
    {                                           \
        delete ret;                             \
        ret = NULL;                             \
    }                                           \
    return ret;\
}

#define INIT_OPTIONS(__OPT__) \
    virtual bool init(const __OPT__ &options);

// DEPRECATED //
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
    #define MF_DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#elif _MSC_VER >= 1400 //vs 2005 or higher
    #define MF_DEPRECATED_ATTRIBUTE __declspec(deprecated)
#else
    #define MF_DEPRECATED_ATTRIBUTE
#endif

// Log //
NS_MF_BEGIN //Start the MonsterFramework Namespace.

#ifdef MONSTERFRAMEWORK_DEBUG //MonsterFramework is in Debug mode.

    //Prototypes for the log functions. (Should not be used directly)
    void __not_to_direct_use_mf_log(const char *pPrefix, const char *pFormat, ...);

    //Just Log the message in Console.
    #define MF_LOG(_format_, ...) do { \
        mf::__not_to_direct_use_mf_log("MFLOG:", _format_, ##__VA_ARGS__); \
    } while(0)

    //Just print a new line.
    #define MF_LOG_NL() \
        mf::__not_to_direct_use_mf_log("","")

    //Log a message with a GREAT warning prefix.
    #define MF_LOG_WARNING(_format_, ...) do { \
        mf::__not_to_direct_use_mf_log("MFLOG [WARNING]:", \
                                       _format_,           \
                                       ##__VA_ARGS__);     \
    } while(0)

    //Log the message and exit.
    #define MF_LOG_ERROR(_format_, ...) do { \
        mf::__not_to_direct_use_mf_log("MFLOG [ERROR]:", \
                                       _format_,         \
                                       ##__VA_ARGS__);   \
        exit(1);                                         \
    } while(0)

    //Assertion.
    #define MF_ASSERT(_cond_, _msg_, ...) do { \
        if(!_cond_) {                                  \
            __not_to_direct_use_mf_log("MFASSERT:",    \
                                       _msg_,          \
                                       ##__VA_ARGS__); \
            abort();                                   \
        }                                              \
    } while(0)

    //Help log the cocos2d's objets that follows the MF_LOG_XXX
    //Point
    #define MF_LOG_POINT(_str_, _point_) \
        MF_LOG("Point (%s): x: %.2f y: %.2f", (_str_), (_point_).x, (_point_).y)
    //Rect
    #define MF_LOG_RECT(_str_, _rect_)                                    \
        MF_LOG("Rect (%s): (%.2f,%.2f)(%.2f,%.2f)", (_str_),              \
                                                    (_rect_).origin.x,    \
                                                    (_rect_).origin.y,    \
                                                    (_rect_).size.width,  \
                                                    (_rect_).size.height)

#else //MONSTERFRAMEWORK_DEBUG - MonsterFramework in Release mode.

    //Just Log the message in Console.
    #define MF_LOG(        _format_, ...     ) do {} while(0)
    #define MF_LOG_WARNING(_format_, ...     ) do {} while(0)
    #define MF_LOG_ERROR(  _format_, ...     ) do {} while(0)
    #define MF_ASSERT(     _cond_, _msg_, ...) do {} while(0)
    #define MF_LOG_POINT(  _str_, _point_    ) do {} while(0)
    #define MF_LOG_RECT(   _str_, _rect_     ) do {} while(0)

#endif //MONSTERFRAMEWORK_DEBUG

NS_MF_END
#endif // defined(__MonsterFramework_include_Utils_MonsterFramework_Utils_h__) //
