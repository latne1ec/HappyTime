//
//  WFBikePower2Data.h
//  WFConnector
//
//  Created by Murray Hughes on 15/08/12.
//  Copyright (c) 2012 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/WFSensorData.h>
#include <AvailabilityMacros.h>
#import <WFConnector/WFBikePowerData_Deprecated.h>
#import <WFConnector/wf_btle_types.h>

/**
 * Represents the most commonly used data available from the Bike Power sensor.
 *
 * The WFBikePowerData combines the most commonly used of this data into a single 
 * entity.  The data represents the latest of each data type sent from the sensor.
 *
 * @note As of 2.3.0 all the old properties for WFBikePowerData have been deprecated
 * in order to replaced them with new properties that apply to both ANT+ and BTLE
 * sensors. The old properties will remain to work with ANT+ sensors but will not
 * return any data when using a BTLE power sensor. It is recomend that you move
 * to the new properties.
 */
@interface WFBikePowerData : WFBikePowerData_Deprecated
{
    WFBikePowerType_t sensorType;
    WFBTLESensorLocation_t sensorLocation;
    
    SSHORT instantPower;
    USHORT instantCadence;
	USHORT instantWheelRPM;
    
    double accumulatedTorque;
    double accumulatedPower;
    ULONG accumulatedEventCount;
    NSTimeInterval accumulatedTime;
	NSTimeInterval accumulatedTimestamp;
	BOOL accumulatedTimestampOverflow;
    
    BOOL cadenceSupported;
    BOOL crankRevolutionSupported;
	double crankRevolutions;
	NSTimeInterval crankTime;
	NSTimeInterval crankTimestamp;
	BOOL crankTimestampOverflow;
    
    BOOL wheelRevolutionSupported;
	double wheelRevolutions;
	NSTimeInterval wheelTime;
	NSTimeInterval wheelTimestamp;
	BOOL wheelTimestampOverflow;
    
    float leftTorqueEffectiveness;
    float rightTorqueEffectiveness;
    float leftPedalSmoothness;
    float rightPedalSmoothness;
    
    NSTimeInterval lastWheelDataTime;
    NSTimeInterval lastCadenceDataTime;
}


// -----------------------------------------------------------------------------
// -- Popular Data
// -----------------------------------------------------------------------------

/**
 * Indicates the type of the power meter.
 *
 * @note After the sensor connects, or is reset, it may take several
 * messages from the device before the sensor type can be determined.
 *
 */
@property (nonatomic, assign) WFBikePowerType_t sensorType;


/**
 * Indicates the location of a power meter
 *
 * @note This is only supported on Bluetooth power meters
 *
 */
@property (nonatomic, assign) WFBTLESensorLocation_t sensorLocation;




/**
 * The instantaneous power
 */
@property (nonatomic, assign) SSHORT instantPower;  

/**
 * The instantaneous cadence (crank RPM), based on the last two sensor measurements.
 */
@property (nonatomic, assign) USHORT instantCadence;

/**
 * The instantaneous wheel RPM, based on the last two sensor measurements.
 */
@property (nonatomic, assign) USHORT instantWheelRPM;


/**
 * The total accumulated torque in Nm.
 *
 * Accumulated torque is the sum of the average torque for each event.
 * For example, in wheel-based power sensors, it is the sum of the average
 * torque for each wheel revolution.
 *
 * If the sensor does not use torque, this value will be calculated from
 * instant / average power.
 *
 * @note The accumulator is initialized when the sensor is first connected, and
 * reset via the WFHardwareConnector::resetAllSensorData method.
 */
@property (nonatomic, assign) double accumulatedTorque;


/**
 * The total accumulated power in Watts
 *
 * Accumulated power is the sum of the average power for each event.
 * For example, in wheel-based power sensors, it is the sum of the average
 * power for each wheel revolution
 *
 * If availible this will be calcualted using Torque, otherwise it will be
 * calculated using Instant/Average Power
 *
 * @note The accumulator is initialized when the sensor is first connected, and
 * reset via the WFHardwareConnector::resetAllSensorData method.

 */
@property (nonatomic, assign) double accumulatedPower;

/**
 * The total number of events accumated
 * 
 * For example, in wheel-based power sensor, it is the total number
 * of wheel revolutions.
 *
 * @note The accumulator is initialized when the sensor is first connected, and
 * reset via the WFHardwareConnector::resetAllSensorData method.
 */
@property (nonatomic, assign) ULONG accumulatedEventCount;

/**
 * The real-time timestamp for the accumulated data
 *
 * @note The accumulator is initialized when the sensor is first connected, and
 * reset via the WFHardwareConnector::resetAllSensorData method.
 */
@property (nonatomic, assign) NSTimeInterval accumulatedTime;

/**
 * The real-time timestamp for accumulated data from the sensor (as an offset
 * from the Cocoa reference date).
 *
 * Time values from the sensors are implemented as an offset in seconds
 * between the time when the sensor is turned on and the time when a
 * data sample is taken.  This value is typically a 16-bit unsigned
 * integer in units of 1/1024 second.  The rollover is then 64 seconds.
 *
 * A base real-time value is stored when the first sample from the
 * sensor is received.  The timestamp of each subsequent sample is the
 * base time value offset by the time value offset from the sensor.
 * If the time between samples is greater than the rollover time, the
 * base time value is set to the time the first sample after the delay
 * is received.
 */
@property (nonatomic, assign) NSTimeInterval accumulatedTimestamp;

/**
 * Indicates that the time between samples from the sensor has
 * exceeded the rollover time (64 seconds).
 */
@property (nonatomic, assign) BOOL accumulatedTimestampOverflow;


// -----------------------------------------------------------------------------
// -- Crank Revs
// -----------------------------------------------------------------------------

/**
 * <c>TRUE</c> if the sensor provides cadence data, otherwise <c>FALSE</c>.
 */
@property (nonatomic, assign) BOOL cadenceSupported;

/**
 * Returns <c>TRUE</c> if the connected sensor supports Crank Revolutions (Cadence)
 */
@property (nonatomic, assign, getter = isCrankRevolutionSupported) BOOL crankRevolutionSupported;

/**
 * The accumulated crank revolutions since the sensor was connected or reset.
 */
@property (nonatomic, assign) double crankRevolutions;


/**
 * The real-time timestamp for the crankRevolutions data
 *
 * @note The timestamp is initialized when the sensor is first connected, and
 * reset via the WFHardwareConnector::resetAllSensorData method.
 */
@property (nonatomic, assign) NSTimeInterval crankTime;

/**
 * The real-time timestamp for crank data from the sensor (as an offset
 * from the Cocoa reference date).
 *
 * Time values from the sensors are implemented as an offset in seconds
 * between the time when the sensor is turned on and the time when a
 * data sample is taken.  This value is typically a 16-bit unsigned
 * integer in units of 1/1024 second.  The rollover is then 64 seconds.
 *
 * A base real-time value is stored when the first sample from the
 * sensor is received.  The timestamp of each subsequent sample is the
 * base time value offset by the time value offset from the sensor.
 * If the time between samples is greater than the rollover time, the
 * base time value is set to the time the first sample after the delay
 * is received.
 */
@property (nonatomic, assign) NSTimeInterval crankTimestamp;
/**
 * Indicates that the time between cadence data samples from the sensor has
 * exceeded the rollover time (64 seconds).
 */
@property (nonatomic, assign) BOOL crankTimestampOverflow;
/**
 * The accumulated wheel revolutions since the sensor was connected or reset.
 */


// -----------------------------------------------------------------------------
// -- Wheel Revs
// -----------------------------------------------------------------------------

/**
 * Returns <c>TRUE</c> if the connected sensor supports Wheel Revolutions (Speed/Distance)
 */
@property (nonatomic, assign, getter = isWheelRevolutionSupported) BOOL wheelRevolutionSupported;

/**
 * The accumulated wheel revolutions since the sensor was connected or reset.
 */
@property (nonatomic, assign) double wheelRevolutions;

/**
 * The real-time timestamp for the wheelRevolutions data
 *
 * @note The timestamp is initialized when the sensor is first connected, and
 * reset via the WFHardwareConnector::resetAllSensorData method.
 */
@property (nonatomic, assign) NSTimeInterval wheelTime;

/**
 * The real-time timestamp for speed data from the sensor (as an offset
 * from the Cocoa reference date).
 *
 * Time values from the sensors are implemented as an offset in seconds
 * between the time when the sensor is turned on and the time when a
 * data sample is taken.  This value is typically a 16-bit unsigned
 * integer in units of 1/1024 second.  The rollover is then 64 seconds.
 *
 * A base real-time value is stored when the first sample from the
 * sensor is received.  The timestamp of each subsequent sample is the
 * base time value offset by the time value offset from the sensor.
 * If the time between samples is greater than the rollover time, the
 * base time value is set to the time the first sample after the delay
 * is received.
 */
@property (nonatomic, assign) NSTimeInterval wheelTimestamp;
/**
 * Indicates that the time between speed data samples from the sensor has
 * exceeded the rollover time (64 seconds).
 */
@property (nonatomic, assign) BOOL wheelTimestampOverflow;


// -----------------------------------------------------------------------------
// -- Torque Effectiveness and Pedal Smoothness
// -----------------------------------------------------------------------------

/**
 * Gets the left leg torque effectiveness as a percent, when available.
 *
 * @note When this value is not available, the value is <c>-1</c>.
 */
@property (nonatomic, assign) float leftTorqueEffectiveness;
/**
 * Gets the right leg torque effectiveness as a percent, when available.
 *
 * @note When this value is not available, the value is <c>-1</c>.
 */
@property (nonatomic, assign) float rightTorqueEffectiveness;
/**
 * Gets the left pedal or combined pedal smoothness as a percent, when available.
 *
 * @note When this value is not available, the value is <c>-1</c>.
 */
@property (nonatomic, assign) float leftPedalSmoothness;
/**
 * Gets the right pedal smoothness as a percent, when available.
 *
 * @note When this value is not available, the value is <c>-1</c>.
 */
@property (nonatomic, assign) float rightPedalSmoothness;

// -----------------------------------------------------------------------------
// -- Interface
// -----------------------------------------------------------------------------


/** \cond InterfaceDocs */
/**
 * Initializes a new WFSensorData instance with the specified timestamps.
 *
 * @note This method is for internal use.
 *
 * @param dataTime The data timestamp.
 * @param wheelTime The speed data timestamp.
 * @param cadenceTime The cadence data timestamp.
 *
 * @return The new WFSensorData instance.
 */
- (id)initWithTime:(NSTimeInterval)dataTime wheelTime:(NSTimeInterval)wheelTime cadenceTime:(NSTimeInterval)cadenceTime;
/** \endcond */


// -----------------------------------------------------------------------------
// -- Formatted Values
// -----------------------------------------------------------------------------

/**
 * Returns the power meter is coasting. In most cases it just uses the 
 * bikeCoastingTimeout in the settings, but for some event based power meters 
 * it will dynamicly adjust the timeout based on the current cadence.
 *
 * @see WFConnectorSettings
 *
 * @return TRUE is the power meter is considered coasting, FALSE otherwise
 */
- (BOOL) isCoasting;


/**
 * Returns the cadence as a string formatted for display.
 *
 * @see WFConnectorSettings
 *
 * @param showUnits If <c>TRUE</c> the units will be included in the string
 * returned.  Otherwise, the units are not included.
 *
 * @return The formatted display string (cadence in RPMs).
 */
- (NSString*)formattedCadence:(BOOL)showUnits;

/**
 * Returns the distance as a string formatted for display.
 *
 * @see WFConnectorSettings
 *
 * @param showUnits If <c>TRUE</c> the units will be included in the string
 * returned.  Otherwise, the units are not included.
 *
 * @return The formatted display string (distance in km or miles).
 */
- (NSString*)formattedDistance:(BOOL)showUnits;

/**
 * Returns the speed as a string formatted for display.
 *
 * @see WFConnectorSettings
 *
 * @param showUnits If <c>TRUE</c> the units will be included in the string
 * returned.  Otherwise, the units are not included.
 *
 * @return The formatted display string (speed in km/h or MPH).
 */
- (NSString*)formattedSpeed:(BOOL)showUnits;

/**
 * Returns the power as a string formatted for display.
 *
 * @see WFConnectorSettings
 *
 * @param showUnits If <c>TRUE</c> the units will be included in the string
 * returned.  Otherwise, the units are not included.
 *
 * @return The formatted display string (power in watts).
 */
- (NSString*)formattedPower:(BOOL)showUnits;


@end
