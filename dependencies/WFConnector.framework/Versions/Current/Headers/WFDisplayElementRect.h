//
//  WFDisplayElementRect.h
//  WFConnector
//
//  Created by Murray Hughes on 16/12/12.
//  Copyright (c) 2012 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "WFDisplayElement.h"


@interface WFDisplayElementRect : WFDisplayElement
{
    wf_display_color_e _color;
    wf_display_color_e _fillColor;
}

// outline color
@property (nonatomic, assign) wf_display_color_e color;

// rect fill color
@property (nonatomic, assign) wf_display_color_e fillColor;

@end