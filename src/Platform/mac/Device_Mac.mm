//
//  Device_Mac.m
//  GameMemory
//
//  Created by Mateus Mesquita on 9/28/16.
//
//

//Header
#include "MonsterFramework/include/Platform/Device.h"

//Prevent the inclusion on NON MAC builds.
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_MAC )

//Objc
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

//Usings
USING_NS_MF;

////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
cc::Size Device::getScreenSize()
{
    NSScreen* ns_screen = [NSScreen mainScreen];
    
    MF_ASSERT_EX(
        ns_screen,
        "[Mac] Device::getWindowSize()",
        "Failed to get an instance of mainScreen"
    );
    
    NSRect ns_rect = [ns_screen visibleFrame];
    return cc::Size(ns_rect.size.width, ns_rect.size.height);
    
}


#endif // ( CC_TARGET_PLATFORM == CC_PLATFORM_MAC ) //
