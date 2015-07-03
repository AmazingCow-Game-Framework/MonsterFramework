//----------------------------------------------------------------------------//
//                  _   _ ____   ___  ____                                    //
//                 | \ | |___ \ / _ \| __ )  ___  _   _ ____                  //
//                 |  \| | __) | | | |  _ \ / _ \| | | |_  /                  //
//                 | |\  |/ __/| |_| | |_) | (_) | |_| |/ /                   //
//                 |_| \_|_____|\___/|____/ \___/ \__, /___|                  //
//                                                |___/                       //
//                                                                            //
//                            Mateus Mesquita                                 //
//                       www.N2OBoyz.com/~n2omatt                             //
//                          N2OMatt@N2OBoyz.com                               //
//                                                                            //
//                   Copyright (C) 2015 Mateus Mesquita.                      //
//                       Copyright (C) 2015 N2OBoyz.                          //
//                                                                            //
//  This software is provided 'as-is', without any express or implied         //
//  warranty. In no event will the authors be held liable for any damages     //
//  arising from the use of this software.                                    //
//                                                                            //
//  Permission is granted to anyone to use this software for any purpose,     //
//  including commercial applications, and to alter it and redistribute it    //
//  freely, subject to the following restrictions:                            //
//                                                                            //
//  1. The origin of this software must not be misrepresented;                //
//     you must not claim that you wrote the original software.               //
//  2. If you use this software in a product, an acknowledgment in the        //
//     product IS HIGHLY APPRECIATED, both in source and binary forms.        //
//     If you will not acknowledge, just send me a email. We'll be VERY       //
//     happy to see our work being used by other people. :)                   //
//     (See opensource.N2OBoyz.com/acknowledgment.html for details).          //
//  3. Altered source versions must be plainly marked as such, and must not   //
//     be misrepresented as being the original software.                      //
//  4. This notice may not be removed or altered from any source              //
//     distribution.                                                          //
//  5. Most important, you must have fun. ;)                                  //
//                                                                            //
//       Visit OpenSource.N2OBoyz.com for more open-source projects.          //
//                                                                            //
//                            Enjoy :)                                        //
//----------------------------------------------------------------------------//

//Header
#include "MonsterFramework/include/UI/MailComposer.h"
//MonsterFramewrok
#include "./private/MailComposer_Functions.h"

//Usings
USING_NS_STD_CC_CD_MF;

// Constants //
const string MailComposer::MIME_JPG = "image/jpeg";
const string MailComposer::MIME_PNG = "image/png";

// Static Methods //
bool MailComposer::canSendMail()
{
    return MailComposer_CanSendMail();
}

// CTOR/DTOR //
MailComposer::MailComposer() :
m_pTarget(nullptr),
m_selector(nullptr)
{
    //Empty...
}
MailComposer::MailComposer(const std::vector<std::string> &to,
                           const std::string &subject,
                           const std::string &message, bool isHTML,
                           cc::Node *pTarget, mf::SEL_MailComposerHandler selector) :
m_toRecipients(to),
m_subject(subject),
m_message(message),
m_isHTML(isHTML),
m_pTarget(pTarget),
m_selector(selector)
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
void MailComposer::addAttachment(const string &name, const string &ext,
                                 const string &mimeType)
{
    m_attachments.push_back(make_tuple(name, ext, mimeType));
}

//Target
void MailComposer::setTarget(cc::Node *target, SEL_MailComposerHandler selector)
{
    m_pTarget  = target;
    m_selector = selector;
}

//Show
void MailComposer::showMailComposerUI()
{
    MailComposer_ShowMailComposer(m_toRecipients, m_ccRecipients, m_bccRecipients,
                                  m_subject, m_message, m_isHTML, m_attachments,
                                  m_pTarget, m_selector);
}
