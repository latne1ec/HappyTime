//
//  TripTableCell.h
//  WahooDemoV2
//
//  Created by Evan Latner on 5/23/15.
//  Copyright (c) 2015 Wahoo Fitness. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WFConnector/WFConnector.h>


@interface TripTableCell : UITableViewCell

@property (nonatomic, strong) WFDeviceInformation* deviceInformation;
@property (nonatomic, strong) NSArray* sensorConnections;

@end
