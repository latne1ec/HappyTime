//
//  WFWahooRawSensorAccelerometerMeasurementSample.h
//  WFConnector
//
//  Created by Chris Uroda on 31/12/2014.
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface WFWahooRawSensorAccelerometerMeasurementSample : NSObject
{
	/** \cond InterfaceDocs */
    NSNumber* sampleIndex;
    NSNumber* sampleRate;
    NSNumber* xAxisReading;
    NSNumber* yAxisReading;
    NSNumber* zAxisReading;
    bool readingRangeIsUnknown;
    /** \endcond */
}

@property (nonatomic, retain) NSNumber* sampleIndex;

@property (nonatomic, retain) NSNumber* sampleRate;

@property (nonatomic, retain) NSNumber* xAxisReading;
@property (nonatomic, retain) NSNumber* yAxisReading;
@property (nonatomic, retain) NSNumber* zAxisReading;

@property (nonatomic, assign) bool readingRangeIsUnknown;

@end
