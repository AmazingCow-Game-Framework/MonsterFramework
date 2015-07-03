//----------------------------------------------------------------------------//
//                  _   _ ____   ___  ____                                    //
//                 | \ | |___ \ / _ \| __ )  ___  _   _ ____                  //
//                 |  \| | __) | | | |  _ \ / _ \| | | |_  /                  //
//                 | |\  |/ __/| |_| | |_) | (_) | |_| |/ /                   //
//                 |_| \_|_____|\___/|____/ \___/ \__, /___|                  //
//                                                |___/                       //
//                                                                            //
//                            Mateus Mesquita                                 //
//                       www.N2OBoyz.com/~n2omatt                             //
//                          N2OMatt@N2OBoyz.com                               //
//                                                                            //
//                   Copyright (C) 2015 Mateus Mesquita.                      //
//                       Copyright (C) 2015 N2OBoyz.                          //
//                                                                            //
//  This software is provided 'as-is', without any express or implied         //
//  warranty. In no event will the authors be held liable for any damages     //
//  arising from the use of this software.                                    //
//                                                                            //
//  Permission is granted to anyone to use this software for any purpose,     //
//  including commercial applications, and to alter it and redistribute it    //
//  freely, subject to the following restrictions:                            //
//                                                                            //
//  1. The origin of this software must not be misrepresented;                //
//     you must not claim that you wrote the original software.               //
//  2. If you use this software in a product, an acknowledgment in the        //
//     product IS HIGHLY APPRECIATED, both in source and binary forms.        //
//     If you will not acknowledge, just send me a email. We'll be VERY       //
//     happy to see our work being used by other people. :)                   //
//     (See opensource.N2OBoyz.com/acknowledgment.html for details).          //
//  3. Altered source versions must be plainly marked as such, and must not   //
//     be misrepresented as being the original software.                      //
//  4. This notice may not be removed or altered from any source              //
//     distribution.                                                          //
//  5. Most important, you must have fun. ;)                                  //
//                                                                            //
//       Visit OpenSource.N2OBoyz.com for more open-source projects.          //
//                                                                            //
//                            Enjoy :)                                        //
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
m_muted(false),
m_prevFxVol(m_pAudioEngine->getEffectsVolume())
{
    //Empty...
}
AudioManager::~AudioManager()
{
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
    
    m_muted = mute;
    MF_LOG("AudioManager - Audio is now %s", mute ? "Off" : "On");
}
bool AudioManager::isMuted()
{
    return m_muted;
}

//Effects
void AudioManager::loadEffect(const std::string &path)
{
#if MONSTERFRAMEWORK_DEBUG
    //In Debug mode check if file exists, and if not emit a warning about that.
    //In Release mode do nothing.
    auto fileExits = CCFileUtils::sharedFileUtils()->isFileExist(path.c_str());
    if(!fileExits)
        MF_LOG_WARNING("Audio Manager - Cannot load effect file [PATH:(%s)]", path.c_str());
#endif
    
    m_effects[path] = -1;
    m_pAudioEngine->preloadEffect(path.c_str());
    
    MF_LOG("AudioManager - LoadEffect: (%s)", path.c_str());
}
void AudioManager::loadEffect(const std::vector<std::string> &list)
{
    for (auto &pair : list)
        loadEffect(pair);
}
void AudioManager::unloadEffect(const std::string &name)
{
    m_pAudioEngine->unloadEffect(name.c_str());
    m_effects.erase(name);
}

void AudioManager::playEffect(const std::string &name, bool loop)
{
    
#if MONSTERFRAMEWORK_DEBUG
    auto it = m_effects.find(name);
    if(it == m_effects.end())
        MF_LOG_WARNING("Audio Manager - Effects file is not loaded:(%s)", name.c_str());
#endif    

    int id = m_pAudioEngine->playEffect(name.c_str(), loop);
    m_effects[name] = id;
    
    MF_LOG("AudioManager - Playing Effect:(%s) - ID:(%d)", name.c_str(), id);
}
void AudioManager::pauseEffect(const std::string &name)
{
    m_pAudioEngine->pauseEffect(m_effects[name]);
}
void AudioManager::pauseAllEffects()
{
    m_pAudioEngine->pauseAllEffects();
}
void AudioManager::resumeEffect(const std::string &name)
{
    m_pAudioEngine->resumeEffect(m_effects[name]);
}
void AudioManager::resumeAllEffects()
{
    m_pAudioEngine->resumeAllEffects();
}
void AudioManager::stopEffect(const std::string &name)
{
    m_pAudioEngine->stopEffect(m_effects[name]);
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
