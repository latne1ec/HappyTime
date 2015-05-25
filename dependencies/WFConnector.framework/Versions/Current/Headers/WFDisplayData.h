//
//  WFBTLEDisplayData.h
//  WFConnector
//
//  Created by Murray Hughes on 13/09/12.
//  Copyright (c) 2012 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WFSensorData.h"

@class WFBTLECommonData;

@interface WFDisplayData : WFSensorData
{
    NSInteger _visablePageIndex;
    WFBTLECommonData* btleCommonData;
    
    BOOL pressureSupported;
    BOOL temperatureSupported;
    double currentPressure;
    double standardPressure;
    double temperature;
    double elevation;  //metres
}

/** Gets the metadata for the BTLE device. */
@property (nonatomic, retain) WFBTLECommonData* btleCommonData;

@property (nonatomic) NSInteger visablePageIndex;


/**
 * Returns <c>TRUE</c> if the connected sensor supports enviromental pressure
 */
@property (nonatomic, assign, getter = isPressureSupported) BOOL pressureSupported;


/**
 * Returns <c>TRUE</c> if the connected sensor supports enviromental temperature
 */
@property (nonatomic, assign, getter = isTemperatureSupported) BOOL temperatureSupported;


// NEED_DOCS:
//altimeter
@property (nonatomic, assign) double currentPressure;
@property (nonatomic, assign) double standardPressure;
@property (nonatomic, assign) double temperature;
@property (nonatomic, assign) double elevation;  //metres


@end
