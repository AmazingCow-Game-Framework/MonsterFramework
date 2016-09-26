
#ifndef __MonsterFramework_include_Utils_Macros_MonsterFramework_Assert_h__
#define __MonsterFramework_include_Utils_Macros_MonsterFramework_Assert_h__

//MonsterFramework
#include "MonsterFramework_Namespaces.h"


////////////////////////////////////////////////////////////////////////////////
// MonsterFramework is in DEBUG mode                                          //
////////////////////////////////////////////////////////////////////////////////
#ifdef MONSTERFRAMEWORK_DEBUG

//Internal use.
//COWTODO: Comment better.
NS_MF_BEGIN
void _mf_assert_print(const char   *pExpr,
                      const char   *pFile,
                      unsigned int line,
                      const char   *pFunc,
                      const char   *pPrefix,
                      const char   *pMsg,
                      ...);
NS_MF_END

#define MF_ASSERT_EX(_cond_, _prefix_, _msg_, ...) \
    if(!(_cond_)) {                                \
        mf::_mf_assert_print(                      \
            #_cond_,                               \
            __FILE__,                              \
            __LINE__,                              \
            __PRETTY_FUNCTION__,                   \
            _prefix_,                              \
            _msg_,                                 \
            ##__VA_ARGS__                          \
        );                                         \
    }

#define MF_ASSERT(_cond_, _msg_, ...) \
    MF_ASSERT_EX(_cond_, "", _msg_, ##__VA_ARGS__);

////////////////////////////////////////////////////////////////////////////////
// MonsterFramework is in RELEASE mode                                        //
////////////////////////////////////////////////////////////////////////////////
#else //!MONSTERFRAMEWORK_DEBUG
#define MF_ASSERT_EX(_cond_, _prefix_, _msg_, ...) void(0);
#define MF_ASSERT(_cond_, _msg_, ...) void(0);

#endif //MONSTERFRAMEWORK_DEBUG
#endif // __MonsterFramework_include_Utils_Macros_MonsterFramework_Assert_h__
