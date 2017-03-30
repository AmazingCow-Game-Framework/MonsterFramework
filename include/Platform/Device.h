//
//  Device.h
//  GameMemory
//
//  Created by Mateus Mesquita on 9/28/16.
//
//

#ifndef __MonsterFramework_include_Platform_Device_h__
#define __MonsterFramework_include_Platform_Device_h__

//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"

NS_MF_BEGIN

class Device
    : public cc::Device
{
    // Public Methods //
public:
    static cc::Size getScreenSize();
    
    static float getScreenSizeRatio()
    {
        auto size = mf::Device::getScreenSize();
        
        return std::max(size.width, size.height) /
               std::min(size.width, size.height);
    }
};

NS_MF_END
#endif /* __MonsterFramework_include_Platform_Device_h__ */
