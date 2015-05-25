//
//  DiscoverViewController.m
//  WahooDemoV2
//
//  Created by Evan Latner on 5/23/15.
//  Copyright (c) 2015 Wahoo Fitness. All rights reserved.
//

#import "DiscoverViewController.h"
#import <WFConnector/WFConnector.h>

@interface DiscoverViewController ()  <WFDiscoveryManagerDelegate>

@property (strong, nonatomic) NSDictionary* sensorConnectionLookup;


@property (nonatomic,strong) WFDiscoveryManager* discoveryManager;
@property (nonatomic,strong) NSMutableArray* discoveredDevices;

@end

@implementation DiscoverViewController

@synthesize heartRateLabel;


- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.

    
    

}



-(void)viewWillAppear:(BOOL)animated {
    
    [self startDiscovery];
}

- (void) viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    
    // Cancel the discovery
    [self cancelDiscovery];
}


- (NSArray*) sensorTypes
{
    // Return nil for wildcard discovery
    return nil;
    
    // Or and array of sensor types you would like to find
    // return @[@(WF_SENSORTYPE_BIKE_POWER),@(WF_SENSORTYPE_HEARTRATE)];
}

- (void) startDiscovery
{
    NSLog(@"startDiscovery");
    
    // Remove any old devices we had cached
    if(self.discoveredDevices.count || !self.discoveredDevices) {
        self.discoveredDevices = [NSMutableArray new];
    }
    
    // Setup the discovery manager
    if(self.discoveryManager==nil) {
        self.discoveryManager = [WFDiscoveryManager new];
        self.discoveryManager.delegate = self;
    }
    
    // Start discovery on both ANT+ and BTLE, only networks that are ready will start.
    [self.discoveryManager discoverSensorTypes:[self sensorTypes] onNetwork:WF_NETWORKTYPE_ANY];
}

- (void) cancelDiscovery
{
    NSLog(@"cancelDiscovery");
    
    [self.discoveryManager cancelDiscovery];
}

#pragma mark -
#pragma mark  WFDiscoveryManagerDelegate

- (void)discoveryManager:(WFDiscoveryManager*)discoveryManager didDiscoverDevice:(WFDeviceInformation*)deviceInformation
{
    
    NSLog(@"Got device");
    self.heartRateLabel.text = @"Found device";
    
}

- (void)discoveryManager:(WFDiscoveryManager*)discoveryManager didLooseDevice:(WFDeviceInformation*)deviceInformation
{
}






@end
