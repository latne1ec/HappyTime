//
//  WFDeviceInformation.h
//  DiscoveryDemo
//
//  Created by Murray Hughes on 26/11/2013.
//  Copyright (c) 2013 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/hardware_connector_types.h>

@class WFConnectionParams;

/**
 * This class represents a collection of general information about a device. It is returned either during a discovery process or
 * from the WFSensorConnection::deviceInformation
 *
 * Information isn't always availible and it is populated when and if it becomes availible.
 * Some require the device to be connected before they are populated.
 */
@interface WFDeviceInformation : NSObject
{
    NSDate* _lastUpdate;
    NSUUID* UUID;
    NSString* deviceIdentifier;
    NSString* name;
    NSString* manufacturer;
    NSArray* supportedSensorTypes;
    NSString* firmwareVersion;
    NSString* hardwareVersion;
    NSString* serialNumber;
    NSString* productKey;
    double batteryLevel; // -1 or [0...1]
    double signalStrength;
    WFNetworkType_t networkType;
    BOOL connected;


    NSDate* lastlastUpdate;
    NSString* rawName;
    NSMutableArray* updateDeltas;
    BOOL dummyDevice;
}

/**
 * Unquie ID for this device, BTL devices use the UUID, ANT+ use a 128
 */
@property (nonatomic, retain, readonly) NSUUID* UUID;

/**
 * BTLE UUID or ANT+ Device ID
 */
@property (nonatomic, copy, readonly) NSString* deviceIdentifier;

/**
 * Gets the last known signal strength. range 0...1, 1 being nearly perfect
 */
@property (atomic, assign, readonly) double signalStrength;

/**
 * Gets the network type of the devie, BTLE or ANT
 */
@property (nonatomic, assign, readonly) WFNetworkType_t networkType;

/**
 * <c>TRUE</c> if the sensor is currently connected, otherwise <c>FALSE</c>.
 */
@property (nonatomic, assign, readonly) BOOL connected;

/**
 * Name of the device. This may be different to the WFDeviceInformation::rawName and is best used for UI display.
 */
@property (nonatomic, copy, readonly) NSString* name;

/**
 * Manufacturer's name if known
 */
@property (nonatomic, copy, readonly) NSString* manufacturer;

/**
 * The date when this device was last seen
 */
@property (atomic, retain, readonly) NSDate* lastUpdate;

/**
 * Array of <c>WFSensorType_t</c> wrapped in <c>NSNumbers<c/> that are supported by this device.
 *
 * @note Eg. TICKR X supports <c>WF_SENSORTYPE_HEARTRATE, WF_SENSORTYPE_FOOTPOD & WF_SENSORTYPE_BIKE_SPEED_CADENCE</c>
 */
@property (nonatomic, retain, readonly) NSArray* supportedSensorTypes;

/**
 * Gets the last known battery level. range 0...1, -1 being not known
 *
 */
@property (nonatomic, assign, readonly) double batteryLevel; // -1 or [0...1]

/**
 * Gets firmware version if known.
 *
 */
@property (nonatomic, copy, readonly) NSString* firmwareVersion;

/**
 * Gets hardware version if known.
 *
 */
@property (nonatomic, copy, readonly) NSString* hardwareVersion;

/**
 * Gets serial number if known.
 *
 */
@property (nonatomic, copy, readonly) NSString* serialNumber;

/**
 * Unque product key for known devices. This is for Wahoo Fitness products and selected 3rd parties.
 *
 * @note If you would like a device added to this list then please submit a support ticket.
 *
 */
@property (nonatomic, copy, readonly) NSString* productKey;

/**
 * Raw Bluetooth advertising name. This may be different to the WFDeviceInformation::name that is recomended for UI display.
 */
@property (nonatomic, copy, readonly) NSString* rawName;

/**
 * <c>TRUE</c> if the device supports battery level, otherwise <c>FALSE</c>.
 *
 */
- (BOOL)isBatteryLevelSupported;

/**
 * Gets an instance of <c>WFConnectionParams</c> that is configured for a given sensor type.
 * This can then be used with WFHardwareConnector::requestSensorConnection:withProximity:error: to make a connection
 */
- (WFConnectionParams*)connectionParamsForSensorType:(WFSensorType_t)sensorType;

/**
 * Returns <c>NSArray</c> of <c>WFConnectionParams</c> for each supported sensor type
 * These can then be used with WFHardwareConnector::requestSensorConnection:withProximity:error: to make a connections
 * You need 1 WFSensorConnection per sensor type.
 */
- (NSArray*)connecitonParamsForAllSupportSensorTypes;

/**
 * @see WFDeviceInformation::signalStrength
 */
@property (atomic, assign, readonly) double signalStrenth UNAVAILABLE_ATTRIBUTE;


@end


/**
 * Defined contants of known products
 * @see WFDeviceInformation::productKey
 */
extern NSString * const WFProductKeyWahooFitnessBlueHR;
extern NSString * const WFProductKeyWahooFitnessBlueSC;
extern NSString * const WFProductKeyWahooFitnessTICKR;
extern NSString * const WFProductKeyWahooFitnessTICKRRun;
extern NSString * const WFProductKeyWahooFitnessTICKRX;
extern NSString * const WFProductKeyWahooFitnessKICKR;
extern NSString * const WFProductKeyWahooFitnessRPM;
extern NSString * const WFProductKeyWahooFitnessRFLKT;
extern NSString * const WFProductKeyWahooFitnessRFLKTPlus;
extern NSString * const WFProductKeyWahooFitnessCasioSTB1000;
extern NSString * const WFProductKeyWahooFitnessBalanceScale;
extern NSString * const WFProductKeyWahooFitnessPROTKT;
extern NSString * const WFProductKeyWahooFitnessANTKey;
extern NSString * const WFProductKeyMagellanEcho;
extern NSString * const WFProductKeyMagellanEchoFit;
extern NSString * const WFProductKeyTimexM054;
extern NSString * const WFProductKeyStagesPower;
extern NSString * const WFProductKeyKineticInRide;
extern NSString * const WFProductKeyMIOGlobalAlpha;
extern NSString * const WFProductKeyPolarRUN;
extern NSString * const WFProductKeyBeetsBLU;
extern NSString * const WFProductKeyCateyeHR;
extern NSString * const WFProductKeyCateyeCSC;
extern NSString * const WFProductKeyMiCoachHRM;
extern NSString * const WFProductKeyPowerBeamProBT;
extern NSString * const WFProductKeyPowerCalBT;
extern NSString * const WFProductKeyPowerTapBT;
extern NSString * const WFProductKeyPEARHRM;
extern NSString * const WFProductKey4iiiiViiiiva;
extern NSString * const WFProductKeyScoscheSpeedCadence;
extern NSString * const WFProductKeyScoscheHRM;
extern NSString * const WFProductKeySleepRateHR;
extern NSString * const WFProductKeySmartEaseHR;
extern NSString * const WFProductKeySpreeFitnessMonitor;
extern NSString * const WFProductKeyLookPolarKeoPower;

