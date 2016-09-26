
#ifndef __MonsterFramework_include_Utils_Macros_MonsterFramework_Disallow_h__
#define __MonsterFramework_include_Utils_Macros_MonsterFramework_Disallow_h__

////////////////////////////////////////////////////////////////////////////////
// CTOR                                                                       //
////////////////////////////////////////////////////////////////////////////////
#define MF_DISALLOW_CTOR(_type_) \
            _type_() = delete;


////////////////////////////////////////////////////////////////////////////////
// COPY / COPY ASSING                                                         //
////////////////////////////////////////////////////////////////////////////////
#define MF_DISALLOW_COPY(_type_) \
            _type_(const _type_&) = delete;

#define MF_DISALLOW_COPY_ASSIGN(_type_) \
            _type_& operator=(const _type_&) = delete;


////////////////////////////////////////////////////////////////////////////////
// MOVE / MOVE ASSIGN                                                         //
////////////////////////////////////////////////////////////////////////////////
#define MF_DISALLOW_MOVE(_type_)  \
            _type_(_type_&&) = delete;

#define MF_DISALLOW_MOVE_ASSIGN(_type_) \
            _type_& operator=(_type_&&) = delete;


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#define MF_DISALLOW_CTOR_COPY_MOVE_ASSIGNS(_type_) \
            MF_DISALLOW_CTOR(_type_)               \
            MF_DISALLOW_COPY(_type_)               \
            MF_DISALLOW_COPY_ASSIGN(_type_)        \
            MF_DISALLOW_MOVE(_type_)               \
            MF_DISALLOW_MOVE_ASSIGN(_type_)


#define MF_DISALLOW_COPY_MOVE_ASSIGNS(_type_) \
            MF_DISALLOW_COPY(_type_)          \
            MF_DISALLOW_COPY_ASSIGN(_type_)   \
            MF_DISALLOW_MOVE(_type_)          \
            MF_DISALLOW_MOVE_ASSIGN(_type_)


#endif // defined(__MonsterFramework_include_Utils_Macros_MonsterFramework_Disallow_h__)
