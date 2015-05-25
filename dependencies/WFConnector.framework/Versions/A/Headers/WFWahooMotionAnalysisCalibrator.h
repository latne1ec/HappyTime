//
//  WFWahooMotionAnalysisCalibrator.h
//  WFConnector
//
//  Created by Chris Uroda on 06/11/2014.
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//

//
//  WFWahooMotionAnalysisCalibrator.h
//  WFConnector
//
//  Created by Chris Uroda on 06/11/2014.
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFSensorConnection.h>

@protocol WFWahooMotionAnalysisCalibratorDelegate;
@class WFTimer;

typedef NS_ENUM(NSInteger, WFWahooMotionAnalysisCalibratorState_t)
{
    WF_WAHOO_MOTION_ANALYSIS_CALIBRATOR_STATE_IDLE,
    WF_WAHOO_MOTION_ANALYSIS_CALIBRATOR_STATE_WORKING,
    WF_WAHOO_MOTION_ANALYSIS_CALIBRATOR_STATE_UPLOADING,
    WF_WAHOO_MOTION_ANALYSIS_CALIBRATOR_STATE_COMPLETED,
    WF_WAHOO_MOTION_ANALYSIS_CALIBRATOR_STATE_FAILED,
};


typedef NS_ENUM(NSInteger, WFWahooMotionAnalysisCalibratorWorkingStatus_t)
{
    WF_WAHOO_MOTION_ANALYSIS_CALIBRATOR_WORKING_STATUS_NOT_AVAILABLE,
    WF_WAHOO_MOTION_ANALYSIS_CALIBRATOR_WORKING_STATUS_WAITING_FOR_DEVICE,
    WF_WAHOO_MOTION_ANALYSIS_CALIBRATOR_WORKING_STATUS_WAITING_FOR_USER_READY,
    WF_WAHOO_MOTION_ANALYSIS_CALIBRATOR_WORKING_STATUS_WAITING_FOR_USER_INPUT,
    WF_WAHOO_MOTION_ANALYSIS_CALIBRATOR_WORKING_STATUS_IN_PROGRESS,
    WF_WAHOO_MOTION_ANALYSIS_CALIBRATOR_WORKING_STATUS_PAUSED,
    WF_WAHOO_MOTION_ANALYSIS_CALIBRATOR_WORKING_STATUS_PROCESSING,
    WF_WAHOO_MOTION_ANALYSIS_CALIBRATOR_WORKING_STATUS_DEVICE_INTERRUPTION,
};


/**
 * Error domain for WFWahooMotionAnalysisCalibrator errors
 */
extern NSString* const WFWahooMotionAnalysisCalibratorErrorDomain;

typedef NS_ENUM(NSUInteger, WFWahooMotionAnalysisCalibratorError)
{
    WFWahooMotionAnalysisCalibratorErrorNone = 0,                       /**< No error has occured. */
    WFWahooMotionAnalysisCalibratorErrorOperationNotPermitted,          /**< The operation is not permitted in the current calibrator state. */
    WFWahooMotionAnalysisCalibratorErrorInvalidParameter,               /**< A supplied parameter is invalid. */
    WFWahooMotionAnalysisCalibratorErrorDeviceTimeout,                  /**< The device for calibration (sensor connection) has timed out. */
    WFWahooMotionAnalysisCalibratorErrorDeviceError,                    /**< The device responded with an unexpected error. */
    WFWahooMotionAnalysisCalibratorErrorDataSourceError,                /**< Required data source is unavailable or missing. */
    WFWahooMotionAnalysisCalibratorErrorCalibrationTimeout,             /**< The calibration has timed out. */
    WFWahooMotionAnalysisCalibratorErrorUserError,                      /**< The user did display unexpected behavior. */
    WFWahooMotionAnalysisCalibratorErrorUnableToResolveCalibration,     /**< No calibration profile could be resolved for the data */
};


/**
 * The base class for all Wahoo Motion Analysis Calibrators.  This class can't be instantiated directly, instead init one of the sub classes.
 */
@interface WFWahooMotionAnalysisCalibrator : NSObject

/**
 * The Sensor Connection which is being used to preform the calibration.
 */
@property (nonatomic, readonly) WFSensorConnection* sensorConnection;


/**
 * The current state of this calibrator instance
 */
@property (nonatomic, readonly) WFWahooMotionAnalysisCalibratorState_t state;


/**
 * The current working status of this calibrator instance.  This is only valid when the current state is WF_WAHOO_MOTION_ANALYSIS_CALIBRATOR_STATE_WORKING.
 */
@property (nonatomic, readonly) WFWahooMotionAnalysisCalibratorWorkingStatus_t workingStatus;


/**
 * The delegate which will receive event/progress update callbacks
 */
@property (nonatomic, assign) id<WFWahooMotionAnalysisCalibratorDelegate> delegate;



/**
 * The designated initialiser
 */
- (instancetype) initWithSensorConnection:(WFSensorConnection*)sensorConnection;


/**
 * Begin the calibration process
 * @return <c>false</c> if an error occurred
 */
- (bool) beginCalibration;


/**
 * Abort the calibration process
 * @return <c>false</c> if an error occurred
 */
- (void) abortCalibration;

/**
 * Continue the calibration process when paused
 * @return <c>false</c> if an error occurred
 */
- (bool) continueCalibration;

@end
