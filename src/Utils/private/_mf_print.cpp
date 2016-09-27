
//Header
#include "_mf_print.h"
//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"
//std
#include <cstdarg>
#include <cstdio>
#include <cstdlib>


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include <android/log.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// MACROS                                                                     //
////////////////////////////////////////////////////////////////////////////////
#define _BUFFER_FROM_VA_ARGS(_pFmt_)               \
    va_list args;                                  \
    va_start(args, _pFmt_);                        \
                                                   \
    constexpr int kBufferSize = 1024;              \
    char buffer[kBufferSize]  = { '\0' };          \
                                                   \
    vsnprintf(buffer, kBufferSize, _pFmt_, args);  \
                                                   \
    va_end(args);



////////////////////////////////////////////////////////////////////////////////
// Declarations                                                               //
////////////////////////////////////////////////////////////////////////////////
void _internal_printf(FILE *pFile, const char *pStr);


////////////////////////////////////////////////////////////////////////////////
// Public Definitions                                                         //
////////////////////////////////////////////////////////////////////////////////
void _mf_printf(const char *pFmt, ...)
{
    _BUFFER_FROM_VA_ARGS(pFmt);
    _internal_printf(stdout, buffer);
}

void _mf_error_printf(const char *pFmt, ...)
{
    _BUFFER_FROM_VA_ARGS(pFmt);
    _internal_printf(stderr, buffer);
}


////////////////////////////////////////////////////////////////////////////////
// Private Definitions                                                        //
////////////////////////////////////////////////////////////////////////////////
void _internal_printf(FILE *pFile, const char *pStr)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

    __android_log_print(
        ANDROID_LOG_DEBUG,
        "MonsterFramework",
        "MF_LOG: %s - %s\n",
        pPrefix,
        buffer
    );

#else //!(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

    fprintf(pFile, pStr);
    fflush(pFile);

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
}
