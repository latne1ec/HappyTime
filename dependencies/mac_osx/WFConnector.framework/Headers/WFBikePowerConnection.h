//
//  WFBikePowerConnection.h
//  WFConnector
//
//  Created by Michael Moore on 11/9/10.
//  Copyright 2010 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/_WFBikePowerConnection.h>


@class WFBikePowerData;
@class WFBikePowerRawData;
@class WFANTBikePowerData;
@class WFBTLEBikePowerData;


/**
 * Represents a connection to an ANT+ Bike Power sensor.
 */
@interface WFBikePowerConnection : _WFBikePowerConnection
{
}


/**
 * Specifies the WFBikePowerDelegate instance which will handle callback
 * methods for this WFBikePowerConnection.
 */
@property (nonatomic, retain) id<WFBikePowerDelegate> cpmDelegate;

/**
 * Specifies the WFBikeTrainerDelegate instance which will handle trainer callback
 * methods for this WFBikePowerConnection.
 */
@property (nonatomic, retain) id<WFBikeTrainerDelegate> btDelegate;

/**
 * Gets or sets a boolean value indicating whether the WFBikePowerConnection
 * should automatically calibrate when calibration data is received from the
 * device.
 *
 * @note The default value is <c>TRUE</c>.
 */
@property (nonatomic, assign) BOOL autoCalibrate;


/**
 * Returns the latest data available from the sensor.
 *
 * @note As of 2.3.0 all the old properties for WFBikePowerData have been deprecated
 * in order to replaced them with new properties that apply to both ANT+ and BTLE
 * sensors. The old properties will remain to work with ANT+ sensors but will not
 * return any data when using a BTLE power sensor. It is recomend that you move
 * to the new properties.
 *
 * @return A WFBikePowerData instance containing data if available,
 * otherwise <c>nil</c>.
 */
- (WFBikePowerData*)getBikePowerData;

/**
 * Returns the latest raw (unformatted) data available from the sensor.
 *
 * @see WFSensorConnection::getRawData
 *
 * @return A WFBikePowerRawData instance containing data if available,
 * otherwise <c>nil</c>.
 */
- (WFBikePowerRawData*)getBikePowerRawData;

/**
 * Sends a calibration message to the Bike Power sensor with the calibration
 * data specified in the ::WFBikePowerCalibrationData_t structure.
 *
 * @param pstData A ::WFBikePowerCalibrationData_t structure containing the
 * calibration information to be sent to the sensor.
 *
 * @return <c>TRUE</c> if the calibration message was sent successfully,
 * otherwise <c>FALSE</c>.
 */
- (BOOL)setBikePowerCalibration:(WFBikePowerCalibrationData_t*)pstData;

/**
 * Sets the calibration offset value for the power meter sensor.
 *
 * The calibration offset value for power sensors is not persisted by the
 * Wahoo Fitness API.  The application should store any offset value returned
 * after a calibration is performed.  This value should be used to set the
 * calibration offset used for power calculations.  Use this method after
 * the power sensor has been connected to set the offset.
 *
 * @note When the sensor is connected or reset, the calibration offset is
 * reset.  This method should be invoked after the sensor is connected, and
 * after a reset operation (see WFHardwareConnector::resetAllSensorData).
 *
 * @param usOffset The calibration offset value.
 *
 * @return <c>TRUE</c> if the calibration offset was set, otherwise <c>FALSE</c>.
 */
- (BOOL)setBikePowerCalibrationOffset:(USHORT)usOffset;

/**
 * Sends the manual zero command to the BTLE bike power sensor.
 *
 * @note This method is only available for Wahoo Fitness BTLE bike
 * power devices.  For other types, this method will return <c>FALSE</c>, and
 * will have no effect.
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)setManualZeroCalibration;


/**
 * Puts the trainer in Erg Mode.
 *
 * Erg Mode attempts to maintain a constant power output regardless
 * of rider speed. If a new target power is desired, trainerSetErgMode must be
 * called again with new targer power.
 * 
 * @param usWatts The target power (in Watts).
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)trainerSetErgMode:(USHORT)usWatts;



/**
 * Puts the trainer in Resistance Mode.
 *
 * Resistance Mode will directly control the strength of the brake and will stay
 * constant regardless of the rider's speed. This mode is similar to a spin bike where
 * the user can increase or decrease the difficulty of their workout.
 *
 * @param fpScale a float from 0.0 to 1.0 that represents the percentage the brake is turned
 * on (0.0 = brake turned off;  0.256 = 25.6% of brake;  1.0 = 100% brake force).
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)trainerSetResistanceMode:(float)fpScale;

/**
 * Puts the trainer in Standard Mode.
 *
 * Standard Mode will mimic a normal fluid trainer's resistance curve. As the rider
 * increases their speed the resistance will get progressively higher. When the trainer is not
 * connected to a device that can control it, the trainer will default to this mode on level 2.
 *
 * @param eLevel A ::WFBikeTrainerLevel_t type that specifies the intensity of the power curve
 * while in standard mode. The range is 0 to 9 where progression at 0 is easiest and 9 is most difficult.
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)trainerSetStandardMode:(WFBikeTrainerLevel_t) eLevel;

/**
 * Puts the trainer in Sim Mode.
 *
 * Sim Mode is used to simulate real world riding situations. This mode will adjust the
 * brake resistance based on the effects of gravity, rolling resistance, and wind resistance. In order
 * to creat an accurate simulation of real world conditions the following variables must be set:
 * rider & bike weight, coefficient of rolling resistance, coefficient of wind resistance, wind speed, wheel circumference,
 * and grade. If these variables are not set, they will default to an "average" value.
 *
 * @note IMPORTANT: the following parameters are set when this function is called; however, the remaining
 * parameters can only be set after the trainer is put in Sim Mode.
 *
 * @param fWeight represents the weight of the combined rider and bicycle in kilograms. The default value for fWeight is 85.0kg.
 * This parameter can not be adjusted without calling trainerSetSimMode again.
 *
 * @param fCrr is the coefficient of rolling resistance (unitless). Can be reset later by calling
 * trainerSetRollingResistance. Default value is 0.004.
 *
 * @param fC is equal to A*Cw*Rho where A is effective frontal area (m^2); Cw is drag coefficent (unitless); and Rho is the air density (kg/m^3).
 * The default value for A*Cw*Rho is 0.60.
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)trainerSetSimMode:(float)fWeight rollingResistance:(float)fCrr windResistance:(float)fC;

/**
 * Sets the coefficient of rolling resistance (Crr) in Sim Mode.
 *
 * @note Trainer must be in Sim Mode before setting Crr.  Crr is unitless. Crr will default to 0.004 when Sim Mode is initialized. 
 * This approximates a road bike tire on an asphalt road. The reason for changing Crr would be to simulate a change in road conditions during a ride.
 * Other factors that affect Crr are tire pressure, tire width, and tire material.
 *
 * Here are some approximate values of Crr for a road bike with common road conditions:
 * <br /><br />
 * <table>
 * <tr><td>Condition</td><td>Value</td></tr>
 * <tr><td>Wooden Track</td><td>0.001</td></tr>
 * <tr><td>Smooth Concrete</td><td>0.002</td></tr>
 * <tr><td>Asphalt Road</td><td>0.004</td></tr>
 * <tr><td>Rough but Paved Road</td><td>0.008</td></tr>
 * </table>
 * 
 * @param fCrr is the coefficient of rolling resistance (unitless).
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)trainerSetRollingResistance:(double)fCrr;

/**
 * Sets the drag coefficient, effective frontal area, and air density as one variable in Sim Mode.
 *
 * @note Trainer must be in Sim Mode before setting C.  C = A*Cw*Rho where A is effective frontal area (m^2);
 * Cw is drag coefficent (unitless); and Rho is the air density (kg/m^3). C will default to 0.60 when Sim Mode is initialized.
 *
 * @param fC is the drag coefficient.
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)trainerSetWindResistance:(float)fC;

/**
 * Sets the hill grade in Sim Mode.
 *
 * @note Trainer must be in Sim Mode before Setting Grade. Grade will default to zero.
 *
 * @param fGrade is the slope of the hill (slope = rise / run).  Should be from -1.0 : 1.0, 
 * where -1.0 is a 45 degree downhill slope, 0.0 is flat ground, and 1.0 is a 45 degree uphil slope.
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)trainerSetGrade:(float)fGrade;

/**
 * Sets the wind speed in Sim Mode
 *
 * @note Trainer must be in Sim Mode before Setting Wind Speed. Wind Speed will default to zero.
 *
 * @param mpsWindSpeed is the headwind in meters per second. A negative headwind represents a tailwind. The range for mspWindSpeed
 * is -30.0:30.0.
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)trainerSetWindSpeed:(float)mpsWindSpeed;

/**
 * Sets the rear wheel circumference.
 *
 * Rear wheel circumference defaults to 2096.0mm. This value is typical of a 700x23c road
 * bike tire.
 *
 * @param mmCircumference is the circumference of the rear wheel in mm. Accurate to 0.1mm.
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)trainerSetWheelCircumference:(float)mmCircumference;

/**
 * Sends request to determine current trainer mode.
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)trainerReadMode;

/**
 * Sends request to establish a connection to an ANT sensor.
 *
 * @param eSensorType The type of ANT sensor to be connected.
 * @param usDeviceId The ANT Device ID of the sensor to be connected (MAY NOT BE WILDCARD).
 * @param bUseForPower If <c>TRUE</c> and the eSensorType is a power meter, the power values
 * will be obtained from the ANT sensor rather than internally in the KICKR.  If <c>FALSE</c>,
 * ant the eSensorType is a power meter, the power meter will be used for cadence values only.
 * This parameter has no effect if the sensor type is not a power meter.
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)trainerRequestAntConnection:(WFSensorType_t)eSensorType deviceId:(USHORT)usDeviceId useForPower:(BOOL)bUseForPower;

/**
 * Initiates the trainer for a spinddown test.
 *
 * When this function is called successfully, the trainer is set to Resistance Mode at 0.0% brake.
 * A spinddown test is used to calibrate the trainer and determine power loss due to friction.
 * A spinddown requires the rider to pedal to speeds above 22 mph and let the bike cost down to less
 * than 13 mph.
 *
 * @return <c>TRUE</c> if the command was sent successfully, otherwise <c>FALSE</c>.
 */
- (BOOL)trainerInitSpindown;


@end
