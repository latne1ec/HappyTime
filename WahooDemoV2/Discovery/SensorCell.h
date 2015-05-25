//
//  SensorCell.h
//  WahooDemoV2
//
//  Created by Murray Hughes on 3/12/2014.
//  Copyright (c) 2014 Wahoo Fitness. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WFConnector/WFConnector.h>

@interface SensorCell : UITableViewCell

@property (nonatomic, strong) WFDeviceInformation* deviceInformation;
@property (nonatomic, strong) NSArray* sensorConnections;

@property (weak, nonatomic) IBOutlet UIButton *startTripButton;


@end
