//
//  WFDisplayPageView.h
//  WFConnector
//
//  Created by Murray Hughes on 30/07/13.
//  Copyright (c) 2013 Wahoo Fitness. All rights reserved.
//

#ifdef MAC_OSX_BUILD
#import <AppKit/AppKit.h>
#define WFView NSView
#define WFImage NSImage
#define WFRect NSRect
#else
#import <UIKit/UIKit.h>
#define WFView UIView
#define WFImage UIImage
#define WFRect CGRect
#endif

#import <WFConnector/hardware_connector_types.h>

@class WFDisplayPage;
@protocol WFDisplayPageRenderProtocol;


@interface WFDisplayPageView : WFView
{
    id<WFDisplayPageRenderProtocol> _displayPageRender;
    WFDisplayPage* _page;
    WFSensorSubType_t _sensorSubType;
    BOOL _invert;
    double _pixelAlpha;


    UIImageView* _imageView;
    UIColor* _defaultBackgroundColor;
    UIColor* _backgroundColor;
}

@property (nonatomic, retain) WFDisplayPage* page;
@property (nonatomic, assign) WFSensorSubType_t sensorSubType;

@property (nonatomic, assign) BOOL invert;

// Alpha applied to on pixels only
@property (nonatomic, assign) double pixelAlpha;

+ (WFImage*) imageWithPage:(WFDisplayPage*) page forSensorSubType:(WFSensorSubType_t) sensorSubType inverted:(BOOL) inverted;

@end
