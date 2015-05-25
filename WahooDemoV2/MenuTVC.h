//
//  ViewController.h
//  WahooDemoV2
//
//  Created by Murray Hughes on 3/12/2014.
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import "ProgressHUD.h"


@interface MenuTVC : UITableViewController <CLLocationManagerDelegate>

@property (strong, nonatomic) IBOutlet UILabel *latLabel;
@property (strong, nonatomic) IBOutlet UILabel *longLabel;
@property (strong, nonatomic) IBOutlet UILabel *addressLabel;

- (IBAction)getLocation:(id)sender;

@property (weak, nonatomic) IBOutlet UIButton *syncButton;

@property (weak, nonatomic) IBOutlet UIButton *myTripsButton;


@end

