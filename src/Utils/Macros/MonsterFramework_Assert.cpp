
// Only compile this file in debug mode.
#ifdef MONSTERFRAMEWORK_DEBUG

//Header
#include "MonsterFramework/include/Utils/Macros/MonsterFramework_Log.h"

//Usings
USING_NS_STD_CC_CD_MF;

NS_MF_BEGIN

void _mf_assert_print(const char   *pExpr,
                      const char   *pFile,
                      unsigned int line,
                      const char   *pFunc,
                      const char   *pPrefix,
                      const char   *pMsg,
                      ...)
{
    //COWTODO: Implement.
}

NS_MF_END
#endif //MONSTERFRAMEWORK_DEBUG
