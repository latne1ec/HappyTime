//
//  WFWahooMotionAnalysisCalibratorDelegate.h
//  WFConnector
//
//  Created by Chris Uroda on 06/11/2014.
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//


#import "WFWahooMotionAnalysisCalibrator.h"

@protocol WFWahooMotionAnalysisCalibratorDelegate <NSObject>

@optional

- (void) wahooMotionAnalysisCalibrator:(WFWahooMotionAnalysisCalibrator*)calibrator didChangeState:(WFWahooMotionAnalysisCalibratorState_t)state;

- (void) wahooMotionAnalysisCalibrator:(WFWahooMotionAnalysisCalibrator*)calibrator didChangeWorkingStatus:(WFWahooMotionAnalysisCalibratorWorkingStatus_t)workingStatus;

- (void) wahooMotionAnalysisCalibrator:(WFWahooMotionAnalysisCalibrator*)calibrator didBeginCalibrationProcessWithError:(NSError*)error;

- (void) wahooMotionAnalysisCalibrator:(WFWahooMotionAnalysisCalibrator*)calibrator didFailCalibrationProcessWithError:(NSError*)error;

- (void) wahooMotionAnalysisCalibrator:(WFWahooMotionAnalysisCalibrator *)calibrator didPauseCalibrationProcessWithDescription:(NSString *)description;

- (void) wahooMotionAnalysisCalibrator:(WFWahooMotionAnalysisCalibrator *)calibrator didContinueCalibrationProcessWithError:(NSError *)error;

- (void) wahooMotionAnalysisCalibrator:(WFWahooMotionAnalysisCalibrator*)calibrator didCompleteCalibrationProcessWithNewCalibrationProfile:(WFWahooMotionAnalysisCalibrationProfile*)newCalibrationProfile;

- (void) wahooMotionAnalysisCalibrator:(WFWahooMotionAnalysisCalibrator*)calibrator didCompleteUploadingWithError:(NSError *)error;

- (void) wahooMotionAnalysisCalibrator:(WFWahooMotionAnalysisCalibrator*)calibrator didProgressToElapsedTime:(NSTimeInterval)elapsedTime ofTotalTime:(NSTimeInterval)totalTime;

@end
