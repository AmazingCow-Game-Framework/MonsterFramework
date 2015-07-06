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

#ifndef __MonsterFramework_MailComposer_h__
#define __MonsterFramework_MailComposer_h__

//std
#include <string>
#include <vector>
//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"

NS_MF_BEGIN

typedef void (cc::CCObject::*SEL_MailComposerHandler)(bool);
#define MailComposer_selector(_SELECTOR) (SEL_MailComposerHandler)(&_SELECTOR)

class MailComposer
{
    // Constants //
public:
    static const std::string MIME_JPG;
    static const std::string MIME_PNG;

    // Static Methods //
public:
    static bool canSendMail();

    // CTOR/DTOR //
public:
    MailComposer();
    MailComposer(const std::vector<std::string> &to,
                 const std::string &subject,
                 const std::string &message, bool isHTML,
                 cc::Node *pTarget, mf::SEL_MailComposerHandler selector);

    // Public Methods //
public:
    //TO
    void setToRecipient(const std::string &to);
    void setToRecipients(const std::vector<std::string> &to);
    //CC
    void setCcRecipients(const std::vector<std::string> &cc);
    //BCC
    void setBccRecipients(const std::vector<std::string> &bcc);

    //Subject
    void setSubject(const std::string &subject);
    //Message
    void setMessage(const std::string &message, bool isHTML);
    //Attachment
    void addAttachment(const std::string &name, const std::string &ext,
                       const std::string &mimeType);

    //Target
    void setTarget(cc::Node *target, mf::SEL_MailComposerHandler selector);

    //Show
    void showMailComposerUI();

    // iVars //
private:
    std::string m_subject;
    std::string m_message;
    bool        m_isHTML;

    std::vector<std::string> m_toRecipients;
    std::vector<std::string> m_ccRecipients;
    std::vector<std::string> m_bccRecipients;

    std::vector<std::tuple<std::string, std::string, std::string>> m_attachments;

    cc::Node                  *m_pTarget;
    mf::SEL_MailComposerHandler  m_selector;
};

NS_MF_END
#endif // defined(__MonsterFramework_MailComposer_h__) //
