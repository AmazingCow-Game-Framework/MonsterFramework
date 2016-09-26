
#ifndef __MonsterFramework_include_Utils_Macros_MonsterFramework_Log_h__
#define __MonsterFramework_include_Utils_Macros_MonsterFramework_Log_h__

//MonsterFramework
#include "MonsterFramework_Namespaces.h"

////////////////////////////////////////////////////////////////////////////////
// MonsterFramework is in DEBUG mode                                          //
////////////////////////////////////////////////////////////////////////////////
#ifdef MONSTERFRAMEWORK_DEBUG

//Internal use.
//COWTODO: Comment better.
NS_MF_BEGIN
void _mf_log_print(const char *pPrefix,
                   const char *pMsg,
                   ...);
NS_MF_END

// Log //
#define MF_LOG_EX(_prefix_, _msg_, ...) \
    mf::_mf_log_print(_prefix_, _msg_, ##__VA_ARGS__)

#define MF_LOG(_msg_, ...) \
    mf::_mf_log_print("", _msg_, ##__VA_ARGS__)


// Warning //
#define MF_LOG_WARNING_EX(_prefix_, _msg_, ...)           \
    mf::_mf_log_print(                                    \
        (std::string("[Warning] - ") + _prefix_).c_str(), \
        _msg_,                                            \
        ##__VA_ARGS__                                     \
    )

#define MF_LOG_WARNING(_msg_, ...) \
    mf::_mf_log_print("[Warning] - ", _msg_, ##__VA_ARGS__)


// Error //
#define MF_LOG_ERROR_EX(_prefix_, _msg_, ...)               \
    do {                                                    \
        mf::_mf_log_print(                                  \
            (std::string("[Error] - ") + _prefix_).c_str(), \
            _msg_,                                          \
            ##__VA_ARGS__                                   \
        );                                                  \
        abort();                                            \
    } while(0)

#define MF_LOG_ERROR(_msg_, ...)                              \
    do {                                                      \
        mf::_mf_log_print("[Error] - ", _msg_, ##__VA_ARGS__) \
    while(0)


////////////////////////////////////////////////////////////////////////////////
// MonsterFramework is in RELEASE mode                                        //
////////////////////////////////////////////////////////////////////////////////
#else //!MONSTERFRAMEWORK_DEBUG

// Log //
#define MF_LOG_EX(_prefix_, _msg_, ...) void(0)
#define MF_LOG(_msg_, ...) void(0)

// Warning //
#define MF_LOG_WARNING_EX(_prefix_, _msg_, ...) void(0)
#define MF_LOG_WARNING(_msg_, ...) void(0)

// Error //
#define MF_LOG_ERROR_EX(_prefix_, _msg_, ...) void(0)
#define MF_LOG_ERROR(_msg_, ...) void(0)


#endif //MONSTERFRAMEWORK_DEBUG
#endif // defined(__MonsterFramework_include_Utils_Macros_MonsterFramework_Log_h__)
