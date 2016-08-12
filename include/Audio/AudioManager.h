//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        AudioManager.h                            //
//            █ █        █ █        MonsterFramework                          //
//             ████████████                                                   //
//           █              █       Copyright (c) 2015, 2016                  //
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

#ifndef __MonsterFramework_include_Audio_AudioManager_h__
#define __MonsterFramework_include_Audio_AudioManager_h__

//std
#include <map>
#include <string>
#include <utility>
#include <vector>
//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"


NS_MF_BEGIN

class AudioManager
{
    // Inner Types //
private:
    struct Sound {
        int currInternalId;
        std::string filepath;
    };


    // Enums / Constants / Typedefs //
public:
    typedef std::function<void (const std::string &)> EffectFinishCallback;
    typedef std::function<void (const std::string &)> MusicFinishCallback;

    const static int kInvalidId   = -123456789;
    const static int kInvalidTime = -987654321;

private:
    typedef std::map<std::string, Sound> SoundMap;


    // Singleton //
public:
    SINGLETON_OF(AudioManager);
private:
     AudioManager();
    ~AudioManager();


    // General //
public:
    void muteAll(bool b);
    bool isMuted();


    // Effects //
private:
    //Load / Unload
    void loadEffect  (const std::string &effectId, const std::string &path);
    void unloadEffect(const std::string &effectId);

    //Play / Pause
    void playEffect(const std::string &effectId, bool loop = false);

    void pauseEffect(const std::string &effectId);
    void pauseAllEffects();

    //Resume
    void resumeEffect(const std::string &effectId);
    void resumeAllEffects();

    //Stop
    void stopEffect(const std::string &effectId);
    void stopAllEffects();

    //Query
    float getEffectsVolume() const;
    void  setEffectsVolume(float volume);


    // Music //
public:
    //Load / Unload
    void loadMusic  (const std::string &musicId, const std::string &path);
    void unloadMusic(const std::string &musicId);

    //Play / Pause / Resume / Stop
    void playMusic(const std::string &musicId,
                   float volume = 1.0f,
                   bool  loop   = false,
                   const MusicFinishCallback &callback = MusicFinishCallback());

    void pauseMusic (const std::string &musicId);
    void resumeMusic(const std::string &musicId);
    void stopMusic  (const std::string &musicId, bool unload = false);

    //Music Time
    float getMusicTotalTime  (const std::string &musicId);
    float getMusicCurrentTime(const std::string &musicId);
    void  setMusicCurrentTime(const std::string &musicId, float time);

    //Query
    bool isPlayingMusic(const std::string &musicId);

    float getMusicVolume() const;
    void  setMusicVolume(float volume);

    // iVars //
private:
    SoundMap m_musicMap;

}; //class AudioManager

NS_MF_END
#endif // defined(__MonsterFramework_include_Audio_AudioManager_h__) //
