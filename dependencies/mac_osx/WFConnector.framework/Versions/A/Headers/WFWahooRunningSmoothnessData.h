//
//  WFWahooRunningSmoothnessData.h
//  WFConnector
//
//  Created by Mark Snaterse on 2014-12-09.
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef MAC_OSX_BUILD
#import <UIKit/UIKit.h>
#endif

/*
 Smoothness scale limits (inclusive)
 */
#define WF_RUNNING_SMOOTHNESS_MIN_VALUE 50
#define WF_RUNNING_SMOOTHNESS_MAX_VALUE 150


@interface WFWahooRunningSmoothnessData : NSObject

@property (nonatomic, retain) NSNumber *runningSmoothness;   /**< A measure of overall running smoothness, between 50-150 (inclusive). Running smoothness is determined relative to other runners so is a dimensionless value.*/



#ifndef MAC_OSX_BUILD

/**
 * @param  Running smoothness value
 * @return A color representation for the smoothness value
 */
+(UIColor *)colorForSmoothness:(double)smoothness;

#else

/**
 * @param  A pointer for red value output for representation of the smoothness value
 * @param  A pointer for green value output for representation of the smoothness value
 * @param  A pointer for blue value output for representation of the smoothness value
 * @param  Running smoothness value
 */
+ (void)colorRed:(double*)redOut green:(double*)greenOut blue:(double*)blueOut forSmoothness:(double)smoothness;

#endif


@end
