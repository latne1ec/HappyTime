//
//  StartTripTableViewController.h
//  WahooDemoV2
//
//  Created by Evan Latner on 5/23/15.
//  Copyright (c) 2015 Wahoo Fitness. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WFConnector/WFConnector.h>


@interface StartTripTableViewController : UITableViewController

@property (nonatomic, strong) WFDeviceInformation* deviceInformation;


@end
