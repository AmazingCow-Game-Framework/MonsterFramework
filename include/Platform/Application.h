
#ifndef Application_h
#define Application_h

//std
#include <string>
//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"

NS_MF_BEGIN

class Application :
    public cc::Application
{
    // CTOR / DTOR //
public:
    Application();
    
    
    // Public Methods //
public:
    const std::string& getApplicationName() const;
    
    
    // iVars //
private:
    std::string m_appName;
};

NS_MF_END

#endif // defined(Application_h) //
