//
//  WFWahooMotionAnalysisCalibrationProfileXCounting.h
//  WFConnector
//
//  Created by Chris Uroda on 2014-11-04
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <WFConnector/WFWahooMotionAnalysisCalibrationProfile.h>



typedef NS_ENUM(NSInteger, WFXCountingExerciseType_t)
{
    WF_X_COUNTING_EXERCISE_TYPE_NONE                            = 0,
    WF_X_COUNTING_EXERCISE_TYPE_POSITION                        = 1,
    WF_X_COUNTING_EXERCISE_TYPE_REPETITIVE_MOTION               = 2,
    WF_X_COUNTING_EXERCISE_TYPE_POSITION_AND_REPETITIVE_MOTION  = 3,
};


typedef NS_ENUM(NSInteger, WFXCountingExercise_t) {
    // Repetitive motions
    WF_X_COUNTING_EXERCISE_ABDOMINAL_CRUNCHES       = 0,
    WF_X_COUNTING_EXERCISE_CHAIR_STEP_UPS           = 1,
    WF_X_COUNTING_EXERCISE_RUNNING_IN_PLACE         = 2,
    WF_X_COUNTING_EXERCISE_LUNGES                   = 3,
    WF_X_COUNTING_EXERCISE_PUSH_UPS                 = 4,
    WF_X_COUNTING_EXERCISE_PUSH_UPS_WITH_ROTATION   = 5,
    WF_X_COUNTING_EXERCISE_SQUATS                   = 6,
    WF_X_COUNTING_EXERCISE_TRICEPS_DIPS             = 7,
    WF_X_COUNTING_EXERCISE_JUMPING_JACKS            = 8,
    
    WF_X_COUNTING_EXERCISE_MOUNTAIN_CLIMBERS        = 9,
    WF_X_COUNTING_EXERCISE_BOX_SQUAT                = 10,
    WF_X_COUNTING_EXERCISE_WALL_PUSH_UPS            = 11,
    WF_X_COUNTING_EXERCISE_BENT_LEG_RAISES          = 12,
    WF_X_COUNTING_EXERCISE_PLIE_SQUATS              = 14,
    WF_X_COUNTING_EXERCISE_DIAMOND_PUSH_UPS         = 15,
    WF_X_COUNTING_EXERCISE_BEAR_CRAWL               = 16,
    WF_X_COUNTING_EXERCISE_SKIPPING                 = 17,
    WF_X_COUNTING_EXERCISE_ONE_LEG_DEADLIFTS        = 18,
    WF_X_COUNTING_EXERCISE_WIDE_PUSH_UPS            = 19,
    
    
    // Positions
    WF_X_COUNTING_EXERCISE_PLANK                    = 1000,
    WF_X_COUNTING_EXERCISE_SIDE_PLANK               = 1001,
    WF_X_COUNTING_EXERCISE_WALL_SIT                 = 1002,
    WF_X_COUNTING_EXERCISE_BIRD_DOG                 = 1003,
};



@interface WFWahooMotionAnalysisCalibrationProfileXCounting : WFWahooMotionAnalysisCalibrationProfile



// exercise type
@property (nonatomic, readonly) WFXCountingExerciseType_t exerciseType;


//
/**
 * Default calibration profile instance for existing exercise
 * @param exercise
 * @return <c>nil</c> if exercise is not supported
 */
- (instancetype)initWithDefaultsForExercise:(WFXCountingExercise_t)exercise;


@end
