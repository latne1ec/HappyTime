//
//  WFDisplayMemoryCalculator.h
//  WFConnector
//
//  Created by Murray Hughes on 13/04/13.
//  Copyright (c) 2013 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "hardware_connector_types.h"

@class WFDisplayConfiguration, WFDisplayPage;

@interface WFDisplayMemoryCalculator : NSObject

// Returns the memory calculator for the latest version for a given sensor subtype
+ (WFDisplayMemoryCalculator*) displayMemoryCalculatorForSensorSubType:(WFSensorSubType_t) subtype;

// Returns memory calculator for a device UUID (correct at the last connection), nil if UUID not found
+ (WFDisplayMemoryCalculator*) displayMemoryCalculatorForDeviceWithUUID:(NSString*) uuidString;

// Returns the total RAM usage for the display configuration: 0.0 -> 1.0
- (double) ramUsageForDisplayConfiguration:(WFDisplayConfiguration*) config;

// Returns the total RAM usage for a single page in the display configuration: 0.0 -> 1.0
- (double) ramUsageForDisplayPage:(WFDisplayPage*) page;

// Returns the total Flash usage for the display configuration: 0.0 -> 1.0
- (double) flashUsageForDisplayConfiguration:(WFDisplayConfiguration*) config;

// Returns the total Flash usage for a single page: 0.0 -> 1.0
- (double) flashUsageForDisplayPage:(WFDisplayPage*) page;

@end


