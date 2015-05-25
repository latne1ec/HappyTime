//
//  SensorTVC.h
//  WahooDemoV2
//
//  Created by Murray Hughes on 3/12/2014.
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WFConnector/WFConnector.h>
#import <CoreLocation/CoreLocation.h>
#import "MenuTVC.h"


@interface SensorTVC : UITableViewController <CLLocationManagerDelegate>

@property (nonatomic, strong) WFDeviceInformation* deviceInformation;

- (IBAction)endTrip:(id)sender;


@end
