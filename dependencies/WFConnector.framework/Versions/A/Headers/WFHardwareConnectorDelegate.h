/*
 *  WFHardwareConnectorDelegate.h
 *  WFHardwareConnector
 *
 *  Created by Michael Moore on 2/10/10.
 *  Copyright 2010 Wahoo Fitness. All rights reserved.
 *
 */

#import <WFConnector/hardware_connector_types.h>


@class WFHardwareConnector;
@class WFSensorConnection;
@class WFDeviceInformation;


/**
 * The WFHardwareConnectorDelegate protocol declares the interface that
 * WFHardwareConnector delegates must implement.
 *
 * The WFHardwareConnectorDelegate protocol should be adopted in classes
 * where the sensor data is processed.  It is common to adopt this protocol
 * in the same class where the WFHardwareConnector instance is created, but
 * this is not necessary.  Sensor data updates and connection status events
 * will be delivered to the delegate.
 */
@protocol WFHardwareConnectorDelegate <NSObject>

@optional

/**
 * Alerts the delegate that a sensor connection has been established.
 *
 * The <i>connectionInfo</i> parameter may be used to determine the type
 * and identification of the sensor which was connected.
 *
 * See the WFHardwareConnector::requestSensorConnection: method for
 * documentation about the sensor connection process.
 *
 * @param hwConnector The WFHardwareConnector instance.
 *
 * @param connectionInfo A WFSensorConnection instance that may be used to
 * determine the sensor type and manage the connection.
 */
- (void)hardwareConnector:(WFHardwareConnector*)hwConnector connectedSensor:(WFSensorConnection*)connectionInfo;

/**
 * Alerts the delegate that a device has been discovered.
 *
 * @note See the WFHardwareConnector::discoverDevicesOfType:onNetwork:searchTimeout:
 * method for documentation about the sensor discovery process.
 *
 * @param hwConnector The WFHardwareConnector instance.
 *
 * @param connectionParams An <c>NSSet</c> instance containing zero or more
 * WFConnectionParams instances.  Each WFConnectionParams instance will contain
 * connection information for the discovered device in the
 * WFConnectionParams::device1 property.
 *
 * @param bCompleted <c>TRUE</c> if the discovery is finished, otherwise <c>FALSE</c>.
 */
- (void)hardwareConnector:(WFHardwareConnector*)hwConnector didDiscoverDevices:(NSSet*)connectionParams searchCompleted:(BOOL)bCompleted DEPRECATED_MSG_ATTRIBUTE("Please use WFDiscoveryManager");

/**
 * Alerts the delegate that a sensor connection has ended.
 *
 * The <i>connectionInfo</i> parameter may be used to determine the type
 * and identification of the sensor which was disconnected.
 *
 * See the WFHardwareConnector::requestSensorConnection: method for
 * documentation about the sensor connection process.
 *
 * @param hwConnector The WFHardwareConnector instance.
 *
 * @param connectionInfo A WFSensorConnection instance that may be used to
 * determine the sensor type.
 */
- (void)hardwareConnector:(WFHardwareConnector*)hwConnector disconnectedSensor:(WFSensorConnection*)connectionInfo;

/**
 * Alerts the delegate that the state of the hardware connector has changed.
 *
 * This method is invoked when the fisica (key or case) accessory device has
 * been physically connected to and recognized by the iPhone, or when it is
 * physically removed from the iPhone.  It will also be invoked at the
 * beginning and end of a reset operation
 * (see WFHardwareConnector::resetConnections).
 *
 * @param hwConnector The WFHardwareConnector instance.
 * @param currentState  The current state of the hardware connector.
 *
 * @note
 * For more information about the possible state values, see
 * WFHardwareConnector::currentState.
 */
- (void)hardwareConnector:(WFHardwareConnector*)hwConnector stateChanged:(WFHardwareConnectorState_t)currentState;

/**
 * Alerts the delegate that data is available.
 *
 * This method may be invoked only when new data is availabe, or on a
 * specified interval.  See the WFHardwareConnector::sampleRate and
 * WFHardwareConnector::setSampleTimerDataCheck: documentation for information
 * about how to configure the data alerts.
 */
- (void)hardwareConnectorHasData;

/**
 * Alerts the delegate that an updated version of the firmware is available.
 *
 * @note This method is only useful for select Wahoo BTLE devices (e.g. KICKR, RFLKT).  
 * For these Wahoo devices that support firmware update, this method is required. For Wahoo
 * BTLE devices which do not support firmware update, as well as BTLE devices
 * from other manufacturers and all ANT+ devices, this method will never be called.
 *
 * The recommended use of this delegate method is to alert the user that a software
 * update is available for the device, remind the user that the update requires the Wahoo Utility app,
 * and allow the user to select whether to update or not.
 *
 * If the user selects to update the firmware, open the WahooUtilityAppURL with the command:
 *     [[UIApplication sharedApplication] openURL:wahooUtilityAppURL];
 *
 * @param hwConnector The WFHardwareConnector instance.
 * @param connectionInfo The WFSensorConnection instance.
 * @param required Indicates that the device will not connect until the firmware is updated.
 * This is determined based on the API version used by the app.
 * @param wahooUtilityAppURL The URL scheme to open the Wahoo Utility app or
 * to allow the user to download the Wahoo Utility app.
 * This paramter may contain one of three values:
 * 1. the custom URL scheme to open the Wahoo Utility app if the Wahoo Utility app is
 * installed on the iOS device.
 * 2. the iTunes URL scheme to open iTunes to download the Wahoo Utility app.
 * 3. the http address to open iTunes on the web to download the Wahoo Utility app.
 */
- (void) hardwareConnector:(WFHardwareConnector*)hwConnector hasFirmwareUpdateAvailableForConnection:(WFSensorConnection*)connectionInfo required:(BOOL)required withWahooUtilityAppURL:(NSURL *)wahooUtilityAppURL;


/**
 * Alerts the delefate that checking of availible firmware with the ffirmware server is complete
 *
 * @param hwConnector The WFHardwareConnector instance.
 * @param connectionInfo The WFSensorConnection instance.
 * @prarm error if something went wrong like network connection, otherwise nil.
 */
- (void) hardwareConnector:(WFHardwareConnector*)hwConnector didCompleteCheckingAvailibleFirmwareForConnection:(WFSensorConnection*)connectionInfo error:(NSError*) error;


/**
 * Alerts the delegate that the state of the ANT Bridge has changed.
 *
 * @see WFHardwareConnector::enableAntBridge:
 * @see WFConnectorSettings::isAntBridgeAutoEnabled
 *
 * @param hwConnector The WFHardwareConnector instance.
 *
 * @param eState An enumerated value of the type WFAntBridgeState_t indicating
 * the current state of the ANT Bridge.
 *
 * @param deviceUUIDString An NSString representation of the CoreBluetooth UUID
 * of the device providing ANT Bridge support.
 */
- (void)hardwareConnector:(WFHardwareConnector*)hwConnector antBridgeStateChanged:(WFAntBridgeState_t)eState onDevice:(NSString*)deviceUUIDString;

@end