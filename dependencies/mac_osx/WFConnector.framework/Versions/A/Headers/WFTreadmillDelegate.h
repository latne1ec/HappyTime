//
//  WFTreadmillDelegate.h
//  WFConnector
//
//  Created by Michael Moore on 11/9/12.
//  Copyright (c) 2012 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/hardware_connector_types.h>
#import <WFConnector/wf_gym_equipment_types.h>

@class WFFootpodConnection;


@protocol WFTreadmillDelegate <NSObject>

@optional

// NEED_DOCS:
- (void)fpConnection:(WFFootpodConnection*)fpConn didReceiveCommandResponse:(WFTreadmillResponseToCommand_t)eCommand status:(WFTreadmillStatus_t)eStatus;
- (void)fpConnection:(WFFootpodConnection*)fpConn didReceiveReadModeResponse:(WFTreadmillMode_t)eMode status:(WFTreadmillStatus_t)eStatus;
- (void)fpConnection:(WFFootpodConnection*)fpConn didReceiveReadInclineResponse:(float)fpIncline status:(WFTreadmillStatus_t)eStatus;
- (void)fpConnection:(WFFootpodConnection*)fpConn didReceiveReadWorkoutTimeResponse:(NSTimeInterval)workoutTime status:(WFTreadmillStatus_t)eStatus;
- (void)fpConnection:(WFFootpodConnection*)fpConn didReceiveReadWorkoutTypeResponse:(WFTreadmillWorkoutType_t)eWorkoutType status:(WFTreadmillStatus_t)eStatus;

@end
