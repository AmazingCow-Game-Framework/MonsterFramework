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

//Cocoa
#import <UIKit/UIKit.h>
//MonsterFramework
#include "MonsterFramework/src/UI/private/CameraView_Functions.h"

//Usings
USING_NS_STD_CC_CD_MF

// CameraView IOS Interface/Implementation //
//Interface
@interface CameraView_UIImagePickerController: NSObject
    <UIImagePickerControllerDelegate,
     UINavigationControllerDelegate>

//
@property (nonatomic, retain) UIImagePickerController *picker;

//
@property (nonatomic) CameraView::Callback        cameraview_callback;
@property (nonatomic) CameraView::ByteArrayPtr    *cameraView_imageData;
@property (nonatomic) CameraView::ByteArrayLength *cameraView_imageDataLength;

- (void)showCamera;
@end

//Implementation
@implementation CameraView_UIImagePickerController

- (void)showCamera
{
    self.picker = [[[UIImagePickerController alloc] init] autorelease];
    self.picker.delegate = self;
    
    [self.picker setSourceType:(CameraView_CanAccessCamera()
                                ? UIImagePickerControllerSourceTypeCamera
                                : UIImagePickerControllerSourceTypePhotoLibrary)];
    
    [self performSelector:@selector(_show) withObject:nil afterDelay:0.3];
}
- (void)showCameraRoll
{
    self.picker = [[[UIImagePickerController alloc] init] autorelease];
    self.picker.delegate = self;
    
    [self.picker setSourceType:UIImagePickerControllerSourceTypePhotoLibrary];
    
    [self performSelector:@selector(_show) withObject:nil afterDelay:0.3];
    
}

- (void)_show
{
    id rvc = [[[UIApplication sharedApplication] keyWindow] rootViewController];
    [rvc presentViewController:self.picker animated:YES completion:^{}];
}

- (void)imagePickerController:(UIImagePickerController *)picker
didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    id rvc = [[[UIApplication sharedApplication] keyWindow] rootViewController];
    
        [rvc dismissViewControllerAnimated:picker completion:^(){
    
            //Get the UIImage selected by user and get the NSData representation of it.
            UIImage *image       = [info objectForKey:UIImagePickerControllerOriginalImage];
            NSData  *nsDataImage = UIImagePNGRepresentation(image);
    
            //Set the CameraView vars pointers.
            *self.cameraView_imageDataLength  = [nsDataImage length];
            *self.cameraView_imageData        = (CameraView::ByteArrayPtr)malloc(*self.cameraView_imageDataLength);
            memcpy(*self.cameraView_imageData, [nsDataImage bytes], *self.cameraView_imageDataLength);
    
            //Inform the listener that user selected the image.
            self.cameraview_callback();
    
            //Release the allocated memory.
            //This is done here because in c++ we just used alloc/init
            //we cannot use autorelease in c++ because the view will be released
            //to soon.
            [self release];
        }];
}


// CameraView Functions Implementation //
bool mf::CameraView_CanAccessCamera()
{
    return [UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera];
}
bool mf::CameraView_CanAccessCameraRoll()
{
    return [UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypePhotoLibrary];
}

void mf::CameraView_ShowCamera(const CameraView::Callback  &func,
                               CameraView::ByteArrayPtr    *pImageData,
                               CameraView::ByteArrayLength *pLength)
{
    CameraView_UIImagePickerController *controller = [[CameraView_UIImagePickerController alloc] init];
    controller.cameraview_callback        = func;
    controller.cameraView_imageData       = pImageData;
    controller.cameraView_imageDataLength = pLength;
    
    [controller showCamera];

}

void mf::CameraView_ShowCameraRoll(const CameraView::Callback  &func,
                                   CameraView::ByteArrayPtr    *pImageData,
                                   CameraView::ByteArrayLength *pLength)
{
    CameraView_UIImagePickerController *controller = [[CameraView_UIImagePickerController alloc] init];
    controller.cameraview_callback        = func;
    controller.cameraView_imageData       = pImageData;
    controller.cameraView_imageDataLength = pLength;
    
    [controller showCameraRoll];
}

@end
