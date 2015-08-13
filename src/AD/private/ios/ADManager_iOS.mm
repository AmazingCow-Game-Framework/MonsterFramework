//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    ADManager_iOS.mm                            //
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

//Prevent this file being included on non Apple devices.
#ifdef MONSTERFRAMEWORK_IOS
//std
#include <string>
//Cocoa
#import <UIKit/UIKit.h>
//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"
#include "MonsterFramework/src/Utils/private/Private_Utils.h"
#include "MonsterFramework/src/AD/private/ADManager_Functions.h"
//Usings
USING_NS_STD_CC_CD_MF

//Prevent the inclusion if the project aren't use the ADMOB stuff.
#ifdef MONSTERFRAMEWORK_USE_MODULE_ADMOB
#import <GoogleMobileAds/GoogleMobileAds.h>

// ADManager iOS Interface/Implementation //
// Interface //
@interface ADManager_iOS : NSObject
    <GADInterstitialDelegate>
{
    NSMutableDictionary *_banners;
    NSMutableDictionary *_interstitials;
}
//Singleton
+ (ADManager_iOS *)instance;

//Umbrella methods.
- (BOOL)showAd  :(const ADManager::AdOptions &)options;
- (BOOL)hideAd  :(const ADManager::AdOptions &)options;
- (BOOL)addAd   :(const ADManager::AdOptions &)options;
- (BOOL)removeAd:(const ADManager::AdOptions &)options;

//Show/Hide banner.
- (BOOL)showBannerAd:(const ADManager::AdOptions &)options;
- (BOOL)hideBannerAd:(const ADManager::AdOptions &)options;
//Show/Hide Interstitial.
- (BOOL)showInterstitialAd:(const ADManager::AdOptions &)options;
//Add/Remove banner.
- (BOOL)addBannerAd   :(const ADManager::AdOptions &)options;
- (BOOL)removeBannerAd:(const ADManager::AdOptions &)options;
//Add/Remove banner.
- (BOOL)addInterstitialAd   :(const ADManager::AdOptions &)options;
- (BOOL)removeInterstitialAd:(const ADManager::AdOptions &)options;
@end

// Implementation //
@implementation ADManager_iOS
//Singleton
+ (ADManager_iOS *)instance
{
    static ADManager_iOS *s_instance = nil;
    if(!s_instance)
        s_instance = [[ADManager_iOS alloc] init];
    return s_instance;
}
//Init
- (instancetype)init
{
    if(self = [super init])
    {
        _banners       = [[NSMutableDictionary alloc] init];
        _interstitials = [[NSMutableDictionary alloc] init];
    }
    return self;
}

//Umbrella methods.
- (BOOL)showAd:(const ADManager::AdOptions &)options
{
    if(options.Type == ADManager::AdOptions::AdType::Banner)
        return [self showBannerAd:options];
    return [self showInterstitialAd:options];
}
- (BOOL)hideAd:(const ADManager::AdOptions &)options
{
    if(options.Type == ADManager::AdOptions::AdType::Banner)
        return [self hideBannerAd:options];

    MF_LOG_WARNING("ADManager_iOS - Trying to hide a InterstitialAd, it'll hide by itself");
    return NO;
}
- (BOOL)addAd:(const ADManager::AdOptions &)options
{
    if(options.Type == ADManager::AdOptions::AdType::Banner)
        return [self addBannerAd:options];
    return [self addInterstitialAd:options];
}
- (BOOL)removeAd:(const ADManager::AdOptions &)options
{
    if(options.Type == ADManager::AdOptions::AdType::Banner)
        return [self removeBannerAd:options];
    return [self removeInterstitialAd:options];
}

//Show/Hide banner.
- (BOOL)showBannerAd:(const ADManager::AdOptions &)options
{
    //Get the reference to banner and check if it's valid.
    GADBannerView *banner = _banners[MF_STR_CPP2NS(options.Key)];
    if(!banner)
    {
        MF_LOG_WARNING("ADManager_iOS - Trying to show a BannerAd that was not previously added");
        return NO;
    }

    //COWTODO: Implement banners.
    return YES;
}
- (BOOL)hideBannerAd:(const ADManager::AdOptions &)options
{
    //COWTODO: Implement banners.
    return YES;
}
//Show/Hide Interstitial.
- (BOOL)showInterstitialAd:(const ADManager::AdOptions &)options
{
    //Get the reference to banner and check if it's valid.
    GADInterstitial *interstitial = _interstitials[MF_STR_CPP2NS(options.Key)];
    if(!interstitial)
    {
        MF_LOG_WARNING("ADManager_iOS - Trying to show a InterstitialAd that was not previously added");
        return NO;
    }

    //Check if the Ad is ok to be displayed.
    if(![interstitial isReady])
    {
        MF_LOG("ADManager_iOS - InterstitialAd is not ready yet...");
        return NO;
    }

    //Get the root view controller.
    id rvc = MF_GETAPPRVC();
    [interstitial presentFromRootViewController:rvc];

    //Everything went fine.
    return YES;
}
//Add/Remove banner.
- (BOOL)addBannerAd:(const ADManager::AdOptions &)options
{
    //COWTODO: Implement banners.
    return YES;
}
- (BOOL)removeBannerAd:(const ADManager::AdOptions &)options
{
    //COWTODO: Implement banners.
    return YES;
}
//Add/Remove Interstitial.
- (BOOL)addInterstitialAd:(const ADManager::AdOptions &)options
{
    //Get the reference for the Ad and check if it's valid.
    GADInterstitial *interstitial = _interstitials[MF_STR_CPP2NS(options.Key)];
    if(interstitial)
    {
        MF_LOG_WARNING("ADManager_iOS - InterstitialAd was previously added");
        return NO;
    }

    //Create and Add it.
    interstitial = [[GADInterstitial alloc] initWithAdUnitID:MF_STR_CPP2NS(options.Key)];
    interstitial.delegate = self;

    //Load it.
    GADRequest *request = [GADRequest request];
    [interstitial loadRequest:request];

    [_interstitials setObject:interstitial forKey:MF_STR_CPP2NS(options.Key)];
    return YES;
}
- (BOOL)removeInterstitialAd:(const ADManager::AdOptions &)options
{
    //Get the reference for the Ad and check if it's valid.
    GADInterstitial *interstitial = _interstitials[MF_STR_CPP2NS(options.Key)];
    if(!interstitial)
    {
        MF_LOG_WARNING("ADManager_iOS - InterstitialAd was not previously added");
        return NO;
    }

    //Remove it.
    [_interstitials removeObjectForKey:MF_STR_CPP2NS(options.Key)];

    return YES;
}

//GADInterstitial Delegate
- (void)interstitialDidDismissScreen:(GADInterstitial *)ad
{
    NSString *key = [[_interstitials allKeysForObject:ad] lastObject];
    if(!key) return;

    //Create the same options as the original.
    auto options = ADManager::AdOptions{
        .Key  = MF_STR_NS2CPP(key),
        .Type = ADManager::AdOptions::AdType::Interstitial
    };

    //As InterstitialAd as one-time use objects, we remove it
    //next add it again. Will be different object with the same options.
    [self removeInterstitialAd:options];
    [self addInterstitialAd:options];
}

@end


// ADManager Functions Implementation //
bool mf::ADManager_ShowAd(const ADManager::AdOptions &options)
{
    return [[ADManager_iOS instance] showAd:options];
}
bool mf::ADManager_HideAd(const ADManager::AdOptions &options)
{
    return [[ADManager_iOS instance] hideAd:options];
}

bool mf::ADManager_AddAd(const ADManager::AdOptions &options)
{
    return [[ADManager_iOS instance] addAd:options];
}
bool mf::ADManager_RemoveAd(const ADManager::AdOptions &options)
{
    return [[ADManager_iOS instance] removeAd:options];
}

#else // Not using MONSTERFRAMEWORK_USE_MODULE_ADMOB //

// Implementation when project aren't using ADMOB.
bool mf::ADManager_ShowAd(const ADManager::AdOptions &options)
{
    return false;
}
bool mf::ADManager_HideAd(const ADManager::AdOptions &options)
{
     return false;
}

bool mf::ADManager_AddAd(const ADManager::AdOptions &options)
{
    return false;
}
bool mf::ADManager_RemoveAd(const ADManager::AdOptions &options)
{
    return false;
}

#endif // MONSTERFRAMEWORK_USE_MODULE_ADMOB //
#endif // MONSTERFRAMEWORK_IOS //
