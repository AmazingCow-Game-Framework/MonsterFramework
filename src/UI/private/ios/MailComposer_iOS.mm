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

//Cocoa
#import <UIKit/UIKit.h>
#import <MessageUI/MessageUI.h>
//std
#include <vector>
#include <string>
//DonkeyBas
#include "../../include/Utils/MonsterFramework_Utils.h"
#include "MailComposer_Functions.h"

//Usings
USING_NS_STD_CC_CD_MF

// Interface //
@interface MailComposer_iOS : UIViewController <MFMailComposeViewControllerDelegate>
{
    cc::CCNode                  *_target;
    mf::SEL_MailComposerHandler _selector;
}

#pragma mark - Init
- (id)initWithTarget:(cc::CCNode *)target selector:(mf::SEL_MailComposerHandler)selector;

#pragma mark - Actions
- (void)showMailComposerWithTo:(const std::vector<std::string> &)toRecipients
                            Cc:(const std::vector<std::string> &)ccRecipients
                           Bcc:(const std::vector<std::string> &)bccRecipients
                       subject:(const std::string &)subject
                       message:(const std::string&)message
                        isHtml:(bool)isHtml
                   attachments:(const std::vector<std::tuple<std::string, std::string, std::string>> &)attachments;

#pragma mark - Helpers
- (NSMutableArray *)buildRecipientArray:(const std::vector<std::string> &)recipients;
- (void)addAttachmentsWithVector:(const std::vector<std::tuple<std::string, std::string, std::string>> &)attachments
               forMailController:(MFMailComposeViewController *)controller;
@end


// Implementation //
@implementation MailComposer_iOS
#pragma mark - Init
- (id)initWithTarget:(cc::CCNode *)target selector:(mf::SEL_MailComposerHandler)selector
{
    if(self = [super init])
    {
        _target   = target;
        _selector = selector;
    }

    return self;
}

#pragma - Actions
- (void)showMailComposerWithTo:(const std::vector<std::string> &)toRecipients
                            Cc:(const std::vector<std::string> &)ccRecipients
                           Bcc:(const std::vector<std::string> &)bccRecipients
                       subject:(const std::string &)subject
                       message:(const std::string &)message
                        isHtml:(bool)isHtml
                   attachments:(const std::vector<std::tuple<std::string, std::string, std::string>> &)attachments
{

    //Turn the vectors into ObjC friendly format.
    NSMutableArray *toArr  = [self buildRecipientArray:toRecipients];
    NSMutableArray *ccArr  = [self buildRecipientArray:ccRecipients];
    NSMutableArray *bccArr = [self buildRecipientArray:bccRecipients];

    //Turn the Subject to ObjC friendly format.
    NSString *subjectStr = [NSString stringWithCString:subject.c_str()
                                              encoding:NSUTF8StringEncoding];

    //Turn the Message to ObjC friendly format.
    NSString *messageStr = [NSString stringWithCString:message.c_str()
                                              encoding:NSUTF8StringEncoding];


    //Build the controller object
    MFMailComposeViewController *controller = [[MFMailComposeViewController alloc] init];
    controller.mailComposeDelegate          = self;

    [controller setToRecipients:toArr];
    [controller setCcRecipients:ccArr];
    [controller setBccRecipients:bccArr];

    [controller setSubject:subjectStr];
    [controller setMessageBody:messageStr isHTML:isHtml];

    //Add the attachments.
    [self addAttachmentsWithVector:attachments forMailController:controller];

    //Get the referece to RootViewController of application
    //and present the Twitter controller into it.
    UIViewController *rvc = [[[UIApplication sharedApplication] keyWindow] rootViewController];
    [rvc presentViewController:controller animated:YES completion:nil];
}

#pragma mark - Helpers
- (NSMutableArray *)buildRecipientArray:(const std::vector<std::string> &)recipients
{
    //For each item in recipients vector build a NSString with it and
    //put the resulting object into a array.
    NSMutableArray *arr = [NSMutableArray arrayWithCapacity:recipients.size()];
    for(auto &str : recipients)
    {
        [arr addObject:[NSString stringWithUTF8String:str.c_str()]];
    }
    return arr;
}
- (void)addAttachmentsWithVector:(const std::vector<std::tuple<std::string, std::string, std::string>> &)attachments
               forMailController:(MFMailComposeViewController *)controller
{
    for(auto &tuple : attachments)
    {
        auto name = std::get<0>(tuple);
        auto ext  = std::get<1>(tuple);
        auto mime = std::get<2>(tuple);

        auto path = CCFileUtils::sharedFileUtils()->fullPathForFilename(name + "." + ext);

        NSData *myData = [NSData dataWithContentsOfFile:[NSString stringWithUTF8String:path.c_str()]];

        // Attach an image to the email
        [controller addAttachmentData:myData
                             mimeType:[NSString stringWithUTF8String:mime.c_str()]
                             fileName:[NSString stringWithUTF8String:name.c_str()]];
    }
}

#pragma mark - MailComposer Delegate
- (void)mailComposeController:(MFMailComposeViewController *)controller
          didFinishWithResult:(MFMailComposeResult)result
                        error:(NSError *)error
{
    //Dismiss the Email View controller.
    [controller dismissViewControllerAnimated:YES completion:^(){
        MF_LOG("MailComposer_iOS - MailComposerController did dissmiss ViewController");
    }];

    if(error)
    {
        //Error! Log it and return false.
        NSLog(@"Mail_iOS: %@", error);

        if(_target && _selector)
            (_target->*_selector)(false);
    }
    else
    {
        //Inform the target that user was done with the Mail. And pass
        //if the mail was sent.
        if(_target && _selector)
            (_target->*_selector)(result == MFMailComposeResultSent);
    }


    //Memory clean up.
    //The (mail)controller is straightforward but the self is because we can not
    //mantain self as autorelease so when the user dismiss the mail controller
    //the work of this class is already done too then we must clean up it.
    [controller release];
    [self release];
}
@end


#pragma mark - MailComposer_Functions Implementation
bool mf::MailComposer_CanSendMail()
{
    return [MFMailComposeViewController canSendMail];
}
void mf::MailComposer_ShowMailComposer(const std::vector<string> &toRecipients,
                                       const std::vector<string> &ccRecipients,
                                       const std::vector<string> &bccRecipients,
                                       const std::string &subject,
                                       const std::string &message, bool isHtml,
                                       const std::vector<std::tuple<std::string, std::string, std::string>> &attachments,
                                       cc::CCNode *target, mf::SEL_MailComposerHandler selector)
{
    //Check if the current device can send mail. Need because if device
    //cannot the further functions will fail. Game should inform the player about this.
    if(!MailComposer_CanSendMail())
    {
        MF_LOG("MailComposer_iOS: This device cannot send mail");
        return;
    }

    //Init the MailComposer_iOS object with the target (a CCNode that will handle the
    //callback funtion) and selector (the callback function)
    MailComposer_iOS *instance = [[MailComposer_iOS alloc] initWithTarget:target
                                                     selector:selector];

    [instance showMailComposerWithTo:toRecipients
                            Cc:ccRecipients
                           Bcc:bccRecipients
                       subject:subject
                       message:message
                        isHtml:isHtml
                   attachments:attachments];
}
#endif //MONSTERFRAMEWORK_IOS
