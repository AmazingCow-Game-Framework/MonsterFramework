//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    AudioManager.cpp                            //
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

//Header
#include "MonsterFramework/include/Audio/AudioManager.h"

//Usings
USING_NS_STD_CC_CD_MF

// Singleton //
AudioManager* AudioManager::instance()
{
    static AudioManager s_instance;
    return &s_instance;
}

// CTOR/DTOR //
AudioManager::AudioManager() :
    m_pAudioEngine(SimpleAudioEngine::getInstance()),
    m_prevFxVol(m_pAudioEngine->getEffectsVolume())
{
    //Empty...
}
AudioManager::~AudioManager()
{
    //Release the SimpleAudioEngine.
    SimpleAudioEngine::end();
}

// Public Methods //
//General
void AudioManager::muteAll(bool mute)
{
    if(mute)
    {
        //Save the current volumes to later restore.
        m_prevFxVol  = getEffectsVolume();
        setEffectsVolume(0);
    }
    else
    {
        //Restore the previous volumes.
        setEffectsVolume(m_prevFxVol);
    }

    MF_LOG("AudioManager - Audio is now %s", mute ? "Off" : "On");
}
bool AudioManager::isMuted()
{
    return getEffectsVolume() == 0;
}

//Effects
void AudioManager::loadEffect(const std::string &effectId, const std::string &path)
{
    //COWTODO: Create and encapsulate the following code in something like MF_ONLY_IN_DEBUG({...});
#if MONSTERFRAMEWORK_DEBUG
    //In Debug mode check if file exists...
    auto fileExists = FileUtils::getInstance()->isFileExist(path.c_str());
    MF_ASSERT(fileExists, "Audio Manager - Cannot load effect file [PATH:(%s)]", path.c_str());
#endif

    //Insert a default invalid id into effects map with effectId key.
    m_effectsMap[effectId] = make_pair(path, -1);
    m_pAudioEngine->preloadEffect(path.c_str());

    MF_LOG("AudioManager - LoadEffect: (%s)", path.c_str());
}
void AudioManager::unloadEffect(const std::string &effectId)
{
    //COWTODO: Create and encapsulate the following code in something like MF_ONLY_IN_DEBUG({...});
    //Check if effectId is valid.
    auto it = m_effectsMap.find(effectId);
    MF_ASSERT((it != end(m_effectsMap)), "Audio Manager - Invalid EffectId %s", effectId.c_str());

    //Remove the effect from audio engine and delete it from effects map.
    m_pAudioEngine->unloadEffect(it->second.first.c_str());
    m_effectsMap.erase(effectId);
}

void AudioManager::playEffect(const std::string &effectId, bool loop /* = false */)
{
    //Get the iterator for effectId.
    auto it = m_effectsMap.find(effectId);

    //COWTODO: Create and encapsulate the following code in something like MF_ONLY_IN_DEBUG({...});
#if MONSTERFRAMEWORK_DEBUG
    //In Debug mode check if file exists...
    MF_ASSERT((it != m_effectsMap.end()), "Audio Manager - EffectId is not loaded:(%s)", effectId.c_str());
#endif

    //Play effect and update its engine id.
    int id = m_pAudioEngine->playEffect(it->second.first.c_str(), loop);
    m_effectsMap[effectId].second = id;

    //Log
    MF_LOG("AudioManager - Playing Effect:(%s) - EngineId:(%d)", effectId.c_str(), id);
}
void AudioManager::pauseEffect(const std::string &effectId)
{
    //Get the iterator for effectId.
    auto it = m_effectsMap.find(effectId);

    //COWTODO: Create and encapsulate the following code in something like MF_ONLY_IN_DEBUG({...});
#if MONSTERFRAMEWORK_DEBUG
    //In Debug mode check if file exists...
    MF_ASSERT((it != m_effectsMap.end()), "Audio Manager - EffectId is not loaded:(%s)", effectId.c_str());
#endif

    m_pAudioEngine->pauseEffect(it->second.second);
}
void AudioManager::pauseAllEffects()
{
    m_pAudioEngine->pauseAllEffects();
}
void AudioManager::resumeEffect(const std::string &effectId)
{
    //Get the iterator for effectId.
    auto it = m_effectsMap.find(effectId);

    //COWTODO: Create and encapsulate the following code in something like MF_ONLY_IN_DEBUG({...});
#if MONSTERFRAMEWORK_DEBUG
    //In Debug mode check if file exists...
    MF_ASSERT((it != m_effectsMap.end()), "Audio Manager - EffectId is not loaded:(%s)", effectId.c_str());
#endif

    m_pAudioEngine->resumeEffect(it->second.second);
}
void AudioManager::resumeAllEffects()
{
    m_pAudioEngine->resumeAllEffects();
}
void AudioManager::stopEffect(const std::string &effectId)
{
    //Get the iterator for effectId.
    auto it = m_effectsMap.find(effectId);

    //COWTODO: Create and encapsulate the following code in something like MF_ONLY_IN_DEBUG({...});
#if MONSTERFRAMEWORK_DEBUG
    //In Debug mode check if file exists...
    MF_ASSERT((it != m_effectsMap.end()), "Audio Manager - EffectId is not loaded:(%s)", effectId.c_str());
#endif

    m_pAudioEngine->stopEffect(it->second.second);
}
void AudioManager::stopAllEffects()
{
    m_pAudioEngine->stopAllEffects();
}

float AudioManager::getEffectsVolume()
{
    return m_pAudioEngine->getEffectsVolume();
}
void AudioManager::setEffectsVolume(float volume)
{
    m_pAudioEngine->setEffectsVolume(volume);
}
