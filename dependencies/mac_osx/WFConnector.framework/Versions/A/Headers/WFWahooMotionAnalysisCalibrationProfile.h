//
//  WFWahooMotionAnalysisCalibrationProfile.h
//  WFConnector
//
//  Created by Chris Uroda on 2014-11-04
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <WFConnector/WFWahooMotionAnalysisData.h>



/**
 * The base type for all Wahoo Motion Analysis Calibration Profiles
 */
@interface WFWahooMotionAnalysisCalibrationProfile : NSObject


/**
 * The activity type of this calibration profile.
 */
@property (nonatomic, readonly) WFWahooMotionAnalysisActivityType_t activityType;


/**
 * Load a previously saved calibration profile
 */
+ (instancetype) calibrationProfileFromSavedData:(NSData*)saveData;

/**
 * Use this method to save a calibration profile to disk or to a database etc.
 */
- (NSData*) exportSaveData;


@end
