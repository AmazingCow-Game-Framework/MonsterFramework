//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    TwitterComposer.cpp                         //
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

//Header
#include "MonsterFramework/include/UI/TwitterComposer.h"
//MonsterFramework
#include "./private/TwitterComposer_Functions.h"

//Usings
USING_NS_STD_CC_CD_MF

// Static Methods //
bool TwitterComposer::canSendTweet()
{
    //    COWTODO:
//    return TwitterComposer_CanSendTweet();
    return false;
}

// CTOR/DTOR //
TwitterComposer::TwitterComposer()
{
    //Empty...
}

TwitterComposer::TwitterComposer(const std::string &text,
                                 const Callback &callback) :
    m_text(text),
    m_callback(callback)
{
    //Empty...
}

// Public Methods //
//Text/Image/URL
void TwitterComposer::setText(const std::string &text)
{
    m_text = text;
}
void TwitterComposer::addImage(const ImageInfo &info)
{
    m_images.push_back(info);
}
void TwitterComposer::addURL(const std::string &url)
{
    m_urls.push_back(url);
}

//Target
void TwitterComposer::setCallback(const Callback &callback)
{
    m_callback = callback;
}

//Show
void TwitterComposer::showTwitterComposer()
{
    //    COWTODO:
//    TwitterComposer_ShowTwitterComposer(m_text,
//                                        m_images,
//                                        m_urls,
//                                        m_callback);
}
