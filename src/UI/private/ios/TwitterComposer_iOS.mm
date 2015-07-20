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
#include <UIKit/UIKit.h>
#include <Twitter/Twitter.h>
//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"
#include "MonsterFramework/src/UI/private/TwitterComposer_Functions.h"
#include "MonsterFramework/src/Utils/private/Private_Utils.h"

//Usings
USING_NS_STD_CC_CD_MF

// Interface //
@interface TwitterComposer_iOS : NSObject
{
    TwitterComposer::Callback _callback;
}

// Init //
- (id)initWithCallback:(const TwitterComposer::Callback &)callback;

// Actions
- (void)showTwitterComposerWithText:(const string &)text
                             images:(const std::vector<TwitterComposer::ImageInfo> &)images
                               urls:(const vector<string> &)urls;

// Helpers //
- (NSMutableArray *)buildImagesArray:(const std::vector<TwitterComposer::ImageInfo> &)vec;
- (NSMutableArray *)buildURLsArray:(const vector<string> &)vec;

// Twitter Composer Callback //
- (void)twitterComposerDidFinishedWithResult:(TWTweetComposeViewControllerResult)result;

@end


// Implementation //
@implementation TwitterComposer_iOS
// Init ///
- (id)initWithCallback:(const TwitterComposer::Callback &)callback
{
    if(self = [super init])
    {
        _callback = callback;
    }
    return self;
}
// Actions //
- (void)showTwitterComposerWithText:(const string &)text
                             images:(const std::vector<TwitterComposer::ImageInfo> &)images
                               urls:(const vector<string> &)urls
{
    //Turn the Text, Images vector and Urls vector to ObjC friendly format.
    NSString       *textStr   = MF_STR_CPP2NS(text);
    NSMutableArray *imagesArr = [self buildImagesArray:images];
    NSMutableArray *urlsArr   = [self buildURLsArray:urls];

    //Build the Twitter controller
    TWTweetComposeViewController *controller = [[TWTweetComposeViewController alloc] init];

    //Text
    [controller setInitialText:textStr];

    //Images
    for (UIImage *image in imagesArr)
         [controller addImage:image];
    
    //Urls
    for (NSURL *url in urlsArr)
        [controller addURL:url];

    //Completion Handlers
    [controller setCompletionHandler:^(TWTweetComposeViewControllerResult result)
    {
        [controller dismissViewControllerAnimated:YES completion:nil];
        [self twitterComposerDidFinishedWithResult:result];
    }];

    //Get the referece to RootViewController of application
    //and present the Twitter controller into it.
    UIViewController *rvc = MF_GETAPPRVC();
    [rvc presentViewController:controller animated:YES completion:nil];
}

// Helpers //
- (NSMutableArray *)buildImagesArray:(const std::vector<TwitterComposer::ImageInfo> &)vec
{
    NSMutableArray *arr = [NSMutableArray arrayWithCapacity:vec.size()];
    for(auto &imageInfo : vec)
    {
        auto path = cc::FileUtils::getInstance()->fullPathForFilename(imageInfo.name + "." + imageInfo.ext);
        
        id       data = [NSData dataWithContentsOfFile:MF_STR_CPP2NS(path)];
        UIImage *img  = [UIImage imageWithData:data];

        [arr addObject:img];
    }
    return arr;
}
- (NSMutableArray *)buildURLsArray:(const vector<string> &)vec
{
    NSMutableArray *arr = [NSMutableArray arrayWithCapacity:vec.size()];

    for(auto &item : vec)
        [arr addObject:[NSURL URLWithString:MF_STR_CPP2NS(item)]];

    return arr;
}

// Twitter Composer Callback
- (void)twitterComposerDidFinishedWithResult:(TWTweetComposeViewControllerResult)result
{
    //Inform that user was done with the Tweet. And pass
    //if the tweet was sent.
    if(_callback)
        _callback(result == TWTweetComposeViewControllerResultDone);

    //Memory clean up.
    //self is because we can not
    //mantain self as autorelease so when the user dismiss the twitter controller
    //the work of this class is already done too then we must clean up it.
    [self release];
}
@end


// TwitterComposer_Functions Implementations //
bool mf::TwitterComposer_CanSendTweet()
{
    return [TWTweetComposeViewController canSendTweet];
}
void mf::TwitterComposer_ShowTwitterComposer(const std::string &text,
                                             const std::vector<TwitterComposer::ImageInfo> &images,
                                             const std::vector<std::string> &urls,
                                             const TwitterComposer::Callback &callback)
{
    //Check if the current device can send tweets. Need because if device
    //cannot the further functions will fail. Game should inform the player about this.
    if(!TwitterComposer_CanSendTweet())
    {
        MF_LOG("TwitterComposer: This device cannot sent tweet");
    }

    //Init the TwitterComposer_iOS object with the target (a CCNode that will handle the
    //callback funtion) and selector (the callback function)
    TwitterComposer_iOS *instance = [[TwitterComposer_iOS alloc] initWithCallback:callback];

    [instance showTwitterComposerWithText:text
                         images:images
                           urls:urls];
}

#endif //MONSTERFRAMEWORK_IOS
