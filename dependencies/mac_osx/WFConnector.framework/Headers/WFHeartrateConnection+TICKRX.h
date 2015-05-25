//
//  WFHeartrateConnection+TICKRX.h
//  WFConnector
//
//  Created by Chris Uroda on 2014-11-04
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <WFConnector/WFHeartrateConnection.h>
#import <WFConnector/WFSensorData.h>
#import <WFConnector/WFWahooMotionAnalysisData.h>
#import <WFConnector/WFWahooMotionAnalysisCalibrationProfile.h>



// +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
#pragma mark - WFHeartrateConnectionTICKRXDelegate
// +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
/**
 * WFHeartrateConnectionTICKRXDelegate
 */
@protocol WFHeartrateConnectionTICKRXDelegate <NSObject>

@optional

/**@name Command response delegate callbacks */
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/**@{*/

/**
 * The callback for the getActivityType: control point method.
 *
 * @param activityType The device's current activity type setting.  If the error parameter is non-nil, this value should be ignored.
 * @param error If an error occurs, an error object containing the error information will be provided.  The error is limited to WFDeviceControlPointErrorDomain.
 */
- (void) hrTICKRXConnection:(WFHeartrateConnection*)connection didGetActivityType:(WFWahooMotionAnalysisActivityType_t)activityType error:(NSError*)error;

/**
 * The callback for the setActivityType: control point method.
 *
 * @param activityType The device's new activity type setting.  If the error parameter is non-nil, this value should be ignored, and it should be assumed that the activity type setting did not change on the device.
 * @param error If an error occurs, an error object containing the error information will be provided.  The error is limited to WFDeviceControlPointErrorDomain.
 */
- (void) hrTICKRXConnection:(WFHeartrateConnection*)connection didSetActivityType:(WFWahooMotionAnalysisActivityType_t)activityType error:(NSError*)error;

/**
 * The callback for the getActivityCalibrationForActivityType: control point method.
 *
 * @param calibration The device's current calibration profile for the specified activity type.  If the error parameter is non-nil, this value should be ignored.
 * @param error If an error occurs, an error object containing the error information will be provided.  The error is limited to WFDeviceControlPointErrorDomain.
 */
- (void) hrTICKRXConnection:(WFHeartrateConnection*)connection didGetActivityCalibration:(WFWahooMotionAnalysisCalibrationProfile*)calibration error:(NSError*)error;

/**
 * The callback for the setActivityCalibration: control point method.
 *
 * @param calibration The device's new calibration profile for the specified activity type.  If the error parameter is non-nil, this value should be ignored, and it should be assumed that no calibration profile changes took place on the device.
 * @param error If an error occurs, an error object containing the error information will be provided.  The error is limited to WFDeviceControlPointErrorDomain.
 */
- (void) hrTICKRXConnection:(WFHeartrateConnection*)connection didSetActivityCalibrationWithError:(NSError*)error;

/**@}*/


/**@name Misc event delegate callbacks */
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/**@{*/

/**
 * Occurs when a double tap event is detected on the device.
 *
 * @param reserved The reserved parameter should be ignored.
 */
- (void) hrTICKRXConnection:(WFHeartrateConnection*)connection didReceiveTapEvent:(NSUInteger)reserved;

/**
 * Occurs when the the device is ready to receive control point commands.
 */
- (void) hrTICKRXConnectionDidReceiveDeviceReady:(WFHeartrateConnection*)connection;

/**@}*/

@end




// +----------------------------------------------------------------------------+
#pragma mark -	 WFHeartRateConnectionMotionAnalysisSpeedProvider
// +----------------------------------------------------------------------------+

/**
 * Protocol to return speed data for motion analysis processing. Speed data is required 
 * in order to calculate some of the motion analysis data (for example running smoothness).
 */
@protocol  WFHeartrateConnectionTICKRXSpeedProvider <NSObject>

/**
 * @return The current running speed. <br>  Important: for best performance do not return the running speed from TICKRX
 * for motion analysis processing. This speed is dependent on running form, and changes in running form will render
 * this speed unreliable. For best performance return an independent measure of running speed, for example from GPS data,
 * a footpod, etc.
 */
- (NSNumber *)hrTICKRXConnection:(WFHeartrateConnection *)connection speedForMotionAnalysisProcessing:(bool)reserved;

@end




// +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
#pragma mark - WFHeartrateConnection+TICKRX
// +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
/**
 * WFHeartrateConnection+TICKRX
 */
@interface WFHeartrateConnection (TICKRX)


/**
 * The delegate which will receive TICKRX related callbacks
 */
@property (nonatomic, assign) id<WFHeartrateConnectionTICKRXDelegate> heartrateConnectionTICKRXDelegate;


/**
 * The delegate responsible for returning current speed used in motion analysis processing
 */
@property (nonatomic, assign) id<WFHeartrateConnectionTICKRXSpeedProvider> motionAnalysisProcessingSpeedProvider;



/**
 * A flag to indicate if the device is ready - if the device is not yet ready, commands should not be sent.
 * When the device is not yet ready, the hrTICKRXConnectionDidReceiveDeviceReady: delegate callback should be called
 * after a short period of time (this should not take longer than 5 seconds after the device connection is correctly established).
 */
@property (nonatomic, readonly) BOOL tickrxDeviceIsReady;


/**
 * Returns the latest data available from the sensor.
 *
 * @see WFSensorConnection::getData
 *
 * @return A WFWahooMotionAnalysisData instance containing data if available,
 * otherwise <c>nil</c>.
 */
- (WFWahooMotionAnalysisData*) getMotionAnalysisData;



#pragma mark - Methods related to Activity Type Management
/**@name Methods related to Activity Type Management */
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/**@{*/

/**
 * Request the current activity type from the device.  The delegate will be notified using the appropriate callback.
 * @see WFHeartrateConnectionTICKRXDelegate hrTICKRXConnection:didGetActivityType:error:
 *
 * @return <c>FALSE</c> if the command could not be sent.<br>Note: a return value of <c>TRUE</c> does not guarantee that the command completed successfully. 
 */
- (BOOL)getActivityType;


/**
 * Set the activity type (mode) of the device.  The delegate will be notified using the appropriate callback.
 * @see WFHeartrateConnectionTICKRXDelegate hrTICKRXConnection:didSetActivityType:error:
 *
 * @param activityType The desired activity type for the device.
 *
 * @return <c>FALSE</c> if the command could not be sent.<br>Note: a return value of <c>TRUE</c> does not guarantee that the command completed successfully. 
 */
- (BOOL)setActivityType:(WFWahooMotionAnalysisActivityType_t)activityType;

/**@}*/


#pragma mark - Methods related to Motion Analysis Calibration Management
/**@name Methods related to Motion Analysis Calibration Management */
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/**@{*/

/**
 * Request the current calibration profile from the device for a specific activity type.  The delegate will be notified using the appropriate callback.
 * @see WFHeartrateConnectionTICKRXDelegate hrTICKRXConnection:didGetActivityCalibration:error:
 *
 * @return <c>FALSE</c> if the command could not be sent.<br>Note: a return value of <c>TRUE</c> does not guarantee that the command completed successfully. 
 */
- (BOOL)getActivityCalibrationForActivityType:(WFWahooMotionAnalysisActivityType_t)activityType;

/**
 * Set the calibration profile on the device for a specific activity type.  The delegate will be notified using the appropriate callback.
 * @see WFHeartrateConnectionTICKRXDelegate hrTICKRXConnection:didSetActivityCalibrationWithError:
 *
 * @param calibrationProfile The desired calibration profile to upload to the device.  Note that the calibration profile itself belongs to a specific activity type.
 *
 * @return <c>FALSE</c> if the command could not be sent.<br>Note: a return value of <c>TRUE</c> does not guarantee that the command completed successfully. 
 */
- (BOOL)setActivityCalibration:(WFWahooMotionAnalysisCalibrationProfile*)calibrationProfile;

/**@}*/

@end
