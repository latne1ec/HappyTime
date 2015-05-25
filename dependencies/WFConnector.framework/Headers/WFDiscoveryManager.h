//
//  WFDiscoveryManager.h
//  WFConnector
//
//  Created by Murray Hughes on 26/11/2013.
//  Copyright (c) 2013 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WFConnector/hardware_connector_types.h>

#import "WFDiscoveryManagerDelegate.h"

@class WFBTLEDiscovery;
@class WFANTDiscovery;


@interface WFDiscoveryManager : NSObject
{
    WFBTLEDiscovery* btleDiscoveryManager;
    WFANTDiscovery* antDiscoveryManager;
    id<WFDiscoveryManagerDelegate> delegate;
    NSMutableArray* mutableDiscoveredDevices;
}


@property (nonatomic, assign) id<WFDiscoveryManagerDelegate> delegate;


/**
 * Initiates device discovery on the specified network(s).
 *
 * @note Device discovery for the SUUNTO network is not supported at this time.
 *
 * @param sensorTypes The array of ::WFSensorType_t to discover (wraped in NSNumbers).  If this value is
 * nil, a wildcard discovery is performed.
 *
 * @param networkType The network on which to perform the discovery or a mask of multiple networks.
 *
 */
- (void)discoverSensorTypes:(NSArray*)sensorTypes onNetwork:(WFNetworkType_t)networkType;

/**
 * Cancels device discovery on the specified network.
 *
 */
- (void)cancelDiscovery;

/**
 * Devices discovered in the currnet discovery process
 *
 * @return An <c>NSArray</c> containing zero or more WFDeviceInformation instances
 * representing all devices discovered.
 */
- (NSArray*) discoveredDevices;

@end
