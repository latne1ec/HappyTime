//
//  WFWahooMotionAnalysisRunningCalibrator.h
//  WFConnector
//
//  Created by Chris Uroda on 06/11/2014.
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//

#import "WFWahooMotionAnalysisCalibrator.h"
#import "WFWahooMotionAnalysisCalibrationProfileRunning.h"

@class WFCalibrationPhase;


@interface WFWahooMotionAnalysisCalibratorRunning : WFWahooMotionAnalysisCalibrator
/**
 *
 * The <b>Regular</b> calibration process requires the user
 * to run at a single speed for two minutes (single phase).
 *
 * The <b>Extended</b> calibration requires the user to run at three
 * different speeds for two minutes each (three phases). For the best
 * result the speeds should be as distinct as possible. The resulting
 * speed estimate can be more accurate than the result from the 
 * the regular calibration process.
 */
@property (assign, nonatomic, readonly) bool extendedCalibrationEnabled;


/**
 * The number of calibration phases.  
 */
@property (assign, nonatomic, readonly) int numberOfPhases;


/**
 * The current calibration phase
 */
@property (assign, nonatomic, readonly) int currentPhase;


/**
 * The time remaining in the current calibration phase
 */
@property (assign, nonatomic, readonly) NSTimeInterval remainingTimeInPhase;


/**
 * Setter for average running speed during current calibration phase.
 * If running speed is required to continue the calibration process
 * the delegate method wahooMotionAnalysisCalibrator:doesRequireRunningSpeedToContinue:
 * is called. Respond to the delegate call using this setter to continue.
 */
@property (assign, nonatomic) NSNumber *averageRunningSpeedForCurrentPhase;



/**
 * The designated initialiser
 * @param <c>false</c> to use regular calibration, <c>true</c> to use extended calibration
 * 
 * <b>Regular calibration</b> process requires the user
 * to run at a single speed for two minutes.
 *
 * <b>Extended calibration</b> requires user to run at three
 * speeds for two minutes each. The resulting speed
 * can be more accurate than the standard calibration.
 */
- (instancetype)initWithSensorConnection:(WFSensorConnection *)sensorConnection extendedCalibration:(bool)extendedCalibration;


/**
 * Resets the current calibration phase and puts the calibration process in a paused state.
 * Call continueCalibration: to continue the calibration process.
 */
- (void)resetCurrentPhase;


@end




/**
 * Extended calibrator delegate protocol for Running
 */

@protocol WFWahooMotionAnalysisCalibratorRunningDelegate <WFWahooMotionAnalysisCalibratorDelegate>

/**
 * Invoked when running speed is required to continue the calibration process. 
 * Use the property averageRunningSpeedForCurrentPhase to (asynchronously) return the requested running speed.
 */
- (void) wahooMotionAnalysisCalibrator:(WFWahooMotionAnalysisCalibrator *)calibrator doesRequireRunningSpeedToContinue:(bool)reserved;

@end

