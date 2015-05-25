//
//  _WFBikePowerConnection.h
//  WFConnector
//
//  Created by Michael Moore on 12/31/12.
//  Copyright (c) 2012 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFSensorConnection.h>
#import <WFConnector/WFBikePowerDelegate.h>
#import <WFConnector/WFBikeTrainerDelegate.h>


@interface _WFBikePowerConnection : WFSensorConnection <WFBikePowerDelegate, WFBikeTrainerDelegate>

@end
