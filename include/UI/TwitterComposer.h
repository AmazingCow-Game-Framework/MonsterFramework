//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    TwitterComposer.h                           //
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

#ifndef __MonsterFramework_include_UI_TwitterComposer_h__
#define __MonsterFramework_include_UI_TwitterComposer_h__

//std
#include <string>
#include <vector>
//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"

NS_MF_BEGIN

class TwitterComposer
{
    // Inner Types //
public:
    //Type that holds the information about the image
    //that will be included in tweet.
    //name is the filename of the image **without** the extension.
    //ext  is the extension of the image **without** the leading dot.
    //Example:
    //  name = "Pingo";     ext = "png";  <- RIGHT
    //  name = "Pingo.png"; ext = "png";  <- WRONG (Name with extension)
    //  name = "Pingo";     ext = ".png"; <- WRONG (Extension with dot)
    struct ImageInfo
    {
        std::string name;
        std::string ext;
    };

    // Static Methods //
public:
    static bool canSendTweet();

    // Enums/Constants/Typedefs //
public:
    typedef std::function<void (bool)> Callback;

    // CTOR/DTOR //
public:
    TwitterComposer();
    TwitterComposer(const std::string &text,
                    const Callback &callback);

    // Public Methods //
public:
    //Text/Image/URL
    void setText (const std::string &text);
    void addImage(const ImageInfo &info);
    void addURL  (const std::string &url);

    //Callback
    void setCallback(const Callback &callback);

    //Show
    void showTwitterComposer();

    // iVars //
private:
    std::string              m_text;
    std::vector<ImageInfo>   m_images;
    std::vector<std::string> m_urls;

    Callback m_callback;
};

NS_MF_END
#endif // defined(__MonsterFramework_include_UI_TwitterComposer_h__) //
