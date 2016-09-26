
#ifndef __MonsterFramework_include_Utils_Macros_MonsterFramework_Macros_h__
#define __MonsterFramework_include_Utils_Macros_MonsterFramework_Macros_h__

//MonsterFramework
#include "MonsterFramework_Namespaces.h"
#include "MonsterFramework_Disallow.h"


////////////////////////////////////////////////////////////////////////////////
// Singleton                                                                  //
////////////////////////////////////////////////////////////////////////////////
#define SINGLETON_OF(__type__)         \
    static __type__ *instance() {      \
        static __type__ t;             \
        return &t;                     \
}                                      \
MF_DISALLOW_COPY_MOVE_ASSIGNS(__type__)


////////////////////////////////////////////////////////////////////////////////
// ONLY IN DEBUG                                                              //
////////////////////////////////////////////////////////////////////////////////
#ifdef MONSTERFRAMEWORK_DEBUG
    #define MF_ONLY_IN_DEBUG(_code_) { _code_ }
#else //!MONSTERFRAMEWORK_DEBUG
    #define MF_ONLY_IN_DEBUG(_code_) void(0);
#endif //MONSTERFRAMEWORK_DEBUG


#endif // defined(__MonsterFramework_include_Utils_Macros_MonsterFramework_Macros_h__)
