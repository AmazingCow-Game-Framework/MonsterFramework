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
#include "MonsterFramework/include/UI/AlertView.h"
//MonsterFramework
#include "private/AlertView_Functions.h"

//Usings
USING_NS_STD_CC_CD_MF

// CTOR/DTOR //
AlertView::AlertView() :
m_pTarget(nullptr),
m_selector(nullptr)
{
    //Empty...
}
AlertView::AlertView(const string &title, const string &message,
                     const string &cancelButtonTitle,
                     const vector<string> &otherButtonTitles,
                     cc::Node *pTarget, mf::SEL_AlertViewHandler selector) :
m_title(title),
m_message(message),
m_cancelButtonTitle(cancelButtonTitle),
m_otherButtonTitles(otherButtonTitles),
m_pTarget(pTarget),
m_selector(selector)
{
    //Empty...
}


// Public Methods //
void AlertView::setTitle(const string &title)
{
    m_title = title;
}
void AlertView::setMessage(const string &message)
{
    m_message = message;
}
void AlertView::setCancelButtonTitle(const string &cancelButtonTitle)
{
    m_cancelButtonTitle = cancelButtonTitle;
}
void AlertView::setOtherButtonTitles(const vector<string> &otherButtonTitles)
{
    m_otherButtonTitles = otherButtonTitles;
}

void AlertView::setTarget(Node *pTarget, SEL_AlertViewHandler selector)
{
    m_pTarget  = pTarget;
    m_selector = selector;
}

void AlertView::showAlertView()
{
    AlertView_ShowAlertView(m_title,
                            m_message,
                            m_cancelButtonTitle,
                            m_otherButtonTitles,
                            m_pTarget, m_selector);
}
