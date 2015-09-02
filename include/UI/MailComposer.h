//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    MailComposer.h                              //
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
//        The email is: acknowledgmentopensource@AmazingCow.com               //
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

#ifndef __MonsterFramework_include_UI_MailComposer_h__
#define __MonsterFramework_include_UI_MailComposer_h__

//std
#include <string>
#include <vector>
//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"

NS_MF_BEGIN

class MailComposer
{
    // Inner Types //
public:
    //Type that holds the information about the attachment
    //that will be included in mail.
    //
    //name     is the filename of the attachment **without** the extension.
    //ext      is the extension of the attachment **without** the leading dot.
    //mimeType is the MIME of the attachement, like (image/jpeg).
    //         check the prefined mimes for jpg and png images.
    //Example:
    //  name = "Pingo";     ext = "png";  <- RIGHT
    //  name = "Pingo.png"; ext = "png";  <- WRONG (Name with extension)
    //  name = "Pingo";     ext = ".png"; <- WRONG (Extension with dot)
    struct Attachment
    {
        const std::string name;
        const std::string ext;
        const std::string mimeType;
    };

    // Enums/Constants/Typedefs //
public:
    static const std::string kMIME_JPG;
    static const std::string kMIME_PNG;
    typedef std::function<void (bool)> Callback;

    // Static Methods //
public:
    static bool canSendMail();

    // CTOR/DTOR //
public:
    MailComposer();
    MailComposer(const std::vector<std::string> &to,
                 const std::string &subject,
                 const std::string &message,
                 bool isHTML,
                 const Callback &callback);

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
    void addAttachment(const Attachment &attachment);

    //Callback
    void setCallback(const Callback &callback);

    //Show
    void showMailComposer();

    // iVars //
private:
    std::string m_subject;
    std::string m_message;
    bool        m_isHTML;

    std::vector<std::string> m_toRecipients;
    std::vector<std::string> m_ccRecipients;
    std::vector<std::string> m_bccRecipients;

    std::vector<Attachment>  m_attachments;

    Callback m_callback;
};

NS_MF_END
#endif // defined(__MonsterFramework_include_UI_MailComposer_h__) //
