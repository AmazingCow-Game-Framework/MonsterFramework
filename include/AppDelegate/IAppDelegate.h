//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        IAppDelegate.h                            //
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

#ifndef  __MonsterFramework_include_AppDelegate_IAppDelegate_h__
#define  __MonsterFramework_include_AppDelegate_IAppDelegate_h__

//std
#include <string>
//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"

NS_MF_BEGIN

class IAppDelegate :
    public cc::Application
{
    // CTOR / DTOR //
public:
    IAppDelegate(const std::string &gameCaption, int fps, bool showStats);
    virtual ~IAppDelegate();


    // Init //
public:
    virtual cc::Scene* getInitialScene() = 0;

    virtual void initGLContextAttrs() override;


    // Lifecycle //
public:
    virtual bool applicationDidFinishLaunching () override;
    virtual void applicationDidEnterBackground () override;
    virtual void applicationWillEnterForeground() override;


    // Getters //
public:
    const cc::Size& getScreenSize             () const;
    float           getScreenRatio            () const;
    const cc::Size& getBestFitDesignResolution() const;

    const std::string& getSpriteSheetSufix  () const;
    const float        getContentScaleFactor() const;


    // Private Methods //
private:
    void createGLView();
    void findBestFitDeviceResolutionSize();


    // iVars //
private:
    std::string m_gameCaption;
    int         m_fps;
    int         m_showStats;

    cc::Size m_deviceScreenSize;
    float    m_deviceScreenRatio;
    cc::Size m_bestFitDesignResolution;

    float       m_scaleFactor;
    std::string m_spriteSheetSufix;
};

NS_MF_END
#endif // __MonsterFramework_include_AppDelegate_IAppDelegate_h__

