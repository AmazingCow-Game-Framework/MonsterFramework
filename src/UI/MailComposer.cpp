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

//Header
#include "MonsterFramework/include/UI/MailComposer.h"
//MonsterFramewrok
#include "./private/MailComposer_Functions.h"

//Usings
USING_NS_STD_CC_CD_MF;

// Constants //
const string MailComposer::kMIME_JPG = "image/jpeg";
const string MailComposer::kMIME_PNG = "image/png";

// Static Methods //
bool MailComposer::canSendMail()
{
    return MailComposer_CanSendMail();
}

// CTOR/DTOR //
MailComposer::MailComposer()
{
    //Empty...
}
MailComposer::MailComposer(const std::vector<std::string> &to,
                           const std::string &subject,
                           const std::string &message, bool isHTML,
                           const Callback &callback) :
    m_toRecipients(to),
    m_subject(subject),
    m_message(message),
    m_isHTML(isHTML),
    m_callback(callback)
{
    //Empty...
}


// Public Methods //
//TO
void MailComposer::setToRecipient(const string &to)
{
    m_toRecipients.clear();
    m_toRecipients.push_back(to);
}
void MailComposer::setToRecipients(const vector<string> &to)
{
    m_toRecipients = to;
}

//CC
void MailComposer::setCcRecipients(const vector<string> &cc)
{
    m_ccRecipients = cc;
}

//BCC
void MailComposer::setBccRecipients(const vector<string> &bcc)
{
    m_bccRecipients = bcc;
}

//Subject
void MailComposer::setSubject(const std::string &subject)
{
    m_subject = subject;
}

//Message
void MailComposer::setMessage(const std::string &message, bool isHTML)
{
    m_message = message;
    m_isHTML  = isHTML;
}

//Attachment
void MailComposer::addAttachment(const Attachment &attachment)
{
    m_attachments.push_back(attachment);
}

//Callback
void MailComposer::setCallback(const Callback &callback)
{
    m_callback = callback;
}

//Show
void MailComposer::showMailComposer()
{
    MailComposer_ShowMailComposer(m_toRecipients,
                                  m_ccRecipients,
                                  m_bccRecipients,
                                  m_subject,
                                  m_message,
                                  m_isHTML,
                                  m_attachments,
                                  m_callback);
}
