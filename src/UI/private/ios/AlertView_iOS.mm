//----------------------------------------------------------------------------//
//                   _   _ ____   ___  ____                                   //
//                  | \ | |___ \ / _ \| __ )  ___  _   _ ____                 //
//                  |  \| | __) | | | |  _ \ / _ \| | | |_  /                 //
//                  | |\  |/ __/| |_| | |_) | (_) | |_| |/ /                  //
//                  |_| \_|_____|\___/|____/ \___/ \__, /___|                 //
//                                                 |___/                      //
//                                                                            //
//                                   N2OMatt                                  //
//                             N2OMatt@N2OBoyz.com                            //
//                           www.N2OBoyz.com/N2OMatt                          //
//                                                                            //
//                         Copyright (C) 2015 N2OBoyz.                        //
//                                                                            //
//      This software is provided 'as-is', without any express or implied     //
//    warranty. In no event will the authors be held liable for any damages   //
//                   arising from the use of this software.                   //
//                                                                            //
//    Permission is granted to anyone to use this software for any purpose,   //
//   including commercial applications, and to alter it and redistribute it   //
//               freely, subject to the following restrictions:               //
//                                                                            //
//     1. The origin of this software must not be misrepresented;             //
//        you must not claim that you wrote the original software.            //
//     2. If you use this software in a product, an acknowledgment in the     //
//        product IS HIGHLY APPRECIATED, both in source and binary forms.     //
//        (See opensource.N2OBoyz.com/acknowledgment.html for details).       //
//        If you will not acknowledge, just send us a email. We'll be         //
//        *VERY* happy to see our work being used by other people. :)         //
//        The email is: acknowledgment.opensource@N2OBoyz.com                 //
//     3. Altered source versions must be plainly marked as such,             //
//        and must notbe misrepresented as being the original software.       //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//         Visit OpenSource.N2OBoyz.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//

//Prevent this file being included on non Apple devices.
#ifdef MONSTERFRAMEWORK_IOS

//std
#include <vector>
#include <string>
//Cocoa
#import <UIKit/UIKit.h>
//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"
#include "MonsterFramework/src/UI/private/AlertView_Functions.h"
#include "MonsterFramework/src/Utils/private/Private_Utils.h"

//Usings
USING_NS_STD_CC_CD_MF

// Interface //
@interface AlertView_iOS : NSObject
    <UIAlertViewDelegate>
{
    AlertView::Callback _callback;
}

// Init //
- (id)initWithCallback:(const AlertView::Callback &)callback;

// Actions //
- (void)showAlertViewWithTitle:(const std::string &)title
                       message:(const std::string &)message
             cancelButtonTitle:(const std::string &)cancelButtonTitle
             otherButtonTitles:(const std::vector<std::string> &)otherButtonTitles;

@end

@implementation AlertView_iOS
// Init //
- (id)initWithCallback:(const AlertView::Callback &)callback
{
    if(self = [super init])
    {
        _callback = callback;
    }

    return self;
}

// Actions //
- (void)showAlertViewWithTitle:(const std::string &)title
                       message:(const std::string &)message
             cancelButtonTitle:(const std::string &)cancelButtonTitle
             otherButtonTitles:(const std::vector<std::string> &)otherButtonTitles
{
    //Build the UIAlertView.
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:MF_STR_CPP2NS(title)
                                                        message:MF_STR_CPP2NS(message)
                                                       delegate:self
                                              cancelButtonTitle:MF_STR_CPP2NS(cancelButtonTitle)
                                              otherButtonTitles:nil, nil];

    //We need add the OtherButtonTitles into the UIAlertView so we will iterate
    //for each item in vector and turn it on NSString and add the result on UIAlertView.
    for(auto &title : otherButtonTitles)
        [alertView addButtonWithTitle:MF_STR_CPP2NS(title)];

    //Present the AlertView.
    [alertView show];
}

// UIAlertView Delegate //
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if(_callback)
    {
        _callback(MF_STR_NS2CPP([alertView buttonTitleAtIndex:buttonIndex]),
                  buttonIndex);
    }

    [alertView release];
    [self release];
}
@end

// AlerView_Functions Implementations //
void mf::AlertView_ShowAlertView(const std::string &title,
                                 const std::string &message,
                                 const std::string &cancelButtonTitle,
                                 const std::vector<std::string> &otherButtonTitles,
                                 const AlertView::Callback &callback)
{
    AlertView_iOS *instance = [[AlertView_iOS alloc] initWithCallback:callback];
    
    [instance showAlertViewWithTitle:title message:message
                   cancelButtonTitle:cancelButtonTitle
                   otherButtonTitles:otherButtonTitles];
}

#endif //MONSTERFRAMEWORK_IOS
