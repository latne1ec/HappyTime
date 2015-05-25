//
//  WFWahooRawSensorControlEventsDelegate.h
//  WFConnector
//
//  Created by Chris Uroda 2014-12-30
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFWahooRawSensorTypes.h>



@protocol WFWahooRawSensorControlEventsDelegate <NSObject>

@optional


/**
 * The callback for the activateMeasurements: control point method.
 *
 * @param error If an error occurs, an error object containing the error information will be provided.  The error is limited to WFDeviceControlPointErrorDomain.
 */
- (void)wahooRawSensorControl:(id)sender didActivateMeasurements:(NSArray*)measurementTypes withError:(NSError*)error;

/**
 * The callback for the deactivateMeasurements: control point method.
 *
 * @param error If an error occurs, an error object containing the error information will be provided.  The error is limited to WFDeviceControlPointErrorDomain.
 */
- (void)wahooRawSensorControl:(id)sender didDeactivateMeasurements:(NSArray*)measurementTypes withError:(NSError*)error;

@end