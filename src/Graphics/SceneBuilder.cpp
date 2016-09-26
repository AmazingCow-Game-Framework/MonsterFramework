
//Header
#include "MonsterFramework/include/Graphics/SceneBuilder.h"
//MonsterFramework
#include "CCBNodeLoader.h"

//Usings
USING_NS_STD_CC_CD_MF

////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
void SceneBuilder::build(const std::string &name, cc::Node *pOwner,
                         mf::ILoadResolver *pResolver)

{
    //Check if the name argument includes the .cbb extension.
    //  If not add it to fullname so FileUtils could find it.
    std::string fullname = name;
    if(name.find(".ccb") == std::string::npos)
        fullname += ".ccb";

    auto fullpath = cc::FileUtils::getInstance()->fullPathForFilename(fullname);

    MF_ASSERT_EX(
        !fullpath.empty(),
        "SceneBuilder::build",
        "Cannot find the .ccb file (%s)",
        fullname.c_str()
    );

    auto ccbMap = cc::FileUtils::getInstance()->getValueMapFromFile(fullpath);
    
    MF_ASSERT_EX(
        ccbMap.empty() == false,
        "SceneBuilder::build",
        "Failed to load ValeuMap from file: %s",
        fullpath.c_str()
    );
    auto nodeGraphMap = ccbMap.at("nodeGraph").asValueMap();
    //COWTODO: Implement the sequence (animation) stuff.
    //auto sequencesMap = ccbMap.at("sequences").asValueVector();

    CCBNodeLoader b;
    b.loadNodeGraph(nodeGraphMap, pOwner, pResolver);
}
