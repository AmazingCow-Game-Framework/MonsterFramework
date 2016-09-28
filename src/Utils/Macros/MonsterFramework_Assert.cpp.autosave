
// Only compile this file in debug mode.
#ifdef MONSTERFRAMEWORK_DEBUG

//Header
#include "MonsterFramework/include/Utils/Macros/MonsterFramework_Log.h"
//std
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
//MonsterFramework
#include "MonsterFramework/src/Utils/private/_mf_print.h"

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
    va_list args;
    va_start(args, pMsg);

    constexpr int kBufferSize = 1024;
    char buffer[kBufferSize]  = { '\0' };

    vsnprintf(buffer, kBufferSize, pMsg, args);

    va_end(args);

    _mf_error_printf(
        "MF_ASSERT: assertion failed on: \n \
        file       : %s \n \
        line       : %d \n \
        function   : %s \n \
        expression : %s \n \
        prefix     : %s \n \
        message    : %s \n",
        pFile,
        line,
        pFunc,
        pExpr,
        pPrefix,
        buffer
    );
}

NS_MF_END
#endif //MONSTERFRAMEWORK_DEBUG
