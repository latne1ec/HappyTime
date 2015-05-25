//
//  WFDisplayElementString.h
//  WFConnector
//
//  Created by Murray Hughes on 16/12/12.
//  Copyright (c) 2012 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "WFDisplayElement.h"
#import "WFDisplayTypes.h"

@interface WFDisplayElementString : WFDisplayElement
{
    wf_display_font_e _font;
    wf_display_alignment_e _align;
    NSString* _value;
    BOOL _bold;
    wf_display_color_e _color;
    BOOL _constant;
    NSInteger _maxLength;
    wf_display_element_location_e _location;
}


// font type
@property (nonatomic, assign) wf_display_font_e font;

// text alignment in frame
@property (nonatomic, assign) wf_display_alignment_e align;

// default/inital value
@property (atomic, copy) NSString* value;

// bold text
@property (nonatomic, assign, getter = isBold) BOOL bold;

// text color
@property (nonatomic, assign) wf_display_color_e color;

// signals if the text is contant and cannot be changed
@property (nonatomic, assign, getter = isConstant) BOOL constant;

@property (nonatomic, assign) NSInteger maxLength;


@property (nonatomic, assign) wf_display_element_location_e location;

@end
