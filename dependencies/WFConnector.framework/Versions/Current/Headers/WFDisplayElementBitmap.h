//
//  WFDisplayElementBitmap.h
//  WFConnector
//
//  Created by Murray Hughes on 16/12/12.
//  Copyright (c) 2012 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WFDisplayElement.h"

// -----------------------------------------------------------------

@interface WFDisplayElementBitmap : WFDisplayElement
{
    NSString* _imageBase64;
    wf_display_color_e _transparentColor;
}

// base 64 encoded string representation of the image
@property (nonatomic, copy) NSString* imageBase64;

// set the transparncy color, select one of the colors in the bitmap
// to be "transparent"
@property (nonatomic, assign) wf_display_color_e transparentColor;


@end

// -----------------------------------------------------------------

