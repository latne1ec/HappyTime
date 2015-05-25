//
//  WFWahooMotionAnalysisData.h
//  WFConnector
//
//  Created by Chris Uroda on 2014-11-04.
//  Copyright 2014 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFSensorData.h>
#import <WFConnector/WFWahooRunningSmoothnessData.h>


/**
 * Motion Analysis Activity Type Enumeration
 */
typedef NS_ENUM(NSInteger, WFWahooMotionAnalysisActivityType_t) {
    WF_WAHOO_MOTION_ANALYSIS_ACTIVITY_TYPE_NONE                     = 0,
    WF_WAHOO_MOTION_ANALYSIS_ACTIVITY_TYPE_RUNNING_UNFILTERED       = 1,
    WF_WAHOO_MOTION_ANALYSIS_ACTIVITY_TYPE_INDOOR_CYCLING           = 2,
    WF_WAHOO_MOTION_ANALYSIS_ACTIVITY_TYPE_CYCLING                  = 3,
    WF_WAHOO_MOTION_ANALYSIS_ACTIVITY_TYPE_SWIMMING                 = 4,
    WF_WAHOO_MOTION_ANALYSIS_ACTIVITY_TYPE_X_COUNTING               = 5,
    WF_WAHOO_MOTION_ANALYSIS_ACTIVITY_TYPE_RUNNING                  = 6,
};


/**
 * Motion Analysis Indoor Cycling Rider Position Enumeration
 */
typedef NS_ENUM(NSInteger, WFWahooMotionAnalysisIndoorCyclingRiderPosition_t) {
    WF_WAHOO_MOTION_ANALYSIS_INDOOR_CYCLING_RIDER_POSITION_NOT_AVAILABLE    = 0,
    WF_WAHOO_MOTION_ANALYSIS_INDOOR_CYCLING_RIDER_POSITION_UNKNOWN          = 1,
    WF_WAHOO_MOTION_ANALYSIS_INDOOR_CYCLING_RIDER_POSITION_SITTING          = 2,
    WF_WAHOO_MOTION_ANALYSIS_INDOOR_CYCLING_RIDER_POSITION_STANDING         = 3,
};


/**
 * Motion Analysis Running is Running Status Enumeration
 */
typedef NS_ENUM(NSInteger, WFWahooMotionAnalysisRunningIsRunningStatus_t) {
    WF_WAHOO_MOTION_ANALYSIS_RUNNING_IS_RUNNING_STATUS_NOT_AVAILABLE        = 0,
    WF_WAHOO_MOTION_ANALYSIS_RUNNING_IS_RUNNING_STATUS_NOT_RUNNING          = 1,
    WF_WAHOO_MOTION_ANALYSIS_RUNNING_IS_RUNNING_STATUS_RUNNING              = 2,
};


/**
 * Motion Analysis Device Orientation Enumeration
 */
typedef NS_ENUM(NSInteger, WFWahooMotionAnalysisDeviceOrientation_t) {
    WF_WAHOO_MOTION_ANALYSIS_DEVICE_ORIENTATION_NOT_AVAILABLE   = 0,
    WF_WAHOO_MOTION_ANALYSIS_DEVICE_ORIENTATION_TOP_UP          = 1,
    WF_WAHOO_MOTION_ANALYSIS_DEVICE_ORIENTATION_TOP_DOWN        = 2,
    WF_WAHOO_MOTION_ANALYSIS_DEVICE_ORIENTATION_RIGHT_UP        = 3,
    WF_WAHOO_MOTION_ANALYSIS_DEVICE_ORIENTATION_RIGHT_DOWN      = 4,
    WF_WAHOO_MOTION_ANALYSIS_DEVICE_ORIENTATION_FACE_UP         = 5,
    WF_WAHOO_MOTION_ANALYSIS_DEVICE_ORIENTATION_FACE_DOWN       = 6,
};


/**
 * Represents the data available from a Wahoo Fitness device which supports
 * Motion Analysis
 */
@interface WFWahooMotionAnalysisData : WFSensorData


// +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
#pragma mark - Generic Fields
// +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
/**@name Generic Fields */
/**@{*/
@property (nonatomic, assign) WFWahooMotionAnalysisActivityType_t activityType; /**< The current activity type of the device.<BR>This dictates what fields will be valid/set in this instance of the object. */
@property (nonatomic, assign) NSTimeInterval motionTimestamp;                   /**< Time interval since the first instant of 1 January 2001, GMT (Based on NSDate timeIntervalSinceReferenceDate). */
@property (nonatomic, assign) uint32_t motionCount;                             /**< Cumulative motion count (eg. step count, crank rev count etc.) */
@property (nonatomic, assign) double cadenceRPM;                                /**< Instantaneous Cadence (motion's per minute). */
/**@}*/


// +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
#pragma mark - Specific Fields for activityType = Running
// +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
/**@name Specific Fields for activityType = WF_WAHOO_MOTION_ANALYSIS_ACTIVITY_TYPE_RUNNING and WF_WAHOO_MOTION_ANALYSIS_ACTIVITY_TYPE_RUNNING_UNFILTERED */
/**@{*/

@property (nonatomic, retain) NSNumber* runningSquaredJerkX;    /**< A measure of the current jerk in the x direction of the device.  The value is squared on the device.  Units are A measure of the current jerk in the x direction of the device.<BR>The value is squared, take the square root to obtain the original value.<BR>Units are m<sup>2</sup>/s<sup>5</sup>. */
@property (nonatomic, retain) NSNumber* runningSquaredJerkY;    /**< A measure of the current jerk in the x direction of the device.  The value is squared on the device.  Units are A measure of the current jerk in the x direction of the device.<BR>The value is squared, take the square root to obtain the original value.<BR>Units are m<sup>2</sup>/s<sup>5</sup>. */
@property (nonatomic, retain) NSNumber* runningSquaredJerkZ;    /**< A measure of the current jerk in the x direction of the device.  The value is squared on the device.  Units are A measure of the current jerk in the x direction of the device.<BR>The value is squared, take the square root to obtain the original value.<BR>Units are m<sup>2</sup>/s<sup>5</sup>. */
@property (nonatomic, retain) WFWahooRunningSmoothnessData* runningSmoothnessData;  /**< Current running smoothness. <BR><b>Running smoothness is only available when the WFHeartrateConnectionTICKRXSpeedProvider delegate is set, and the delegate returns valid speed data.</b> */
@property (nonatomic, retain) NSNumber* runningGroundContactTimeSeconds;    /**< Current Ground Contact Time. Units are seconds.  */
@property (nonatomic, retain) NSNumber* runningVerticalOscillationMetres;   /**< Current Vertical Oscillation. Units are metres.  */
@property (nonatomic, assign) WFWahooMotionAnalysisRunningIsRunningStatus_t runningIsRunningStatus;     /**< Current isRunning status.  */
/**@}*/


// +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
#pragma mark - Specific Fields for activityType = IndoorCycling
// +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
/**@name Specific Fields for activityType = WF_WAHOO_MOTION_ANALYSIS_ACTIVITY_TYPE_INDOOR_CYCLING */
/**@{*/
@property (nonatomic, retain) NSNumber* indoorCyclingTrunkAngleDegrees;             /**< Current trunk (torso) angle in degrees.  Range is 0 to 359.<BR>0 degrees = Face down (trunk parallel to ground)<BR>90 degrees = Upright (feet to ground)<BR>180 degrees = Face up (trunk parallel to ground)<BR>270 degrees = Head to ground, feet to sky.  */
@property (nonatomic, assign) WFWahooMotionAnalysisIndoorCyclingRiderPosition_t indoorCyclingRiderPosition;     /**< Current rider position.  */
@property (nonatomic, retain) NSNumber* indoorCyclingCumulativeSittingTime;         /**< Cumulative Sitting time, in seconds.  */
@property (nonatomic, retain) NSNumber* indoorCyclingCumulativeStandingTime;        /**< Cumulative Standing time, in seconds.  */
/**@}*/

// +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
#pragma mark - Specific Fields for activityType = XCounting
// +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
/**@name Specific Fields for activityType = WF_WAHOO_MOTION_ANALYSIS_ACTIVITY_TYPE_X_COUNTING */
/**@{*/
@property (nonatomic, retain) NSNumber* xCountingCumulativeMovingTime;                  /**< Cumulative time elapsed of the user/device moving (not being still), in seconds.  */
@property (nonatomic, retain) NSNumber* xCountingCumulativeCorrectPositionHeldTime;     /**< Cumulative time elapsed of the user/device being (still) in the "correct position", in seconds.  */
@property (nonatomic, retain) NSNumber* xCountingCumulativeIncorrectPositionHeldTime;   /**< Cumulative time elapsed of the user/device being (still) in a position other than the "correct, in seconds.  */
@property (nonatomic, assign) WFWahooMotionAnalysisDeviceOrientation_t xCountingCurrentDeviceOrientation;   /**< Current orientation of the device.  */
/**@}*/

// +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
#pragma mark - Methods
// +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
- (NSTimeInterval) timeSinceMotion;     /**< Returns time in seconds that have elapsed since the last known motion event.  */
- (NSString*) formattedCadence;         /**< Returns the cadenceRPM in string form, formatted to two decimal places.  No units etc. are included in the string.  */

@end
