//
//  WFFootpodConnection.h
//  WFConnector
//
//  Created by Michael Moore on 11/10/10.
//  Copyright 2010 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFSensorConnection.h>
#import <WFConnector/WFTreadmillDelegate.h>

@class WFFootpodData;
@class WFFootpodRawData;


/**
 * Represents a connection to an ANT+ Stride sensor.
 */
@interface WFFootpodConnection : WFSensorConnection <WFTreadmillDelegate>
{
    id<WFTreadmillDelegate> treadmillDelegate;
}


/**
 * Specifies the WFTreadmillDelegate instance which will handle treadmill callback
 * methods for this WFFootpodConnection.
 */
@property (nonatomic, retain) id<WFTreadmillDelegate> treadmillDelegate;


/**
 * Returns the latest data available from the sensor.
 *
 * @see WFSensorConnection::getData
 *
 * @return A WFFootpodData instance containing data if available,
 * otherwise <c>nil</c>.
 */
- (WFFootpodData*)getFootpodData;

/**
 * Returns the latest raw (unformatted) data available from the sensor.
 *
 * @see WFSensorConnection::getRawData
 *
 * @return A WFFootpodRawData instance containing data if available,
 * otherwise <c>nil</c>.
 */
- (WFFootpodRawData*)getFootpodRawData;

/**
 * Sends a request to set the treadmill mode.
 *
 * @note This command is only valid for Wahoo Gym Equipment Treadmill devices,
 * all others will return <c>FALSE</c>.
 *
 * @param eMode The WFTreadmillMode_t to be set.
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)treadmillSetMode:(WFTreadmillMode_t)eMode;
/**
 * Sends a request to read the current treadmill mode.
 *
 * @note This command is only valid for Wahoo Gym Equipment Treadmill devices,
 * all others will return <c>FALSE</c>.
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)treadmillReadMode;
/**
 * Sends a request to set the treadmill incline.
 *
 * @note This command is only valid for Wahoo Gym Equipment Treadmill devices,
 * all others will return <c>FALSE</c>.
 *
 * @param fpDegrees The incline to be set, in degrees.
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)treadmillSetIncline:(float)fpDegrees;
/**
 * Sends a request to read the current treadmill incline.
 *
 * @note This command is only valid for Wahoo Gym Equipment Treadmill devices,
 * all others will return <c>FALSE</c>.
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)treadmillReadIncline;
/**
 * Sends a request to set the treadmill workout time.
 *
 * @note This command is only valid for Wahoo Gym Equipment Treadmill devices,
 * all others will return <c>FALSE</c>.
 *
 * @param time The workout time to be set, in seconds.
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)treadmillSetWorkoutTime:(NSTimeInterval)time;
/**
 * Sends a request to read the current treadmill workout time.
 *
 * @note This command is only valid for Wahoo Gym Equipment Treadmill devices,
 * all others will return <c>FALSE</c>.
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)treadmillReadWorkoutTime;
/**
 * Sends a request to set the treadmill workout type.
 *
 * @note This command is only valid for Wahoo Gym Equipment Treadmill devices,
 * all others will return <c>FALSE</c>.
 *
 * @param eType The WFTreadmillWorkoutType_t to be set.
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)treadmillSetWorkoutType:(WFTreadmillWorkoutType_t)eType;
/**
 * Sends a request to read the current treadmill workout type.
 *
 * @note This command is only valid for Wahoo Gym Equipment Treadmill devices,
 * all others will return <c>FALSE</c>.
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)treadmillReadWorkoutType;

@end
