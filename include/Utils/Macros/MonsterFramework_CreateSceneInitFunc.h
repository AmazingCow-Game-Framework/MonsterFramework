
#ifndef __MonsterFramework_include_Utils_Macros_MonsterFramework_CreateSceneInitFunc_h__
#define __MonsterFramework_include_Utils_Macros_MonsterFramework_CreateSceneInitFunc_h__

////////////////////////////////////////////////////////////////////////////////
// Scene Func                                                                 //
////////////////////////////////////////////////////////////////////////////////
//Similar to cocos2d's CREATE_FUNC macro, but for scenes.
#define SCENE_FUNC(__LAYER_TYPE__)         \
static cc::Scene* scene()                  \
{                                          \
    auto scene = cc::Scene::create();      \
    auto layer = __LAYER_TYPE__::create(); \
    scene->addChild(layer);                \
    return scene;                          \
}

//Similar to SCENE_FUNC, but the scene will receive one
//parameter called options with the type passed in __OPT_TYPE__.
//This method will call the create(options) of the __LAYER_TYPE__.
#define SCENE_FUNC_OPTIONS(__LAYER_TYPE__, __OPT_TYPE__) \
static cc::Scene* scene(const __OPT_TYPE__ &options)     \
{                                                        \
    auto scene = cc::Scene::create();                    \
    auto layer = __LAYER_TYPE__::create(options);        \
    scene->addChild(layer);                              \
    return scene;                                        \
}


////////////////////////////////////////////////////////////////////////////////
// Create Func                                                                //
////////////////////////////////////////////////////////////////////////////////
//Similar to the CREATE_FUNC of cocos2d, but the __TYPE__'s
//init will be called with the options of type __OPT_TYPE__
//passed as argument.
#define CREATE_FUNC_OPTIONS(__TYPE__, __OPT__)  \
static __TYPE__* create(const __OPT__ &options) \
{                                               \
    auto ret = new __TYPE__();                  \
    if(ret && ret->init((options)))             \
    {                                           \
        ret->autorelease();                     \
    }                                           \
    else                                        \
    {                                           \
        delete ret;                             \
        ret = NULL;                             \
    }                                           \
    return ret;\
}


////////////////////////////////////////////////////////////////////////////////
// Init                                                                       //
////////////////////////////////////////////////////////////////////////////////
#define INIT_OPTIONS(_UNUSED_TYPE_, __OPT__) \
    virtual bool init(const __OPT__ &options);
#define INIT(_UNUSED_TYPE_) \
    virtual bool init() override;


#endif // defined(__MonsterFramework_include_Utils_Macros_MonsterFramework_CreateSceneInitFunc_h__)
