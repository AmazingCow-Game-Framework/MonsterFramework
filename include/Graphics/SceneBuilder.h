
#ifndef __MonsterFramework_include_Graphics_SceneBuilder_h__
#define __MonsterFramework_include_Graphics_SceneBuilder_h__

//std
#include <string>
//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"

NS_MF_BEGIN

//Forward Declarations.
class ILoadResolver;

class SceneBuilder
{
    // Singleton //
public:
    SINGLETON_OF(SceneBuilder);

private:
    SceneBuilder()  { /* Empty */ }
    ~SceneBuilder() { /* Empty */ }

    // Public Methods //
public:
    void build(const std::string &name, cc::Node *pOwner,
               mf::ILoadResolver *pResolver);

};

NS_MF_END
#endif // defined(__MonsterFramework_include_Graphics_SceneBuilder_h__) //
