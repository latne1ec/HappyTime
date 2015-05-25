//
//  WFDiscoveryManagerDelegate.h
//  WFConnector
//
//  Created by Murray Hughes on 26/11/2013.
//  Copyright (c) 2013 Wahoo Fitness. All rights reserved.
//

#import <Foundation/Foundation.h>

@class WFDiscoveryManager;
@class WFDeviceInformation;

@protocol WFDiscoveryManagerDelegate <NSObject>

- (void)discoveryManager:(WFDiscoveryManager*)discoveryManager didDiscoverDevice:(WFDeviceInformation*)deviceInformation;

- (void)discoveryManager:(WFDiscoveryManager*)discoveryManager didLooseDevice:(WFDeviceInformation*)deviceInformation;


@end
