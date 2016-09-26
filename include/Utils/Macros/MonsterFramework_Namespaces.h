
#ifndef __MonsterFramework_include_Utils_Macros_MonsterFramework_Namespaces_h__
#define __MonsterFramework_include_Utils_Macros_MonsterFramework_Namespaces_h__

// Needed to create a namespace alias.
#include "cocos2d.h"

////////////////////////////////////////////////////////////////////////////////
// Namespaces                                                                 //
////////////////////////////////////////////////////////////////////////////////
// Create aliases to reduce the verbosity of the use of cocos2d's namespaces.
namespace cc = cocos2d;

// Help reduce verbosity of MonsterFramework namespace declarations.
#define NS_MF_BEGIN namespace mf {
#define NS_MF_END   }

// One shot using...
#define USING_NS_STD_CC_CD_MF \
    using namespace std;      \
    using namespace cocos2d;  \
    using namespace mf;


#endif // defined(__MonsterFramework_include_Utils_Macros_MonsterFramework_Namespaces_h__)
