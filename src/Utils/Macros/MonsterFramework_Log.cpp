
// Only compile this file in debug mode.
#ifdef MONSTERFRAMEWORK_DEBUG

//Header
#include "MonsterFramework/include/Utils/Macros/MonsterFramework_Log.h"
//std
#include <cstdarg>
#include <cstdio>
#include <cstdlib>

//Usings
USING_NS_STD_CC_CD_MF;

NS_MF_BEGIN

void _mf_log_print(const char *pPrefix,
                   const char *pMsg,
                   ...)
{
    va_list args;
    va_start(args, pMsg);
    
    constexpr int kBufferSize = 1024;
    char buffer[kBufferSize]  = { '\0' };
    
    vsnprintf(buffer, kBufferSize, pMsg, args);
    
    va_end(args);
    
    if(strlen(pPrefix) != 0)
        fprintf(stdout, "MF_LOG: %s - %s\n", pPrefix, buffer);
    else
        fprintf(stdout, "MF_LOG: %s\n", buffer);
}

NS_MF_END
#endif //MONSTERFRAMEWORK_DEBUG
