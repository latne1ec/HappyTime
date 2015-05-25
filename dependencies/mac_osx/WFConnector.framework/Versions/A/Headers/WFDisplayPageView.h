//
//  WFDisplayPageView.h
//  WFConnector
//
//  Created by Murray Hughes on 30/07/13.
//  Copyright (c) 2013 Wahoo Fitness. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <WFConnector/hardware_connector_types.h>


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

@class WFDisplayPage;
@protocol WFDisplayPageRenderProtocol;


@interface WFDisplayPageView : NSView
{
    id<WFDisplayPageRenderProtocol> _displayPageRender;
    WFDisplayPage* _page;
    WFSensorSubType_t _sensorSubType;
    BOOL _invert;
    double _pixelAlpha;
    
    
    NSImageView* _imageView;
    NSColor* _defaultBackgroundColor;
    NSColor* _backgroundColor;
}


@property (nonatomic, retain) WFDisplayPage* page;
@property (nonatomic, assign) WFSensorSubType_t sensorSubType;
@property (nonatomic, retain) NSColor* backgroundColor;

@property (nonatomic, assign) BOOL invert;

// Alpha applied to on pixels only
@property (nonatomic, assign) double pixelAlpha;

@end
