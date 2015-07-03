//
//  Private_Utils.h
//  U7_MasterKidsGames
//
//  Created by Mateus Mesquita on 6/15/15.
//
//

#ifndef U7_MasterKidsGames_Private_Utils_h
#define U7_MasterKidsGames_Private_Utils_h

// String //
//char * -> NSString
#define N2O_MF_STR_C2NS(_str_) [NSString stringWithFormat:@"%s", _str_]
//std::string -> NSString
#define N2O_MF_STR_CPP2NS(_str_) N2O_MF_STR_C2NS(_str_.c_str())
//NSString -> char *
#define N2O_MF_STR_NS2C(_str_) [_str_ UTF8String]
//NSString -> std::string
#define N2O_MF_STR_NS2CPP(_str_) std::string(N2O_MF_STR_NS2C(_str_))

// Get the App's RootViewController //
#define N2O_MF_GETAPPRVC() [[[UIApplication sharedApplication] keyWindow] rootViewController]
#endif
