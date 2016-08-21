//----------------------------------------------------------------------------//
// █  █   //
// ████████   //
//   ████ //
//  ███  █  █  ███AudioManager.cpp//
//  █ ██ █MonsterFramework//
//   ████████████ //
// █  █   Copyright (c) 2015 AmazingCow   //
//█ ██ █  www.AmazingCow.com  //
//█ ██ █  //
// █  █   N2OMatt - n2omatt@amazingcow.com//
//   ████████████ www.amazingcow.com/n2omatt  //
////
////
//  This software is licensed as BSD-3//
// CHECK THE COPYING FILE TO MORE DETAILS //
////
//Permission is granted to anyone to use this software for any purpose,   //
//   including commercial applications, and to alter it and redistribute it   //
//   freely, subject to the following restrictions:   //
////
// 0. You **CANNOT** change the type of the license.  //
// 1. The origin of this software must not be misrepresented; //
//you must not claim that you wrote the original software.//
// 2. If you use this software in a product, an acknowledgment in the //
//product IS HIGHLY APPRECIATED, both in source and binary forms. //
//(See opensource.AmazingCow.com/acknowledgment.html for details).//
//If you will not acknowledge, just send us a email. We'll be //
//*VERY* happy to see our work being used by other people. :) //
//The email is: acknowledgmentopensource@AmazingCow.com   //
// 3. Altered source versions must be plainly marked as such, //
//and must notbe misrepresented as being the original software.   //
// 4. This notice may not be removed or altered from any source   //
//distribution.   //
// 5. Most important, you must have fun. ;)   //
////
//  Visit opensource.amazingcow.com for more open-source projects.//
////
//  Enjoy :)  //
//----------------------------------------------------------------------------//

//Header
#include "MonsterFramework/include/Audio/AudioManager.h"
//Cocos2dx
#include "AudioEngine.h"

//Usings
USING_NS_STD_CC_CD_MF


////////////////////////////////////////////////////////////////////////////////
// MACROS                                                                     //
////////////////////////////////////////////////////////////////////////////////
#define _AE cc::experimental::AudioEngine

#define _CHECK_AND_WARN_IF_EXISTS(_msg_fmt_, _container_, _sound_id_) \
    if(_container_.find(_sound_id_) != std::end(_container_))         \
    {                                                                 \
        MF_LOG_WARNING(                                               \
            _msg_fmt_,                                                \
            _sound_id_.c_str(),                                       \
            _container_[_sound_id_].filepath.c_str()                  \
        );                                                            \
        return;                                                       \
    }

#define _CHECK_AND_WARN_IF_NOT_EXISTS(_msg_fmt_, _container_, _sound_id_, ...) \
    if(_container_.find(_sound_id_) == std::end(_container_))                  \
    {                                                                          \
        MF_LOG_WARNING(                                                        \
            _msg_fmt_,                                                         \
            _sound_id_.c_str()                                                 \
        );                                                                     \
        return __VA_ARGS__;                                                \
    }

#define _CHECK_AND_WARN_IF_INVALID_ID(_msg_fmt_, _container_, _sound_id_, ...) \
    if(_container_[_sound_id_].currInternalId == AudioManager::kInvalidId)\
    {                                                                          \
        MF_LOG_WARNING(                                                        \
            _msg_fmt_,                                                         \
            _sound_id_.c_str()                                                 \
        );                                                                     \
        return __VA_ARGS__;                                                    \
    }

////////////////////////////////////////////////////////////////////////////////
// Singleton                                                                  //
////////////////////////////////////////////////////////////////////////////////
AudioManager::AudioManager()
{
    //Empty...
}

AudioManager::~AudioManager()
{
    //Empty..
}


////////////////////////////////////////////////////////////////////////////////
// General                                                                    //
////////////////////////////////////////////////////////////////////////////////
void AudioManager::muteAll(bool b)
{
    //COWTODO: Implement.
}

bool AudioManager::isMuted()
{
    //COWTODO: Implement.
}



////////////////////////////////////////////////////////////////////////////////
// Effects//
////////////////////////////////////////////////////////////////////////////////
//Load / Unload
void AudioManager::loadEffect(const std::string &effectId,
                              const std::string &path,
                              bool ignoreIfAlreadyLoaded)
{
    if(!ignoreIfAlreadyLoaded)
    {
        _CHECK_AND_WARN_IF_EXISTS(
            "AudioManager::loadEffect - Already preloaded: EffectId (%s) Path (%s)",
            m_effectMap,
            effectId
        );
    }

    _AE::preload(path);

    auto p = std::make_pair(
        effectId,
        Sound { AudioManager::kInvalidId, path }
    );
    m_effectMap.insert(p);
}

void AudioManager::unloadEffect(const std::string &effectId)
{
    _CHECK_AND_WARN_IF_NOT_EXISTS(
        "AudioManager::unloadEffect - EffectId is not loaded: (%s)",
        m_effectMap,
        effectId
    );

    _AE::uncache(m_effectMap[effectId].filepath);
    m_effectMap.erase(effectId);
}


//Play / Pause
//COWTODO: Make the signature equal to the playMusic
void AudioManager::playEffect(const std::string &effectId,
                              bool loop /* = false */)
{
    _CHECK_AND_WARN_IF_NOT_EXISTS(
        "AudioManager::playEffect - Effect is not loaded: (%s)",
        m_effectMap,
        effectId
    );

    //Get the sound info object.
    auto& sound = m_effectMap[effectId];

    //Upadte the current internal id.
    sound.currInternalId = _AE::play2d(sound.filepath, loop, 1.0f);
}


void AudioManager::pauseEffect(const std::string &effectId)
{
    //COWTODO: Implement.
}

void AudioManager::pauseAllEffects()
{
    //COWTODO: Implement.
}


//Resume
void AudioManager::resumeEffect(const std::string &effectId)
{
    //COWTODO: Implement.
}

void AudioManager::resumeAllEffects()
{
    //COWTODO: Implement.
}


//Stop
void AudioManager::stopEffect(const std::string &effectId)
{
    //COWTODO: Implement.
}

void AudioManager::stopAllEffects()
{
    //COWTODO: Implement.
}


//Query
float AudioManager::getEffectsVolume() const
{
    //COWTODO: Implement.
}

void AudioManager::setEffectsVolume(float volume)
{
    //COWTODO: Implement.
}



////////////////////////////////////////////////////////////////////////////////
// Music  //
////////////////////////////////////////////////////////////////////////////////
//Load / Unload
void AudioManager::loadMusic(const std::string &musicId, const std::string &path)
{
    _CHECK_AND_WARN_IF_EXISTS(
        "AudioManager::loadMusic - Already preloaded: MusicId (%s) Path (%s)",
        m_musicMap,
        musicId
    );

    _AE::preload(path);
    m_musicMap.insert(std::make_pair(musicId, Sound{AudioManager::kInvalidId, path}));
}

void AudioManager::unloadMusic(const std::string &musicId)
{
    _CHECK_AND_WARN_IF_NOT_EXISTS(
        "AudioManager::unloadMusic - MusicId is not loaded: (%s)",
        m_musicMap,
        musicId
    );

    _AE::uncache(m_musicMap[musicId].filepath);
    m_musicMap.erase(musicId);
}


//Play / Pause / Resume / Stop
void AudioManager::playMusic(
        const std::string &musicId,
        float volume /* = 1.0f  */,
        bool  loop   /* = false */,
        const MusicFinishCallback &callback /*= MusicFinishCallback() */
)
{
    _CHECK_AND_WARN_IF_NOT_EXISTS(
        "AudioManager::playMusic - MusicId is not loaded: (%s)",
        m_musicMap,
        musicId
    );

    if(isPlayingMusic(musicId))
    {
        MF_LOG_WARNING(
            "AudioManager::playMusic - Already playing MusicId: (%s)",
            musicId.c_str()
        );
        return;
    }

    //Get the sound info object.
    auto& sound = m_musicMap[musicId];

    //Upadte the current internal id.
    sound.currInternalId = _AE::play2d(sound.filepath, loop, volume);

    //Set the callback if needed.
    if(callback)
    {
        _AE::setFinishCallback(sound.currInternalId,
                               [musicId, callback](int, const std::string &){
            callback(musicId);
        });
    }
}


void AudioManager::pauseMusic(const std::string &musicId)
{
    _CHECK_AND_WARN_IF_NOT_EXISTS(
        "AudioManager::pauseMusic - MusicId is not loaded: (%s)",
        m_musicMap,
        musicId
    );

    _AE::pause(m_musicMap[musicId].currInternalId);
}

void AudioManager::resumeMusic(const std::string &musicId)
{
    _CHECK_AND_WARN_IF_NOT_EXISTS(
        "AudioManager::resumeMusic - MusicId is not loaded: (%s)",
        m_musicMap,
        musicId
    );

    _AE::resume(m_musicMap[musicId].currInternalId);
}

void AudioManager::stopMusic(const std::string &musicId,
                             bool unload /* = false */)
{
    _CHECK_AND_WARN_IF_NOT_EXISTS(
        "AudioManager::stopMusic - MusicId is not loaded: (%s)",
        m_musicMap,
        musicId
    );

    _AE::stop(m_musicMap[musicId].currInternalId);
    if(unload)
        unloadMusic(musicId);
}


//Music Time
float AudioManager::getMusicTotalTime(const std::string &musicId)
{
    _CHECK_AND_WARN_IF_NOT_EXISTS(
        "AudioManager::getMusicTotalTime - MusicId is not loaded: (%s)",
        m_musicMap,
        musicId,
        AudioManager::kInvalidTime
    );

    _CHECK_AND_WARN_IF_INVALID_ID(
        "AudioManager::getMusicTotalTime - MusicId (%s) has invalid internal, perhaps you did forget to play it",
        m_musicMap,
        musicId,
        AudioManager::kInvalidTime
    );

    return _AE::getDuration(m_musicMap[musicId].currInternalId);
}

float AudioManager::getMusicCurrentTime(const std::string &musicId)
{
    _CHECK_AND_WARN_IF_NOT_EXISTS(
        "AudioManager::getMusicCurrentTime - MusicId is not loaded: (%s)",
        m_musicMap,
        musicId,
        AudioManager::kInvalidTime
    );

    _CHECK_AND_WARN_IF_INVALID_ID(
        "AudioManager::getMusicCurrentTime - MusicId (%s) has invalid internal, perhaps you did forget to play it",
        m_musicMap,
        musicId,
        AudioManager::kInvalidTime
    );

    return _AE::getCurrentTime(m_musicMap[musicId].currInternalId);
}

void AudioManager::setMusicCurrentTime(const std::string &musicId, float time)
{
    _CHECK_AND_WARN_IF_NOT_EXISTS(
        "AudioManager::setMusicCurrentTime - MusicId is not loaded: (%s)",
        m_musicMap,
        musicId
    );

    _CHECK_AND_WARN_IF_INVALID_ID(
        "AudioManager::setMusicCurrentTime - MusicId (%s) has invalid internal, perhaps you did forget to play it",
        m_musicMap,
        musicId
    );

    _AE::setCurrentTime(m_musicMap[musicId].currInternalId, time);
}


//Query
bool AudioManager::isPlayingMusic(const string &musicId)
{
    _CHECK_AND_WARN_IF_NOT_EXISTS(
        "AudioManager::isPlayingMusic - MusicId is not loaded: (%s)",
        m_musicMap,
        musicId,
        false
    );

    auto internalId = m_musicMap[musicId].currInternalId;
    return _AE::getState(internalId) == _AE::AudioState::PLAYING;
}

float AudioManager::getMusicVolume() const
{
    //COWTODO: Implement.
}

void AudioManager::setMusicVolume(float volume)
{
    //COWTODO: Implement.
}
