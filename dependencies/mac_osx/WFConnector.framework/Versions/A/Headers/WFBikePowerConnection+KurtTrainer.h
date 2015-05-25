//
//  WFBikePowerConnection+KurtTrainer.h
//  WFConnector
//
//  Created by Murray Hughes on 24/01/13.
//  Copyright (c) 2013 Wahoo Fitness. All rights reserved.
//

#import "WFBikePowerConnection.h"
#include <AvailabilityMacros.h>


@interface WFBikePowerConnection (KurtTrainer)

- (BOOL)kurtSetDriveCircumference:(float)circumferenceInMeters driveRatio:(UCHAR)ucDriveRatio DEPRECATED_ATTRIBUTE;
- (BOOL)kurtSetSpindownParams:(USHORT)usReadyPeriod startPeriod:(USHORT)usStartPeriod endPeriod:(USHORT)usEndPeriod debounceThreshold:(USHORT)usDebounce DEPRECATED_ATTRIBUTE;
- (BOOL)kurtSetDragParams:(float)offsetSlope offsetYIntercept:(float)yIntercept DEPRECATED_ATTRIBUTE;
- (BOOL)kurtSetMomentOfInertia:(float)momentOfInertia DEPRECATED_ATTRIBUTE;


//
// see -                    (void)cpmConnection:(WFBikePowerConnection*)cpmConn
//          didReceiveKurtSetProFlywheelEnabled:(BOOL) proFlywheelEnabled
//                              spindownEnabled:(BOOL) spindownEnabled
//                                     response:(BOOL)bSuccess;
//
- (BOOL) kurtSetProFlyWheelEnabled:(BOOL) proFlywheel spindownEnabled:(BOOL) spindownEnabled;

@end
