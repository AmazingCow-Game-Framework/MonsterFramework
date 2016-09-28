//
//  Device_iOS.m
//  GameMemory
//
//  Created by Mateus Mesquita on 9/28/16.
//

//Header
#include "MonsterFramework/include/Platform/Device.h"

//Prevent the inclusion on NON IOS builds.
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )

//Objc
#import <Foundation/Foundation.h>
#import <UIKit/UiKit.h>

//Usings
USING_NS_MF;

////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
cc::Size Device::getScreenSize()
{
    UIScreen *ui_screen = [UIScreen mainScreen];
    MF_ASSERT_EX(
        ui_screen,
        "[iOS] Device::getWindowSize()",
        "Failed to get an instance of mainScreen"
    );
    
    CGRect  screenBounds = [ui_screen bounds];
    CGFloat screenScale  = [ui_screen scale];
    
    return cc::Size(
               screenBounds.size.width * screenScale,
               screenBounds.size.height * screenScale
           );
}


#endif // ( CC_TARGET_PLATFORM == CC_PLATFORM_MAC ) //
