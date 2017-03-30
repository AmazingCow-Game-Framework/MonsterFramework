//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        IAppDelegate.cpp                          //
//            █ █        █ █        MonsterFramework                          //
//             ████████████                                                   //
//           █              █       Copyright (c) 2017                        //
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

//Header
#include "MonsterFramework/include/AppDelegate/IAppDelegate.h"
//MonsterFramework
#include "MonsterFramework/include/Platform/Application.h"
#include "MonsterFramework/include/Platform/Device.h"

//Usings
USING_NS_STD_CC_CD_MF;


////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
const static auto kDesignResolutionSize_4_3  = cc::Size(1536, 2048);
const static auto kDesignResolutionSize_16_9 = cc::Size(1080, 1920);

constexpr auto kSizeRatio_4_3  = (2048.0f / 1536.0f);
constexpr auto kSizeRatio_16_9 = (1920.0f / 1080.0f);

constexpr auto kHighScale   = 1.0f;
constexpr auto kMediumScale = 0.5f;
constexpr auto kSmallScale  = 0.3f;
constexpr auto kHighSuffix   = "hd";
constexpr auto kMediumSuffix = "md";
constexpr auto kSmallSuffix  = "sd";


////////////////////////////////////////////////////////////////////////////////
// Helper Functions                                                           //
////////////////////////////////////////////////////////////////////////////////
cc::GLViewImpl* create_glview_desktop(std::string &caption, cc::Size bestFit)
{
    return GLViewImpl::createWithRect(
        caption,
        cc::Rect(
            0, 0,
            bestFit.width  / 3,
            bestFit.height / 3
        )
    );
}

cc::GLViewImpl* create_glview_mobile(const std::string &caption)
{
    return GLViewImpl::create(caption);
}



////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
IAppDelegate::IAppDelegate(const std::string &gameCaption,int fps, bool showStats) :
    m_gameCaption(gameCaption),
    m_fps        (fps        ),
    m_showStats  (showStats  )
{
    //Empty...
}

IAppDelegate::~IAppDelegate()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Init                                                                       //
////////////////////////////////////////////////////////////////////////////////
void IAppDelegate::initGLContextAttrs()
{
    //Let alone from cocos2dx template.
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}


////////////////////////////////////////////////////////////////////////////////
// Lifecycle methods                                                          //
////////////////////////////////////////////////////////////////////////////////
bool IAppDelegate::applicationDidFinishLaunching()
{
    //Calculate the Best Fit Design Resolution.
    m_deviceScreenSize  = mf::Device::getScreenSize     ();
    m_deviceScreenRatio = mf::Device::getScreenSizeRatio();

    findBestFitDeviceResolutionSize();

    auto pDirector = cc::Director::getInstance();
    createGLView();

    //Setup Director.
    pDirector->setAnimationInterval(1.0f / m_fps);
    pDirector->setDisplayStats     (m_showStats );

    //Set the content factor and sprite sheet name.
    auto frameSize = pDirector->getOpenGLView()->getFrameSize();
    auto scale     = std::min(
        frameSize.width  / m_bestFitDesignResolution.width,
        frameSize.height / m_bestFitDesignResolution.height
    );

    m_scaleFactor      = kHighScale;
    m_spriteSheetSufix = kHighSuffix;
    if(scale < kHighScale)
    {
        m_scaleFactor      = kMediumScale;
        m_spriteSheetSufix = kMediumSuffix;
    }
    if(scale < kSmallScale)
    {
        m_scaleFactor      = kSmallScale;
        m_spriteSheetSufix = kSmallSuffix;
    }

    pDirector->setContentScaleFactor(m_scaleFactor);

    //To make the cards flip correctly.
    pDirector->setProjection(cc::Director::Projection::_2D);;

    //Start the game.
    pDirector->runWithScene(getInitialScene());

    return true;
}

void IAppDelegate::applicationDidEnterBackground()
{
    MF_LOG("AppDelegate::applicationDidEnterBackground");
    cc::Director::getInstance()->stopAnimation();
}

void IAppDelegate::applicationWillEnterForeground()
{
    MF_LOG("AppDelegate::applicationWillEnterForeground");
    cc::Director::getInstance()->startAnimation();
}


////////////////////////////////////////////////////////////////////////////////
// Getters                                                                    //
////////////////////////////////////////////////////////////////////////////////
const cc::Size& IAppDelegate::getScreenSize() const
{
    return m_deviceScreenSize;
}

float IAppDelegate::getScreenRatio() const
{
    return m_deviceScreenRatio;
}

const Size &IAppDelegate::getBestFitDesignResolution() const
{
    return m_bestFitDesignResolution;
}

const std::string& IAppDelegate::getSpriteSheetSufix() const
{
    return m_spriteSheetSufix;
}

const float IAppDelegate::getContentScaleFactor() const
{
    return m_scaleFactor;
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
void IAppDelegate::createGLView()
{
    //Desktop
    #if( CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_MAC )
        auto pGLView = create_glview_desktop(m_gameCaption, m_bestFitDesignResolution);
    //Mobile
    #else
        auto pGLView = create_glview_mobile(m_gameCaption);
    #endif // #if( CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_MAC )

    MF_ASSERT_EX(
        pGLView != nullptr,
        "IAppDelegate::createGLView",
        "Failed to create GLView"
    );

    cc::Director::getInstance()->setOpenGLView(pGLView);

    //Set the design resolution.
    pGLView->setDesignResolutionSize(
        m_bestFitDesignResolution.width,
        m_bestFitDesignResolution.height,
        ResolutionPolicy::SHOW_ALL
    );
}

void IAppDelegate::findBestFitDeviceResolutionSize()
{
    if(std::abs(m_deviceScreenRatio - kSizeRatio_4_3) < std::abs(m_deviceScreenRatio - kSizeRatio_16_9))
        m_bestFitDesignResolution = kDesignResolutionSize_4_3;
    else
        m_bestFitDesignResolution = kDesignResolutionSize_16_9;
}
