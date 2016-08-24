//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        ILoadResolver.h                           //
//            █ █        █ █        MonsterFramework                          //
//             ████████████                                                   //
//           █              █       Copyright (c) 2015, 2016                  //
//          █     █    █     █      AmazingCow - www.AmazingCow.com           //
//          █     █    █     █                                                //
//           █              █       N2OMatt - n2omatt@amazingcow.com          //
//             ████████████         www.amazingcow.com/n2omatt                //
//                                                                            //
//                  This software is licensed as GPLv3                        //
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
//        The email is: acknowledgment_opensource@AmazingCow.com              //
//     3. Altered source versions must be plainly marked as such,             //
//        and must not be misrepresented as being the original software.      //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//      Visit opensource.amazingcow.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//

#ifndef __MonsterFramework_include_Graphics_ILoadResolver_h__
#define __MonsterFramework_include_Graphics_ILoadResolver_h__

//std
#include <string>
//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"

NS_MF_BEGIN

class ILoadResolver
{
    // ILoadResolver Interface //
public:
    virtual void resolveVarAssignment(const std::string &name, cc::Node  *pVar)
    {
        //Empty...
    }
    virtual void resolveMenuSelector(const std::string &name, cc::MenuItem *pVar)
    {
        //Empty..
    }
    virtual cc::Node* resolveCustomClass(const std::string &name,
                                         const cc::ValueVector &customProperties)
    {
        return nullptr;
    }

    //NOTICE:
    //This are the same methods above, but formatted nicely to be pasted
    //in the header file. Just to ease the process.
//    // ILoadResolver Interface //
//public:
//    void      resolveVarAssignment(const std::string &name, cc::Node     *pVar) override;
//    void      resolveMenuSelector (const std::string &name, cc::MenuItem *pVar) override;
//    cc::Node* resolveCustomClass  (const std::string &name                    ) override;
};

NS_MF_END

////////////////////////////////////////////////////////////////////////////////
// Utility Macros                                                             //
////////////////////////////////////////////////////////////////////////////////
// Selector
#define MF_ILOADRESOLVER_RESOLVE_SELECTOR(_selector_, _name_, _pvar_, _func_, _target_) \
    if((_selector_) == (_name_)) {                                  \
        _pvar_->setCallback(CC_CALLBACK_1(_func_, _target_)); \
        return;                                                     \
    }                                                               \

#define MF_ILOADRESOLVER_RESOLVE_SELECTOR_ASSERT(_name_) \
    MF_ASSERT(                                                                 \
        false,                                                                 \
        "ILoadResolver::resolveMenuSelector - Failed to resolve selector:(%s)",\
        _name_.c_str()                                                         \
    );

//Var assignment
#define MF_ILOADRESOLVER_RESOLVE_VAR(_var_name_, _dst_var_, _type_, _name_, _pvar_) \
    if((_var_name_) == (_name_)) {               \
        _dst_var_ = static_cast<_type_ *>(_pvar_); \
        return;                                  \
    }

#define MF_ILOADRESOLVER_RESOLVE_VAR_ASSERT(_name_) \
    MF_ASSERT(                                                                 \
        false,                                                                 \
        "ILoadResolver::resolveVarAssignment - Failed to resolve var:(%s)",\
        _name_.c_str()                                                         \
    );

#endif // defined(__MonsterFramework_include_Graphics_ILoadResolver_h__) //
