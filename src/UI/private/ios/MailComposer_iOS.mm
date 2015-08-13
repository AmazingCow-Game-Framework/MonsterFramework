//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    MailComposer_iOS.mm                         //
//              █ █        █ █    MonsterFramework                            //
//               ████████████                                                 //
//             █              █   Copyright (c) 2015 AmazingCow               //
//            █     █    █     █  www.AmazingCow.com                          //
//            █     █    █     █                                              //
//             █              █   N2OMatt - n2omatt@amazingcow.com            //
//               ████████████     www.amazingcow.com/n2omatt                  //
//                                                                            //
//                                                                            //
//                  This software is licensed as BSD-3                        //
//                 CHECK THE COPYING FILE TO MORE DETAILS                     //
//                                                                            //
//    Permission is granted to anyone to use this software for any purpose,   //
//   including commercial applications, and to alter it and redistribute it   //
//               freely, subject to the following restrictions:               //
//                                                                            //
//     0. You **CANNOT** change the type of the license.                      //
//     1. The origin of this software must not be misrepresented;             //
//        you must not claim that you wrote the original software.            //
//     2. If you use this software in a product, an acknowledgment in the     //
//        product IS HIGHLY APPRECIATED, both in source and binary forms.     //
//        (See opensource.AmazingCow.com/acknowledgment.html for details).    //
//        If you will not acknowledge, just send us a email. We'll be         //
//        *VERY* happy to see our work being used by other people. :)         //
//        The email is: acknowledgment.opensource@AmazingCow.com              //
//     3. Altered source versions must be plainly marked as such,             //
//        and must notbe misrepresented as being the original software.       //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//      Visit opensource.amazingcow.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//


//Prevent this file being included on non Apple devices.
#ifdef MONSTERFRAMEWORK_IOS

//Cocoa
#import <UIKit/UIKit.h>
//std
#include <vector>
#include <string>
//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"
#include "MonsterFramework/include/UI/MailComposer.h"
#include "MonsterFramework/src/UI/private/MailComposer_Functions.h"
#include "MonsterFramework/src/Utils/Private/Private_Utils.h"

//Usings
USING_NS_STD_CC_CD_MF

//Prevent the inclusion if the project aren't use the Mail stuff.
#ifdef MONSTERFRAMEWORK_USE_MAIL_MODULE
#import <MessageUI/MessageUI.h>

// Interface //
@interface MailComposer_iOS : UIViewController
    <MFMailComposeViewControllerDelegate>
{
    MailComposer::Callback _callback;
}

// Init //
- (id)initWithCallback:(const MailComposer::Callback &)callback;

// Actions //
- (void)showMailComposerWithTo:(const std::vector<std::string> &)toRecipients
                            Cc:(const std::vector<std::string> &)ccRecipients
                           Bcc:(const std::vector<std::string> &)bccRecipients
                       subject:(const std::string &)subject
                       message:(const std::string&)message
                        isHtml:(bool)isHtml
                   attachments:(const std::vector<MailComposer::Attachment> &)attachments;

// Helpers //
- (NSMutableArray *)buildRecipientArray:(const std::vector<std::string> &)recipients;
- (void)addAttachmentsWithVector:(const std::vector<MailComposer::Attachment> &)attachments
               forMailController:(MFMailComposeViewController *)controller;
@end


// Implementation //
@implementation MailComposer_iOS
// Init //
- (id)initWithCallback:(const MailComposer::Callback &)callback
{
    if(self = [super init])
    {
        _callback = callback;
    }

    return self;
}

// Actions //
- (void)showMailComposerWithTo:(const std::vector<std::string> &)toRecipients
                            Cc:(const std::vector<std::string> &)ccRecipients
                           Bcc:(const std::vector<std::string> &)bccRecipients
                       subject:(const std::string &)subject
                       message:(const std::string&)message
                        isHtml:(bool)isHtml
                   attachments:(const std::vector<MailComposer::Attachment> &)attachments
{

    //Turn the vectors into ObjC friendly format.
    NSMutableArray *toArr  = [self buildRecipientArray:toRecipients];
    NSMutableArray *ccArr  = [self buildRecipientArray:ccRecipients];
    NSMutableArray *bccArr = [self buildRecipientArray:bccRecipients];

    //Turn the Subject to ObjC friendly format.
    NSString *subjectStr = MF_STR_CPP2NS(subject);
    //Turn the Message to ObjC friendly format.
    NSString *messageStr = MF_STR_CPP2NS(message);

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
    UIViewController *rvc = MF_GETAPPRVC();
    [rvc presentViewController:controller animated:YES completion:nil];
}

// Helpers //
- (NSMutableArray *)buildRecipientArray:(const std::vector<std::string> &)recipients
{
    //For each item in recipients vector build a NSString with it and
    //put the resulting object into a array.
    NSMutableArray *arr = [NSMutableArray arrayWithCapacity:recipients.size()];
    for(auto &str : recipients)
    {
        [arr addObject:MF_STR_CPP2NS(str)];
    }
    return arr;
}
- (void)addAttachmentsWithVector:(const std::vector<MailComposer::Attachment> &)attachments
               forMailController:(MFMailComposeViewController *)controller
{
    for(auto &attachment : attachments)
    {
        auto path = cc::FileUtils::getInstance()->fullPathForFilename(attachment.name + "." + attachment.ext);

        NSData *myData = [NSData dataWithContentsOfFile:MF_STR_CPP2NS(path)];

        // Attach an image to the email
        [controller addAttachmentData:myData
                             mimeType:MF_STR_CPP2NS(attachment.mimeType)
                             fileName:MF_STR_CPP2NS(attachment.name)];
        
    }
}

// MailComposer Delegate //
- (void)mailComposeController:(MFMailComposeViewController *)controller
          didFinishWithResult:(MFMailComposeResult)result
                        error:(NSError *)error
{
    //Dismiss the Email View controller.
    [controller dismissViewControllerAnimated:YES completion:^(){
        MF_LOG("MailComposer_iOS - MailComposerController did dissmiss ViewController");
    }];

    bool wasSent = true;
    if(error)
    {
        //Error! Log it and return false.
        NSLog(@"Mail_iOS: %@", error);
        wasSent = false;
    }

    //Inform that user was done with the Mail. And pass
    //if the mail was sent.
    if(_callback)
        _callback(result == MFMailComposeResultSent || wasSent);

    //Memory clean up.
    //The (mail)controller is straightforward but the self is because we can not
    //mantain self as autorelease so when the user dismiss the mail controller
    //the work of this class is already done too then we must clean up it.
    [controller release];
    [self release];
}
@end


// MailComposer_Functions Implementation //
bool mf::MailComposer_CanSendMail()
{
    return [MFMailComposeViewController canSendMail];
}
void mf::MailComposer_ShowMailComposer(const std::vector<string> &toRecipients,
                                       const std::vector<string> &ccRecipients,
                                       const std::vector<string> &bccRecipients,
                                       const std::string &subject,
                                       const std::string &message,
                                       bool isHtml,
                                       const std::vector<MailComposer::Attachment> &attachments,
                                       const MailComposer::Callback &callback)
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
    MailComposer_iOS *instance = [[MailComposer_iOS alloc] initWithCallback:callback];

    [instance showMailComposerWithTo:toRecipients
                            Cc:ccRecipients
                           Bcc:bccRecipients
                       subject:subject
                       message:message
                        isHtml:isHtml
                   attachments:attachments];
}

#else // Not using MONSTERFRAMEWORK_USE_MAIL_MODULE //

bool mf::MailComposer_CanSendMail()
{
    return false;
}
void mf::MailComposer_ShowMailComposer(const std::vector<string> &toRecipients,
                                       const std::vector<string> &ccRecipients,
                                       const std::vector<string> &bccRecipients,
                                       const std::string &subject,
                                       const std::string &message,
                                       bool isHtml,
                                       const std::vector<MailComposer::Attachment> &attachments,
                                       const MailComposer::Callback &callback)
{
    //COWTODO: Here we should invoke the callback or do nothing?
}

#endif // MONSTERFRAMEWORK_USE_MAIL_MODULE //
#endif // MONSTERFRAMEWORK_IOS //
