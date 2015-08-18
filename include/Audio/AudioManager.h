//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    AudioManager.h                              //
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

#ifndef __MonsterFramework_include_Audio_AudioManager_h__
#define __MonsterFramework_include_Audio_AudioManager_h__

//std
#include <string>
#include <vector>
#include <map>
#include <utility>
//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"

NS_MF_BEGIN

class AudioManager
{
    // Enums/Constants/Typedefs //
private:

    // Singleton //
public:
    static AudioManager* instance();

    // CTOR/DTOR //
private:
    AudioManager();
    virtual ~AudioManager();

    // Public Methods //
public:
    //General
    void muteAll(bool b);
    bool isMuted();

    //Effects
    void loadEffect(const std::string &effectId, const std::string &path);
    void unloadEffect(const std::string &effectId);

    void playEffect(const std::string &effectId, bool loop = false);

    void pauseEffect(const std::string &effectId);
    void pauseAllEffects();

    void resumeEffect(const std::string &effectId);
    void resumeAllEffects();

    void stopEffect(const std::string &effectId);
    void stopAllEffects();

    float getEffectsVolume();
    void setEffectsVolume(float volume);

    // Private Methods //
private:

    // iVars //
private:
    cd::SimpleAudioEngine      *m_pAudioEngine;
    //COWTODO: typedef it.
    std::map<std::string, std::pair<std::string, int>> m_effectsMap;

    float m_prevFxVol;
}; //class AudioManager

NS_MF_END
#endif // defined(__MonsterFramework_include_Audio_AudioManager_h__) //
