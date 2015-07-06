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
#include "../../include/Utils/MonsterFramework_Utils.h"
#include "ActionSheet_Functions.h"

//Usings
USING_NS_STD_CC_CD_MF

// Interface //
@interface ActionSheet_iOS : NSObject <UIActionSheetDelegate>
{
    CCNode                 *_target;
    SEL_ActionSheetHandler  _selector;
}

#pragma mark - Init
- (id)initWithTarget:(CCNode *)target selector:(SEL_ActionSheetHandler)selector;

#pragma mark - Actions
- (void)showActionSheetWithTitle:(const string &)title
               cancelButtonTitle:(const string &)cancelButtonTitle
          destructiveButtonTitle:(const string &)destructiveButtonTitle
               otherButtonTitles:(const vector<string> &)otherButtonTitles;

#pragma mark - Helpers
- (NSString *)NSStringOrNilIfEmpty:(const string &)str;

@end


// Implementation //
@implementation ActionSheet_iOS

#pragma mark - Init
- (id)initWithTarget:(cc::CCNode *)target selector:(mf::SEL_ActionSheetHandler)selector
{
    if(self = [super init])
    {
        _target   = target;
        _selector = selector;
    }
    return self;
}

#pragma mark - Actions
- (void)showActionSheetWithTitle:(const string &)title
               cancelButtonTitle:(const string &)cancelButtonTitle
          destructiveButtonTitle:(const string &)destructiveButtonTitle
               otherButtonTitles:(const vector<string> &)otherButtonTitles
{
    //Turn Title, CancelButtonTitle and DestructiveButtonTitle
    //into a ObjC friendly format.
    NSString *titleStr                  = [self NSStringOrNilIfEmpty:title];
    NSString *cancelButtonTitleStr      = [self NSStringOrNilIfEmpty:cancelButtonTitle];
    NSString *destructiveButtonTitleStr = [self NSStringOrNilIfEmpty:destructiveButtonTitle];

    //Buid the UIActionSheet.
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:titleStr
                                                             delegate:self
                                                    cancelButtonTitle:cancelButtonTitleStr
                                               destructiveButtonTitle:destructiveButtonTitleStr
                                                    otherButtonTitles:nil, nil];

    //We need add the OtherButtonTitles into the UIActionSheet so we will iterate
    //for each item in vector and turn it on NSString and add the result on UIActionSheet
    for(auto &title : otherButtonTitles)
    {
        NSString *currentStr = [NSString stringWithUTF8String:title.c_str()];
        [actionSheet addButtonWithTitle:currentStr];
    }

    //Get the referece to RootViewController of application
    //and present the Twitter controller into it.
    UIViewController *rvc = [[[UIApplication sharedApplication] keyWindow] rootViewController];
    [actionSheet showInView:rvc.view];
}

#pragma mark - Helpers
- (NSString *)NSStringOrNilIfEmpty:(const string &)str
{
    return (str == "") ? nil : [NSString stringWithUTF8String:str.c_str()];
}

#pragma mark - UIActionSheet Delegate
- (void)actionSheet:(UIActionSheet *)actionSheet didDismissWithButtonIndex:(NSInteger)buttonIndex
{
    //Call the callback, if it exists.
    if(_target && _selector)
        (_target->*_selector)(buttonIndex);

    //Memory clean up.
    //The actionShet is straightforward but the self is because we can not
    //mantain self as autorelease so when the user dismiss the mail controller
    //the work of this class is already done too then we must clean up it.
    [actionSheet release];
    [self release];
}
@end

#pragma mark - AlertView_Functions Implementations
void mf::ActionSheet_ShowActionSheet(const string &title,
                                     const string &cancelButtonTitle,
                                     const string &destructiveButtonTitle,
                                     const vector<string> otherButtonTitles,
                                     cc::CCNode *pTarget,
                                     mf::SEL_ActionSheetHandler selector)
{
    ActionSheet_iOS *instance = [[ActionSheet_iOS alloc] initWithTarget:pTarget
                                                               selector:selector];
    [instance showActionSheetWithTitle:title
                     cancelButtonTitle:cancelButtonTitle
                destructiveButtonTitle:destructiveButtonTitle
                     otherButtonTitles:otherButtonTitles];
}
#endif //MONSTERFRAMEWORK_IOS
