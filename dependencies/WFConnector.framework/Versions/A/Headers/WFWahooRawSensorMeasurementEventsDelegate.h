//
//  WFWahooRawSensorMeasurementEventsDelegate.h
//  WFConnector
//
//  Created by Chris Uroda 2014-12-30
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <wfConnector/WFWahooRawSensorAccelerometerMeasurementSample.h>



@protocol WFWahooRawSensorMeasurementEventsDelegate <NSObject>

@optional

- (void)wahooRawSensorMeasurement:(id)sender didDetectAccelerometerMeasurementSampleRateChange:(NSNumber*)sampleRateHz error:(NSError*)error;
- (void)wahooRawSensorMeasurement:(id)sender didReceiveAccelerometerMeasurement:(WFWahooRawSensorAccelerometerMeasurementSample*)sample error:(NSError*)error;

@end