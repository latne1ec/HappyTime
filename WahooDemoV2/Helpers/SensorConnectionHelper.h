//
//  SensorConnectionHelper.h
//  WahooDemoV2
//
//  Created by Murray Hughes on 3/12/2014.
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFConnector.h>

@interface SensorConnectionHelper : NSObject

+ (WFSensorConnectionStatus_t) combindedSensorStatusFromConnections:(NSArray*) connections;

@end
